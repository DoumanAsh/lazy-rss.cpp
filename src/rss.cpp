#include "utils/utils.hpp"
#include "rss/rss.hpp"

using namespace utils::http;

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    try {
        auto result = http::HTTPS_Request("https://www.nyaa.se/?page=rss").set_method(Poco::Net::HTTPRequest::HTTP_GET)
                                                                          .set_relaxed_ssl()
                                                                          .run();
        rss::parser::Parser().parse(result.body());
        return 0;
    }
    catch (Poco::Exception &exc) {
        std::cerr << exc.displayText() << std::endl;
        return 1;
    }
}
