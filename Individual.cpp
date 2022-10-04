#include "Individual.h"
#include "User.h"
#include "Broker.h"
#include "Investor.h"
#include "Portfolio.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

Individual::Individual()
{
    First_Name = "N/A";
    Last_Name = "N/A";
    Balance = 0;
    Account_Number = 0;
    Account_Type = "N/A";
    Current_Year = 2014;
    Investors_Portfolio = new Portfolio;
}

Individual::Individual(int ID)
{
    Account_Number = ID;
    Get_Individual_Details();
    Account_Type = "I";
    Current_Year = 2014;
    Investors_Portfolio = new Portfolio;
    Logged_In = 1;
    Display_Options();

}

void Individual::Get_Individual_Details()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Nothing;
    string Temp_First_Name;
    string Temp_Last_Name;
    string line;
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            Int_Temp_ID = stoi(Temp_ID);
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_First_Name, ',');
            getline(ss, Temp_Last_Name, ',');
            if(Int_Temp_ID == Account_Number)
            {
                First_Name = Temp_First_Name;
                Last_Name = Temp_Last_Name;
                break;
            }
    }
     Information.close(); 
}

void Individual::Print_Individual_Portfolio()///////////////////////////////////////////////////
{

}

void Individual::Individual_Display_Results_Test()
{
    cout << "Name: " << First_Name << " " << Last_Name << " balance: " << Balance << endl;
}

Individual::~Individual()
{
    delete Investors_Portfolio;
}