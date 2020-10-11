//
// defender : RSA implementation
// @file : RSA.cpp
// @author: Abhishek Jha
//

# include "RSA.h"


long int RSA::e = 23;
long int RSA::d = 47;
long int RSA::n = 143;

std::string RSA::encrypt(std::string message,RSA_Key key){
     std::string cipher="";
     for(auto m:message){
         long int pt = (int)m;
         
         int k = 1;
        for(int j = 0; j < key.key; j++)
        {
          k = k * pt;
          k = k % key.n;
        }
      
      char ct = k;
      cipher+=ct;
      
     }

     return cipher;
}

std::string RSA::decrypt(std::string cipher,RSA_Key key){
    std::string message = "";
    for(auto c:cipher){
        long int ct = (int)c;
        
        int k=1;
        for(int j = 0; j < key.key; j++)
        {
          k = k * ct;
          k = k % key.n;
        }
      
      char pt = k;
      message+=pt;

    }
    return message;
}
