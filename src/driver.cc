#include <iostream>
#include <cstdlib>
#include <fstream>
#include <limits> 
#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"
#define WATCH_TIME
#ifdef WATCH_TIME
#include <chrono> 
#endif
using namespace std;
#define RUNTEST 1
#ifndef RUNTEST
int main(int argc, char *argv[])
{   
    if(argc != 5) 
       {
        std::cout <<argc ;
        std::cout << "Please run with input file name width height output file name"<< std::endl;
        return -1;
       }
    std::string inputfile = static_cast<std::string>(argv[1]);
    std::string widths = static_cast<std::string>(argv[2]);
    std::string heights = static_cast<std::string>(argv[3]);
    std::string outputfile = static_cast<std::string>(argv[4]);
    size_t width = 0;
    size_t height = 0;
    try
    {
            width = static_cast<size_t>(stoi(widths));   
            height = static_cast<size_t>(stoi(heights));         
    }
    catch(const std::exception& e)
    {
        std::cerr << "Width or Height is not digital" << std::endl;
        std::cerr << e.what() << '\n';
        throw runtime_error("Error parameters");
    }
  #ifdef WATCH_TIME
   using namespace std::chrono;
 high_resolution_clock::time_point t1 = high_resolution_clock::now();
  #endif  
    ElevationDataset Dataset(inputfile, width, height);
    std::cout << "Read Elevation Data" << std::endl;
    //std::cout << Dataset ;
    GrayscaleImage   GImage(Dataset);
    std::cout << "Generated Gray Image" << std::endl;
    PathImage        PImage(GImage,Dataset);
    std::cout << "Overlay Path onto Gray Image" << std::endl;
    PImage.ToPpm(outputfile);
    std::cout << "Output Path image to PPM" << std::endl;
  #ifdef WATCH_TIME
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
  std::cout << "It took me " << time_span.count() << " seconds.";
  std::cout << std::endl;
  #endif    
}
#endif 