#include <vector>

#ifndef __CELL_H__
#define __CELL_H__

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
  std::vector<Cell> Population;
  std::vector<Type*> Types;
public:
  World(int x, int y);
  void Iterate();
  void SeedWorld(std::vector<Type> init);
  void SeedWorld(std::vector<int> init);
  void addType();
  std::vector<int> getWorldWithID();
};

#endif