#include "path.hpp"
  // Initializes the primitive data members with their respective values from arguments;
  // initializes path_ std::vector<size_t> of length elements. 
Path::Path(size_t length, size_t starting_row)
{ 
   starting_row_ = starting_row;
   length_  = length;
   ele_change_ = 0;
   path_.resize(length);  
}
size_t Path::Length() const
{
   return length_;
}
size_t Path::StartingRow() const
{
    return starting_row_ ;
} 
unsigned int Path::EleChange() const
{
    return ele_change_ ;
}
void Path::IncEleChange(unsigned int value)
{
    ele_change_ += value;
}
const std::vector<size_t>& Path::GetPath() const
{
    return path_ ;
}
//Assigns the value of row (path_.at(col) will evaluate to row)
void Path::SetLoc( size_t col, size_t row )
{
   path_.at(col) = row;
}
