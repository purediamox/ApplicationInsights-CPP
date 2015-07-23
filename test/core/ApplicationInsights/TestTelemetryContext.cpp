#include "../targetver.h"
#include "../specializations.h"
#include "CppUnitTest.h"
#include "TelemetryContext.h"

using namespace ApplicationInsights::CX;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Platform;

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
			};
		}
	}
}