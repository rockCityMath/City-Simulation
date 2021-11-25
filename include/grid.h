#ifndef GRID_H
#define GRID_H

#include "../include/cell.h"
#include "../include/init.h"
#include <sstream>
#include <algorithm>

///Struct to hold adjacent cell types
struct adjCellType {
    cellType topLeft;
    cellType top;
    cellType topRight;
    cellType middleLeft;
    cellType middleRight;
    cellType bottomLeft;
    cellType bottom;
    cellType bottomRight;

};

///Struct to hold adjacent cell populations
struct adjCellPopulation {
    int topLeft;
    int top;
    int topRight;
    int middleLeft;
    int middleRight;
    int bottomLeft;
    int bottom;
    int bottomRight;

};

///Struct to hold cell coords and population
struct cellInformation {
    int y;
    int x;
    int adjPopulationTotal;
    int cellPopulation;
    adjCellPopulation adjPop;

    //Sort cells by given priority list
    bool operator() (cellInformation a, cellInformation b) {

        if(a.cellPopulation != b.cellPopulation) { return(a.cellPopulation > b.cellPopulation); }
        else {

            if(a.adjPopulationTotal != b.adjPopulationTotal) { return a.adjPopulationTotal > b.adjPopulationTotal; }
            else {

                if(a.y != b.y) {return a.y < b.y; }
                else {
                    return a.x < b.x;
                }
            }
        }
    }

};

///Main grid class
class Grid{

private:
    int cols;
    int rows;
    Cell** grid; //the collection of cells that make up the grid
    bool isUpdated;

public:

    //Get+set functions
    int GetCols();
    int GetRows();
    Cell** GetGrid();
    void SetCols(int cols);
    void SetRows(int rows);
    void SetGrid(Cell** grid);
    void SetUpdated(bool isUpdated);
    bool GetUpdated();
    int GetTotalPopulation();
    int GetTotalWorkers();
	int GetTotalGoods();
	
    //Functions on a grid
    void AllocateGrid();
    void InitGrid(initData configInfo);
    void PrintGrid();
    void CleanGrid();

    //Simulation functions on a grid
    bool RunSim(initData configData);
    void ResidentialTimestep();
    void IndustrialTimestep();
    void CommercialTimestep();
    bool isAdjacent(int y ,int x, cellType type);
    bool isAdjacentPopulated(int y, int x, int amtCells, int amtPop);  //pass coords + how many adjacent cells need to have how much population
    int AdjacentPopulation(int y, int x);
    adjCellPopulation GetAdjacentCellsPopulations(int y, int x);
    bool isAdjacentPopulatedVector(int y, int x, adjCellPopulation adj, int amtCells, int amtPop);
    void PrintFinalData();
    void PrintPollutionGrid();

};




#endif