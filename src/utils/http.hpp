#pragma once

#include <iostream>

#define POCO_WIN32_UTF8
#include "Poco/Exception.h"
#include "Poco/URI.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/StreamCopier.h"
#include "Poco/SharedPtr.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"
#include "Poco/Net/AcceptCertificateHandler.h"
#include "Poco/Net/RejectCertificateHandler.h"

/**
 * HTTP facilities.
 */
namespace http {

/**
 * HTTP Method enum.
 *
 * See [definitions](https://www.w3.org/Protocols/rfc2616/rfc2616-sec9.html)
 */
enum class METHOD {
    GET,    /**< HTTP GET Method*/
    HEAD,   /**< HTTP HEAD Method*/
    PUT,    /**< HTTP PUT Method*/
    POST,   /**< HTTP POST Method*/
    OPT,    /**< HTTP OPTIONS Method*/
    DEL,    /**< HTTP DELETE Method*/
    TRACE,  /**< HTTP TRACE Method*/
    CONNECT,/**< HTTP CONNECT Method*/
};

/**
 * Represents HTTP(s) response.
 */
class HTTP_Response {
    public:
        /**
         * Creates HTTP Response.
         *
         * @param status Status code of Request.
         * @param reason Reason description.
         * @param body Content of response. Moved.
         */
        HTTP_Response(int status, const std::string &reason, std::string &body) noexcept(true);

        /**
         * @return Status code of response.
         */
        int status() const;

        /**
         * @return Reason description of status code.
         */
        const std::string& reason() const;

        /**
         * @return Content of response.
         */
        const std::string& body() const;

        /**
         * @return Whether response is success or not.
         *
         * @retval true If response code is either 200 or 201
         * @retval false Otherwise.
         */
        operator bool() const;

        /**
         * @return Whether response is failure or not.
         */
        operator !() const;

        /**
         * String representation of HTTP Response.
         *
         * Can be used as debug information.
         */
        explicit operator std::string() const;

    private:
        int _status;
        std::string _reason;
        std::string _body;
};

class HTTP_Request {
    public:
        /**
         * Initializes request class.
         *
         * Default method is GET.
         *
         * @param url Valid HTTP URI string.
         */
        explicit HTTP_Request(const char* url);

        /**
         * Sets method type.
         *
         * @param method HTTP Method type.
         */
        HTTP_Request& set_method(METHOD method);

        /**
         * @return Response to HTTP request.
         */
        HTTP_Response run();

    protected:
        Poco::URI uri;
        METHOD method;

        /**
         * @return Poco method string.
         */
        const std::string& method_str() const;
};

/**
 * HTTPS request.
 */
class HTTPS_Request: public HTTP_Request {
    public:
        /**
         * Initializes request class alongside with SSL facilities.
         *
         * Default method is GET.
         *
         * @param url Valid HTTPS URI string.
         */
        explicit HTTPS_Request(const char* url);

        /**
         * Default destructor to terminate SSL facilities.
         */
        ~HTTPS_Request();

        /**
         * Sets method type.
         *
         * @param method HTTP Method type.
         */
        HTTPS_Request& set_method(METHOD method);

        /**
         * Sets strict SSL verification mode.
         *
         * Failed certificate is being rejected.
         */
        HTTPS_Request& set_strict_ssl();

        /**
         * Sets relaxed SSL verification mode.
         *
         * Failed certificate is accepted.
         */
        HTTPS_Request& set_relaxed_ssl();

        /**
         * @return Response to HTTP request.
         */
        HTTP_Response run();
};
}
