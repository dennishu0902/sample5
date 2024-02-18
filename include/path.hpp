#ifndef PATH_H
#define PATH_H
#include <cstddef>
#include <vector>
#include <iostream>
using namespace std;
class Path
{
public:  
  // Initializes the primitive data members with their respective values from arguments;
  // initializes path_ std::vector<size_t> of length elements. 
  Path(size_t length, size_t starting_row);
  size_t Length() const ;
  size_t StartingRow() const ;
  unsigned int EleChange() const ;
  void IncEleChange(unsigned int value);
  const std::vector<size_t>& GetPath() const;
  //Assigns the value of row (path_.at(col) will evaluate to row)
  void SetLoc( size_t col, size_t row );
  friend ostream& operator<<(std::ostream &os,  const Path &g_in)
   {
      os << "Path" << g_in.starting_row_ << ": " ;
      for(auto pos1:g_in.path_)
      {
         os << pos1<<" ";
      }
      return os;
   };
private:
  std::vector<size_t> path_ ;
  size_t length_ ; //Number of columns in path_.
  size_t starting_row_ ; //Row that this path begins from.
  unsigned int ele_change_ ;//Total elevation change “experienced” by a person walking the path.
};
#endif