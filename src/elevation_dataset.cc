#include <fstream>
#include <stdexcept>
#include <limits.h>
#include <iostream>
#include <cassert>
#include "elevation_dataset.hpp"
using namespace std;
    //Initializes the primitive data members with their respective values as read from the file; 
    //populates the two-dimensional std::vector<std::vector<int>> with elevation data from file. 
    //Sets width_ and height_ appropriately. Records max_ele_ and min_ele_ observed.
ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height)
{
   std::string s1; 
   size_t w1,h1;
   int value;
   std::ifstream ifs;
   std::vector<int> rowv;
   ifs.open(filename,std::ifstream::in);
   if(!ifs.is_open()) goto error_process;
   w1 = 0;
   h1 = 0;
   rowv.resize(width,0);
   data_.resize(height,rowv);
   
   min_ele_ = std::numeric_limits<int>::max();
   max_ele_ = std::numeric_limits<int>::min();
   
   w1 = 0;
   while(ifs >> s1) //Read string, use space or LR as seperator 
   {
    try { 
        value = std::stoi(s1); 
        if(value < min_ele_) min_ele_ = value;
        if(value > max_ele_) max_ele_ = value;
        data_.at(h1).at(w1) = value;
        w1++;
        if(w1==width) 
        {   w1 = 0;
            h1++;
            if(h1==height) break;//read done
        }
        }
     catch (const std::invalid_argument& ia) 
     {
	     std::cout << "Invalid argument: " << ia.what() << '\n';
         goto error_process;
      }
   }
   if(h1 != height) goto error_process; //too less data in the file
   if(ifs>>s1)  goto error_process; //too much data in the file
    width_ = width;
    height_ =height;
    ifs.close();
    return;
error_process:
    throw std::runtime_error ("a runtime error");
}
//Returns the “width” of the dataset
size_t ElevationDataset::Width() const
{
    return width_;
}
//Returns the “height” of the dataset
size_t ElevationDataset::Height() const
{
    return height_;
}
 //Returns the maximum elevation value observed in the dataset
int ElevationDataset::MaxEle() const
{
    return max_ele_;
}
//Returns the minimum elevation value observed in the dataset
int ElevationDataset::MinEle() const
{
    return min_ele_;
}
//Returns the value recorded for (row, col)
int ElevationDataset::DatumAt(size_t row, size_t col) const
{
     assert(row<height_);
     assert(col<width_);
     return data_.at(row).at(col);
}
//Returns reference to const to data_.
const std::vector<std::vector<int> >& ElevationDataset::GetData() const
{
    return data_;
}
