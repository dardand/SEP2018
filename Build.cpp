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
      std::cout << "HERE AT water" << std::endl;
      return water;
    }
    case 2:
    {
      Sep::Field *obstacle = new Sep::Field(FieldType::OBSTACLE, 1, 1);
      std::cout << "HERE AT obstacle" << std::endl;
      return obstacle;
    }
    case 3:
    {
      Sep::Field *street = new Sep::Field(FieldType::STREET, 1, 1);
      std::cout << "HERE AT street" << std::endl;
      return street;
    }
    default:
    {
      Sep::Field *unknown = new Sep::Field(FieldType::UNKNOWN, 1, 1);
      //std::cout << "[ERR] Usage: build\n";
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
  Sep::Interface io_;
  Sep::Game get_money(game);
  Build obj;
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
  Sep::Field *type = obj.getType(parameters[0]);
  if(is_not_number || type->getType() == FieldType::UNKNOWN)
  {
    std::cout << "[ERR] Usage: build\n";
  }
  else
  {
    io_.out(Sep::Interface::MONEY, std::to_string(get_money.getMoney()));
    game.setField(*type, stoi(parameters[1], nullptr, 10), stoi(parameters[2], nullptr, 10));
  }
  
  return -1;
}
