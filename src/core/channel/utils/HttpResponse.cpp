#include "HttpResponse.h"

using namespace ApplicationInsights::core;

/// <summary>
/// Initializes a new instance of the <see cref="HttpResponse"/> class.
/// </summary>
HttpResponse::HttpResponse()
{
}

/// <summary>
/// Finalizes an instance of the <see cref="HttpResponse"/> class.
/// </summary>
HttpResponse::~HttpResponse()
{
}

/// <summary>
/// Sets the error code.
/// </summary>
/// <param name="error">The error.</param>
void HttpResponse::SetErrorCode(int error)
{
	m_errorCode = error;
}

/// <summary>
/// Gets the error code.
/// </summary>
/// <returns>the error code</returns>
int HttpResponse::GetErrorCode() const
{
	return m_errorCode;
}

/// <summary>
/// Sets the payload.
/// </summary>
/// <param name="payload">The payload.</param>
void HttpResponse::SetPayload(std::string &payload)
{
    m_payload = payload;
}

/// <summary>
/// Gets the payload.
/// </summary>
/// <returns>the payload</returns>
const char *HttpResponse::GetPayload() const
{
	return m_payload.c_str();
}


/// <summary>
/// Appends the specified buffer to the payload.
/// Added to workaround an apparent issue with gcc.
/// </summary>
void HttpResponse::AppendPayload(const char* pValue, size_t length)
{
	m_payload.append(pValue, length);
}
