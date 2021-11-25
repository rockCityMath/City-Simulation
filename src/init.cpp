//Functions to initialize the program
#ifndef INIT_CPP
#define INIT_CPP

#include "../include/init.h"

///Read in user specified config file and return struct with that information
initData initConfig(){

    bool validFile = false;
    std::fstream configFile;
    std::string fileName;
    initData returnInfo;

    //Get config file from user and check that it is valid
    while( validFile == false ) {

        std::cout << "Enter config file name: ";
        std::getline(std::cin, fileName);
        configFile.open(fileName);

        if(configFile.good()) {
            std::cout << "Valid config file!" << std::endl;
            validFile = true; }
        else { std::cout << "Invalid config file..." << std::endl; }

    }

    //Init variables for config file
    std::string layoutFile= " ";
    int timeLimit = 0;
    int refreshRate = 0;

    //Read in variable from config file (ignore until semicolon found, then assign variable)
    configFile.ignore(256, ':');
    std::getline(configFile, layoutFile);

    configFile.ignore(256, ':');
    configFile >> timeLimit;

    configFile.ignore(256, ':');
    configFile >> refreshRate;
    configFile.close();

    //Save data from config file to initData struct so that we can return it to the main function
    returnInfo.fileName = layoutFile;
    returnInfo.timeLimit = timeLimit;
    returnInfo.refreshRate = refreshRate;

    return returnInfo;
}

///Calculates size of grid from CSV file, returns the amount of rows and columns in a struct. To be used to create the 2d array (the grid)
gridSize calcGridSize(std::string fileName){

    //Open file specified by config file
    std::fstream layoutFile;
    layoutFile.open(fileName);

    //Tell user if layout file is valid
    if(layoutFile.good()){ std::cout << "Valid Layout File..." << std::endl; }
    else { std::cout << "Invalid Layout File..." << std::endl; }

    int temp;
    int amtCols = 0;
    int amtRows = 0;
    std::string tempStr;

    //Get amount of rows
    //Each time the program can read in a row from the CSV file, increase amtRows by 1
    while( std::getline(layoutFile, tempStr) ) {

        amtRows++;

    }

    //Reload file since we just read to the end of it to find rows, definitely a better way to do this
    layoutFile.close();
    layoutFile.open(fileName);

    //Get amount of columns
    //Amount of commas + 1
    std::getline(layoutFile, tempStr);
    amtCols = std::count(tempStr.begin(), tempStr.end(), ',');
    amtCols++;

    gridSize returnInfo;
    returnInfo.amtRows = amtRows;
    returnInfo.amtCols = amtCols;

    layoutFile.close();

    return returnInfo;

}


void printInfo(gridSize gridInfo, initData configData){

    //Output config data information for checking/debugging
    std::cout << std::endl << "------INFO-------" << std::endl;
    std::cout << "Layout File: " << configData.fileName << std::endl;
    std::cout << "Time Limit: " << configData.timeLimit << std::endl;
    std::cout << "Refresh Rate: " << configData.refreshRate << std::endl << std::endl;

    //Output grid size information for checking/debugging
    std::cout << "amtCols: " << gridInfo.amtCols << std::endl;
    std::cout << "amtRows: " << gridInfo.amtRows << std::endl << std::endl;

}


#endif