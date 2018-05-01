//------------------------------------------------------------------------------
// Game.cpp
//
// Group: Group 18762, study assistant: Philip Loibl
//
// Authors: Stefan Schnutt (11708769)
// Dardan Dermaku (01637087)
// Ermal Gashi (01635065)
//------------------------------------------------------------------------------
//
#include "Build.h"
#include "Interface.h"

//------------------------------------------------------------------------------
Build::Build()
{
}

//------------------------------------------------------------------------------
Sep::Field Build::getType(std::string type)
{
  int check = 0;
  if(!type.compare("water"))
  {
    check = 0;
  }
  else if(!type.compare("obstacle"))
  {
    check = 1;
  }
  else if(!type.compare("street"))
  {
    check = 2;
  }
  switch(check)
  {
    case 0:
    {
      Sep::Field water(FieldType::WATER, 1, 1);
      return water;
    }
    case 1:
    {
      Sep::Field obstacle(FieldType::OBSTACLE, 1, 1);
      return obstacle;
    }
    case 2:
    {
      Sep::Field street(FieldType::STREET, 1, 1);
      return street;
    }
  }
  
}

//------------------------------------------------------------------------------
Build::Build(std::string name) : Command(name)
{
}

//------------------------------------------------------------------------------
Build::~Build()
{
}

//------------------------------------------------------------------------------
int Build::execute(Sep::Game& game, std::vector<std::string>& parameters)
{
  Sep::Interface io_;
  Sep::Game get_money(game);
  Build obj;
  Sep::Field *type = new Sep::Field;
  *type = obj.getType(parameters[0]);
  if(parameters.size() != 3)
  {
    std::cout << "[ERR] Usage: build\n";
    return -1;
  }
  bool is_not_number = false;
  for(int i = 1; i < parameters.size(); i++)
  {
    for(int j = 0; j < parameters[i].length(); j++)
    {
      if(!(isdigit(parameters[i][j])))
      {
        is_not_number = true;
        break;
      }
    }
  }
  
  if(is_not_number)
  {
    std::cout << "[ERR] Usage: build\n";
  }
  else
  {
    io_.out(Sep::Interface::MONEY, std::to_string(get_money.getMoney()));
    game.setField(*type, stoi(parameters[1], nullptr, 10), stoi(parameters[2], nullptr, 10));
  }
  
  delete type;
  return -1;
}
