#include "Cell.h"

Type::Type(int id)
  : ID(id)
{
 ; 
}

int Type::getID()
{
  return ID;
}
  
Cell::Cell(int x, int y)
{
  Coor[0] = x;
  Coor[1] = y;
  owner = 0;
}

Cell::~Cell()
{
  ;
}

void Cell::SetOwner(Type* newOwner)
{
  owner = newOwner;
}

void Cell::setAlive(bool state)
{
  alive = state;
}

bool Cell::isAlive()
{
  return alive;
}

Type Cell::getOwner()
{
  return *owner;
}

World::World(int x, int y)
{
  Dimen[0] = x;
  Dimen[1] = y;
  addType();
  for (int i = 0; i < y; i++)
    for (int j = 0; j < x; j++)
    {
      Population.push_back(Cell(j,i));
      Population[i * x + j].SetOwner(Types[0]);
      Population[i * x + j].setAlive(false);
    }
}

void World::Iterate()
{
  std::vector<Cell> newGeneration = Population;
   for (int i = 0; i < Dimen[0]; i++)
    for (int j = 0; j < Dimen[1]; j++)
    {
      /*
      std::vector<int>neighbourCount(Types.size(), 0);
      if (i - 1 >= 0 && j - 1 >= 0)
	neighbourCount[Population[Dimen[0] * (j-1) + (i-1)].getOwner().getID()] =
	neighbourCount[Population[Dimen[0] * (j-1) + (i-1)].getOwner().getID()] + 1;
      
      if (i - 1 >= 0)
	neighbourCount[Population[Dimen[0] * (j) + (i-1)].getOwner().getID()] =
	neighbourCount[Population[Dimen[0] * (j) + (i-1)].getOwner().getID()] + 1;
      
      if (j - 1 >= 0)
	neighbourCount[Population[Dimen[0] * (j-1) + (i)].getOwner().getID()] =
	neighbourCount[Population[Dimen[0] * (j-1) + (i)].getOwner().getID()] + 1;
      
      
      if (i + 1 >= 0 && j + 1 >= 0)
	neighbourCount[Population[Dimen[0] * (j+1) + (i+1)].getOwner().getID()] =
	neighbourCount[Population[Dimen[0] * (j+1) + (i+1)].getOwner().getID()] + 1;
      
      
      if (i + 1 >= 0)
	neighbourCount[Population[Dimen[0] * (j) + (i+1)].getOwner().getID()] =
	neighbourCount[Population[Dimen[0] * (j) + (i+1)].getOwner().getID()] + 1;
      
      
      if (j + 1 >= 0)
	neighbourCount[Population[Dimen[0] * (j+1) + (i)].getOwner().getID()] =
	neighbourCount[Population[Dimen[0] * (j+1) + (i)].getOwner().getID()] + 1;
      
      
      if (i + 1 >= 0 && j - 1 >= 0)
	neighbourCount[Population[Dimen[0] * (j-1) + (i+1)].getOwner().getID()] =
	neighbourCount[Population[Dimen[0] * (j-1) + (i+1)].getOwner().getID()] + 1;
      
      
      if (i - 1 >= 0 && j + 1 >= 0)
	neighbourCount[Population[Dimen[0] * (j+1) + (i-1)].getOwner().getID()] =
	neighbourCount[Population[Dimen[0] * (j+1) + (i-1)].getOwner().getID()] + 1;
      
      int newID = 0;
      int count = 0;
      for (unsigned k = 0; k < neighbourCount.size(); k++)
	if (neighbourCount[k] > count)
	{
	  newID = k;
	  count = neighbourCount[k];
	}
      newGeneration[Dimen[0] * (j) + (i)].SetOwner(Types[newID]);
      */
      int count = 0;
      if (i - 1 >= 0 && j - 1 >= 0 && Population[Dimen[0] * (j-1) + (i-1)].isAlive())
	count++;
      if (i - 1 >= 0 && Population[Dimen[0] * (j) + (i-1)].isAlive())
	count++;
      if (j - 1 >= 0 && Population[Dimen[0] * (j-1) + (i)].isAlive())
	count++;
      if (i + 1 < Dimen[0] && j + 1 < Dimen[1] && Population[Dimen[0] * (j+1) + (i+1)].isAlive())
	count++;
      if (i + 1 < Dimen[0] && Population[Dimen[0] * (j) + (i+1)].isAlive())
	count++;
      if (j + 1 < Dimen[1] && Population[Dimen[0] * (j+1) + (i)].isAlive())
	count++;
      if (i + 1 < Dimen[0] && j - 1 >= 0 && Population[Dimen[0] * (j-1) + (i+1)].isAlive())
	count++;
      if (i - 1 >= 0 && j + 1 < Dimen[1] && Population[Dimen[0] * (j+1) + (i-1)].isAlive())
	count++;
      
      if (count == 3 && !(Population[Dimen[0] * j + i].isAlive()))
	Population[Dimen[0] * j + i].setAlive(true);
      else if ((count == 2 || count == 3) && 
	      (Population[Dimen[0] * j + i].isAlive()))
	Population[Dimen[0] * j + i].setAlive(true);
      else
	Population[Dimen[0] * j + i].setAlive(false);
    }
    //Population = newGeneration;
}

void World::SeedWorld(std::vector<int> init)
{
  for (unsigned i = 0; i < init.size(); i++)
    if (i < Population.size())
      Population[i].setAlive(bool(init[i]));
}

void World::addType()
{
  Type* newType = new Type(Types.size());
  Types.push_back(newType);
}

std::vector<int> World::getWorldWithID()
{
  std::vector<int> retVal;
  for (unsigned i = 0; i < Population.size(); i++)
    if (Population[i].isAlive())
      retVal.push_back(1);
    else
      retVal.push_back(0);
  return retVal;
}
