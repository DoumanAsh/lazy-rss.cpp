#include <sstream>
#include "http.hpp"

using namespace http;

HTTP_Response::HTTP_Response(int status, const std::string &reason, std::string &body) noexcept(true)
    :
    _status(status),
    _reason(reason),
    _body(std::move(body))
{
}

int HTTP_Response::status() const {
    return _status;
}

const std::string& HTTP_Response::reason() const {
    return _reason;
}

const std::string& HTTP_Response::body() const {
    return _body;
}

HTTP_Response::operator bool() const {
    return _status == 200 or _status == 201;
}

HTTP_Response::operator !() const {
    return _status != 200 and _status != 201;
}

HTTP_Response::operator std::string() const {
    std::ostringstream stream;
    stream << "HTTP Response(" << this->status() << ", " << this->reason() << ")";
    return stream.str();
}

HTTPS_Request::HTTPS_Request(const char* url) {
    this->uri = Poco::URI(url);
    Poco::Net::initializeSSL();
}

HTTPS_Request::~HTTPS_Request() {
    Poco::Net::uninitializeSSL();
}

HTTPS_Request& HTTPS_Request::set_method(const std::string &method) {
    this->method = method;
    return *this;
}

HTTPS_Request& HTTPS_Request::set_strict_ssl() {
    auto cert = new Poco::Net::RejectCertificateHandler(true);
    auto context = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE, "");
    Poco::Net::SSLManager::instance().initializeClient(0, cert, context);
    return *this;
}

HTTPS_Request& HTTPS_Request::set_relaxed_ssl() {
    auto cert = new Poco::Net::AcceptCertificateHandler(true);
    auto context = new Poco::Net::Context(Poco::Net::Context::CLIENT_USE,
                                          "", "", "",
                                          Poco::Net::Context::VERIFY_NONE,
                                          9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    Poco::Net::SSLManager::instance().initializeClient(0, cert, context);
    return *this;
}

HTTP_Response HTTPS_Request::run() {
    //TODO: consider to avoid exceptions.
    Poco::Net::HTTPSClientSession session(this->uri.getHost(), this->uri.getPort());
    Poco::Net::HTTPRequest request(this->method, this->uri.getPathAndQuery());
    Poco::Net::HTTPResponse response;

    session.sendRequest(request);
    std::istream& rs = session.receiveResponse(response);

    std::string response_body;
    Poco::StreamCopier::copyToString(rs, response_body);

    return HTTP_Response(response.getStatus(), response.getReason(), response_body);
}
