#include "gtest/gtest.h"

#include "item.hpp"
#include "parser.hpp"

using namespace parser;

static std::string gen_rss_item(const item::Item &rss_item) {
    std::ostringstream stream;

    stream << "<item>"
           << "<title>" << rss_item.title() << "</title>"
           << "<category>" << rss_item.category() << "</category>"
           << "<description>" << rss_item.desc() << "</description>"
           << "<link>" << rss_item.link() << "</link>"
           << "<guid>" << rss_item.guid() << "</guid>"
           << "</item>"
           << std::endl;

    return stream.str();
}

static std::string gen_rss_feed(const std::vector<item::Item> &items) {
    std::string feed = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?> <rss version=\"2.0\"> <channel> <title>RSS Title</title> <description>This is an example of an RSS feed</description> <link>http://www.example.com/main.html</link> <lastBuildDate>Mon, 06 Sep 2010 00:01:00 +0000 </lastBuildDate> <pubDate>Sun, 06 Sep 2009 16:20:00 +0000</pubDate> <ttl>1800</ttl>";

    for (auto &item : items) {
        feed.append(gen_rss_item(item));
    }

    feed.append("</channel></rss>");

    return feed;
}

TEST(Parser, ParseRssXml) {
    std::vector<item::Item> expected_items = {
        item::Item("Title 1", "First cat", "http://random-link.com/1", "guid1", "Some description for item 1"),
        item::Item("Title 2", "Second cat", "http://random-link.com/2", "guid2", "Some description for item 2")
    };

    auto feed = gen_rss_feed(expected_items);

    std::vector<item::Item> items;

    parser_cb parser_callback = [&items](const item::Item &rss_item) {
        items.push_back(rss_item);
    };

    Parser(parser_callback).parse(feed);

    ASSERT_EQ(items.size(), expected_items.size());

    for (size_t idx = 0; idx < items.size(); idx++) {
        auto item = items[idx];
        auto expect = expected_items[idx];

        EXPECT_EQ(item.title(), expect.title());
        EXPECT_EQ(item.category(), expect.category());
        EXPECT_EQ(item.desc(), expect.desc());
        EXPECT_EQ(item.link(), expect.link());
        EXPECT_EQ(item.guid(), expect.guid());
    }
}

TEST(Parser, ParseEmptyRssXml) {
    std::vector<item::Item> expected_items = {
    };

    auto feed = gen_rss_feed(expected_items);

    std::vector<item::Item> items;

    parser_cb parser_callback = [&items](const item::Item &rss_item) {
        items.push_back(rss_item);
    };

    Parser(parser_callback).parse(feed);

    ASSERT_EQ(items.size(), (size_t)0);
    ASSERT_EQ(items.size(), expected_items.size());
}
