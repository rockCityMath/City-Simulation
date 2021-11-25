#ifndef INIT_H
#define INIT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

///Holds data from config file
struct initData {

    std::string fileName;
    int timeLimit;
    int refreshRate;

};

///Holds amount of rows and columns as calculated from CSV file
struct gridSize {

    int amtRows;
    int amtCols;

};

///Read in user specified config file and return struct with that information
initData initConfig();

///Calculates size of grid from CSV file, returns the amount of rows and columns in a struct. To be used to create the 2d array (the grid)
gridSize calcGridSize(std::string fileName);

///Print information about grid/config file, for debugging
void printInfo(gridSize gridInfo, initData configData);


#endif