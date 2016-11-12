#include "cli.hpp"

using namespace cli;

ParseError::ParseError():_result(0), _desc("") {
}

ParseError::ParseError(int result):_result(result), _desc("") {
}

ParseError::ParseError(int result, const char* desciption):_result(result), _desc(desciption) {
}

const char* ParseError::what() const throw() {
    return _desc;
}

ParseError::result() const {
    return _result;
}

Options::Options(int argc, char *argv[]) {
    if (argc < 2) throw ParseError();

    for (int idx = 1; idx < argc; ++idx) {
        std::string arg(argv[idx]);

        if (arg[0] == '-') _handle_option(arg);
        else               _handle_url(arg);
    }

    if (_urls.empty()) throw ParseError(1, "No urls are specified\n");
}

void Options::_handle_option(const std::string &option) {
    if (option == "-h" or option == "--help") throw ParseError();

    //Wrong usage.
    else throw ParseError(1, "Invalid option\n");
}

void Options::_handle_url(const std::string &url) {
    _urls.push_back(url);
}

const std::vector<std::string>& Options::urls() const {
    return _urls;
}

const char* Options::usage =
R"(Lazy RSS scrapper.

Usage:
    get_rss [options] url...

Options:
    -h, --help  Display this message.
)";
