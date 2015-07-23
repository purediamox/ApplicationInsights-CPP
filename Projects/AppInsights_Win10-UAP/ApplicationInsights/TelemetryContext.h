#pragma once
#include "collection.h"
#include "Contracts/User.h"
#include "Contracts/Device.h"
#include "Contracts/Application.h"
#include "Contracts/Session.h"

namespace ApplicationInsights
{
	namespace CX
	{
		public ref class TelemetryContext sealed
		{
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="TelemetryContext"/> class.
			/// </summary>
			TelemetryContext();

			/// <summary>
			/// Initializes the context.
			/// </summary>
			void InitContext();

			property User^ UserContext
			{
				User^ get() 
				{
					return m_user;
				}

				void set(User^ value)
				{
					m_user = value;
				}
			}

			property Device^ DeviceContext
			{
				Device^ get()
				{
					return m_device;
				}

				void set(Device^ value)
				{
					m_device = value;
				}
			}

			property Application^ ApplicationContext
			{
				Application^ get()
				{
					return m_app;
				}

				void set(Application^ value)
				{
					m_app = value;
				}
			}

			/// <summary>
			/// Renews the session.
			/// </summary>
			void RenewSession();

			/// <summary>
			/// Gets the context tags.
			/// </summary>
			/// <returns>The tags.</returns>
			void GetContextTags(Windows::Foundation::Collections::IMap<Platform::String^, Platform::String^>^ map);

		private:
			/// <summary>
			/// Initializes the user context.
			/// </summary>
			void InitUser();

			/// <summary>
			/// Initializes the device context.
			/// </summary>
			void InitDevice();

			/// <summary>
			/// Initializes the application.
			/// </summary>
			void InitApplication();

			/// <summary>
			/// Initializes the session.
			/// </summary>
			void InitSession();

			User^ m_user;
			Device^ m_device;
			Application^ m_app;
			Session^ m_session;
		};
	}
}
