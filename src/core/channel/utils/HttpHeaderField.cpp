#include "HttpHeaderField.h"
#include "../../common/Utils.h"
#if defined(WINAPI_FAMILY_PARTITION)
#include <codecvt>    // codecvt not available on GCC yet
#endif
#include <locale>

using namespace ApplicationInsights::core;

/// <summary>
/// Initializes a new instance of the <see cref="HttpHeaderField" /> class.
/// </summary>
/// <param name="name">The name.</param>
/// <param name="value">The value.</param>
HttpHeaderField::HttpHeaderField(const std::wstring& name, const std::wstring& value)
	: m_strName(name),
	m_strValue(value)
{
}

/// <summary>
/// Convert header fields to the string.
/// </summary>
/// <returns>string representation of the fields</returns>
std::string HttpHeaderField::ToString() const
{
	std::wstring str = m_strName + L": " + m_strValue;

	// Return the ANSI version of the string we built
	//std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	//return converter.to_bytes(str);

	return Utils::ConvertToUtf8(str);
}

/// <summary>
/// Convert header fields to the string.
/// </summary>
/// <returns>wstring representation of the fields</returns>
std::wstring HttpHeaderField::ToWString() const
{
	return (m_strName + L": " + m_strValue);
}
