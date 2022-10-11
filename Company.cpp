#include "Company.h"
#include "Investor.h"
#include "User.h"
#include "Portfolio.h"
#include "Broker.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;

Company::Company()
{
    Director_First_Name = new string[1];
    Director_First_Name[0] = "N/A";
    Director_Last_Name = new string[1];
    Director_Last_Name[0] = "N/A";
    Registered_Name = "N/A";
    Balance = 0;
    Account_Number = 0;
    Account_Type = "N/A";
    Current_Year = 2014;
    Number_Of_Directors = 1;
    Investors_Portfolio = new Portfolio;
}

Company::Company(int ID)
{
    Account_Number = ID;
    Get_Company_Details();
    Account_Type = "C";
    Current_Year = 2014;
    Investors_Portfolio = new Portfolio;
    Logged_In = 1;
    Display_Options();
}

void Company::Get_Company_Details()
{
    Set_Director_Count();
    Set_Names();

}

void Company::Print_Trust_portfolio() /////////////////////////////////////////////
{

}

void Company::Company_Display_Results_Test()
{
    cout << "Company name is: " << Registered_Name << endl;
    for(int i=0;i<Number_Of_Directors;i++)
    {
        cout << "First name: " << Director_First_Name[i] << " Last name: " << Director_Last_Name[i] << endl;
    }
    cout << Number_Of_Directors << endl;
}

void Company::Set_Director_Count()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Nothing;
    string Temp_Director_Count;
    string line;
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            Int_Temp_ID = stoi(Temp_ID);
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Director_Count, ',');
            if(Int_Temp_ID == Account_Number)
            {
                Number_Of_Directors = stoi(Temp_Director_Count);
                Information.close(); 
                break;
            }
    }
    Information.close();
}

void Company::Set_Names()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Nothing;
    string Temp_Name;
    string Temp_First_Name;
    string Temp_Last_Name;
    string line;
    Director_First_Name = new string[Number_Of_Directors];
    Director_Last_Name = new string[Number_Of_Directors];
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            Int_Temp_ID = stoi(Temp_ID);
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Name, ',');
            getline(ss, Temp_Nothing, ',');
            if(Int_Temp_ID == Account_Number)
            {
                Registered_Name = Temp_Name;
                for(int i=0;i<Number_Of_Directors;i++)
                {
                    getline(ss, Temp_First_Name , ',');
                    getline(ss, Temp_Last_Name, ',');
                    Director_First_Name[i] = Temp_First_Name;
                    Director_Last_Name[i] = Temp_Last_Name;
                }
                Information.close(); 
                break;
            }
    }
    Information.close();
}

void Company::Print()
{
    Investor::Print();
    ofstream Printed_Portfolio;
    Printed_Portfolio.open("Trust Portfolio Report.csv");
    int Share_Count = Investors_Portfolio->Get_Share_Count();
    Printed_Portfolio << "Report for Company Investors" << endl;
    Printed_Portfolio << "Company Name: " << Registered_Name << endl;
    for(int i=0;i<Number_Of_Directors;i++)
    {
        Printed_Portfolio << "Trustee Number: " << i+1 << endl;
        Printed_Portfolio << "\t First Name: " << Director_First_Name[i] << endl;
        Printed_Portfolio << "\t Last Name: " << Director_Last_Name[i] << endl;
    }
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
    cout << "Please find your report called \"Trust Portfolio Report\" " << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

Company::~Company()
{
    delete [] Director_First_Name;
    delete [] Director_Last_Name;
    delete Investors_Portfolio;
}