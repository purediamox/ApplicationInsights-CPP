#if WIN32 // Win32
#include "targetver.h"
#include "specializations.h"
#include "TelemetryContext.h"
#include "TelemetryClient.h"
#include "Channel/TelemetryChannel.h"
#include "Channel/Utils/Persistence.hpp"
#include "Channel/Utils/HttpResponse.hpp"
#include "Contracts/Contracts.h"
#include <regex>
#include <stdio.h>
#include <Windows.h>


#include <thread>
#include <chrono>
using namespace ApplicationInsights::core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


typedef std::wstring wstr;
typedef std::string str;
typedef std::map<std::wstring, std::wstring> map_wstr_wstr;
typedef std::regex re;
#define re_match(input, regex) std::regex_match(input, regex)

const int ITERATIONS = 2;

namespace core {
	namespace tests
	{
		namespace basicEndToEnd
		{
			class MockTelemetryChannel : public TelemetryChannel
			{
			public:
				static MockTelemetryChannel* GetInstance()
				{
					channel = TelemetryChannel::GetInstance();
					
					PERSISTCONFIG config = Persistence::GetDefaultConfig();
					config.uploadIntervalMins = 0;

					channel->InitializePersistance(config);
					return (MockTelemetryChannel*)channel;
				}

				
			private:
				static TelemetryChannel* channel;

			};
			TelemetryChannel* MockTelemetryChannel::channel = nullptr;

			class MockTelemetryClient : public TelemetryClient
			{
			public:
				MockTelemetryClient(std::wstring& iKey) 
				{
					m_instrumentationKey = iKey;
					m_context = new TelemetryContext(iKey);
					m_context->InitContext();
					m_channel = TelemetryChannel::Initialize();
					PERSISTCONFIG config = Persistence::GetDefaultConfig();
					config.uploadIntervalMins = 0;
					if (m_channel == nullptr)
					{
						m_channel = TelemetryChannel::Initialize();
					}
					m_channel->InitializePersistance(config);
				}

				void Flush()
				{
					m_channel->Send();
				}

			};

			TEST_CLASS(TestBasicEndToEnd)
			{
			public:
				TEST_CLASS_INITIALIZE(Initialize)
				{
					WORD wVersionRequested;

					WSADATA wsaData;
					int err;

					/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
					wVersionRequested = MAKEWORD(2, 2);

					err = WSAStartup(wVersionRequested, &wsaData);
				}

				TEST_CLASS_CLEANUP(Cleanup)
				{
					WSACleanup();
				}

				
				TEST_METHOD(BasicEndToEnd)
				{
					std::wstring iKey = L"ba0f19ca-aa77-4838-ac05-dbba85d6b677";
					MockTelemetryClient tc(iKey);
					
					
					wchar_t message[100];
					for (int i = 0; i < ITERATIONS; i++)
					{
						swprintf(message, sizeof(message), L"%s %i", L"HELLO EVENT", i);
						tc.TrackEvent(message);

						swprintf(message, sizeof(message), L"%s %i", L"MY METRIC", i);
						tc.TrackMetric(message, 42.5);

						swprintf(message, sizeof(message), L"%s %i", L"PAGE VIEW", i);
						tc.TrackPageView(message);

						swprintf(message, sizeof(message), L"%s %i", L"MY SPECIAL MESSAGE", i);
						tc.TrackTrace(message);
					}
					tc.Flush();

					Sleep(2000);

					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					std::queue<HttpResponse> responses;
					channel->GetPersistance()->GetAllResponses(responses);

					if (responses.size() > 0)
					{
						Assert::AreEqual(200, responses.front().GetErrorCode());
					}
					else
					{
						Assert::IsTrue(false, L"Failed to get a response");
					}

					char strSent[256];
					sprintf_s(strSent, 256, "%d", ITERATIONS * 4);
					std::string payload = responses.front().GetPayload();
					int recv = payload.find("itemsRecieved");
					int recvBegin = recv + 15;
					int recvEnd = payload.find(",", recvBegin);
					std::string numReceived = str(&payload[recvBegin], &payload[recvEnd]);
					Assert::AreEqual(numReceived, str(strSent), L"Did not receive correct number of responses");

					int accepted = payload.find("itemsAccepted");
					int acceptedBegin = accepted + 15;
					int acceptedEnd = payload.find(",", acceptedBegin);
					std::string numAccepted = str(&payload[acceptedBegin], &payload[acceptedEnd]);
					Assert::AreEqual(numAccepted, str(strSent), L"Did not receive correct number of items accepted");
				};
			};
		}
	}
}
#endif