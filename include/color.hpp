#ifndef COLOR_H 
#define COLOR_H
class Color
{
public:
    //Assigns each data member its zero value.
    Color();
    //Initializes a new Color object, ensuring the values assigned to 
    //red_, green_, and blue_ are each within the range 0 to 255 inclusive. 
    //Throw an exception if any of the arguments are outside that range.
    Color(int r, int g, int b);
    int Red() const ;
    int Green() const ;
    int Blue() const ;
private:
    static constexpr int kColorValueMin = 0;
    static constexpr int kColorValueMax = 255;
    int red_ ;
    int green_ ;
    int blue_ ;    
};
#endif