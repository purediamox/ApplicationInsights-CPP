#include "Persistence.h"
#include "../../../src/core/common/utils.hpp"
#include <ppltasks.h>

using namespace ApplicationInsights::CX;
using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation; 
using namespace Windows::Storage;
using namespace Windows::Storage::Search;
using namespace Windows::System::Threading;

/// <summary>
/// Initializes a new instance of the <see cref="Persistence"/> class.
/// </summary>
Persistence::Persistence()
{
	m_hThread = NULL;
	m_hRecvdResp = CreateEvent(NULL, false, false, NULL);
	m_hStopThread = CreateEvent(NULL, false, false, NULL);
	InitializeCriticalSectionEx(&m_cs, 0, 0);
}

/// <summary>
/// Finalizes an instance of the <see cref="Persistence"/> class.
/// </summary>
Persistence::~Persistence()
{
	StopThread();
	DeleteCriticalSection(&m_cs);	
}

void Persistence::StopThread()
{
	SetEvent(m_hStopThread);
	DWORD wait = WaitForSingleObject(m_hThread, 30000); //Wait for 10 seconds for the process to exit 

	CloseHandle(m_hThread);
}

bool Persistence::Initialize()
{
	if (m_hThread != NULL)
	{
		StopThread();
	}

	/*if (config == NULL)
	{
		m_currentConfig.endpointUrl = defaultConfig.endpointUrl;
		m_currentConfig.folderLocation = defaultConfig.folderLocation;
		m_currentConfig.uploadIntervalMins = defaultConfig.uploadIntervalMins;
	}
	else
	{
		m_currentConfig.endpointUrl = config->endpointUrl;
		m_currentConfig.folderLocation = config->folderLocation;
		if (config->uploadIntervalMins < 0)
		{
			m_currentConfig.uploadIntervalMins = 0;
		}
		else
		{
			m_currentConfig.uploadIntervalMins = config->uploadIntervalMins;
		}
	}*/

	//if there are any leftover files from a previous run move them to an uploadable state
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	task<StorageFolder^> appInsightsFolder = create_task(localFolder->CreateFolderAsync("ApplicationInsights", Windows::Storage::CreationCollisionOption::OpenIfExists));
	appInsightsFolder.then([](StorageFolder^ folder)
	{
		//Get the files in the current folder
		return folder->GetFilesAsync();
	}).then([](Windows::Foundation::Collections::IVectorView<StorageFile^>^ files)
	{
		for (auto file : files)
		{
			if (*(file->Name->Begin()) != wchar_t(L"u"))
			{
				String^ uploadFileName = L"u-" + file->Name;
				file->RenameAsync(uploadFileName);
			}
		}		
	}).then([]()
	{
		IAsyncAction^ threadPoolWorkItem = ThreadPool::RunAsync(
			ref new WorkItemHandler(&Persistence::Upload));
	});
}

void Persistence::save(std::wstring jsonPayload)
{
	StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
	String^ fileName = ref new String(ApplicationInsights::core::Utils::GenerateRandomUUID().c_str()) + L".txt";
	try
	{
		task<StorageFolder^> appInsightsFolder = create_task(localFolder->CreateFolderAsync("ApplicationInsights", Windows::Storage::CreationCollisionOption::OpenIfExists));
		appInsightsFolder.then([fileName](StorageFolder^ folder)
		{
			folder->CreateFileAsync(fileName, CreationCollisionOption::ReplaceExisting);
		}).then([this, jsonPayload](StorageFile^ file)
		{
			try
			{
				FileIO::WriteTextAsync(file, ref new String(jsonPayload.c_str()));
			}
			catch (Exception^ e)
			{
				ApplicationInsights::core::Utils::WriteDebugLine(L"Error storing to file!\n");
			}
			return file;
		}).then([fileName](StorageFile^ file)
		{
			String^ uploadFileName = L"u-" + fileName;
			file->RenameAsync(uploadFileName);
		});
	}
	catch (Exception^ e)
	{
		ApplicationInsights::core::Utils::WriteDebugLine(L"Error creating file!\n");
	}
}

void Persistence::Upload(IAsyncAction^ op)
{
	while (true)
	{
		std::list<std::wstring> uploadList;
		bool createDir = CreateDirectory(m_currentConfig.folderLocation.c_str(), NULL);
		if (createDir || GetLastError() == ERROR_ALREADY_EXISTS)
		{
			GetUploadList(m_currentConfig.folderLocation, uploadList);

			for (std::list<std::wstring>::iterator iter = uploadList.begin(); iter != uploadList.end(); iter++)
			{
				std::wstring filename = *iter;
				std::wstring payload = readFile(filename);

				//upload the file
				HttpRequest request(HTTP_REQUEST_METHOD::POST, m_currentConfig.endpointUrl.c_str(), L"/v2/track", payload);
				request.GetHeaderFields().SetField(L"Content-Type", L"application/json");
				HttpResponse resp;
				if (request.Send([filename, &resp](const HttpResponse &response) {
#ifdef CPP_LIB_DEBUG
					std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
					std::wstring wstrResp = converter.from_bytes(response.GetPayload());

					std::wstring wstrOutput = L"RESPONSE :\r\n" + wstrResp;
					Utils::WriteDebugLine(wstrOutput);
#endif
					if (response.GetErrorCode() >= static_cast<int>(HTTP_RESPONSE_CODE::HTTP_OK) && response.GetErrorCode() < static_cast<int>(HTTP_RESPONSE_CODE::HTTP_REDIRECTION))
					{
						DeleteFile(filename.c_str());
					}
					else if (response.GetErrorCode() == static_cast<int>(HTTP_RESPONSE_CODE::HTTP_NETWORK_AUTH_REQUIRED) ||
						response.GetErrorCode() == static_cast<int>(HTTP_RESPONSE_CODE::HTTP_REQUEST_TIMEOUT) ||
						response.GetErrorCode() == static_cast<int>(HTTP_RESPONSE_CODE::HTTP_SERVICE_UNAVAILABLE) ||
						response.GetErrorCode() == static_cast<int>(HTTP_RESPONSE_CODE::HTTP_SVR_ERROR) ||
						response.GetErrorCode() == static_cast<int>(HTTP_RESPONSE_CODE::HTTP_TOO_MANY_REQUESTS))
					{

					}
					else
					{
						DeleteFile(filename.c_str());
					}
#ifdef _DEBUG
					resp = response;
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
					SetEvent(hRespRecv);
#endif
#endif
				}) == 0) {
					EnterCriticalSection(&m_cs);
					m_respQueue.push(resp);
					LeaveCriticalSection(&m_cs);
					SetEvent(m_hRecvdResp);
				}

				DWORD wait = WaitForSingleObject(m_hStopThread, 10);
				if (wait == WAIT_OBJECT_0)
				{
					return 1;
				}
			}
		}

		int waitTime = 0;
		if (m_currentConfig.uploadIntervalMins == 0)
		{
			waitTime = 100;
		}
		else
		{
			waitTime = 1000 * 60 * m_currentConfig.uploadIntervalMins;
		}

		DWORD foo = WaitForSingleObject(m_hStopThread, waitTime);
		if (foo == WAIT_OBJECT_0)
		{
			return 1;
		}
	}
	return 1;
}