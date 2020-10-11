//
// defender : RSA declaration
// @file : RSA.h
// @author: Abhishek Jha
//

# pragma once
#ifndef DEFENDER_RSA_H
#define DEFENDER_RSA_H



#include<string>

struct RSA_Key{
  long int key;
  long int n;

  RSA_Key(long int k,long int num){
    key=k;
    n=num;
  }
};


class RSA{
    
    static long int e;
    static long int d;
    static long int n;

    public:
      std::string encrypt(std::string,RSA_Key key);
      std::string decrypt(std::string,RSA_Key key);
};





#endif //DEFENDER_RSA