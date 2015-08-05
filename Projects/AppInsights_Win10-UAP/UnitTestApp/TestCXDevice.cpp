#include "targetver.h"
#include "specializations.h"
#include "CppUnitTest.h"

using namespace ApplicationInsights::CX;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Storage;

namespace CX {
	namespace tests
	{
		namespace ApplicationInsights
		{
			TEST_CLASS(TestCXDevice)
			{
			public:
				TEST_METHOD(CtorWorksAsExpected)
				{
					Device ^device = ref new Device();
				};

				TEST_METHOD(IdWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->Id = expected;
					Assert::AreEqual(expected, device->Id);
				};

				TEST_METHOD(IpWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->Ip = expected;
					Assert::AreEqual(expected, device->Ip);
				};

				TEST_METHOD(LanguageWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->Language = expected;
					Assert::AreEqual(expected, device->Language);
				};

				TEST_METHOD(LocaleWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->Locale = expected;
					Assert::AreEqual(expected, device->Locale);
				};

				TEST_METHOD(ModelWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->Model = expected;
					Assert::AreEqual(expected, device->Model);
				};

				TEST_METHOD(NetworkWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->Network = expected;
					Assert::AreEqual(expected, device->Network);
				}

				TEST_METHOD(OemNameWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->OemName = expected;
					Assert::AreEqual(expected, device->OemName);
				};

				TEST_METHOD(OsWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->Os = expected;
					Assert::AreEqual(expected, device->Os);
				};

				TEST_METHOD(OsVersionWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->OsVersion = expected;
					Assert::AreEqual(expected, device->OsVersion);
				};

				TEST_METHOD(RoleInstanceWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->RoleInstance = expected;
					Assert::AreEqual(expected, device->RoleInstance);
				};

				TEST_METHOD(RoleNameWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->RoleName = expected;
					Assert::AreEqual(expected, device->RoleName);
				};

				TEST_METHOD(ScreenResolutionWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->ScreenResolution = expected;
					Assert::AreEqual(expected, device->ScreenResolution);
				};

				TEST_METHOD(TypeWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->Type = expected;
					Assert::AreEqual(expected, device->Type);
				};

				TEST_METHOD(MachineNameWorksAsExpected)
				{
					Device ^device = ref new Device();
					String ^expected = L"TEST";
					device->MachineName = expected;
					Assert::AreEqual(expected, device->MachineName);
				};
			};
		}
	}
}
