#ifndef ELEVEATIONDAT_H
#define ELEVEATIONDAT_H
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;
class ElevationDataset
{
public:
    //Initializes the primitive data members with their respective values as read from the file; 
    //populates the two-dimensional std::vector<std::vector<int>> with elevation data from file. 
    //Sets width_ and height_ appropriately. Records max_ele_ and min_ele_ observed.
    ElevationDataset(const std::string& filename, size_t width, size_t height);
    size_t Width() const; //Returns the “width” of the dataset
    size_t Height() const;//Returns the “height” of the dataset
    int MaxEle() const; //Returns the maximum elevation value observed in the dataset
    int MinEle() const;//Returns the minimum elevation value observed in the dataset
    int DatumAt(size_t row, size_t col) const;//Returns the value recorded for (row, col)
    const std::vector<std::vector<int> >& GetData() const;//Returns reference to const to data_.
    friend ostream& operator<<(std::ostream &os,  const ElevationDataset &e_in)
    {
      os << "Elevation min"<<e_in.MinEle() << e_in.MaxEle() << ": "<<std::endl ;
      for(auto row:e_in.data_)
      {
        for(auto col:row)
         os << col <<" ";
        os << std::endl; 
      }
      return os;
    };
private:
    std::vector<std::vector<int> > data_;//Houses the elevation data read from the file.
    size_t width_;
    size_t height_;
    int max_ele_;
    int min_ele_;

};
#endif 