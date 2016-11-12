#include "utils/utils.hpp"
#include "rss/rss.hpp"
#include "cli/cli.hpp"

using namespace utils::http;

inline static void parse(const char *rss_feed_url) {
    auto result = http::HTTPS_Request(rss_feed_url).set_method(http::METHOD::GET)
                                                   .set_relaxed_ssl()
                                                   .run();

    rss::parser::parser_cb parser_callback = [](const rss::item::Item &rss_item) {
        std::cout << static_cast<std::string>(rss_item) << std::endl;
    };

    rss::parser::Parser(parser_callback).parse(result.body());
}

inline static int parse_urls(const std::vector<std::string> &urls) {
    try {
        for (auto &url : urls) {
            parse(url.c_str());
        }
    }
    catch (Poco::Exception &exc) {
        std::cerr << exc.displayText() << std::endl;
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    try {
        cli::Options cli_opts(argc, argv);

        return parse_urls(cli_opts.urls());
    }
    catch (cli::ParseError &exc) {
        std::cerr << exc.what();
        std::cout << cli::Options::usage << std::endl;
        return exc.result();
    }

}
