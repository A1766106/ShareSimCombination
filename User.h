#ifndef USER_H
#define USER_H
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

class User
{
    protected:
        int Logged_In;
        int Account_Number; // Account Number
        std::string Account_Type; // String indicating Account_Type
        int Current_Year;
    public:
        std::string Get_Account_Type(); //Function Returning Account Type
        void Set_Account_Type(); //Function Setting Account Type
};

#endif