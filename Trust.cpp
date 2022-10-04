#include "Trust.h"
#include "Investor.h"
#include "User.h"
#include "Portfolio.h"
#include "Broker.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

Trust::Trust()
{
    Bene_First_Name = new string[1];
    Bene_First_Name[0] = "N/A";
    Bene_Last_Name = new string[1];
    Bene_Last_Name[0] = "N/A";
    Trustee_First_Name = new string[1];
    Trustee_First_Name[0] = "N/A";
    Trustee_Last_Name = new string[1];
    Bene_Last_Name[0] = "N/A";
    Balance = 0;
    Account_Number = 0;
    Account_Type = "N/A";
    Current_Year = 2014;
    Number_Of_Trustee = 1;
    Number_Of_Bene = 1;
    Investors_Portfolio = new Portfolio;

}

Trust::Trust(int ID)
{
    Account_Number = ID;
    Get_Trust_Details();
    Account_Type = "T";
    Current_Year = 2014;
    Investors_Portfolio = new Portfolio;
    Logged_In = 1;
    Display_Options();

}

void Trust::Get_Trust_Details()
{
    Set_Bene_Count();
    Set_Names();
}
void Trust::Print_Trust_Portfolio() //////////////////////////////////////////
{

}

void Trust::Trust_Display_Results_Test()
{
    for(int i=0;i<Number_Of_Bene;i++)
    {
        cout << "First name: " << Bene_First_Name[i] << " Last name: " << Bene_Last_Name[i] << endl;
    }
    for(int i=0;i<Number_Of_Trustee;i++)
    {
        cout << "First name: " << Trustee_First_Name[i] << " Last name: " << Trustee_Last_Name[i] << endl;
    }
    cout << "Bene count: " << Number_Of_Bene << endl;
    cout << "Trustee count: " << Number_Of_Trustee << endl;

}

void Trust::Set_Bene_Count()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Nothing;
    string Temp_Bene_Count;
    string line;
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            Int_Temp_ID = stoi(Temp_ID);
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Bene_Count, ',');
            if(Int_Temp_ID == Account_Number)
            {
                Number_Of_Bene = stoi(Temp_Bene_Count);
                Information.close(); 
                break;
            }
    }
    Information.close();
}


void Trust::Set_Names()
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
    string Temp_Trustee_Count;
    string Bene_Temp_First_Name;
    string Bene_Temp_Last_Name;
    string Trustee_Temp_First_Name;
    string Trustee_Temp_Last_Name;
    Bene_First_Name = new string[Number_Of_Bene];
    Bene_Last_Name = new string[Number_Of_Bene];
    Trustee_First_Name = new string[Number_Of_Bene];
    Trustee_Last_Name = new string[Number_Of_Bene];
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
                for(int i=0;i<Number_Of_Bene;i++)
                {
                    getline(ss, Bene_Temp_First_Name , ',');
                    getline(ss, Bene_Temp_Last_Name, ',');
                    Bene_First_Name[i] = Bene_Temp_First_Name;
                    Bene_Last_Name[i] = Bene_Temp_Last_Name;
                }
                getline(ss ,Temp_Trustee_Count,',');
                this->Number_Of_Trustee = stoi(Temp_Trustee_Count);
                for(int i=0;i<Number_Of_Trustee;i++)
                {
                    getline(ss, Trustee_Temp_First_Name , ',');
                    getline(ss, Trustee_Temp_Last_Name, ',');
                    Trustee_First_Name[i] = Trustee_Temp_First_Name;
                    Trustee_Last_Name[i] = Trustee_Temp_Last_Name;
                }
                Information.close(); 
                break;
                
            }
    }
    Information.close();
}

Trust::~Trust()
{
    delete [] Bene_First_Name;
    delete [] Bene_Last_Name;
    delete [] Trustee_First_Name;
    delete [] Trustee_Last_Name;
    delete Investors_Portfolio;
}