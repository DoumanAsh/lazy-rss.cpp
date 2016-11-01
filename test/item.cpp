#include "gtest/gtest.h"

#include <string>

#include "item.hpp"

using namespace item;

TEST(Item, CheckRssItemClassConstructor) {
    const std::string title = "Some title";
    const std::string category = "Some category";
    const std::string link = "Some link";
    const std::string guid = "Some guid";
    const std::string desc = "Some description";

    Item item(title, category, link, guid, desc);

    EXPECT_TRUE(item);
    EXPECT_EQ(item.title(), title);
    EXPECT_EQ(item.category(), category);
    EXPECT_EQ(item.link(), link);
    EXPECT_EQ(item.guid(), guid);
    EXPECT_EQ(item.desc(), desc);

    item.reset();

    EXPECT_FALSE(item);
    EXPECT_TRUE(item.title().empty());
    EXPECT_TRUE(item.category().empty());
    EXPECT_TRUE(item.link().empty());
    EXPECT_TRUE(item.guid().empty());
    EXPECT_TRUE(item.desc().empty());
}

TEST(Item, CheckRssItemClassSetters) {
    const std::string title = "Some title";
    const std::string category = "Some category";
    const std::string link = "Some link";
    const std::string guid = "Some guid";
    const std::string desc = "Some description";

    Item item;

    EXPECT_FALSE(item);

    item.set_title(title)
        .set_category(category)
        .set_link(link)
        .set_guid(guid)
        .set_desc(desc);

    EXPECT_TRUE(item);
    EXPECT_EQ(item.title(), title);
    EXPECT_EQ(item.category(), category);
    EXPECT_EQ(item.link(), link);
    EXPECT_EQ(item.guid(), guid);
    EXPECT_EQ(item.desc(), desc);

    item.reset();

    EXPECT_FALSE(item);
    EXPECT_TRUE(item.title().empty());
    EXPECT_TRUE(item.category().empty());
    EXPECT_TRUE(item.link().empty());
    EXPECT_TRUE(item.guid().empty());
    EXPECT_TRUE(item.desc().empty());
}
