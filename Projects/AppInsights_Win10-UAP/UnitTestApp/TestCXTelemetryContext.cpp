#include "targetver.h"
#include "specializations.h"
#include "CppUnitTest.h"
#include <regex>
#include <string.h>

using namespace ApplicationInsights::CX;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Platform;

typedef std::wregex wre;
#define wre_match(input, wregex) std::regex_match(input, wregex)

namespace CX {
	namespace tests
	{
		namespace ApplicationInsights
		{
			TEST_CLASS(TestCXTelemetryContext)
			{
			public:
				TEST_METHOD(CtorWorksAsExpected)
				{
					TelemetryContext ^context = ref new TelemetryContext();
				};

				TEST_METHOD(InitializeWorksAsExpected)
				{
					TelemetryContext ^context = ref new TelemetryContext();
					context->InitContext();

					Application^ app = context->ApplicationContext;
					User^ user = context->UserContext;
					Device^ device = context->DeviceContext;
					Session^ session = context->SessionContext;

					std::wstring version = app->Ver->Data();
					wre verMatcher(L"([0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12})\\s+\\([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+\\)");
					Assert::IsTrue(wre_match(version, verMatcher), L"Invalid regex for version");
						
					wre dateMatcher(L"\\d{4}-\\d{2}-\\d{2}T\\d{2}:\\d{2}:\\d{2}.\\d\\d?\\d?Z");
					std::wstring date = user->AccountAcquisitionDate->Data();
					Assert::IsTrue(wre_match(date, dateMatcher), L"Invalid regex for date");

					wre uuidMatcher(L"(\\{){0,1}[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}(\\}){0,1}");
					std::wstring uuid = user->Id->Data();
					Assert::IsTrue(wre_match(uuid, uuidMatcher), L"Invalid regex for uuid");

					Assert::IsTrue(device->Id != nullptr);
					Assert::IsTrue(device->Ip == nullptr);
					Assert::AreEqual(L"en-US", device->Language->Data());
					Assert::AreEqual(L"United States", device->Locale->Data());
					Assert::IsTrue(device->Model == nullptr);
					Assert::AreEqual(L"Ethernet", device->Network->Data());
					Assert::IsTrue(device->OemName == nullptr);
					Assert::AreEqual(L"Windows", device->Os->Data());
					Assert::IsTrue(device->OsVersion== nullptr);
					Assert::IsTrue(device->RoleInstance == nullptr);
					Assert::IsTrue(device->RoleName == nullptr);
					Assert::IsTrue(device->ScreenResolution == nullptr);
					Assert::AreEqual(L"Store", device->Type->Data());
					Assert::IsTrue(device->MachineName == nullptr);

					wre sessionUuidMatcher(L"(\\{){0,1}[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}(\\}){0,1}");
					std::wstring sessionUuid = session->Id->Data();
					Assert::IsTrue(wre_match(sessionUuid, sessionUuidMatcher), L"Invalid regex for session uuid");
					Assert::AreEqual(L"True", session->IsFirst->Data());
					Assert::AreEqual(L"True", session->IsNew->Data());
				};

				TEST_METHOD(RenewSessionWorkAsExpected)
				{
					TelemetryContext ^context = ref new TelemetryContext();
					context->InitContext();
					Session ^session = context->SessionContext;
					std::wstring origUuid = session->Id->Data();

					context->RenewSession();
					wre uuidMatcher(L"(\\{){0,1}[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}(\\}){0,1}");
					std::wstring sessionUuid = session->Id->Data();

					Assert::IsTrue(wre_match(sessionUuid, uuidMatcher), L"Invalid regex for session uuid");
					Assert::IsTrue(wcscmp(origUuid.c_str(), sessionUuid.c_str()) != 0, L"Session Id should not be the same after renew");
					Assert::AreEqual(L"False", session->IsFirst->Data(), L"IsFirst should be false");
					Assert::AreEqual(L"True", session->IsNew->Data(), L"IsNew should be true");
				}
			};
		}
	}
}
