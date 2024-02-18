#ifdef RUNTEST
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "color.hpp"
TEST_CASE("Sample0","Color-1")
{
    Color color1(2,3,10);
    const int red   = 2;
    const int green = 3;
    const int blue  = 10;
    REQUIRE((red==color1.Red()));
    REQUIRE((green==color1.Green()));
    REQUIRE((blue==color1.Blue()));
}
TEST_CASE("Sample1","Color-2")
{
    CHECK_THROWS(Color(2,3,256));
    CHECK_THROWS(Color(-1,3,256));
    CHECK_THROWS(Color(2,-1,256));
}

#endif 