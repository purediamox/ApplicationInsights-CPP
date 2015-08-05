#include "Persistence.hpp"
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Win32
#include "../../Common/Utils.hpp"
#include "HttpRequest.hpp"
#include <sstream>
#include <fstream>
#include <codecvt>

using namespace ApplicationInsights::core;

const PERSISTCONFIG defaultConfig = { L"ApplicationInsights", 5, L"dc.services.visualstudio.com" };

Persistence::Persistence()
{
	m_hThread = NULL;
	m_hRecvdResp = CreateEvent(NULL, false, false, NULL);
	m_hStopThread = CreateEvent(NULL, false, false, NULL);
	InitializeCriticalSectionEx(&m_cs, 0, 0);
}

Persistence::~Persistence()
{
	StopThread();
	DeleteCriticalSection(&m_cs);
}

bool Persistence::Initialize(PPERSISTCONFIG config)
{
	if (m_hThread != NULL)
	{
		StopThread();
	}

	if (config == NULL)
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
	}

	//if there are any leftover files from a previous run move them to an uploadable state
	bool createDir = CreateDirectory(m_currentConfig.folderLocation.c_str(), NULL);
	if (createDir || GetLastError() == ERROR_ALREADY_EXISTS)
	{
		WIN32_FIND_DATA FindFileData;
		HANDLE hFind;
		wchar_t filenamePattern[1024];
		wchar_t renameFilename[1024];
		wchar_t filename[1024];
		swprintf_s(filenamePattern, 1024, L"%s\\*.txt", m_currentConfig.folderLocation.c_str());

		hFind = FindFirstFile(filenamePattern, &FindFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			swprintf_s(filename, 1024, L"%s/%s", m_currentConfig.folderLocation.c_str(), FindFileData.cFileName);
			swprintf_s(renameFilename, 1024, L"%s/u-%s.txt", m_currentConfig.folderLocation.c_str(), Utils::GenerateRandomUUID().c_str());
			MoveFileEx(filename, renameFilename, MOVEFILE_WRITE_THROUGH);

			while (FindNextFile(hFind, &FindFileData) != 0)
			{
				memset(filename, 0, sizeof(filename));
				swprintf_s(filename, 1024, L"%s/%s", m_currentConfig.folderLocation.c_str(), FindFileData.cFileName);
				memset(renameFilename, 0, sizeof(renameFilename));
				swprintf_s(renameFilename, 1024, L"%s/u-%s.txt", m_currentConfig.folderLocation.c_str(), FindFileData.cFileName);
				MoveFileEx(filename, renameFilename, MOVEFILE_WRITE_THROUGH);
			}
		}

		FindClose(hFind);
	}

	m_hThread = CreateThread(NULL, 0, Persistence::UploadThreadProc, (LPVOID)this, 0, NULL);

	if (m_hThread == NULL)
	{
		Utils::WriteDebugLine(L"Failed to create persistence thread!\n");
		return false;
	}
	return true;
}

void Persistence::save(std::wstring jsonPayload)
{
	bool createDir = CreateDirectory(m_currentConfig.folderLocation.c_str(), NULL);
	if (!createDir && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		Utils::WriteDebugLine(L"Error creating directory file!\n");
		return;
	}

	wchar_t filename[256];
	swprintf_s(filename, 256, L"%s/%s.txt", m_currentConfig.folderLocation.c_str(), Utils::GenerateRandomUUID().c_str());

	errno_t err;
	FILE *saveFile;
	err = _wfopen_s(&saveFile, filename, L"w+");

	if (err != 0)
	{
		Utils::WriteDebugLine(L"Error opening file!\n");
		return;
	}

	fwprintf_s(saveFile, L"%s", jsonPayload.c_str());
	fclose(saveFile);

	wchar_t renameFilename[256];
	swprintf_s(renameFilename, 256, L"%s/u-%s.txt", m_currentConfig.folderLocation.c_str(), Utils::GenerateRandomUUID().c_str());
	MoveFileEx(filename, renameFilename, MOVEFILE_WRITE_THROUGH);
}

std::wstring readFile(std::wstring filename)
{
	std::wifstream inFile(filename);
	inFile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wstringStream;
	wstringStream << inFile.rdbuf();
	return wstringStream.str();
}

void GetUploadList(std::wstring folderLocation, std::list<std::wstring> &uploadList)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	wchar_t filename[1024];
	swprintf_s(filename, 256, L"%s\\u-*.txt", folderLocation.c_str());

	hFind = FindFirstFile(filename, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		memset(filename, 0, sizeof(filename));
		swprintf_s(filename, 1024, L"%s\\%s", folderLocation.c_str(), FindFileData.cFileName);
		uploadList.push_back(filename);

		while (FindNextFile(hFind, &FindFileData) != 0)
		{
			memset(filename, 0, sizeof(filename));
			swprintf_s(filename, 1024, L"%s\\%s", folderLocation.c_str(), FindFileData.cFileName);
			uploadList.push_back(filename);
		}
	}
	FindClose(hFind);
}

DWORD WINAPI Persistence::UploadThreadProc(LPVOID lpParam)
{
	Persistence* pThis = (Persistence*)lpParam;
	return pThis->Upload();
}

DWORD WINAPI Persistence::Upload()
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

PERSISTCONFIG Persistence::GetDefaultConfig()
{
	return defaultConfig;
}

PERSISTCONFIG Persistence::GetCurrentConfig()
{
	return m_currentConfig;
}

void Persistence::StopThread()
{
	SetEvent(m_hStopThread);  
	DWORD wait = WaitForSingleObject(m_hThread, 30000); //Wait for 10 seconds for the process to exit 

	CloseHandle(m_hThread);	
}

void Persistence::GetAllResponses(std::queue<HttpResponse> &resp)
{
	HttpResponse temp;

	for (int i = 0; i < 3; i++)
	{
		DWORD wait = WaitForSingleObject(m_hRecvdResp, 5000);
		if (wait == WAIT_OBJECT_0)
		{
			EnterCriticalSection(&m_cs);
			while (m_respQueue.size() > 0)
			{
				temp = m_respQueue.front();
				m_respQueue.pop();
				resp.push(temp);
			}
			LeaveCriticalSection(&m_cs);
			break;
		}
	}
}
#endif