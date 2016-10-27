#include "utils/utils.hpp"

using namespace utils;

int main(int argc, char *argv[]) {
    try {
        auto result = http::HTTPS_Request("https://www.nyaa.se/?page=rss").set_method(Poco::Net::HTTPRequest::HTTP_GET)
                                                                          .set_relaxed_ssl()
                                                                          .run();
        if (result) {
            std::cout << result;
        }
        return 0;
    }
    catch (Poco::Exception &exc) {
        std::cerr << exc.displayText() << std::endl;
        return 1;
    }
}
