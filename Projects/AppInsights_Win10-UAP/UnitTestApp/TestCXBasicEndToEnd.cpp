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
			TEST_CLASS(TestCXBasicEndToEnd)
			{
			public:
				TEST_METHOD(CXBasicToEnd)
				{
					TelemetryClient^ client = ref new TelemetryClient(L"ba0f19ca-aa77-4838-ac05-dbba85d6b677");

					for (int i = 0; i < 2; i++)
					{
						client->TrackEvent(L"CX TEST EVENT");
						client->TrackMetric("My CX METRIC", 9.0);
						client->TrackTrace("MY CX MSG");
					}
				};
			};
		}
	}
}
