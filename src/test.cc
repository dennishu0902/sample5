#ifdef RUNTEST
#include <algorithm>
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"
TEST_CASE("Sample0","Color-1")
{
    Color color1(2,3,10);
    const int red   = 2;
    const int green = 3;
    const int blue  = 10;
    REQUIRE((red==color1.Red()));
    REQUIRE((green==color1.Green()));
    REQUIRE((blue==color1.Blue()));
}
TEST_CASE("Sample1","Color-2")
{
    CHECK_THROWS(Color(2,3,256));
    CHECK_THROWS(Color(-1,3,256));
    CHECK_THROWS(Color(2,-1,256));
}
TEST_CASE("Sample2","elevationdata-2")
{
    std::vector<std::vector<int>> data1={
        {1974, 1979, 1939, 1892, 1864, 1850, 1838, 1822, 1816, 1811}, 
        {1819, 1808, 1780, 1770, 1757, 1760, 1755, 1729, 1723, 1720}, 
        {1710, 1701, 1694, 1693, 1692, 1699, 1699, 1694, 1685, 1677},
        {1672, 1670, 1659, 1641, 1630, 1624, 1619, 1606, 1606, 1602}, 
        {1602, 1604, 1609, 1618, 1623, 1624, 1629, 1637, 1646, 1657}, 
        {1670, 1685, 1705, 1727, 1753, 1781, 1818, 1859, 1911, 1966}, 
        {2013, 2120, 2252, 2325, 2276, 2236, 2245, 2199, 2154, 2108}, 
        {2078, 2009, 1976, 1929, 1902, 1880, 1874, 1870, 1838, 1838}, 
        {1819, 1777, 1739, 1711, 1689, 1671, 1642, 1610, 1600, 1597}, 
        {1588, 1558, 1533, 1513, 1499, 1479, 1465, 1456, 1449, 1421}, 
        {1402, 1388, 1373, 1361, 1354, 1343, 1329, 1321, 1313, 1308}, 
        {1304, 1302, 1301, 1300, 1299, 1298, 1297, 1297, 1297, 1297}, 
        {1296, 1297, 1297, 1296, 1296, 1296, 1296, 1295, 1295, 1295}, 
        {1295, 1295, 1295, 1294, 1294, 1294, 1294, 1294, 1294, 1294}, 
        {1295, 1294, 1294, 1294, 1294, 1294, 1294, 1295, 1294, 1295}, 
        {1295, 1295, 1295, 1295, 1295, 1295, 1295, 1295, 1295, 1295},
    };
    std::vector<std::vector<size_t>> paths=
      {{0,0,0,0,0,0,0,0,0,0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
       {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},{3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
       {4, 4, 4, 4, 4, 4, 4, 4, 4, 4},{5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
       {6, 7, 7, 7, 7, 7, 7, 7, 7, 7},{7, 6, 6, 6, 6, 6, 6, 6, 6, 6},
       {8, 8, 8, 8, 8, 8, 8, 8, 8, 8},{9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
       {10, 10, 10, 10, 10, 10, 10, 10, 10, 10},{11, 11, 11, 11, 11, 11, 11, 11, 11, 11}, 
       {12, 12, 12, 12, 12, 12, 12, 12, 12, 12},{13, 13, 13, 13, 13, 13, 13, 13, 13, 13},
       {14, 15, 15, 15, 15, 15, 15, 15, 15, 15},{15, 15, 15, 15, 15, 15, 15, 15, 15, 15}};
    size_t best_row = 14;
    int ele_chane = 0;

    ElevationDataset ed("dataset1.txt", 10,16);
    REQUIRE(std::equal(data1.begin(),data1.end(),ed.GetData().begin(),ed.GetData().end()));
    CHECK_NOTHROW(GrayscaleImage(ed));
    GrayscaleImage   GImage(ed);
    CHECK_NOTHROW(PathImage(GImage,ed));
    PathImage        PImage(GImage,ed);
    for(size_t i=0; i< PImage.Paths().size(); i++)
    {   Path cur_path = PImage.Paths().at(i);
        REQUIRE(std::equal(paths.at(i).begin(),paths.at(i).end(),
         cur_path.GetPath().begin(),cur_path.GetPath().end()));
    }
    CHECK_NOTHROW(ElevationDataset("dataset1.txt", 10,16));
    CHECK_THROWS(ElevationDataset("dataset1.txt", 10,15));
    CHECK_THROWS(ElevationDataset("dataset1.txt", 10,17));
    CHECK_THROWS(ElevationDataset("dataset2.txt", 10,16));
}


#endif 