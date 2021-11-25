//Main functionality of the program, contains high level functions (functions on a grid, etc..)

#include "../include/main.h"

int main() {

    Grid grid;

    //Read in data from config file and assign it to appropriate variables
    initData configData = initConfig();
    gridSize gridInfo = calcGridSize(configData.fileName);
    grid.SetRows(gridInfo.amtRows + 2); //create an extra row/col of cells on each side for boundary
    grid.SetCols(gridInfo.amtCols + 2);

    //Allocate memory for, initialize, and print grid
    grid.AllocateGrid();
    grid.InitGrid(configData);
    std::cout << "Initial Region State" << std::endl;
    grid.PrintGrid();

    //Main logic, runs until sim has finished
    if (grid.RunSim(configData)) {
        std::cout << "Simulation Complete!" << std::endl;
    }
    else {
        std::cout << "Simulation failed!" << std::endl;
    }


    //Cleanup
    grid.CleanGrid();

    return 0;


}