#pragma once
namespace ApplicationInsights
{
	namespace CX
	{
		public ref class Device sealed
		{
		public:
			Device() {};
			virtual ~Device() {};

			property Platform::String^ Id;
			property Platform::String^ Ip;
			property Platform::String^ Language;
			property Platform::String^ Locale;
			property Platform::String^ Model;
			property Platform::String^ Network;
			property Platform::String^ OemName;
			property Platform::String^ Os;
			property Platform::String^ OsVersion;
			property Platform::String^ RoleInstance;
			property Platform::String^ RoleName;
			property Platform::String^ ScreenResolution;
			property Platform::String^ Type;
			property Platform::String^ MachineName;
		};
	}
}