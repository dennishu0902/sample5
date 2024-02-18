#include <stdexcept>
#include "color.hpp"


//Assigns each data member its zero value.
Color::Color()
{
      red_ = 0;
      green_ = 0;
      blue_ = 0;
}
//Initializes a new Color object, ensuring the values assigned to 
//red_, green_, and blue_ are each within the range 0 to 255 inclusive. 
//Throw an exception if any of the arguments are outside that range.
//TestCase required.
Color::Color(int r, int g, int b)
{
    
    if(( r < kColorValueMin) || (r > kColorValueMax)) 
         goto error_process;
    else if(( g < kColorValueMin) || (g > kColorValueMax)) 
          goto error_process;
    else if(( b < kColorValueMin) || (b > kColorValueMax)) 
         goto error_process;
    red_ = r;
    green_= g;
    blue_ = b;
    return;
error_process:
    //throw exception
    throw std::runtime_error("error rgb value");
}
int Color::Red() const 
{
    return red_;
}
int Color::Green() const
{
    return green_;
}
int Color::Blue() const
{
    return blue_;
}
/*
TEST_CASE("Sample","Color-1")
{
    Color color1(2,3,10);
    const int red   = 2;
    const int green = 3;
    const int blue  = 10;
    REQUIRE(std::equal(red==color1.Red()));
    REQUIRE(std::equal(green==color1.Green()));
    REQUIRE(std::equal(blue==color1.Blue()));

}
*/