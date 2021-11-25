//Simulation functions on a grid

#ifndef SIM_CPP
#define SIM_CPP

#include "../include/grid.h"

///Run the simulation
bool Grid::RunSim(initData configData){

    //Initial variables
    int timeLimit = configData.timeLimit;
    int refreshRate = configData.refreshRate;
    int timeStep = 1;
    int availableWorkers = 0;
    int availableGoods = 0;

    //Loops for each time step, or until there is no change between timesteps
    while(timeStep <= timeLimit) {

        isUpdated = false;

        //Run timestep functions
		CommercialTimestep();
		IndustrialTimestep();
        ResidentialTimestep();
		
		//Stop simulation if theres been no update on the grid
        if(isUpdated == false) {
            std::cout << "Final Grid State" << std::endl;
            PrintGrid();
            std::cout << std::endl;
            PrintFinalData();
            break;
        }

        std::cout << "Time Step: " << timeStep << std::endl;
        std::cout << "Availible Workers: " << GetTotalWorkers() << std::endl;
        std::cout << "Availible Goods: " << GetTotalGoods() << std::endl;
        std::cout << std::endl;

        //Output grid based on refresh rate
        if(( (timeStep + 1)% refreshRate) == 0){

            PrintGrid();
            std::cout << std::endl;

        }

        timeStep++;

    }

    return true;

}

///Recieves a type of cell and its location, and returns true or false based on if that type of cell is adjacent to the current
bool Grid::isAdjacent(int y, int x, cellType type) {

    bool adjacent = false;
    adjCellType adj;

    //Get all adjacent cell types
    adj.topLeft = grid[y-1][x-1].GetCellType();
    adj.top = grid[y-1][x].GetCellType();
    adj.topRight = grid[y-1][x+1].GetCellType();
    adj.middleLeft = grid[y][x-1].GetCellType();
    adj.middleRight = grid[y][x+1].GetCellType();
    adj.bottomLeft = grid[y+1][x-1].GetCellType();
    adj.bottom = grid[y+1][x].GetCellType();
    adj.bottomRight = grid[y+1][x+1].GetCellType();

    //Set true if any cells are of type specified
    if((adj.topLeft == type) or (adj.top == type) or (adj.topRight == type) or (adj.middleLeft == type) or (adj.middleRight == type)
       or (adj.bottomLeft == type) or (adj.bottom == type) or (adj.bottomRight == type)) {
        adjacent = true;
    }

    return adjacent;
}

///Receives coords on the grid, as well as the amount of adjacent cells of specified population needed to return true
bool Grid::isAdjacentPopulated(int y, int x, int amtCells, int amtPop) {

    bool meetsRequirements = false;
    int cellsMeetingRequirements = 0;
    adjCellPopulation adj;

    //Get all adjacent cell populations
    adj.topLeft = grid[y-1][x-1].GetPopulation();
    adj.top = grid[y-1][x].GetPopulation();
    adj.topRight = grid[y-1][x+1].GetPopulation();
    adj.middleLeft = grid[y][x-1].GetPopulation();
    adj.middleRight = grid[y][x+1].GetPopulation();
    adj.bottomLeft = grid[y+1][x-1].GetPopulation();
    adj.bottom = grid[y+1][x].GetPopulation();
    adj.bottomRight = grid[y+1][x+1].GetPopulation();

    if(adj.topLeft >= amtPop) { cellsMeetingRequirements++; }
    if(adj.top >= amtPop) { cellsMeetingRequirements++; }
    if(adj.topRight >= amtPop) { cellsMeetingRequirements++; }
    if(adj.middleLeft >= amtPop) { cellsMeetingRequirements++; }
    if(adj.middleRight >= amtPop) { cellsMeetingRequirements++; }
    if(adj.bottomLeft >= amtPop) { cellsMeetingRequirements++; }
    if(adj.bottom >= amtPop) { cellsMeetingRequirements++; }
    if(adj.bottomRight >= amtPop) { cellsMeetingRequirements++; }

    if(cellsMeetingRequirements >= amtCells) {

        meetsRequirements = true;

    }

    return meetsRequirements;

}

///Get total population currently in the simulation
int Grid::GetTotalPopulation() {

    int population = 0;

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
				
			   if (grid[i][j].GetCellType() == 'R')
					population = population + grid[i][j].GetPopulation();

        }
    }

    return population;

}

///Gets total amount of workers without a job on the grid
int Grid::GetTotalWorkers() {

    int workers = GetTotalPopulation();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){

            if(grid[i][j].GetCellType() == 'I' || grid[i][j].GetCellType() == 'C') {

                workers = workers - grid[i][j].GetWorkers();

            }
        }
    }

    return workers;
}

///Gets total amount of goods available for commercial
int Grid::GetTotalGoods() {
	
	int goods = 0;
	int numCommercialCells = 0;
	
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			
			if(grid[i][j].GetCellType() == 'I' || grid[i][j].GetCellType() == 'C') {
				
				goods += grid[i][j].GetGoods();
				
			}
		}
	}
	
	return goods;
}
		
///Returns total adjacent population of a given cell
int Grid::AdjacentPopulation(int y, int x) {

    adjCellPopulation adj;
    int totalAdjacentPopulation = 0;

    //Add all adjacent cell's populations to the total
    totalAdjacentPopulation = totalAdjacentPopulation + grid[y-1][x-1].GetPopulation();
    totalAdjacentPopulation = totalAdjacentPopulation + grid[y-1][x].GetPopulation();
    totalAdjacentPopulation = totalAdjacentPopulation + grid[y-1][x+1].GetPopulation();
    totalAdjacentPopulation = totalAdjacentPopulation + grid[y][x-1].GetPopulation();
    totalAdjacentPopulation = totalAdjacentPopulation + grid[y][x+1].GetPopulation();
    totalAdjacentPopulation = totalAdjacentPopulation + grid[y+1][x-1].GetPopulation();
    totalAdjacentPopulation = totalAdjacentPopulation + grid[y+1][x].GetPopulation();
    totalAdjacentPopulation = totalAdjacentPopulation + grid[y+1][x+1].GetPopulation();

    return totalAdjacentPopulation;

}

///Returns struct holding all adjacent cell population values
adjCellPopulation Grid::GetAdjacentCellsPopulations(int y, int x) {

    adjCellPopulation adj;

    //Get all adjacent cell populations
    adj.topLeft = grid[y-1][x-1].GetPopulation();
    adj.top = grid[y-1][x].GetPopulation();
    adj.topRight = grid[y-1][x+1].GetPopulation();
    adj.middleLeft = grid[y][x-1].GetPopulation();
    adj.middleRight = grid[y][x+1].GetPopulation();
    adj.bottomLeft = grid[y+1][x-1].GetPopulation();
    adj.bottom = grid[y+1][x].GetPopulation();
    adj.bottomRight = grid[y+1][x+1].GetPopulation();

    return adj;

}

///Function to use with the vector, pass in an adjCellPopulation struct to determine bool
bool Grid::isAdjacentPopulatedVector(int y, int x, adjCellPopulation adj, int amtCells, int amtPop) {

    bool meetsRequirements = false;
    int cellsMeetingRequirements = 0;

    if(adj.topLeft >= amtPop) { cellsMeetingRequirements++; }
    if(adj.top >= amtPop) { cellsMeetingRequirements++; }
    if(adj.topRight >= amtPop) { cellsMeetingRequirements++; }
    if(adj.middleLeft >= amtPop) { cellsMeetingRequirements++; }
    if(adj.middleRight >= amtPop) { cellsMeetingRequirements++; }
    if(adj.bottomLeft >= amtPop) { cellsMeetingRequirements++; }
    if(adj.bottom >= amtPop) { cellsMeetingRequirements++; }
    if(adj.bottomRight >= amtPop) { cellsMeetingRequirements++; }

    if(cellsMeetingRequirements >= amtCells) {

        meetsRequirements = true;

    }

    return meetsRequirements;

}

#endif