#ifndef COMMERCIAL_CPP
#define COMMERCIAL_CPP

#include "../include/grid.h"

//Function to run each commercial cell at each timestep
void Grid::CommercialTimestep()
{
    std::vector<cellInformation> cellsList;
    cellInformation cellInfo;

    //Get vector of cells we are going to operate on with all the information we will need
    //We must grab this information now before it gets updated on the grid
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            if(grid[i][j].GetCellType() == 'C'){

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

	for (auto it = begin (cellsList); it != end (cellsList); ++it) 
	{
			if((isAdjacent(it->y, it->x, powerLine) || isAdjacent(it->y, it->x, powerOverRoad)) && it->cellPopulation == 0 && GetTotalWorkers() >= 1 && GetTotalGoods() >= 1)
			{
				grid[it->y][it->x].IncreasePopulation();
				grid[it->y][it->x].IncreaseWorkers();
				grid[it->y][it->x].DecreaseGoods();
				
				isUpdated = true;
			}
			else if(it->cellPopulation == 0 && isAdjacentPopulatedVector(it->y, it->x, it->adjPop, 1, 1) && GetTotalWorkers() >= 1 && it->cellPopulation == 0 && GetTotalGoods() >= 1)
			{
				grid[it->y][it->x].IncreasePopulation();
				grid[it->y][it->x].IncreaseWorkers();
				grid[it->y][it->x].DecreaseGoods();
				
				isUpdated = true;
			}
			else if(it->cellPopulation == 1 && isAdjacentPopulatedVector(it->y, it->x, it->adjPop, 2, 1) && GetTotalWorkers() >= 1 && GetTotalGoods() >= 1)
			{
				grid[it->y][it->x].IncreasePopulation();
				grid[it->y][it->x].IncreaseWorkers();
				grid[it->y][it->x].DecreaseGoods();
				
				isUpdated = true;
			}
	}
}

#endif