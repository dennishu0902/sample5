#include <fstream>
#include <cmath>
#include <iostream>
#include "grayscale_image.hpp"


    //Initializes the primitive data members with their respective values as read from the dataset; 
    //populates the two-dimensional std::vector<std::vector<Color>> with
    // Color representation of each elevation datum. Sets width_ and height_ appropriately.
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset)
{
    size_t col=0,row=0;
    std::vector<Color> rowv;
    int ele=0;
  
    int min_ele = dataset.MinEle();
    int max_ele = dataset.MaxEle();
   
    size_t w1 = dataset.Width();
    size_t h1 = dataset.Height();
    width_  = w1;
    height_ = h1; 
    for(col=0;col<w1;col++) rowv.push_back(Color(0,0,0));  
    for(row =0; row< h1; row++)
      {
      if(max_ele!=min_ele)  
      {
         for(col=0;col<w1;col++)
         {
            ele = dataset.DatumAt(row,col);
//ele= static_cast<int>(std::round((double)(ele - min_ele) / (double)(max_ele - min_ele)*255.0));//double to int
ele= static_cast<int>(std::round(((ele - min_ele)*255+(max_ele - min_ele)/2) / (max_ele - min_ele)));//double to int
            rowv.at(col) = Color(ele,ele,ele);
         }
       }
       image_.push_back(rowv);
      }
        
}
    //filename contains elevation data. It is reasonable to create an 
    //ElevationDataset object in this function and use it to implement
    // the desired behavior of this constructor. 
    //This constructor initializes the primitive data members with their 
    //respective values as read from the file; 
    //populates the two-dimensional std::vector<std::vector<Color>> with translated Color 
    //representation from each read elevation datum. Sets width_ and height_ appropriately.
GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height)
{
    width_  = width;
    height_ = height;
    ElevationDataset eledata = ElevationDataset(filename, width,  height);
    new(this) GrayscaleImage(eledata); //call another constructor
}

size_t GrayscaleImage::Width() const
{
    return width_;
}
size_t GrayscaleImage::Height() const
{
    return height_;
}
unsigned int GrayscaleImage::MaxColorValue() const
{
    return kMaxColorValue;
}
//Returns the Color at row col by reference to const
const Color& GrayscaleImage::ColorAt(int row, int col) const
{
      return image_.at(row).at(col);  
}
//Returns reference to const to image_.
const std::vector<std::vector<Color> >& GrayscaleImage::GetImage() const
{
   return image_;
}
//Writes out image_ in plain PPM format; filename is name.
//P3
//width height
//maxcolor
//data
void GrayscaleImage::ToPpm( const std::string& name ) const
{
   std::string s1; 
   std::ofstream ofs;
   ofs.open(name,std::ifstream::out);
   if(!ofs.is_open())  std::runtime_error("ToPpm file open error");
   size_t w1 = Width();
   size_t h1 = Height();
   ofs <<"P3"<<std::endl;
   ofs <<w1<<std::endl;
   ofs <<h1<<std::endl;
   ofs <<MaxColorValue()<<std::endl;
   for(size_t row=0;row<h1;row++)
    {
        for(size_t col=0;col<w1;col++)
        {
            Color colorv= ColorAt((int)row,(int)col);
            ofs << colorv.Red()<<' ';
            ofs << colorv.Green()<<' ';
            ofs << colorv.Blue()<<' ';
        }
            ofs << std::endl;
    }
    ofs.close();
}
