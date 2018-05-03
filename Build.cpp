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
#include "Buildable.h"
//------------------------------------------------------------------------------
Build::Build()
{
}

//------------------------------------------------------------------------------
Sep::Field* Build::getType(std::string type)
{
  int check = 0;
  if(!type.compare("water"))
  {
    check = 1;
  }
  else if(!type.compare("obstacle"))
  {
    check = 2;
  }
  else if(!type.compare("street"))
  {
    check = 3;
  }
  switch(check)
  {
    case 1:
    {
      Sep::Field *water = new Sep::Field(FieldType::WATER, 1, 1);
      return water;
    }
    case 2:
    {
      Sep::Field *obstacle = new Sep::Field(FieldType::OBSTACLE, 1, 1);
      return obstacle;
    }
    case 3:
    {
      Sep::Field *street = new Sep::Field(FieldType::STREET, 1, 1);
      return street;
    }
    default:
    {
      Sep::Field *unknown = new Sep::Field(FieldType::UNKNOWN, 1, 1);
      return unknown;
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
  bool is_not_number = false;
  int position_x;
  int position_y;
  Sep::Interface io_;
  Sep::Game get_money(game);
  Build obj;
  if(parameters.size() != 3)
  {
    std::cout << "[ERR] Usage: build\n";
    return -1;
  }
  for(int i = 1; i < parameters.size(); i++)
  {
    for(int j = 0; j < parameters[i].size(); j++)
    {
      if(!isdigit(parameters[i][j]))
      {
        is_not_number = true;
        break;
      }
    }
  }
  try
  {
    position_x = std::stoi(parameters[1]);
    position_y = std::stoi(parameters[2]);
  }
  catch(std::invalid_argument&) //or catch(...) to catch all exceptions
  {
    std::cout << "[ERR] Usage1: build\n";
    return -1;
  }
  Sep::Field *type = obj.getType(parameters[0]);
  Sep::Buildable buildable_(Sep::Buildable::FieldType(type->getType()), position_x, position_y);
  if(type->getType() == FieldType::UNKNOWN || is_not_number)
  {
    std::cout << "[ERR] Usage: build\n";
  }
  else if(get_money.getMoney() < buildable_.getBuildCost())
  {
    std::cout << get_money.getMoney();
    std::cout << "[INFO] Insufficient funds!\n";
  }
  else
  {
    if(game.setField(*type, stoi(parameters[1], nullptr, 10), stoi(parameters[2], nullptr, 10)))
    {
      game.setMoney(get_money.getMoney() - buildable_.getBuildCost());
      io_.out(Sep::Interface::MONEY, std::to_string(get_money.getMoney() - buildable_.getBuildCost()));
    }
  }
  return -1;
}
