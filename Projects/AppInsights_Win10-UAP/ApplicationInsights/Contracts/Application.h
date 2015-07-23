#pragma once

namespace ApplicationInsights
{
	namespace CX
	{
		public ref class Application sealed
		{
		public:
			Application() {};
			virtual ~Application() {};
			property Platform::String^ Ver;
			property Platform::String^ Build;
		};
	}
}