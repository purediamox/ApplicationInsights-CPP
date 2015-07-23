#include "../targetver.h"
#include "../specializations.h"
#include "CppUnitTest.h"
#include "TelemetryClient.h"


using namespace ApplicationInsights::CX;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace CX {
	namespace tests
	{
		namespace ApplicationInsights
		{
			TEST_CLASS(TesCXtPageTracking)
			{
			public:
				TEST_CLASS_INITIALIZE(initialize)
				{
#ifdef WINAPI_FAMILY_PARTITION // it's SOME kind of Windows
#if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) // store or phone
					ApplicationData::Current->ClearAsync();
#endif
#endif
				}

				TEST_METHOD(CtorWorksAsExpected)
				{
					PageTracking ^session = ref new PageTracking();
				};

				TEST_METHOD(InitializeWorksAsExpected)
				{
					String^ iKey = L"IKEYSTRING";
					PageTracking ^page = ref new PageTracking();
					page->Initialize(nullptr, iKey);
				};

				TEST_METHOD(InitializeWorksWithNullsAsExpected)
				{
					PageTracking ^page = ref new PageTracking();
					page->Initialize(nullptr, nullptr);
				};

				TEST_METHOD(NavigatingWorksAsExpected)
				{
					String^ iKey = L"IKEYSTRING";
					PageTracking ^page = ref new PageTracking();
					page->Initialize(nullptr, iKey);
					
					Windows::Globalization::Calendar^ beforeCal = ref new Windows::Globalization::Calendar();
					Windows::Foundation::DateTime before = beforeCal->GetDateTime();

					page->OnNavigating(nullptr, nullptr);

					Windows::Globalization::Calendar^ afterCal = ref new Windows::Globalization::Calendar();
					Windows::Foundation::DateTime after = afterCal->GetDateTime();

					ApplicationDataContainer^ localSettings = ApplicationData::Current->LocalSettings;
					ApplicationDataContainer^ container = localSettings->CreateContainer("AppInsights", ApplicationDataCreateDisposition::Always);
					auto values = localSettings->Containers->Lookup("AppInsights")->Values;

					DateTime startPageLoad;
					if (values->HasKey("StartPageLoad"))
					{
						startPageLoad = (DateTime)values->Lookup("StartPageLoad");
					}
					else
					{
						Assert::IsTrue(false, L"Failed to get start of page load time");
					}

					Assert::IsTrue(startPageLoad.UniversalTime > before.UniversalTime);
					Assert::IsTrue(startPageLoad.UniversalTime < after.UniversalTime);
				};

				TEST_METHOD(NavigatedWorksAsExpected)
				{
					String^ iKey = L"IKEYSTRING";
					PageTracking ^page = ref new PageTracking();
					page->Initialize(nullptr, iKey);

					page->OnNavigating(nullptr, nullptr);

					page->OnNavigated(nullptr, nullptr);

					ApplicationDataContainer^ localSettings = ApplicationData::Current->LocalSettings;
					ApplicationDataContainer^ container = localSettings->CreateContainer("AppInsights", ApplicationDataCreateDisposition::Always);
					auto values = localSettings->Containers->Lookup("AppInsights")->Values;

					Assert::IsFalse(values->HasKey("StartPageLoad"));
				};
			};
		}
	}
}
