#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H
#include "User.h"
#include "Investor.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

class Individual:public Investor
{
    private:
        std::string First_Name;
        std::string Last_Name;
    public:
        Individual(); // Default constructor
        Individual(int ID); // Constructor 
        void Get_Individual_Details(); // Sets user First Name and Last Name Per Accounts.csv
        void Individual_Display_Results_Test(); // Test for Displaying Results
        void Print(); // Overloading inherited function
        ~Individual(); // Destructor
};


#endif