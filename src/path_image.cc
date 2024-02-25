#include <iostream>
#include <cstdlib>
#include <fstream>
#include <limits> 
#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

using namespace std;
    //Initializes the primitive data members with their respective values read from image; 
    //populates the two-dimensional std::vector<std::vector<Color>> with values from 
    //the image’s image_. Calculates and stores all paths through the image; 
    //you may wish to maintain the row of the best path in a variable best_path_row_.
PathImage::PathImage(const GrayscaleImage &image, const ElevationDataset &dataset)
{
    size_t best_row=0,row=0,col=0;
    int cur_ele=0,n_ele1=0,n_ele2=0,n_ele3=0,ele_change=0;
    int int_max = std::numeric_limits<int>::max();
    unsigned int min_ele_change=std::numeric_limits<unsigned int>::max();
    path_image_ = image.GetImage(); //Copy from gray image     

    size_t w1 = image.Width();
    size_t h1 = image.Height();
    width_ = w1;
    height_= h1;
    best_path_row_ = 0;
    for(row=0;row<h1;row++)         //how many path
    {
       paths_.push_back(Path(w1, row));//path, different starting row
    }
   
    for(row=0; row < h1; row++)
    {
     Path& cur_path = paths_.at(row);
     cur_path.SetLoc(0,row); //SetLoc(col,row)
     cur_ele = dataset.DatumAt(row,0);//start point ele
     best_row = row; //start point
     for(col=1;col<w1;col++) //search from col=1
     {
        //if row=0; we can't find from row-1. best_row is size_t, conver to unisgned long, size_t can't compare with zero
        if(static_cast<unsigned int>(best_row) == 0) n_ele1 = int_max;//if row=0; we can't find from row-1. 
        else n_ele1 = dataset.DatumAt(best_row - 1,col); //Get (row-1,col)
        if((best_row + 1) == h1) n_ele3 = int_max; //if row + 1 = h1, we can't find from row+1. 
        else n_ele3 = dataset.DatumAt(best_row + 1,col);
       
        n_ele2 = dataset.DatumAt(best_row,col);
        ChooseBestWay(best_row, cur_ele, n_ele1, n_ele2, n_ele3, ele_change);
        cur_path.IncEleChange(ele_change);
        cur_path.SetLoc(col,best_row);
        cur_ele = dataset.DatumAt(best_row,col);
      } 
      if(cur_path.EleChange()<min_ele_change)
      {
        min_ele_change = cur_path.EleChange();
        best_path_row_ = row;
      }
     // std::cout << cur_path << std::endl;
    }
    PutPathtoImage();
 } 
void PathImage::ChooseBestWay(size_t& best_row, int cur_ele, int n_ele1, 
                              int n_ele2, int n_ele3, int &ele_change)
{
        //middle
        int row_change = 0; 
        ele_change = abs(n_ele2 - cur_ele);
        //down
        if(abs(n_ele3 - cur_ele) < ele_change) 
        { row_change = 1; ele_change = abs(n_ele3 - cur_ele);}
        //up
        if(abs(n_ele1 - cur_ele) < ele_change) 
        { row_change = -1; ele_change = abs(n_ele1 - cur_ele);}
        //Get min ele change 
        if(row_change == -1) best_row = best_row - 1;
        else if(row_change ==  1) best_row = best_row + 1;
}
void  PathImage::PutPathtoImage()
{
    Color kPathColorValue=Color(252,25,63);
    Color kBestpathColorValue=Color(31,253,13);   
     //put path onto path_image_, Fill specified color to the image
    for(size_t row=0;row<height_;row++)
    {
       Path& cur_path = paths_.at(row); 
       if(row != best_path_row_) //Fill best_path_row_ later, make sure not being overided  
       {
         for(size_t col=0;col<width_;col++)  
            path_image_.at(cur_path.GetPath().at(col)).at(col)=kPathColorValue;
       }
    }    
    //put best_path onto path_image_, fill specified color to the image
    Path& cur_path = paths_.at(best_path_row_); 
    for(size_t col=0;col<width_;col++)  
        path_image_.at(cur_path.GetPath().at(col)).at(col)=kBestpathColorValue;
        
}
size_t PathImage::Width() const
{
    return width_;
}
size_t PathImage::Height() const
{
    return height_ ;
}
//Returns the value stored in kMaxColorValue
unsigned int PathImage::MaxColorValue() const
{
    return kMaxColorValue;
}
//Returns reference to const to paths_.
const std::vector<Path>& PathImage::Paths() const
{
    return paths_;
}
//Returns reference to const to path_image_
const std::vector<std::vector<Color> >& PathImage::GetPathImage() const
{
     return path_image_;
}
//Returns the Color at row col by reference to const
const Color& PathImage::ColorAt(int row, int col) const
{
    return path_image_.at(row).at(col);
}
//Writes out image_ in plain PPM format; filename is name.
//P3
//width height
//maxcolor
//data
//Writes out path_image_ in plain PPM format; filename is name.
void PathImage::ToPpm(const std::string& name) const
{
   std::string s1; 
   std::ofstream ofs;
   ofs.open(name);
   if(!ofs.is_open())  std::runtime_error("ToPpm file open error");
   size_t w1 = Width();
   size_t h1 = Height();
   ofs<<"P3"<<std::endl;
   ofs<<w1<<std::endl;
   ofs<<h1<<std::endl;
   ofs<<MaxColorValue()<<std::endl;
   for(size_t row=0;row<h1;row++)
    {
        for(size_t col=0;col<w1;col++)
        {
            Color colorv = ColorAt(row,col);
            ofs << colorv.Red()<<' ';
            ofs << colorv.Green()<<' ';
            ofs << colorv.Blue()<<' ';
        }
            ofs << std::endl;
    }
    ofs.close();
}
