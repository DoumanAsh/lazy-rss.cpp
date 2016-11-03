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
         * @param url Valid HTTP URI string.
         */
        explicit HTTP_Request(const char* url);

        /**
         * Sets method type.
         *
         * @param method Poco method type.
         */
        HTTP_Request& set_method(const std::string &method);

        /**
         * @return Response to HTTP request.
         */
        HTTP_Response run();

    protected:
        Poco::URI uri;
        std::string method;
};

/**
 * HTTPS request.
 */
class HTTPS_Request: public HTTP_Request {
    public:
        /**
         * Initializes request class alongside with SSL facilities.
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
         * @param method Poco method type.
         */
        HTTPS_Request& set_method(const std::string &method);
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
