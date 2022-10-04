#ifndef BROKER_H
#define BROKER_H
#include "User.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

class Broker:public User
{
    private:
        int *Clients_ID;
        int Client_Count;
        int Commission;
        std::string *Recommendations;
    public:
        Broker(); // Default constructor
        Broker(int ID); // Constructor
        void Get_Information(); // Function that gets details from accounts csv file
        void Set_Commission(); // Sets broker commission per csv file
        void Change_Commission(int Given_Commission); // Sets broker commission to given amount////////////////////////////////////////
        int Get_Commission(); // Returns commission
        void Set_Recommendations(); // Allows broker to modify recommendations
        void Set_Clients_Count(); // Sets Brokers clients count
        void Set_Clients(); // Sets Brokers clients
        void Broker_Display_Results_Test(); // Displays features to assist int testing
        std::string *Get_Recommendations(); // Returns array of recommendations
        ~Broker(); // Destructor

};

#endif