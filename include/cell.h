#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

///Enum for cell types
enum cellType {

    residential='R',
    industrial='I',
    commercial='C',
    road='-',
    powerLine='T',
    powerOverRoad='#',
    powerPlant='P',
    bound='|',
    none=' '


};

///Class for a single cell on the grid
//Grid is made of an array of pointers to arrays of Cells
class Cell {

private:

    cellType type;
    int pollution;
    int population;
    int workerCount;
    int goodsCount;

public:

    ///Default + parameterized constructor
    Cell();

    ///Get/set function declarations
    cellType GetCellType();
    int GetPopulation();
    int GetPollution();
    char GetCellChar();
    int GetWorkers();
	int GetGoods();
    
    void SetCellType(cellType type);
    void SetPopulation(int population);
    void SetPollution(int pollution);
    void SetWorkers(int workers);

    ///Other functions
    void PrintInfo();
    void IncreasePopulation();
    void IncreaseWorkers();
    void DecreaseWorkers();
	void IncreaseGoods();
    void DecreaseGoods();

};

#endif