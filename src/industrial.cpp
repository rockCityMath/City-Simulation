#ifndef INDUSTRIAL_CPP
#define INDUSTRIAL_CPP

#include "../include/grid.h"

void Grid::IndustrialTimestep()
{
	std::vector<cellInformation> cellsList;
	cellInformation cellInfo;

    //Get vector of cells we are going to operate on with all the information we will need
    //We must grab this information now before it gets updated on the grid
	for(int i = 0; i < rows; i++) 
	{
        for (int j = 0; j < cols; j++) 
		{

            if(grid[i][j].GetCellType() == 'I')
			{
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
	for (auto it = begin (cellsList); it != end (cellsList); ++it)
	{

	    /*  -------- Debugging statements, please leave in case we need later -------
        std::cout << std::endl;
        std::cout << "----TRUTH TABLE-----" << std::endl;
        std::cout << "Coords: " << it->y << " " << it->x << " Population: " << it->cellPopulation << std::endl;
        if(isAdjacentPopulatedVector(it->y, it->x, it->adjPop ,1,  1)) {std::cout << "isAdPop11" << std::endl; }
        if(isAdjacentPopulatedVector(it->y, it->x, it->adjPop ,4,  2)) {std::cout << "isAdPop42" << std::endl; }
        if(isAdjacentPopulatedVector(it->y, it->x, it->adjPop ,2,  1)) {std::cout << "isAdPop21" << std::endl; }
        if(isAdjacent(it->y, it->x, powerLine) or isAdjacent(it->y, it->x, powerOverRoad)){std::cout << "Powered" << std::endl; }
        */

        if ( (it->cellPopulation == 2) and (isAdjacentPopulatedVector(it->y, it->x, it->adjPop, 4, 2)) and (GetTotalWorkers() >= 2) )
        {
            grid[it->y][it->x].IncreasePopulation();
            grid[it->y][it->x].IncreaseGoods();
            grid[it->y][it->x].IncreaseWorkers();
            grid[it->y][it->x].IncreaseWorkers();

            isUpdated = true;
        }
        else if ( (it->cellPopulation == 1) and (isAdjacentPopulatedVector(it->y, it->x, it->adjPop, 2, 1)) and (GetTotalWorkers() >= 2) )
        {
            grid[it->y][it->x].IncreasePopulation();
            grid[it->y][it->x].IncreaseGoods();
            grid[it->y][it->x].IncreaseWorkers();
            grid[it->y][it->x].IncreaseWorkers();

            isUpdated = true;
        }
		else if ( (it->cellPopulation == 0) and (isAdjacent(it->y, it->x, powerLine) or isAdjacent(it->y, it->x, powerOverRoad)) and (GetTotalWorkers() >= 2) )
		{
			grid[it->y][it->x].IncreasePopulation();
			grid[it->y][it->x].IncreaseGoods();
			grid[it->y][it->x].IncreaseWorkers();
			grid[it->y][it->x].IncreaseWorkers();
			
			isUpdated = true;
		}
		else if ( (it->cellPopulation == 0) and (isAdjacentPopulatedVector(it->y, it->x, it->adjPop, 1, 1)) and (GetTotalWorkers() >= 2) )
		{
			grid[it->y][it->x].IncreasePopulation();
			grid[it->y][it->x].IncreaseGoods();
			grid[it->y][it->x].IncreaseWorkers();
			grid[it->y][it->x].IncreaseWorkers();
			
			isUpdated = true;
		}

	} //for
			
} //function

#endif
