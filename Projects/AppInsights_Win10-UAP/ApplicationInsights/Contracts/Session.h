#pragma once

namespace ApplicationInsights
{
	namespace CX
	{
		public ref class Session sealed
		{
		public:
			Session();
			virtual ~Session() {};

			property Platform::String^ IsFirst
			{
				Platform::String^ get();
				void set(Platform::String^ value);
			}

			property Platform::String^ IsNew
			{
				Platform::String^ get();
				void set(Platform::String^ value);
			}

			property Platform::String^ Id
			{
				Platform::String^ get();
				void set(Platform::String^ value);
			}
		};
	}
}