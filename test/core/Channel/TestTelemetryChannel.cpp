#include "../targetver.h"
#include "../specializations.h"
#include "Common/Utils.h"
#include "CppUnitTest.h"
#include "Channel/TelemetryChannel.h"
#include "TelemetryClientConfig.h"
#include "TelemetryContext.h"
#include <stdio.h>
#include <regex>

#ifdef WINAPI_FAMILY_PARTITION
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
#include <memory>
#include <ppl.h>
#include <ppltasks.h>
#include <Windows.h>

using namespace concurrency;
using namespace Windows::Storage;
#endif
#endif

using namespace ApplicationInsights::core;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

typedef std::wstring wstr;
typedef std::string str;
typedef std::map<std::wstring, std::wstring> map_wstr_wstr;
typedef std::regex re;
#define re_match(input, regex) std::regex_match(input, regex)

namespace core {
	namespace tests
	{
		class MockTelemetryChannel : public TelemetryChannel
		{
		public:
			static MockTelemetryChannel* GetInstance()
			{
				return (MockTelemetryChannel*)TelemetryChannel::GetInstance();
			}

			int GetChannelId() { return m_channelId; }
			int GetSeqNum() { return m_seqNum; }
			//const TelemetryClientConfig *GetConfig() { return m_config; }
			const std::vector<std::wstring> GetBuffer() { return m_buffer; }

			void SetBufferSize(int maxSize) { m_maxBufferSize = maxSize; }

#ifdef WINAPI_FAMILY_PARTITION
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
			DWORD WaitForResponse()
			{
				DWORD dwRet = WaitForSingleObjectEx(hRespRecv, 5000, TRUE);

				if (dwRet == (DWORD)WAIT_FAILED)
				{
					LPVOID lpMsgBuf;
					DWORD error = GetLastError();
					FormatMessage(
						FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_IGNORE_INSERTS,
						nullptr,
						error,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						(LPTSTR)&lpMsgBuf,
						0, nullptr);
					int i = 0;
				}
				return dwRet;
			}
#endif
#endif
			const HttpResponse& GetResponse() const {
				return resp;
			}
		};

		TEST_CLASS(TestTelemetryChannel)
		{
		public:
			TEST_CLASS_INITIALIZE(initialize)
			{
#ifdef WINAPI_FAMILY_PARTITION // it's SOME kind of Windows
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
				ApplicationData::Current->ClearAsync();
#endif
#endif
				Sleep(5000);
			}

			TEST_METHOD_CLEANUP(cleanup)
			{
				Sleep(5000);
			}

			TEST_METHOD(InitializeWorksAsExpected)
			{
				TelemetryChannel *channel = TelemetryChannel::Initialize();

				Assert::IsNotNull(channel);
			};

			TEST_METHOD(GetInstanceWorksAsExpected)
			{
				TelemetryChannel *channel = TelemetryChannel::Initialize();
				channel = TelemetryChannel::GetInstance();

				Assert::IsNotNull(channel);
			};
			
			TEST_METHOD(EnqueueWorksAsExpected)
			{
				wstr iKey = L"foo";
				TelemetryClientConfig config(iKey);
				TelemetryContext context(iKey);
				context.InitContext();

				MockTelemetryChannel *channel = (MockTelemetryChannel*)TelemetryChannel::Initialize();
				std::vector<std::wstring> buffer;
				int channelId = channel->GetChannelId();
				for (int i = 0; i < 5; i++)
				{
					MessageData telemetry;
					telemetry.SetMessage(L"Hello");
					channel->Enqueue(iKey, context, (Domain)telemetry);

					buffer = channel->GetBuffer();
					Assert::AreEqual(i + 1, (int)buffer.size());
					Assert::AreEqual(channelId, channel->GetChannelId());
					Assert::AreEqual(i+1, channel->GetSeqNum());

					std::wstring envelope = *buffer.rbegin();
					std::wstring::size_type namePos = envelope.find(L"Microsoft.ApplicationInsights.Message");
					Assert::AreNotEqual(std::wstring::npos, namePos);

					int timePos = envelope.find(L"time");
					int timeBegin = timePos + 7;
					re dateMatcher("\\d{4}-\\d{2}-\\d{2}T\\d{2}:\\d{2}:\\d{2}.\\d\\d?\\d?Z");
					std::string date = str(&envelope[timeBegin], &envelope[timeBegin + 24]);
					Assert::IsTrue(re_match(date, dateMatcher), L"Invalid regex for date");

					int seqPos = envelope.find(L"seq");
					int channelBegin = seqPos + 6;
					int channelEnd = envelope.find(L":", channelBegin);
					int seqBegin = channelEnd + 1;
					int seqEnd = envelope.find(L"\"", channelBegin);
					std::wstring strChannel = wstr(&envelope[channelBegin], &envelope[channelEnd]);
					std::wstring seq = wstr(&envelope[seqBegin], &envelope[seqEnd]);

					wchar_t channelIdString[256];
					wchar_t indexString[8];
					swprintf_s(channelIdString, 256, L"%d", channelId);
					swprintf_s(indexString, 8, L"%d", i);

					Assert::AreEqual(strChannel.c_str(), channelIdString, L"ChannelId does not match");
					Assert::AreEqual(seq.c_str(), indexString, L"Seq does not match");
				}

			};

			TEST_METHOD(EnqueueAutoSendsWhenMaxBufferSizeIsReached)
			{
				wstr iKey = L"foo";
				auto ui = task_continuation_context::use_current();
				TelemetryClientConfig config(iKey);
				TelemetryContext context(iKey);
				context.InitContext();

				MockTelemetryChannel *channel = (MockTelemetryChannel*)TelemetryChannel::Initialize();
				channel->SetBufferSize(2);
				channel->Send();
				std::list<std::wstring> buffer;
				int channelId = channel->GetChannelId();
				int seqOffset = channel->GetSeqNum();
				Assert::AreEqual((int)channel->GetBuffer().size(), 0, L"Failed to clear queue before the test started");

				for (int i = 0; i < 3; i++)
				{
#ifdef WINAPI_FAMILY_PARTITION
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store

					auto testTask = create_task([&iKey, &config, &context, &i, &seqOffset]() -> bool {
						MockTelemetryChannel *channel = MockTelemetryChannel::GetInstance();
#endif	
#endif
						MessageData telemetry;
						telemetry.SetMessage(L"Hello");

						channel->Enqueue(iKey, context, (Domain)telemetry);
						
#ifdef WINAPI_FAMILY_PARTITION
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
						return true;
					});
#endif
#endif					
				}
				Sleep(10000);
				Assert::AreEqual(channel->GetSeqNum(), 3 + seqOffset, L"Failed: seq number updates after enqueue");
				Assert::AreEqual(channel->GetChannelId(), channelId, L"Failed: channel ID changed");
				Assert::AreEqual((int)channel->GetBuffer().size(), 1, L"Failed to auto send queue");
			};

			TEST_METHOD(SendWorksAsExpected)
			{
				wstr iKey = L"foo";
				TelemetryClientConfig config(iKey);
				TelemetryContext context(iKey);
				context.InitContext();

				MockTelemetryChannel *channel = (MockTelemetryChannel*)TelemetryChannel::Initialize();
				channel->SetBufferSize(5);
				channel->Send();
				int channelId = channel->GetChannelId();
#ifdef WINAPI_FAMILY_PARTITION
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
				auto testTask = create_task([&iKey, &context, &config]() -> bool {
				MockTelemetryChannel *channel = MockTelemetryChannel::GetInstance();
#endif	
#endif
				std::list<std::wstring> buffer;
				
				MessageData telemetry;
				telemetry.SetMessage(L"Hello");

				channel->Enqueue(iKey, context, (Domain)telemetry);
				Assert::IsTrue((channel->GetBuffer().size() > 0), L"Failed to queue data");
				channel->Send();

#ifdef WINAPI_FAMILY_PARTITION
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // Windows phone or store
				DWORD ret = channel->WaitForResponse();
				return true;
				});
				Sleep(10000);
#endif
#endif
				Assert::AreEqual((int)channel->GetBuffer().size(), 0, L"Failed to clear queue");
				Assert::AreEqual(channel->GetChannelId(), channelId, L"Failed: channel ID changed");
			};

			TEST_METHOD(GetInstanceWorksIsThreadSafe)
			{
				TelemetryChannel *channel = TelemetryChannel::Initialize();
				
				// A task_group object that can be used from multiple threads.
				task_group tasks;

				// Concurrently add several tasks to the task_group object.
				parallel_invoke(
					[] { TelemetryChannel *channel = TelemetryChannel::GetInstance(); },
					[] { TelemetryChannel *channel = TelemetryChannel::GetInstance(); },
					[] { TelemetryChannel *channel = TelemetryChannel::GetInstance(); },
					[] { TelemetryChannel *channel = TelemetryChannel::GetInstance(); },
					[] { TelemetryChannel *channel = TelemetryChannel::GetInstance(); }
				);
			};

			TEST_METHOD(EnqueueIsThreadSafe)
			{
				wstr iKey = L"foo";
				TelemetryContext context(iKey);
				context.InitContext();

				MockTelemetryChannel *channel = (MockTelemetryChannel*)TelemetryChannel::Initialize();
				channel->SetBufferSize(3);
				channel->Send();
				int seqOffset = channel->GetSeqNum();

				// A task_group object that can be used from multiple threads.
				task_group tasks;

				// Concurrently add several tasks to the task_group object.
				parallel_invoke(
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 1");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				},
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 2");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				},
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 3");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				},
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 4");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				},
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 5");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				}
				);

				Sleep(10000);
				Assert::AreEqual((int)channel->GetBuffer().size(), 2, L"Failed to clear queue");
				Assert::AreEqual((int)channel->GetSeqNum(), 5 + seqOffset, L"Failed to update sequence number");
			};

			TEST_METHOD(SendIsThreadSafe)
			{
				wstr iKey = L"foo";
				TelemetryContext context(iKey);
				context.InitContext();

				MockTelemetryChannel *channel = MockTelemetryChannel::GetInstance();
				channel->SetBufferSize(1);
				channel->Send();
				int seqOffset = channel->GetSeqNum();

				// A task_group object that can be used from multiple threads.
				task_group tasks;

				// Concurrently add several tasks to the task_group object.
				parallel_invoke(
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 1");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				},
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 2");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				},
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 3");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				},
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 4");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				},
					[&iKey, &context] {
					TelemetryChannel *channel = TelemetryChannel::GetInstance();
					MessageData telemetry;
					telemetry.SetMessage(L"Hello 5");
					channel->Enqueue(iKey, context, (Domain)telemetry);
				}
				);

				Sleep(10000);
				Assert::AreEqual((int)channel->GetBuffer().size(), 0, L"Failed to clear queue");
				Assert::AreEqual((int)channel->GetSeqNum(), 5 + seqOffset, L"Failed to update sequence number");
			};
		};
	}
}