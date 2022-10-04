#include "Partnership.h"
#include "User.h"
#include "Investor.h"
#include "Portfolio.h"
#include "Broker.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

Partnership::Partnership()
{
    First_Name = new string[1];
    First_Name[0] = "N/A";
    Last_Name = new string[1];
    Last_Name[0] = "N/A";
    Balance = 0;
    Account_Number = 0;
    Account_Type = "N/A";
    Current_Year = 2014;
    Number_Of_Partners = 1;
    Investors_Portfolio = new Portfolio;
}

Partnership::Partnership(int ID)
{
    Account_Number = ID;
    Get_Partnership_Details();
    Account_Type = "P";
    Current_Year = 2014;
    Investors_Portfolio = new Portfolio;
    Logged_In = 1;
    Display_Options();
}

void Partnership::Get_Partnership_Details()
{
    Set_Partners_Count();
    Set_Partners_Names();
}

void Partnership::Print_Partnership_Portfolio() //////////////////////////////////////////
{

}

void Partnership::Partnersip_Display_Results_Test()
{
    for(int i=0;i<Number_Of_Partners;i++)
    {
        cout << "First name: " << First_Name[i] << " Last name: " << Last_Name[i] << endl;
    }
    cout << Number_Of_Partners << endl;
}

void Partnership::Set_Partners_Count()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Nothing;
    string Temp_Partner_Count;
    string line;
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            Int_Temp_ID = stoi(Temp_ID);
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Partner_Count, ',');
            if(Int_Temp_ID == Account_Number)
            {
                Number_Of_Partners = stoi(Temp_Partner_Count);
                Information.close(); 
                break;
            }
    }
    Information.close(); 
}

void Partnership::Set_Partners_Names()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Nothing;
    string line;
    string Temp_First_Name;
    string Temp_Last_Name;
   First_Name = new string[Number_Of_Partners];
   Last_Name = new string[Number_Of_Partners];
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            Int_Temp_ID = stoi(Temp_ID);
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Nothing, ',');
            if(Int_Temp_ID == Account_Number)
            {
                for(int i=0;i<Number_Of_Partners;i++)
                {
                    getline(ss, Temp_First_Name , ',');
                    getline(ss, Temp_Last_Name, ',');
                    First_Name[i] = Temp_First_Name;
                    Last_Name[i] = Temp_Last_Name;
                }
                Information.close(); 
                break;
            }
    }
    Information.close();
}

Partnership::~Partnership()
{
    delete [] First_Name;
    delete [] Last_Name;
    delete Investors_Portfolio;
}