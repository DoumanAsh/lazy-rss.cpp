#pragma once

#include <string>
#include <functional>

#include "item.hpp"

/**
 * RSS Parser module.
 */
namespace parser {
/// Parser callback type
typedef std::function<void(const item::Item&)> parser_cb;
/**
 * RSS Parser class.
 */
class Parser {
    public:
        /**
         * Constructor.
         *
         * @param cb Callback of type @ref parser_cb.
         */
        Parser(parser_cb &cb) noexcept(true);
        /**
         * Performs parsing of RSS feed.
         *
         * @param rss_xml RSS Feed string.
         */
        void parse(const std::string &rss_xml);

    private:
        parser_cb _cb;
};
}
