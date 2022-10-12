#include "Broker.h"
#include "User.h"
#include "Individual.h"
#include "Partnership.h"
#include "Trust.h"
#include "Company.h"
#include "Investor.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

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
    Logged_In = 1;
    Display_Options();

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

void Broker::Display_Options()
{   
    while(Logged_In == 1)
    { 
        system("Clear");
        string Option;
            cout << "Please select the number correlating to the function you wish to utilise: " << endl;
            cout << "1 - View Clients" << endl;
            cout << "2 - Replace Client " << endl;
            cout << "3 - Print Clients" << endl;
            cout << "0 - Log Out" << endl;
        cin >> Option;
        while (Option != "0" && Option != "1" && Option != "2" && Option != "3")
        {
            system("Clear");
            cout << "You didnt use a valid number! Please try again! " << endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("Clear");
            string Option;
            cout << "Please select the number correlating to the function you wish to utilise: " << endl;
            cout << "1 - View Clients" << endl;
            cout << "2 - Replace Client " << endl;
            cout << "3 - Print Clients" << endl;
            cout << "0 - Log Out" << endl;
            cin >> Option;
        }
        if(Option == "0")
            {
                system("Clear");
                Logged_In = 0;
            }
            else if(Option == "1")
            {
                system("Clear");
                Print_Clients();
            }
            else if(Option == "2")
            {
                system("Clear");
                Swap_Clients();
                
            }
            else if(Option == "3")
            {
                system("Clear");
                Print_To_CSV();
            }
    } 
}

void Broker::Print_Clients()
{

    for(int i=0;i<Client_Count;i++)
    {
        int Temp_ID_To_Search = Clients_ID[i];
        ifstream Information;
        Information.open("Accounts.csv");

        if(!Information.is_open()){
            cout << "File wasnt found and openned " << endl;
        }
        string Temp_Recommendation[3] = {"N/A"};
        string Temp_ID;
        int Int_Temp_ID;
        string Temp_Nothing;
        string line;
        string Temp_First_Name;
        string Temp_Type;
        string Temp_Partner_Count;
        string Temp_Bene_Count;
        string Temp_Trustee_Count;
        string Temp_Dir_Count;
        while(getline(Information, line))
        {
                stringstream ss(line);
                getline(ss, Temp_ID, ',');
                Int_Temp_ID = stoi(Temp_ID);
                getline(ss, Temp_Nothing, ',');
                getline(ss, Temp_Type, ',');
                if(Int_Temp_ID == Temp_ID_To_Search)
                {
                    if(Temp_Type == "B")
                    {

                        cout << "Client Number: " << i+1 << endl;
                        cout << "Client ID: " << Temp_ID_To_Search << endl;
                        cout << "\t You have a broker saved in as a client and thus this information cant be displayed" << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                    else if (Temp_Type == "I")
                    {
                        cout << "Client Number: " << i+1 << endl;
                        cout << "Client ID: " << Temp_ID_To_Search << endl;
                        cout << "\t Client Type: Invdividual" << endl;
                        cout << "\t Client ID: " << Int_Temp_ID << endl;
                        getline(ss, Temp_Nothing, ',');
                        cout << "\t First Name: " << Temp_Nothing << endl;
                        getline(ss, Temp_Nothing, ',');
                        cout << "\t Last Name: " << Temp_Nothing << endl;
                    }
                    else if (Temp_Type == "P")
                    {
                        cout << "Client Number: " << i+1 << endl;
                        cout << "Client ID: " << Temp_ID_To_Search << endl;
                        cout << "\t Client Type: Partnership" << endl;
                        cout << "\t Client ID: " << Int_Temp_ID << endl;
                        getline(ss, Temp_Partner_Count, ',');
                        for(int j=0;j<stoi(Temp_Partner_Count);j++)
                        {
                            cout << "\t Partner Number: " << j+1 << endl;
                            getline(ss, Temp_Nothing, ',');
                            cout << "\t\t First Name: " << Temp_Nothing << endl;
                            getline(ss, Temp_Nothing, ',');
                            cout << "\t\t Last Name: " << Temp_Nothing << endl;
                        }
                    }
                    else if (Temp_Type == "T")
                    {
                        cout << "Client Number: " << i+1 << endl;
                        cout << "Client ID: " << Temp_ID_To_Search << endl;
                        cout << "\t Client Type: Trust" << endl;
                        cout << "\t Client ID: " << Int_Temp_ID << endl;
                        getline(ss, Temp_Bene_Count, ',');
                        for(int j=0;j<stoi(Temp_Bene_Count);j++)
                        {
                            cout << "\t Beneficiary Number: " << j+1 << endl;
                            getline(ss, Temp_Nothing, ',');
                            cout << "\t\t First Name: " << Temp_Nothing << endl;
                            getline(ss, Temp_Nothing, ',');
                            cout << "\t\t Last Name: " << Temp_Nothing << endl;
                        }
                        getline(ss, Temp_Trustee_Count, ',');
                        for(int j=0;j<stoi(Temp_Trustee_Count);j++)
                        {
                            cout << "Trustee Number: " << j+1 << endl;
                            getline(ss, Temp_Nothing, ',');
                            cout << "\t\t First Name: " << Temp_Nothing << endl;
                            getline(ss, Temp_Nothing, ',');
                            cout << "\t\t Last Name: " << Temp_Nothing << endl;
                        }
                    }
                    else if (Temp_Type == "C")
                    {
                        cout << "Client Number: " << i+1 << endl;
                        cout << "Client ID: " << Temp_ID_To_Search << endl;
                        cout << "\t Client Type: Company" << endl;
                        cout << "\t Client ID: " << Int_Temp_ID << endl;
                        getline(ss, Temp_Nothing, ',');
                        cout << "\t Company Name: " << Temp_Nothing << endl;
                        getline(ss, Temp_Dir_Count, ',');
                        for(int j=0;j<stoi(Temp_Dir_Count);j++)
                        {
                            cout << "\t Director Number: " << j+1 << endl;
                            getline(ss, Temp_Nothing, ',');
                            cout << "\t\t First Name: " << Temp_Nothing << endl;
                            getline(ss, Temp_Nothing, ',');
                            cout << "\t\t Last Name: " << Temp_Nothing << endl;
                        }
                    }
                    Information.close();
                    break;
                }
        }
        Information.close(); 
    }
    cout << "Press enter to return to main page" << endl;
    cin.ignore();
    cin.get();

}

bool Broker::Check_Remove_Choice(int Choice)
{
    for(int i=0;i<Client_Count;i++)
    {
        if(Clients_ID[i] == Choice)
        {
            return true;
        }
    }
    return false;
}

bool Broker::Check_Add_Choice(int Choice)
{
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_ID;
    string line;
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            if(Choice == stoi(Temp_ID))
            {
                Information.close();
                return true;
            }
    }
    Information.close();
    return false;
}

void Broker::Replace_ID(int Remove_ID, int Replace_ID)
{
    for(int i=0;i<Client_Count;i++)
    {
        if(Clients_ID[i] == Remove_ID)
        {
            Clients_ID[i] = Replace_ID;
            cout << "You Replaced That Client" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void Broker::Swap_Clients()
{
    int Remove_Client;
    int Add_Client;
    cout << "Which client would you like to remove: ";
    cin >> Remove_Client;
    if(Check_Remove_Choice(Remove_Client))
    {
        cout << "What client would you like to add: ";
        cin >> Add_Client;
        if(Check_Add_Choice(Add_Client))
        {
            if(!Check_Remove_Choice(Add_Client))
            {
                Replace_ID(Remove_Client, Add_Client);
                cout << "These clients have been swapped! " << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
            else
            {
                cout << "You already have this client! " << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        }
        else
        {
            cout << "This client doesn't exist! Returning to main menu! " << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
    else
    {
        cout << "You dont have this client! Returning to main menu! " << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void Broker::Print_To_CSV()
{

    cout << "Your report has been printed" << endl;
    cout << "Please find it under the name \"Broker Client Report\"" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    ofstream Printed_Client;
    Printed_Client.open("Broker Client Report.csv");
    Printed_Client << "Report for Brokers" << endl;
    for(int i=0;i<Client_Count;i++)
    {
        Printed_Client << "Client Number: " << i+1 << endl;
        ifstream Information;
        Information.open("Accounts.csv");
        string Temp_ID;
        int Int_Temp_ID;
        string Temp_Nothing;
        string Temp_Partner_Count;
        string Temp_Bene_Count;
        string Temp_Trustee_Count;
        string Temp_Dir_Count;
        string Account_Types;
        string line;
        while(getline(Information, line))
        {
                stringstream ss(line);
                getline(ss, Temp_ID, ',');
                Int_Temp_ID = stoi(Temp_ID);
                if(Int_Temp_ID == Clients_ID[i])
                {
                    getline(ss,Temp_Nothing, ',');
                    getline(ss,Account_Types, ',');
                    if(Account_Types == "B")
                    {
                        Printed_Client << "\t ID: " << Int_Temp_ID << endl;
                        Printed_Client << "\t This is a broker and as such no information can be displayed" << endl;
                    }
                    else if(Account_Types == "I")
                    {
                        Printed_Client << "\t Investor Type: Individual" << endl;
                        Printed_Client << "\t Investor ID: " << Int_Temp_ID << endl;
                        getline(ss,Temp_Nothing,',');
                        Printed_Client << "\t\t First Name: " << Temp_Nothing << endl;
                        getline(ss,Temp_Nothing,',');
                        Printed_Client << "\t\t Last Name: " << Temp_Nothing << endl;
                    }
                    else if(Account_Types == "P")
                    {
                        Printed_Client << "\t Investor Type: Partnership" << endl;
                        Printed_Client << "\t Investor ID: " << Int_Temp_ID << endl;
                        getline(ss,Temp_Partner_Count,',');
                        for(int i=0;i<stoi(Temp_Partner_Count);i++)
                        {
                            Printed_Client << "\t\t Partner Number: " << i+1 << endl;
                            getline(ss,Temp_Nothing,',');
                            Printed_Client << "\t\t\t First Name: " << Temp_Nothing << endl;
                            getline(ss,Temp_Nothing,',');
                            Printed_Client << "\t\t\t Last Name: " << Temp_Nothing << endl;
                        }
                    }
                    else if(Account_Types == "T")
                    {
                        Printed_Client << "\t Investor Type: Trust" << endl;
                        Printed_Client << "\t Investor ID: " << Int_Temp_ID << endl;
                        getline(ss,Temp_Trustee_Count,',');
                        for(int i=0;i<stoi(Temp_Trustee_Count);i++)
                        {
                            Printed_Client << "\t\t Trustee Number: " << i+1 << endl;
                            getline(ss,Temp_Nothing,',');
                            Printed_Client << "\t\t\t First Name: " << Temp_Nothing << endl;
                            getline(ss,Temp_Nothing,',');
                            Printed_Client << "\t\t\t Last Name: " << Temp_Nothing << endl;
                        }
                        getline(ss,Temp_Bene_Count,',');
                        for(int i=0;i<stoi(Temp_Bene_Count);i++)
                        {
                            Printed_Client << "\t\t Beneficiary Number: " << i+1 << endl;
                            getline(ss,Temp_Nothing,',');
                            Printed_Client << "\t\t\t First Name: " << Temp_Nothing << endl;
                            getline(ss,Temp_Nothing,',');
                            Printed_Client << "\t\t\t Last Name: " << Temp_Nothing << endl;
                        }
                    }
                    else if(Account_Types == "C")
                    {
                        Printed_Client << "\t Investor Type: Company" << endl;
                        Printed_Client << "\t Investor ID: " << Int_Temp_ID << endl;
                        getline(ss,Temp_Nothing,',');
                        Printed_Client << "\t Company Name: " << Temp_Nothing << endl;
                        getline(ss,Temp_Dir_Count,',');
                        for(int i=0;i<stoi(Temp_Dir_Count);i++)
                        {
                            Printed_Client << "\t\t Director Number: " << i+1 << endl;
                            getline(ss,Temp_Nothing,',');
                            Printed_Client << "\t\t\t First Name: " << Temp_Nothing << endl;
                            getline(ss,Temp_Nothing,',');
                            Printed_Client << "\t\t\t Last Name: " << Temp_Nothing << endl;
                        }
                    }

                }
        }
        Information.close(); 
                    
    }
    Printed_Client.close();
}

Broker::~Broker()
{
    delete [] Recommendations;
    delete [] Clients_ID;
}