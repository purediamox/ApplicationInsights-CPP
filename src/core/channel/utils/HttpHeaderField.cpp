#include "HttpHeaderField.hpp"
#include <codecvt>
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
/// Gets the field name.
/// </summary>
/// <returns>the field name</returns>
const std::wstring& HttpHeaderField::GetName() const 
{
	return m_strName;
}

/// <summary>
/// Gets the field value.
/// </summary>
/// <returns>the value of the field</returns>
const std::wstring& HttpHeaderField::GetValue() const 
{
	return m_strValue;
}

/// <summary>
/// Determine if two header fields have the same name (value may differ)
/// </summary>
/// <param name="field">The field.</param>
/// <returns>true if the fields match, otherwise false</returns>
bool HttpHeaderField::operator == (const HttpHeaderField& field) const {
	return _wcsicmp(m_strName.c_str(), field.m_strName.c_str()) == 0;
}

/// <summary>
/// Determine if two header fields different names (value might be the same)
/// </summary>
/// <param name="field">The field.</param>
/// <returns>true if the fields DO NOT match, otherwise false</returns>
bool HttpHeaderField::operator != (const HttpHeaderField& field) const {
#if WINAPI_FAMILY || _WIN32
	return _wcsicmp(m_strName.c_str(), field.m_strName.c_str()) != 0;
#else
	return wcscasecmp(m_strName.c_str(), field.m_strName.c_str()) != 0;
#endif
}

/// <summary>
/// Convert header fields to the string.
/// </summary>
/// <returns>string representation of the fields</returns>
std::string HttpHeaderField::ToString() const
{
	std::wstring str = m_strName + L": " + m_strValue;

	// Return the ANSI version of the string we built
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(str);
}

/// <summary>
/// Convert header fields to the string.
/// </summary>
/// <returns>wstring representation of the fields</returns>
std::wstring HttpHeaderField::ToWString() const
{
	return (m_strName + L": " + m_strValue);
}
