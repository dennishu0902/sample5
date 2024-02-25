#ifndef GRAYSACLE_IMAGE_H
#define GRAYSACLE_IMAGE_H
#include <cstdlib>
#include <vector>
#include "elevation_dataset.hpp"
#include "color.hpp"
using namespace std;
class GrayscaleImage
{
public:
    //Initializes the primitive data members with their respective values as read from the dataset; 
    //populates the two-dimensional std::vector<std::vector<Color>> with
    // Color representation of each elevation datum. Sets width_ and height_ appropriately.
    GrayscaleImage(const ElevationDataset& dataset);
    //filename contains elevation data. It is reasonable to create an 
    //ElevationDataset object in this function and use it to implement
    // the desired behavior of this constructor. 
    //This constructor initializes the primitive data members with their 
    //respective values as read from the file; 
    //populates the two-dimensional std::vector<std::vector<Color>> with translated Color 
    //representation from each read elevation datum. Sets width_ and height_ appropriately.
    GrayscaleImage(const std::string& filename, size_t width, size_t height);
    size_t Width() const;
    size_t Height() const;
    unsigned int MaxColorValue() const;
    //Returns the Color at row col by reference to const
    const Color& ColorAt(int row, int col) const;
    //Returns reference to const to image_.
    const std::vector<std::vector<Color> >& GetImage() const;
    //Writes out image_ in plain PPM format; filename is name.
    void ToPpm( const std::string& name ) const;
private:
    //Image representation of converted elevation data stored as Color values
    std::vector<std::vector<Color> > image_ ;
    size_t height_ ;
    size_t width_ ;
    static const int kMaxColorValue = 255;
};
#endif