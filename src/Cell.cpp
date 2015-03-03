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
  RemoveAllRules();
  addType();
  for (int i = 0; i < y; i++)
    for (int j = 0; j < x; j++)
    {
      Population.push_back(Cell(j,i));
      Population[i * x + j].SetOwner(Types[0]);
      Population[i * x + j].setAlive(false);
    }
}

void World::Init(GameRules rules)
{
  RemoveAllRules();
  switch (rules)
  {
    case Conway:
      AddGrowthRule(3);
      AddLivesRule(2);
      AddLivesRule(3);
      break;
    case Replicator:
      AddGrowthRule(1);
      AddGrowthRule(3);
      AddGrowthRule(5);
      AddGrowthRule(7);
      AddLivesRule(1);
      AddLivesRule(3);
      AddLivesRule(5);
      AddLivesRule(7);
      break;
    case Seeds:
      AddGrowthRule(2);
      break;
    case LifeWithoutDeath:
      AddGrowthRule(3);
      AddLivesRule(0);
      AddLivesRule(1);
      AddLivesRule(2);
      AddLivesRule(3);
      AddLivesRule(4);
      AddLivesRule(5);
      AddLivesRule(6);
      AddLivesRule(7);
      AddLivesRule(8);
      break;
    case Life34:
      AddGrowthRule(3);
      AddGrowthRule(4);
      AddLivesRule(3);
      AddLivesRule(4);
      break;
    case Diamoeba:
      AddGrowthRule(3);
      AddGrowthRule(5);
      AddGrowthRule(6);
      AddGrowthRule(7);
      AddGrowthRule(8);
      AddLivesRule(5);
      AddLivesRule(6);
      AddLivesRule(7);
      AddLivesRule(8);
      break;
    case TwoByTwo:
      AddGrowthRule(3);
      AddGrowthRule(6);
      AddLivesRule(1);
      AddLivesRule(2);
      AddLivesRule(5);
      break;
    case HighLife:
      AddGrowthRule(3);
      AddGrowthRule(6);
      AddLivesRule(2);
      AddLivesRule(3);
      break;
    case DayAndNight:
      AddGrowthRule(3);
      AddGrowthRule(6);
      AddGrowthRule(7);
      AddGrowthRule(8);
      AddLivesRule(3);
      AddLivesRule(4);
      AddLivesRule(6);
      AddLivesRule(7);
      AddLivesRule(8);
      break;
    case Morley:
      AddGrowthRule(3);
      AddGrowthRule(6);
      AddGrowthRule(8);
      AddLivesRule(2);
      AddLivesRule(4);
      AddLivesRule(5);
      break;
  } 
}

void World::AddGrowthRule(unsigned k)
{
  if (k >= 0 && k <= numNeighbours)
    Growth[k] = true;
}

void World::AddLivesRule(unsigned k)
{
  if (k >= 0 && k <= numNeighbours)
    Lives[k] = true;
}

void World::RemoveGrowthRule(unsigned k)
{
  if (k >= 0 && k <= numNeighbours)
    Growth[k] = false;
}

void World::RemoveLivesRule(unsigned k)
{
  if (k >= 0 && k <= numNeighbours)
    Lives[k] = false;
}

void World::RemoveAllRules()
{
  for (unsigned i = 0; i <= numNeighbours; i++)
  {
    RemoveGrowthRule(i);
    RemoveLivesRule(i);
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
      
      if (CheckGrowsOn(count) && 
	  !(Population[Dimen[0] * j + i].isAlive()))
	newGeneration[Dimen[0] * j + i].setAlive(true);
      else if (CheckLivesOn(count) && 
	       (Population[Dimen[0] * j + i].isAlive()))
	newGeneration[Dimen[0] * j + i].setAlive(true);
      else
	newGeneration[Dimen[0] * j + i].setAlive(false);
    }
    Population = newGeneration;
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

bool World::CheckGrowsOn(unsigned k)
{
  return Growth[k];
}

bool World::CheckLivesOn(unsigned k)
{
  return Lives[k];
}