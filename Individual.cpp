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
#include <chrono>
#include <thread>

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

void Individual::Print()
{
    Investor::Print();
    ofstream Printed_Portfolio;
    Printed_Portfolio.open("Individual Portfolio Report.csv");
    int Share_Count = Investors_Portfolio->Get_Share_Count();
    Printed_Portfolio << "Report for Individual Investors" << endl;
    Printed_Portfolio << "First Name: " << First_Name << endl;
    Printed_Portfolio << "Last Name: " << Last_Name << endl;
    for(int i=0;i<Share_Count;i++)
    {        
        int Temp_Units = Investors_Portfolio->Units(i);
        int Temp_Current_Price = Investors_Portfolio->Current_Price(i);
        int Temp_Previous_Price = Investors_Portfolio->Previous_Price(i);
        string Temp_Name = Investors_Portfolio->Name(i);
        Printed_Portfolio << "Share Number " << i+1 << " - " << Temp_Name << endl;
        Printed_Portfolio << "\t Units: " << Temp_Units << endl;
        Printed_Portfolio << "\t Current Price: $" << Temp_Current_Price << endl;
        Printed_Portfolio << "\t Previous Price: $" << Temp_Previous_Price << endl;
        Printed_Portfolio << "\t 12 Month Price Change: $" << (Temp_Current_Price-Temp_Previous_Price)*Temp_Units << endl;
    }
    Printed_Portfolio << "Your Bank Balance is furthermore: $" << Investors_Portfolio->Get_Cash() << endl;
    Printed_Portfolio.close();
    cout << "Please find your report called \"Individaul Portfolio Report\" " << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

void Individual::Individual_Display_Results_Test()
{
    cout << "Name: " << First_Name << " " << Last_Name << " balance: " << Balance << endl;
}

Individual::~Individual()
{
    delete Investors_Portfolio;
}