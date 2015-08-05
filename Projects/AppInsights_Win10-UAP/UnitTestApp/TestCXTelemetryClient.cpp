#include "targetver.h"
#include "specializations.h"
#include "CppUnitTest.h"
#include <collection.h>

using namespace ApplicationInsights::CX;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Storage;

namespace CX {
	namespace tests
	{
		namespace ApplicationInsights
		{
			TEST_CLASS(TestCXTelemetryClient)
			{
			public:
				TEST_METHOD(CtorWorksAsExpected)
				{
					TelemetryClient ^client = ref new TelemetryClient("MY_IKEY");
				};

				TEST_METHOD(CtorWithContextWorksAsExpected)
				{
					TelemetryContext ^context = ref new TelemetryContext();
					TelemetryClient ^client = ref new TelemetryClient(context, "MY_IKEY");
				};

				TEST_METHOD(CtorWithNullptrContextWorksAsExpected)
				{
					TelemetryClient ^client = ref new TelemetryClient(nullptr, "MY_IKEY");
				};

				TEST_METHOD(SetGetGlobalPropertiesWorksAsExpected)
				{
					TelemetryClient ^client = ref new TelemetryClient("MY_IKEY");
					
					String^ key = L"MyKEY";
					String^ value = L"MyValue";
					Windows::Foundation::Collections::IMap<String^, String^>^ props = 
						ref new Platform::Collections::Map<String^, String^>{ {key, value} };
					client->GlobalProperties = props;
					Assert::AreEqual(client->GlobalProperties->Lookup(key), value);
				};
			};
		}
	}
}

///// <summary>
///// Initializes a new instance of the <see cref="TelemetryClient"/> class.
///// </summary>
///// <param name="iKey">The iKey.</param>
//TelemetryClient(Platform::String^ iKey);
//
///// <summary>
///// Initializes a new instance of the <see cref="TelemetryClient"/> class.
///// </summary>
///// <param name="context">The context.</param>
//TelemetryClient(TelemetryContext^ context, Platform::String^ iKey);
//
///// <summary>
///// Finalizes an instance of the <see cref="" /> class.
///// </summary>
///// <returns></returns>
//virtual ~TelemetryClient();
//
///// <summary>
//
///// <summary>
///// Gets the global properties.
///// </summary>
//Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ GetGlobalProperties();