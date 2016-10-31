#include "gtest/gtest.h"

#include "http.hpp"

using namespace http;

TEST(HTTP, CheckOkResponse) {
    const int code = 200;
    const std::string reason = "Ok";
    const std::string body = "<html>test</html>";
    const std::string response_string = "HTTP Response(200, Ok)";

    auto body_copy = body; //Note that body is moved to avoid copy.

    auto response = HTTP_Response(code, reason, body_copy);

    EXPECT_EQ(response.status(), code);
    EXPECT_EQ(response.reason(), reason);
    EXPECT_EQ(response.body(), body);

    //200 is ok code so bool value should be true.
    EXPECT_TRUE(response);
    EXPECT_FALSE(!response);

    EXPECT_EQ(static_cast<std::string>(response), response_string);
}

TEST(HTTP, CheckErrorResponse) {
    const int code = 400;
    const std::string reason = "Bad Request";
    const std::string body = "<html>test</html>";
    const std::string response_string = "HTTP Response(400, Bad Request)";

    auto body_copy = body; //Note that body is moved to avoid copy.

    auto response = HTTP_Response(code, reason, body_copy);

    EXPECT_EQ(response.status(), code);
    EXPECT_EQ(response.reason(), reason);
    EXPECT_EQ(response.body(), body);

    EXPECT_TRUE(!response);
    EXPECT_FALSE(response);

    EXPECT_EQ(static_cast<std::string>(response), response_string);
}
