#include "Data.h"
#include "../common/Common.hpp"
#include "../common/JsonWriter.hpp"
#include "../common/Serializer.hpp"
using namespace ApplicationInsights::core;

Data::Data()
{
}

Data::~Data()
{
}

void Data::Serialize(Serializer& serializer) const
{
    Base::Serialize(serializer);
    serializer.WritePropertyName(L"baseData");
    serializer.WriteObjectValue(m_baseData);
}

