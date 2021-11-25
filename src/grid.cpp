//Main functions on the grid itself
/*     --IMPORTANT TO NOTE THAT GRID IS ACCESSED IN GRID[Y][X] SYNTAX--     */
#ifndef GRID_CPP
#define GRID_CPP

#include "../include/grid.h"
#include "../include/cell.h"

//Class set/get functions
int Grid::GetCols() {return cols; }
int Grid::GetRows() {return rows; }
Cell** Grid::GetGrid() {return grid; }
void Grid::SetGrid(Cell **grid) {this->grid = grid; }
void Grid::SetCols(int cols) {this->cols = cols; }
void Grid::SetRows(int rows) {this->rows = rows; }
void Grid::SetUpdated(bool isUpdated) {this->isUpdated = isUpdated; }
bool Grid::GetUpdated() {return isUpdated; }

///Allocate memory for the grid (array of pointers to arrays) (allows for grid[y][x] syntax) (needed because array is dynamic)
void Grid::AllocateGrid() {

    grid = new Cell*[rows];      //creates an array of pointers to Cell objects (y axis)
    for (int i = 0; i < rows; i++){

        grid[i] = new Cell[cols];    //creates a new array of cells at each previous array that will act as x axis

    }

}

///Uses CSV file to initialize the grid with specified cell types
void Grid::InitGrid(initData configInfo) {

    std::cout << "Initializing grid..." << std::endl;
    std::fstream gridFile;
    gridFile.open(configInfo.fileName);

    //Create temporary grid to read into, initialized with spaces
    char gridIn[rows][cols];
    gridIn[rows][cols] = ' ' ;

    //Read in characters to temp board
    for (int i = 1; i < rows - 1; i++) {

        std::string fileLine;
        std::getline(gridFile, fileLine); //get a whole line from the file
        std::istringstream streamLine(fileLine); //assign that line to a string stream, works as if it was a direct input

        for (int j = 1; j < cols - 1; j++) {

            std::string val = " ";
            std::getline(streamLine, val, ',');   //use previous string stream, assign the value to "val", use comma as delim
            std::istringstream toGrid(val);                  //create a new string stream with just the character we extracted
            char newChar = ' ';
            toGrid >> newChar;
            gridIn[i][j] = newChar;

        }
    }

    //Assign values from the temp grid to the real grid
    for (int i = 1; i < rows - 1; i++){

        for(int j = 1; j < cols - 1; j++){

            grid[i][j].SetPollution(0);
            grid[i][j].SetPopulation(0);

            //Assign the real grid its cell types based on the type of cell from the temp grid
            if (gridIn[i][j] == 'R') { grid[i][j].SetCellType(residential ); }
            else if (gridIn[i][j] == 'I') { grid[i][j].SetCellType(industrial ); }
            else if (gridIn[i][j] == 'C') { grid[i][j].SetCellType(commercial ); }
            else if (gridIn[i][j] == '-') { grid[i][j].SetCellType(road ); }
            else if (gridIn[i][j] == 'T') { grid[i][j].SetCellType(powerLine ); }
            else if (gridIn[i][j] == '#') { grid[i][j].SetCellType(powerOverRoad ); }
            else if (gridIn[i][j] == 'P') { grid[i][j].SetCellType(powerPlant ); }
            else { grid[i][j].SetCellType(none); }

        }
    }
}

///Prints entire grid as cell type chars
void Grid::PrintGrid() {

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){

            if(grid[i][j].GetCellType() == 'R' and grid[i][j].GetPopulation() > 0) {
                std::cout << grid[i][j].GetPopulation() << " ";
            }
            else if (grid[i][j].GetCellType() == 'I' and grid[i][j].GetPopulation() > 0) {
                std::cout << grid[i][j].GetPopulation() << " ";
            }
            else if (grid[i][j].GetCellType() == 'C' and grid[i][j].GetPopulation() > 0) {
                std::cout << grid[i][j].GetPopulation() << " ";
            }
            else{
                std::cout << grid[i][j].GetCellChar() << " ";
            }

        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

///Deallocate the memory used by the grid
void Grid::CleanGrid() {

    for (int i = 0; i < rows; i++) {

        delete[] grid[i];

    }
    delete[] grid;

}

///Prints the pollution grid at the end of the simulation
void Grid::PrintPollutionGrid() {
    int pollutionMatrix[rows][cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j].GetCellType() == 'I' && grid[i][j].GetPopulation() > 0) {
                pollutionMatrix[i][j] = grid[i][j].GetPopulation();
            }
            else {
                pollutionMatrix[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (pollutionMatrix[i][j] > 1) {
                if (pollutionMatrix[i - 1][j + 1] == 0) {
                    pollutionMatrix[i - 1][j + 1] = pollutionMatrix[i][j] - 1;
                    grid[i - 1][j + 1].SetPollution(pollutionMatrix[i][j] - 1);
                }
                if (pollutionMatrix[i][j + 1] == 0) {
                    pollutionMatrix[i][j + 1] = pollutionMatrix[i][j] - 1;
                    grid[i][j + 1].SetPollution(pollutionMatrix[i][j] - 1);
                }
                if (pollutionMatrix[i + 1][j + 1] == 0) {
                    pollutionMatrix[i + 1][j + 1] = pollutionMatrix[i][j] - 1;
                    grid[i + 1][j + 1].SetPollution(pollutionMatrix[i][j] - 1);
                }
                if (pollutionMatrix[i - 1][j] == 0) {
                    pollutionMatrix[i - 1][j] = pollutionMatrix[i][j] - 1;
                    grid[i - 1][j].SetPollution(pollutionMatrix[i][j] - 1);
                }
                if (pollutionMatrix[i + 1][j] == 0) {
                    pollutionMatrix[i + 1][j] = pollutionMatrix[i][j] - 1;
                    grid[i + 1][j].SetPollution(pollutionMatrix[i][j] - 1);
                }
                if (pollutionMatrix[i - 1][j - 1] == 0) {
                    pollutionMatrix[i - 1][j - 1] = pollutionMatrix[i][j] - 1;
                    grid[i - 1][j - 1].SetPollution(pollutionMatrix[i][j] - 1);
                }
                if (pollutionMatrix[i][j - 1] == 0) {
                    pollutionMatrix[i][j - 1] = pollutionMatrix[i][j] - 1;
                    grid[i][j - 1].SetPollution(pollutionMatrix[i][j] - 1);
                }
                if (pollutionMatrix[i + 1][j - 1] == 0) {
                    pollutionMatrix[i + 1][j - 1] = pollutionMatrix[i][j] - 1;
                    grid[i + 1][j - 1].SetPollution(pollutionMatrix[i][j] - 1);
                }
            }
        }
    }
    for (int i = 1; i < rows-1; i++) {
        std::cout << "  ";
        for (int j = 1; j < cols-1; j++) {
            std::cout << pollutionMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

///Prints the last outputs of the simulation
void Grid::PrintFinalData() {
    int totalResidentialPop = 0;
    int totalIndustrialPop = 0;
    int totalCommercialPop = 0;
    int totalPollution = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            totalPollution = totalPollution + grid[i][j].GetPollution();
            if (grid[i][j].GetCellType() == 'R') {
                totalResidentialPop = totalResidentialPop + grid[i][j].GetPopulation();
            }
            else if (grid[i][j].GetCellType() == 'I') {
                totalIndustrialPop = totalIndustrialPop + grid[i][j].GetPopulation();
            }
            else if (grid[i][j].GetCellType() == 'C') {
                totalCommercialPop = totalCommercialPop + grid[i][j].GetPopulation();
            }
        }
    }

    std::cout << "The total populations for the region are:" << std::endl;
    std::cout << "Residential: " << totalResidentialPop << std::endl;
    std::cout << "Industrial: " << totalIndustrialPop << std::endl;
    std::cout << "Commercial: " << totalCommercialPop << std::endl;
    //std::cout << "The total amount of pollution in the region is " << totalPollution << " units." << std::endl;
    //std::cout << "Please enter the diagonal corners of the area you wish to have more information about. (MinX = 0, MinY = 0, MaxX = 7, MaxY = 7)" << std::endl;
}

#endif