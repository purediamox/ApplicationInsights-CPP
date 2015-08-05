#pragma once

namespace ApplicationInsights
{
	namespace CX
	{
		[Windows::Foundation::Metadata::WebHostHiddenAttribute]
		public ref class Utils sealed
		{
		public:
			/// <summary>
			/// Gets the current date time.
			/// </summary>
			/// <returns>string represenation of the current time</returns>
			static Platform::String^ GetCurrentDateTime();

			/// <summary>
			/// Generates the random UUID.
			/// </summary>
			/// <returns>string respresentationof the generated UUID</returns>
			static Platform::String^ GenerateRandomUUID();

			// store or phone
			/// <summary>
			/// Gets the local settings container.
			/// </summary>
			/// <returns>the local settings container for AppInsights</returns>
			static Windows::Foundation::Collections::IPropertySet^ GetLocalSettingsContainer();
		};
	}
}