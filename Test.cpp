#include <iostream>
#include "Relations.h"
#include "Tuple.h"
int main()
{

    Relation *alpha = new Relation;
    Relation *beta = new Relation;
    Relation *joined = new Relation;

    Tuple alpha1;
    alpha1.push_back("1");
    alpha1.push_back("2");
    alpha1.push_back("5");

    Tuple alpha2;
    alpha2.push_back("1");
    alpha2.push_back("4");
    alpha2.push_back("1");

    Tuple alpha3;
    alpha3.push_back("2");
    alpha3.push_back("3");
    alpha3.push_back("2");

    Tuple alpha4;
    alpha4.push_back("3");
    alpha4.push_back("3");
    alpha4.push_back("2");

    Tuple alpha5;
    alpha5.push_back("6");
    alpha5.push_back("7");
    alpha5.push_back("4");

    Tuple beta1;
    beta1.push_back("3");
    beta1.push_back("4");
    beta1.push_back("2");
    beta1.push_back("4");

    Tuple beta2;
    beta2.push_back("6");
    beta2.push_back("4");
    beta2.push_back("9");
    beta2.push_back("2");

    Tuple beta3;
    beta3.push_back("4");
    beta3.push_back("3");
    beta3.push_back("2");
    beta3.push_back("7");

    Tuple beta4;
    beta4.push_back("1");
    beta4.push_back("5");
    beta4.push_back("2");
    beta4.push_back("4");

    Tuple beta5;
    beta5.push_back("1");
    beta5.push_back("5");
    beta5.push_back("8");
    beta5.push_back("3");

    alpha->addAttribute(new std::string("cat"));
    alpha->addAttribute(new std::string("dog"));
    alpha->addAttribute(new std::string("fish"));

    beta->addAttribute(new std::string("cat"));
    beta->addAttribute(new std::string("fish"));
    beta->addAttribute(new std::string("bird"));
    beta->addAttribute(new std::string("bunny"));

    alpha->addTuple(alpha1);
    alpha->addTuple(alpha2);
    alpha->addTuple(alpha3);
    alpha->addTuple(alpha4);
    alpha->addTuple(alpha5);

    beta->addTuple(beta1);
    beta->addTuple(beta2);
    beta->addTuple(beta3);
    beta->addTuple(beta4);
    beta->addTuple(beta5);

    std::cout << alpha->toString() << std::endl;
    std::cout << beta->toString() << std::endl;

    joined = joined->join(alpha, beta);

    std::cout << joined->toString() << std::endl;

    return 0;
}