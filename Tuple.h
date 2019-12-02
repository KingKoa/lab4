#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>
#include "Predicate.h"

class Tuple : public std::vector<std::string> {
public:
    Tuple() {}
    //Tuple(std::vector<std::string*> *newData) { tupData = newData; }
    //void addTuple(std::vector<std::string*> *newData) { tupData = newData; }
    //std::vector<std::string*> *getData() { return tupData; }

    std::string toString() const
    {
      std::string returnString = "( ";

      for(unsigned int i = 0; i < this->size(); i++)
      {
        returnString += this->at(i);
        returnString += " ";
      }

      returnString += ")";

      return returnString;
    }
/*
    bool operator == (Tuple compare)
    {
      std::vector<std::string*> *otherData = compare.getData();

      for(unsigned int i = 0; i < this->tupData->size(); ++i)
      {
        if(*(this->tupData->at(i)) != *(otherData->at(i)))
        {
          return false;
        }
      }
      return true;
    }

    bool operator < (Tuple compare)
    {
      std::vector<std::string*> *otherData = compare.getData();

      for(unsigned int i = 0; i < this->tupData->size(); ++i)
      {
        if(*(this->tupData->at(i)) < *(otherData->at(i)))
        {
          return true;
        }
      }

      return false;
    }
*/
private:
//  std::vector<std::string*> *tupData;

};

#endif //TUPLE_H
