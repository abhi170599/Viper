//
// defender : RSA declaration
// @file : RSA.h
// @author: Abhishek Jha
//

# pragma once
#ifndef DEFENDER_RSA_H
#define DEFENDER_RSA_H



#include<string>

class RSA{
    
    static long int e;
    static long int d;
    static long int n;

    public:
      std::string encrypt(std::string);
      std::string decrypt(std::string);
};





#endif //DEFENDER_RSA