//
// defender : RSA implementation
// @file : RSA.cpp
// @author: Abhishek Jha
//

# include "RSA.h"


long int RSA::e = 7;
long int RSA::d = 3;
long int RSA::n = 33;

std::string RSA::encrypt(std::string message){
     std::string cipher="";
     for(auto m:message){
         long int pt = (int)m;
         pt = pt - 96;
         int k = 1;
        for(int j = 0; j < e; j++)
        {
          k = k * pt;
          k = k % n;
        }
      
      char ct = k + 96;
      cipher+=ct;
      
     }

     return cipher;
}

std::string RSA::decrypt(std::string cipher){
    std::string message = "";
    for(auto c:cipher){
        long int ct = (int)c;
        ct = ct-96;
        int k=1;
        for(int j = 0; j < d; j++)
        {
          k = k * ct;
          k = k % n;
        }
      
      char pt = k + 96;
      message+=pt;

    }
    return message;
}
