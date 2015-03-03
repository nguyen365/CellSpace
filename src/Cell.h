#include <vector>

#ifndef __CELL_H__
#define __CELL_H__
const unsigned numNeighbours = 8;
enum GameRules {Conway, Replicator, Seeds, LifeWithoutDeath, 
  Life34, Diamoeba, TwoByTwo, HighLife, DayAndNight, Morley
};

class Type
{
private:
  int ID;
public:
  Type(int id);
  int getID();
};

class Cell
{
private:
  int Coor[2];
  bool alive;
  Type* owner;
public:
  Cell(int x, int y);
  ~Cell();
  void SetOwner(Type* newOwner);
  void setAlive(bool);
  bool isAlive();
  Type getOwner();
private:
};

class World
{
private:  
  int Dimen[2];
  bool Growth[numNeighbours+1];
  bool Lives[numNeighbours+1];
  std::vector<Cell> Population;
  std::vector<Type*> Types;
public:
  World(int x, int y);
  void Init(GameRules rules);
  void AddGrowthRule(unsigned k);
  void AddLivesRule(unsigned k);
  void RemoveGrowthRule(unsigned k);
  void RemoveLivesRule(unsigned k);
  void RemoveAllRules();
  void Iterate();
  void SeedWorld(std::vector<Type> init);
  void SeedWorld(std::vector<int> init);
  void addType();
  bool CheckGrowsOn(unsigned k);
  bool CheckLivesOn(unsigned k);
  std::vector<int> getWorldWithID();
};

#endif