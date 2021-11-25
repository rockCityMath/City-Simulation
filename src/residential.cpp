#ifndef RESIDENTIAL_CPP
#define RESIDENTIAL_CPP

#include "../include/grid.h"

///Function to be run at each timestep to update the residential cells
void Grid::ResidentialTimestep(){

    //Initial variables
    int population = 0;
    std::vector<cellInformation> cellsList;
    cellInformation cellInfo;

    //Get vector of cells we are going to operate on with all the information we will need
    //We must grab this information now before it gets updated on the grid
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            if(grid[i][j].GetCellType() == 'R'){

                cellInfo.adjPopulationTotal = AdjacentPopulation(i, j);
                cellInfo.cellPopulation = grid[i][j].GetPopulation();
                cellInfo.y = i;
                cellInfo.x = j;
                cellInfo.adjPop = GetAdjacentCellsPopulations(i, j);

                cellsList.push_back(cellInfo);

            }
        }
    }

    //Sort the vector so that the iterator will operate on cells in appropriate order
    std::sort(cellsList.begin(), cellsList.end(), cellInfo);

    //Iterate through cells and apply region specific logic
    for (auto it = begin (cellsList); it != end (cellsList); ++it) {

        //Conditions from given list
        if( (it->cellPopulation == 4) and (isAdjacentPopulatedVector(it->y, it->x, it->adjPop, 8, 4)) ) {

            grid[it->y][it->x].IncreasePopulation();
            isUpdated = true;
        }
        if((it->cellPopulation == 3) and (isAdjacentPopulatedVector(it->y, it->x, it->adjPop ,6,  3)) ){

            grid[it->y][it->x].IncreasePopulation();
            isUpdated = true;
        }
        if((it->cellPopulation == 2) and (isAdjacentPopulatedVector(it->y, it->x, it->adjPop ,4,  2)) ){

            grid[it->y][it->x].IncreasePopulation();
            isUpdated = true;
        }
        if((it->cellPopulation == 1) and (isAdjacentPopulatedVector(it->y, it->x, it->adjPop ,2,  1)) ){

            grid[it->y][it->x].IncreasePopulation();
            isUpdated = true;
        }
        if((it->cellPopulation == 0) and (isAdjacent(it->y, it->x, powerLine) or isAdjacent(it->y, it->x, powerOverRoad)) ) {

            grid[it->y][it->x].IncreasePopulation();
            isUpdated = true;
        }
        if((it->cellPopulation == 0) and (isAdjacentPopulatedVector(it->y, it->x, it->adjPop ,1,  1)) ){

            grid[it->y][it->x].IncreasePopulation();
            isUpdated = true;
        }

    }

}

#endif