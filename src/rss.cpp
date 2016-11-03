#include "utils/utils.hpp"
#include "rss/rss.hpp"

using namespace utils::http;

static int parse(const char *rss_feed_url) {
    auto result = http::HTTPS_Request(rss_feed_url).set_method(Poco::Net::HTTPRequest::HTTP_GET)
                                                   .set_relaxed_ssl()
                                                   .run();

    rss::parser::parser_cb parser_callback = [](const rss::item::Item &rss_item) {
        std::cout << static_cast<std::string>(rss_item) << std::endl;
    };

    rss::parser::Parser(parser_callback).parse(result.body());

    return 0;
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    try {
       return parse("https://www.nyaa.se/?page=rss");
    }
    catch (Poco::Exception &exc) {
        std::cerr << exc.displayText() << std::endl;
        return 1;
    }
}
