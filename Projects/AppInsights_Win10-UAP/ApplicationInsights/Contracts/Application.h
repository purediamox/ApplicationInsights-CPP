#ifndef CX_APPLICATION_H
#define CX_APPLICATION_H
//#pragma once

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
#endif