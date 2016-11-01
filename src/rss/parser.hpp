#pragma once

#include <string>

/**
 * RSS Parser module.
 */
namespace parser {
/**
 * RSS Parser class.
 */
class Parser {
    public:
        Parser();
        void parse(const std::string &rss_xml);

    private:
};
}
