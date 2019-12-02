#include "DataBase.h"
#include <iostream>

void DataBase::addSchemes(std::vector<Predicate*> mySchemes)
{
    for(unsigned int i = 0; i < mySchemes.size(); i++)
    {
      Relation* newRelation = new Relation();

      Predicate curScheme = *(mySchemes.at(i));

      newRelation->setScheme(curScheme.getName(), curScheme.getParams());
      myRelations.push_back(newRelation);
    }
}

void DataBase::addFacts(std::vector<Predicate*> myFacts)
{
  for(unsigned int i = 0; i < myFacts.size(); i++)
  {
    Predicate* curFact = myFacts.at(i);

    for(unsigned int j = 0; j < myRelations.size(); j++)
    {
      std::string relName = myRelations.at(j)->getName();
      if(relName == curFact->getName())
      {
        myRelations.at(j)->setTuple(curFact->getParams());
        break;
      }
    }
  }
}

void addRules(std::vector<Rule*> myRules)
{

}

std::string DataBase::printDB()
{
  std::string returnString = "";
  for(unsigned int i = 0; i < myRelations.size(); ++i)
  {
      returnString += myRelations.at(i)->toString();
      returnString += "\n";
  }

  return returnString;
}
