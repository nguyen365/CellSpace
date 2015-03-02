#include <vector>

#ifndef __CELL_H__
#define __CELL_H__

class Colour
{
private:
  int ID;
public:
  Colour(int id);
  int getID();
};

class Cell
{
private:
  int Coor[2];
  bool alive;
  Colour* owner;
public:
  Cell(int x, int y);
  ~Cell();
  void SetOwner(Colour* newOwner);
  void setAlive(bool);
  bool isAlive();
  Colour getOwner();
private:
};

class World
{
private:  
  int Dimen[2];
  std::vector<Cell> Population;
  std::vector<Colour*> Types;
public:
  World(int x, int y);
  void Iterate();
  void SeedWorld(std::vector<Colour> init);
  void SeedWorld(std::vector<int> init);
  void addType();
  std::vector<int> getWorldWithID();
};

#endif