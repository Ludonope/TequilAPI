#ifndef TEQUILAPI_HTTP_STATUSCODE_HPP_
# define TEQUILAPI_HTTP_STATUSCODE_HPP_

namespace teq
{
  namespace http
  {
    struct StatusCode
    {
      enum
      {
        // Informational
        Continue = 100,
        SwitchingProtocol = 101,

        // Success
        OK = 200,
        Created = 201,
        Accepted = 202,
        NonAuthoritativeInformation = 203,
        NoContent = 204,
        ResetContent = 205,
        PartialContent = 206,

        // Redirection
        MultipleChoices = 300,
        MovedPermanently = 301,
        Found = 302,
        SeeOther = 303,
        NotModified = 304,
        UseProxy = 305,
        TemporaryRedirect = 307,

        // Client Error
        BadRequest = 400,
        Unauthorized = 401,
        PaymentRequired = 402,
        Forbidden = 403,
        NotFound = 404,
        MethodNotAllowed = 405,
        NotAcceptable = 406,
        ProxyAuthentificationRequired = 407,
        RequestTimeOut = 408,
        Conflict = 409,
        Gone = 410,
        LengthRequired = 411,
        PreconditionFailed = 412,
        RequestEntityTooLarge = 413,
        RequestURITooLarge = 414,
        UnsupportedMediaType = 415,
        RequestedRangeNotSatisfiable = 416,
        ExpectationFailed = 417,

        // Server Error
        InternalServerError = 500,
        NotImplemented = 501,
        BadGateway = 502,
        ServiceUnavailable = 503,
        GatewayTimeOut = 504,
        HTTPVersionNotSupported = 505
      };
    };
  }
}

#endif // !TEQUILAPI_HTTP_STATUSCODE_HPP_