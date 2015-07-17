#include "../targetver.h"
#include "../specializations.h"
#include "CppUnitTest.h"
#include "channel/utils/Persistence.hpp"
#include "common/Utils.hpp"
#include <sstream>
#include <fstream>
#include <codecvt>

using namespace ApplicationInsights::core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

typedef std::wstring wstr;

namespace core {
	namespace tests
	{
		namespace persistence
		{
			TEST_CLASS(TestPersitence)
			{
			public:
				TEST_CLASS_INITIALIZE(initialize)
				{
					
				}

				TEST_METHOD_CLEANUP(cleanup)
				{
					std::wstring folder = L"ApplicationInsights";
					bool createDir = CreateDirectory(folder.c_str(), NULL);
					if (createDir || GetLastError() == ERROR_ALREADY_EXISTS)
					{
						//clean out the upload directory
						WIN32_FIND_DATA FindFileData;
						HANDLE hFind;
						wchar_t filenamePattern[1024];
						wchar_t filename[1024];

						swprintf_s(filenamePattern, 1024, L"%s\\*.txt", folder.c_str());

						hFind = FindFirstFile(filenamePattern, &FindFileData);
						if (hFind != INVALID_HANDLE_VALUE)
						{
							swprintf_s(filename, 1024, L"%s/%s", folder.c_str(), FindFileData.cFileName);
							DeleteFile(filename);

							while (FindNextFile(hFind, &FindFileData) != 0)
							{
								DeleteFile(filename);
							}
						}
					}

					Sleep(2000);	//Let the thread clean up
				}

				TEST_METHOD(InitializeWorksAsExpected)
				{
					Persistence persist;
					persist.Initialize();
					PERSISTCONFIG config = persist.GetCurrentConfig();
					PERSISTCONFIG defaultConfig = Persistence::GetDefaultConfig();

					Assert::AreEqual(config.endpointUrl, defaultConfig.endpointUrl);
					Assert::AreEqual(config.folderLocation, defaultConfig.folderLocation);
					Assert::AreEqual(config.uploadIntervalMins, defaultConfig.uploadIntervalMins);
				};
				
				TEST_METHOD(InitializeWithConfigWorksAsExpected)
				{
					Persistence persist;
					PERSISTCONFIG myConfig = { L"myfolder", 10, L"myurl" };
					persist.Initialize(&myConfig);
					PERSISTCONFIG config = persist.GetCurrentConfig();
					

					Assert::AreEqual(config.endpointUrl, myConfig.endpointUrl);
					Assert::AreEqual(config.folderLocation, myConfig.folderLocation);
					Assert::AreEqual(config.uploadIntervalMins, myConfig.uploadIntervalMins);
				};

				std::wstring readFile(std::wstring filename)
				{
					std::wifstream inFile(filename);
					inFile.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
					std::wstringstream wstringStream;
					wstringStream << inFile.rdbuf();
					return wstringStream.str();
				}

				TEST_METHOD(saveWorksAsExpected)
				{
					Persistence persist;
					std::wstring contents = L"HELLO WORLD";
					PERSISTCONFIG myConfig = { L"myfolder", 10, L"myurl" };
					persist.Initialize();
					persist.save(contents);

					WIN32_FIND_DATA FindFileData;
					HANDLE hFind;
					wchar_t filenamePattern[1024];
					wchar_t renameFilename[1024];
					wchar_t filename[1024];
					std::wstring folder = L"ApplicationInsights";
					swprintf_s(filenamePattern, 1024, L"%s\\*.txt", folder.c_str());

					hFind = FindFirstFile(filenamePattern, &FindFileData);
					if (hFind != INVALID_HANDLE_VALUE)
					{
						swprintf_s(filename, 1024, L"%s/%s", folder.c_str(), FindFileData.cFileName);

						std::wstring fileContent = readFile(filename);
					}
					else
					{
						Assert::IsTrue(false, L"Did not find any files");
					}
				};
				
				TEST_METHOD(uploadWorksWithValidPayloadAsExpected)
				{
					Persistence persist;
					EventData telemetry;
					Data data; 
					std::wstring buffer; 
					StringWriter content(&buffer);
					JsonWriter json(content);
					Envelope envelope;

					telemetry.SetName(L"HELLO WORLD");
					data.SetBaseData(telemetry);
					data.SetBaseType(telemetry.GetBaseType());

					envelope.SetData(data);
					envelope.SetIKey(L"ba0f19ca-aa77-4838-ac05-dbba85d6b677");
					envelope.SetTime(Utils::GetCurrentDateTime());
					envelope.SetName(telemetry.GetEnvelopeName());
					json.WriteObjectValue(&envelope);

					std::wstring payload = content.ToString();
					PERSISTCONFIG myConfig = Persistence::GetDefaultConfig();
					myConfig.uploadIntervalMins = 0;
					persist.Initialize(&myConfig);
					persist.save(payload);

					Sleep(2000);

					std::queue<HttpResponse> resp;
					persist.GetAllResponses(resp);
					if(resp.size() > 0)
					{
						Assert::AreEqual((int)HTTP_RESPONSE_CODE::HTTP_OK, resp.front().GetErrorCode(), L"Error code does not match");

						WIN32_FIND_DATA FindFileData;
						HANDLE hFind;
						wchar_t filenamePattern[1024];
						wchar_t renameFilename[1024];
						wchar_t filename[1024];
						std::wstring folder = L"ApplicationInsights";
						swprintf_s(filenamePattern, 1024, L"%s\\*.txt", folder.c_str());

						hFind = FindFirstFile(filenamePattern, &FindFileData);
						Assert::AreEqual(INVALID_HANDLE_VALUE, hFind, L"Expected to have deleted the file");
					}
					else
					{
						Assert::IsTrue(false, L"Failed to get a response");
					}
				};
				
				TEST_METHOD(uploadWorksWithBadPayloadAsExpected)
				{
					Persistence persist;
					
					std::wstring contents = L"HELLO WORLD";
					PERSISTCONFIG myConfig = Persistence::GetDefaultConfig();
					myConfig.uploadIntervalMins = 0;
					persist.Initialize(&myConfig);
					persist.save(contents);

					Sleep(2000);

					std::queue<HttpResponse> resp;
					persist.GetAllResponses(resp);
					if (resp.size() > 0)
					{
						Assert::AreEqual((int)HTTP_RESPONSE_CODE::HTTP_BAD_REQUEST, resp.front().GetErrorCode(), L"Error code does not match");

						WIN32_FIND_DATA FindFileData;
						HANDLE hFind;
						wchar_t filenamePattern[1024];
						wchar_t renameFilename[1024];
						wchar_t filename[1024];
						std::wstring folder = L"ApplicationInsights";
						swprintf_s(filenamePattern, 1024, L"%s\\*.txt", folder.c_str());

						hFind = FindFirstFile(filenamePattern, &FindFileData);
						Assert::AreEqual(INVALID_HANDLE_VALUE, hFind, L"Expected to have deleted the file");
					}
					else
					{
						Assert::IsTrue(false, L"Failed to get a response");
					}
				};
			};
		}
	}
}