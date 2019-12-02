#include "Relations.h"
/*
Relation::Relation(const Relation &copyCat)
{
  this->addScheme(copyCat.getScheme());
  std::set<Tuple> otherTups = copyCat.getTuple();

  std::set<Tuple>::iterator it = otherTups.begin();

  while (it != otherTups.end())
  {
    this->addTuple(*it);
    it++;
  }

}
*/
void Relation::setScheme(std::string newName, std::vector<std::string*> *newAttributes)
{
  myScheme.setName(newName);
  myScheme.setAttributes(newAttributes);
}

void Relation::setTuple(std::vector<std::string*> *tupData)
{
  Tuple newTup;
  for (unsigned int i = 0; i < tupData->size(); ++i)
  {
    newTup.push_back(*(tupData->at(i)));
  }

  if(myTuples.insert(newTup).second)
  {
    myTuples.insert(newTup);
  }
}

void Relation::addTuple(Tuple newTuple)
{
  if(myTuples.insert(newTuple).second)
  {
    myTuples.insert(newTuple);
  }
}


Relation* Relation::select(std::string selectThis, std::string thisCol)
{
  unsigned int i;
  Relation* newRelation = new Relation();
  newRelation->setScheme(myScheme);

  for (i = 0; i < myScheme.getAttributes()->size(); ++i)
  {
    if (thisCol == *(myScheme.getAttributes()->at(i))) { break; }
  }

  std::set<Tuple>::iterator it = myTuples.begin();

  while (it != myTuples.end())
  {
    if (selectThis == (*it).at(i))
    {
      newRelation->addTuple(*it);
    }

    it++;
  }

  return newRelation;
}

Relation* Relation::selectMatching(std::string opOne, std::string opTwo)
{
  unsigned int i;
  unsigned int j;
  Relation* newRelation = new Relation();
  newRelation->setScheme(myScheme);

  for (i = 0; i < myScheme.getAttributes()->size(); ++i)
  {
    if (opOne == *(myScheme.getAttributes()->at(i))) { break; }
  }

  for (j = 0; j < myScheme.getAttributes()->size(); ++j)
  {
    if (opTwo == *(myScheme.getAttributes()->at(j))) { break; }
  }

  std::set<Tuple>::iterator it = myTuples.begin();

  while (it != myTuples.end())
  {
    if ((*it).at(j) == (*it).at(i))
    {
      newRelation->addTuple(*it);
    }

    it++;
  }

  return newRelation;
}

Relation* Relation::project(std::map<unsigned int,std::string> firstTimer)
{
  unsigned int i = 0;
  Relation* newRelation = new Relation();
  std::map<unsigned int,std::string>::iterator mapIt;


  std::set<Tuple>::iterator it = myTuples.begin();
  while (it != myTuples.end())
  {
    Tuple myTuple;

    for(i = 0; i < it->size(); ++i)
    {
        for (mapIt = firstTimer.begin(); mapIt != firstTimer.end(); ++mapIt)
        {
            if(i == mapIt->first)
            {   // string's value
                myTuple.push_back(it->at(i));
            }
        }
    }

    newRelation->addTuple(myTuple);
    it++;
  }

  return newRelation;
}

Relation* Relation::rename(std::map<unsigned int,std::string> firstTimer)
{
    //unsigned int i;
    Relation* newRelation = new Relation();
    std::map<unsigned int,std::string>::iterator mapIt;

    for (mapIt = firstTimer.begin(); mapIt != firstTimer.end(); ++mapIt)
    {
        newRelation->myScheme.addAttribute(new std::string(mapIt->second));
    }

    newRelation->setTuple(myTuples);
    /*
  std::set<Tuple>::iterator it = myTuples.begin();
  while (it != myTuples.end())
  {
    newRelation->addTuple(*it);
    it++;
  }
    */
  return newRelation;
}

Relation* Relation::join(Relation *firstRel, Relation *secondRel)
{
    Relation* newRelation = new Relation();

    //Catch Duplicate Attribute Positions
    std::vector<std::pair<unsigned int, unsigned int>*> dupAttribute;
    // Combine schemes
    newRelation->setScheme(firstRel->getScheme());

    bool isDup = false;
    unsigned int k;
    std::vector<std::string*> *schemeAttributes = secondRel->getAttributes();

    for(unsigned int i = 0; i < schemeAttributes->size(); ++i)
    {
        isDup = false;

        for(k = 0; k < newRelation->getAttributes()->size(); ++k)
        {
            if(*(newRelation->getAttributes()->at(k)) == *(schemeAttributes->at(i)))
            {
                isDup = true;
                break;
            }
        }

        if(!isDup)
        {
            newRelation->addAttribute(schemeAttributes->at(i));
        }
        else
        {
            dupAttribute.push_back(new std::pair(k, i));
        }
    }
    // Go through every pair of tuples
        //See if you can combine the tuples
            //Does every column that's supposed to match match?
        //If tuples can be combined combine them.

    std::cout << newRelation->getScheme().toString() << std::endl;
    std::set<Tuple>::iterator itFirst = firstRel->getTuple().begin();
    std::set<Tuple>::iterator itSecond;
    bool isJoinable = true;
    bool dontAdd = false;

    while (itFirst != firstRel->getTuple().end())
    {
        itSecond = secondRel->getTuple().begin();

        while(itSecond != secondRel->getTuple().end())
        {

            for(int i = 0; i < dupAttribute.size(); ++i)
            {
                std::cout << "It's the dpuAttribute list i:" << i << std::endl;
                std::cout << dupAttribute.at(0)->first << " first" << std::endl;
                std::cout << dupAttribute.at(0)->second << " second" << std::endl;
                std::cout << itFirst->toString() << std::endl;
                std::cout << itSecond->toString() << std::endl;
                itFirst++;
                std::cout << itFirst->toString() << std::endl;
                std::cout << (*itFirst).at(0) << " itFirst at 0" << std::endl;
                std::cout << itSecond->at(0) << " itSecond at 0" << std::endl;
                if(itFirst->at(dupAttribute.at(i)->first) != itSecond->at(dupAttribute.at(i)->second)) { isJoinable = false; }
            }

            if(isJoinable)
            {
                Tuple joinedTup;

                for(int i = 0; i < itFirst->size(); ++i)
                {
                    joinedTup.push_back(itFirst->at(i));
                }

                for(int i = 0; i < itSecond->size(); ++i)
                {
                    dontAdd = false;

                    for(int j = 0; j < dupAttribute.size(); ++j)
                    {
                        if(i == dupAttribute.at(j)->first) { dontAdd = true; }
                    }

                    if(!dontAdd)
                    {
                        joinedTup.push_back(itSecond->at(i));
                    }
                }

                newRelation->addTuple(joinedTup);
            }
            ++itSecond;
        }

        ++itFirst;
    }
    //bool isJoinable(){}
    //Scheme combineSchemes(){}
    //Tuple combineTuples(){}


    return newRelation;
}

Relation* unionize(Relation firstRel, Relation secondRel)
{
    Relation* newRelation = new Relation();
    /*
     * Be consistent about which Relation is which
     * The one you are inside is the database relation
     * The one you pass in as an argument is the result from the rule evaluation
     * When adding a tuple from the rule evaluation to the database, check if it already existed → if(mySet.insert(myTuple).second)
     * If it already existed, do nothing
     * If it is a new tuple, print out and add to DB relation
     */

    return newRelation;
}

std::string Relation::toString()
{
    std::string returnString = "";
//  returnString += "Relation:\n";
//  returnString += "  ";
//  returnString += myScheme.toString();
//  returnString += "\n";

  std::set<Tuple>::iterator it = myTuples.begin();

  while (it != myTuples.end())
  {
    if(myScheme.getAttributes()->size() != 0) { returnString += "  "; }

    for (unsigned int i = 0; i < myScheme.getAttributes()->size(); ++i)
    {
      returnString += *(myScheme.getAttributesAt(i));
      returnString += "=";
      returnString += (*it).at(i);

      if (i+1 != myScheme.getAttributes()->size())
      {
        returnString += ", ";
      }
    }

    it++;
    if(myScheme.getAttributes()->size() != 0) { returnString += "\n"; }
    //if (it != myTuples.end()) { returnString += "\n"; }
  }

  //returnString += "\n";
  return returnString;
}

/*
std::vector<std::string*> *myAttributes = myScheme.getAttributes();
for (unsigned int i = 0; i < parmList->size(); ++i)
{
  for (unsigned int j = 0; j < myAttributes->size(); ++j)
  {
    if (*(parmList->at(i)) == *(myAttributes->at(j))) break;
  }
}

int searching;

if ((i - 1) < 0) { searching = 1; }
else { searching = 0; }
*/
