#include "../targetver.h"
#include "../specializations.h"
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
			TEST_CLASS(TestCXTelemetryClient)
			{
			public:
				TEST_METHOD(CtorWorksAsExpected)
				{
					TelemetryClient ^client = ref new TelemetryClient("MY_IKEY");
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
///// Renews the session.
///// </summary>
//void RenewSession();
//
///// <summary>
///// Gets the global properties.
///// </summary>
//Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ GetGlobalProperties();