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
        ///Default constructor.
        Parser();
        /**
         * Performs parsing of RSS feed.
         *
         * @param rss_xml RSS Feed string.
         */
        void parse(const std::string &rss_xml);

    private:
};
}
