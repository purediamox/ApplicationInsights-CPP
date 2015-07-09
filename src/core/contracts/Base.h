#ifndef BASE_H
#define BASE_H

#include "../common/Common.hpp"
#include "../common/Serializer.hpp"
#include "../common/Nullable.h"
#include <map>
#include <string>
#include <vector>

namespace ApplicationInsights
{
	namespace core
	{
		class TELEMETRYCLIENT_API Base : public ISerializable
		{
		private:
			std::wstring m_baseType;

		public:
			Base();
			virtual ~Base();

			const std::wstring& GetBaseType() const { return m_baseType; }
			void SetBaseType(const std::wstring& value) { m_baseType = value; }

			virtual void Serialize(Serializer& serializer) const;
		};
	}
}
#endif
