//Functions on cells

#include "../include/cell.h"

Cell::Cell(){
    type = none;
    pollution = 0;
    population = 0;

}

//Get+set functions
cellType Cell::GetCellType() { return type; }
int Cell::GetPopulation() { return population; }
int Cell::GetPollution() { return pollution; }
char Cell::GetCellChar() { return type; }
void Cell::SetCellType(cellType type) { this->type = type; }
void Cell::SetPopulation(int population) { this->population = population; }
void Cell::SetPollution(int pollution) { this->pollution = pollution; }
int Cell::GetWorkers() { return workerCount; }
int Cell::GetGoods() { return goodsCount; }

//Other functions
void Cell::PrintInfo() {

    std::cout << "Cell Type: " << GetCellType() << std::endl;
    std::cout << "Cell Population: " << GetPopulation() << std::endl;
    std::cout << "Cell Pollution: " << GetPollution() << std::endl;

}

void Cell::IncreasePopulation(){

    population++;

}

void Cell::SetWorkers(int workers){

    workerCount = workers;

}

void Cell::IncreaseWorkers(){
    workerCount++;
}

void Cell::DecreaseWorkers(){
    workerCount--;
}

void Cell::IncreaseGoods(){
	goodsCount++;
}

void Cell::DecreaseGoods(){
    goodsCount--;
}
