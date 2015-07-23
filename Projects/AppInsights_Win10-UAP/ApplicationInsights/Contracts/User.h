#pragma once

namespace ApplicationInsights
{
	namespace CX
	{
		public ref class User sealed
		{
		public:
			User();
			virtual ~User() {};

			property Platform::String^ AccountAcquisitionDate
			{
				Platform::String^ get();
			}

			property Platform::String^ Id
			{
				Platform::String^ get();
			}

			property Platform::String^ UserAgent;
			property Platform::String^ AccountId;
			property Platform::String^ StoreRegion;

		};
	}
}