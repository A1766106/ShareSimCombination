#include "Broker.h"
#include "User.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

Broker::Broker()
{
    Clients_ID = new int[1];
    Clients_ID[0] = 0;
    Account_Type = "B";
    Account_Number = 0;
    Client_Count = 1;
    Commission = 0;
    Recommendations = new string[1];
    Recommendations[0] = "N/A";
}

Broker::Broker(int ID)
{
    Account_Number = ID;
    Account_Type = "B";
    Get_Information();

}

void Broker::Get_Information()
{
    Set_Commission();
    Set_Recommendations();
    Set_Clients_Count();
    Set_Clients();
}

void Broker::Set_Commission()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Nothing;
    string Temp_Commission;
    string line;
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            Int_Temp_ID = stoi(Temp_ID);
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Commission, ',');
            if(Int_Temp_ID == Account_Number)
            {
                Commission = stoi(Temp_Commission);
                Information.close(); 
                break;
            }
    }
    Information.close();
}

void Broker::Change_Commission(int Given_Commission)/////////////////////////////////////////////
{
    this->Commission = Given_Commission;
}

int Broker::Get_Commission()
{
    return Commission;
}

void Broker::Set_Recommendations()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Nothing;
    string Temp_Recommendation;
    Recommendations = new string[3];
    string line;
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
                for(int i=0;i<3;i++)
                {
                    getline(ss, Temp_Recommendation, ',');
                   Recommendations[i] = Temp_Recommendation; 
                }
                Information.close(); 
                break;
            }
    }
    Information.close();
}

void Broker::Set_Clients_Count()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Client_Count;
    string Temp_Nothing;
    string line;
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
                for(int i=0;i<3;i++)
                {
                    getline(ss, Temp_Nothing, ',');
                }
                getline(ss, Temp_Client_Count, ',');
                Client_Count = stoi(Temp_Client_Count);
                Information.close(); 
                break;
            }
    }
    Information.close();
}

void Broker::Set_Clients()
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    int Int_Temp_ID;
    string Temp_Client_ID;
    Clients_ID = new int[Client_Count];
    string Temp_Nothing;
    string line;
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
                for(int i=0;i<3;i++)
                {
                    getline(ss, Temp_Nothing, ',');
                }
                getline(ss, Temp_Nothing, ',');
                for(int i=0;i<Client_Count;i++)
                {
                    getline(ss, Temp_Client_ID, ',');
                    Clients_ID[i] = stoi(Temp_Client_ID);
                }
                Information.close(); 
                break;
            }
        }
    Information.close(); 
}

void Broker::Broker_Display_Results_Test()
{
    cout << "Commission: " << Commission << endl;
    for(int i=0;i<3;i++)
    {
        cout << Recommendations[i] << endl;
    }
    for(int i=0;i<Client_Count;i++)
    {
        cout << Clients_ID[i] << endl;
    }
}

std::string *Broker::Get_Recommendations()
{
    return Recommendations;
}

Broker::~Broker()
{
    delete [] Recommendations;
    delete [] Clients_ID;
}