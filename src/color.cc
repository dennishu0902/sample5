#include <stdexcept>
#include "color.hpp"

bool operator==(const Color &lhs, const Color &rhs)
{
    return (lhs.Blue()==rhs.Blue() && lhs.Green()==rhs.Green() && lhs.Red()==rhs.Red());
}

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
Color::Color(int r, int g, int b):red_(r), green_(g),blue_(b)
{
    
    if(( r < kColorValueMin) || (r > kColorValueMax) ||
       ( g < kColorValueMin) || (g > kColorValueMax) 
    || ( b < kColorValueMin) || (b > kColorValueMax)) 
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
