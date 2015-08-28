#include "targetver.h"
#include "specializations.h"
#include "CppUnitTest.h"
#include <time.h>

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
			TEST_CLASS(TestCXBasicEndToEnd)
			{
			public:
				TEST_METHOD(CXBasicToEnd)
				{
					TelemetryClient^ client = ref new TelemetryClient(L"0d92f68c-72ba-4172-8c70-ba402cf403a5");

					for (int i = 0; i < 200; i++)
					{
						client->TrackEvent(L"CX TEST EVENT " + i.ToString());
						client->TrackMetric("My CX METRIC " + i.ToString(), 9.0);
						client->TrackTrace("MY CX MSG " + i.ToString());
					}
					
				};
			};
		}
	}
}
