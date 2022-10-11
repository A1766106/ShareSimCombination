#include "Console.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;

Console::Console()
{
    Logged_In_Status = 1;
    Welcome_Message();
}

void Console::Welcome_Message()
{
   system("Clear"); // Clears terminal
    cout << " .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  " << endl;
    cout << "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. | " << endl;
    cout << "| | _____  _____ | || |  _________   | || |   _____      | || |     ______   | || |     ____     | || | ____    ____ | || |  _________   | | " << endl;
    cout << "| ||_   _||_   _|| || | |_   ___  |  | || |  |_   _|     | || |   .' ___  |  | || |   .'    `.   | || ||_   \\  /   _|| || | |_   ___  |  | | " << endl;
    cout << "| |  | | /\\ | |  | || |   | |_  \\_|  | || |    | |       | || |  / .'   \\_|  | || |  /  .--.  \\  | || |  |   \\/   |  | || |   | |_  \\_|  | | " << endl;
    cout << "| |  | |/  \\| |  | || |   |  _|  _   | || |    | |   _   | || |  | |         | || |  | |    | |  | || |  | |\\  /| |  | || |   |  _|  _   | |  " << endl;
    cout << "| |  |   /\\   |  | || |  _| |___/ |  | || |   _| |__/ |  | || |  \\ `.___.'\\  | || |  \\  `--'  /  | || | _| |_\\/_| |_ | || |  _| |___/ |  | | " << endl;
    cout << "| |  |__/  \\__|  | || | |_________|  | || |  |________|  | || |   `._____.'  | || |   `.____.'   | || ||_____||_____|| || | |_________|  | | " << endl;
    cout << "| |              | || |              | || |              | || |              | || |              | || |              | || |              | |  " << endl;
    cout << "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |  " << endl;
    cout << " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'   " << endl << endl; // Output welcome message
    this_thread::sleep_for(chrono::seconds(2));
    system("Clear"); // Clears terminal
    cout << "Loading." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("Clear"); // Clears terminal
    cout << "Loading.." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("Clear"); // Clears terminal
    cout << "Loading..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("Clear"); // Clears terminal
    string Confirmation = ""; // Initialises confirmation
    cout << "Do you already have an account? (Y/N) "; // Requests input from user clarrifying if user has an existing account
    cin >> Confirmation;
    while(Confirmation != "Y" && Confirmation != "y" && Confirmation != "n" && Confirmation != "N") // Confirms valid entry from user.
    {
        cout << "You entered an invalid input! Do you already have an account? (Y/N) "; // Requests input from user clarrifying if user has an existing account
        cin >> Confirmation;
    }
    if(Confirmation == "Y" || Confirmation == "y")
    {
        Existing_User = 1;
    }
    else
    {
        Existing_User = 0;
    } 

}

int Console::Get_Existing_User()
{
    return Existing_User;
}

int Console::Login()
{
    string Given_ID;
    string Given_Password;
    cout << "Please provide your ID: ";
    cin >> Given_ID;
    cout << "Please provide your Password: ";
    cin >> Given_Password;
    ifstream AccountsList;
    AccountsList.open("Accounts.csv");
    if(!AccountsList.is_open()){
        cout << "File Failed To Open" << endl;
        Log_Out();
    }
    string Temp_ID;
    string Temp_Password;
    string Temp_Type;
    string Line;
    while(getline(AccountsList, Line))
    {
        stringstream ss(Line);
        getline(ss, Temp_ID, ',');
        getline(ss, Temp_Password, ',');
        getline(ss, Temp_Type, ',');
        if(Temp_ID == Given_ID && Temp_Password == Given_Password)
        {
            if(Temp_Type == "B")
            {
                User_Type = 0;
            }
            else if (Temp_Type == "I")
            {
                User_Type = 1;
            }
            else if (Temp_Type == "P")
            {
                User_Type = 2;
            }
            else if (Temp_Type == "T")
            {
                User_Type = 3;
            }
            else if (Temp_Type == "C")
            {
                User_Type = 4;
            }            
            
            AccountsList.close();
            return stoi(Given_ID);
        }
    }
    AccountsList.close();
    Log_Out();
    return -1;

}

int Console::Create_Account()
{
    string Account_Type;
    int Account_Number;
    system("Clear");
    cout << "What type of user are you?" << endl;
    cout << "1 - Broker" << endl;
    cout << "2 - Investor" << endl;
    cin >> Account_Type;
    while (Account_Type != "1" && Account_Type != "2")
    {
        cout << "You Entered an invalid input! Please Try Again!" << endl;
        cout << "What type of user are you? ";
        cout << "1 - Broker" << endl;
        cout << "2 - Investor" << endl;
        cin >> Account_Type;
    }
    if(Account_Type == "1")
    {
        Account_Number = Create_Broker();
        this->User_Type = 0;
    }
    else
    {
        string Investor_Type;
        system("Clear");
        cout << "Please select the number associated with the entity type you are: " << endl;
        cout << "1 - Individual" << endl;
        cout << "2 - Partnership" << endl;
        cout << "3 - Trust" << endl;
        cout << "4 - Company" << endl;
        cin >> Investor_Type;
        while(Investor_Type != "1" && Investor_Type != "2" && Investor_Type != "3" && Investor_Type != "4")
        {
            system("Clear");
            cout << "You selected an option that wasnt in the avaliable options! Please try again! " << endl;
            cout << "Please select the number associated with the entity type you are: " << endl;
            cout << "1 - Individual" << endl;
            cout << "2 - Partnership" << endl;
            cout << "3 - Trust" << endl;
            cout << "4 - Company" << endl;
            cin >> Investor_Type;
        }
        if (Investor_Type == "1")
        {
            User_Type = 1;
            Account_Number = Create_Individual();
        }
        else if (Investor_Type == "2")
        {
            User_Type = 2;
            Account_Number = Create_Partnership();
        }
        else if (Investor_Type == "3") 
        {
            User_Type = 3;
            Account_Number = Create_Trust();
        }
        else if (Investor_Type == "4") 
        {
            User_Type = 4;
            Account_Number = Create_Company();
        } 
        
    }
    return Account_Number;
}

void Console::Log_Out()
{
    Logged_In_Status = 0;
}

bool Console::Logged_In()
{
    if(Logged_In_Status == 1)
    {
        return true;
    }
    return false;
}

void Console::Bye_Message()
{
    system("Clear"); // Clears terminal
    cout << ".----------------.  .----------------.  .----------------."   << endl;
    cout << "| .--------------. || .--------------. || .--------------. |" << endl;
    cout << "| |   ______     | || |  ____  ____  | || |  _________   | |" << endl;
    cout << "| |  |_   _ \\    | || | |_  _||_  _| | || | |_   ___  |  | |" << endl;
    cout << "| |    | |_) |   | || |   \\ \\  / /   | || |   | |_  \\_|  | |" << endl;
    cout << "| |    |  __'.   | || |    \\ \\/ /    | || |   |  _|  _   | |" << endl;
    cout << "| |   _| |__) |  | || |    _|  |_    | || |  _| |___/ |  | |" << endl;
    cout << "| |  |_______/   | || |   |______|   | || | |_________|  | |" << endl;
    cout << "| |              | || |              | || |              | |" << endl;
    cout << "| '--------------' || '--------------' || '--------------' |" << endl;
    cout << "'----------------'  '----------------'  '----------------'  " << endl;
}

int Console::Create_Broker()
{
    int Given_ID;
    string Given_Password;
    int Commission;
    string Recommendations[3];
    int Client_Count;
    // int Client_ID[3];
    Given_ID = Get_ID();
    cout << "Please provide password: ";
    cin >> Given_Password;
    cout << "Please provide your default fee (in dollars): ";
    cin >> Commission;
    for(int i=0;i<3;i++)
    {
        cout << "Please provide your stock recommendation number " << i+1 << ": ";
        cin >> Recommendations[i];
    }
    cout << "Whats the maximum amount of clients you would like to have: ";
    cin >> Client_Count;
    int Client_ID[Client_Count];
    for(int j=0;j<Client_Count;j++)
    {
        cout << "Please provide the default ID's for your clients " << j+1 << " (Or 0 if you dont have enough clients for quota of 3): ";
        cin >> Client_ID[j];
        while(!Duplicate_ID(Client_ID[j]) && Client_ID[j] != 0)
        {
            cout << "You entered a non-existant ID!" << endl;
            cout << "Please try again and enter the ID of client number " << j+1 << " (Or 0 if you dont have enough clients for quota of 3): ";
            cin >> Client_ID[j];
        }
    }
    fstream Accounts;
    Accounts.open("Accounts.csv", fstream::app);
    Accounts << Given_ID << "," << Given_Password << "," << "B" << "," << Commission << "," << Recommendations[0] 
    << "," << Recommendations [1] << "," << Recommendations [2] << "," << Client_Count;
    for(int i=0;i<Client_Count;i++)
    {
        Accounts << "," << Client_ID[i];
    }
    Accounts << ",,,\n";
    Accounts.close();
    return Given_ID;
}

int Console::Create_Individual()
{
    system("Clear");
    int Given_ID;
    string Given_Password;
    string Individual_First_Name;
    string Individual_Last_Name;
    Given_ID = Get_ID();
    cout << "Please provide password: ";
    cin >> Given_Password;
    cout << "Please provide your first name as you would like it to appear on your portfolio statement: ";
    cin >> Individual_First_Name;
    cout << "Please provide your last name as you would like it to appear on your portfolio statement: ";
    cin >> Individual_Last_Name;
    fstream Accounts;
    Accounts.open("Accounts.csv", fstream::app);
    Accounts << Given_ID << "," << Given_Password << "," << "I" << "," << Individual_First_Name << "," << Individual_Last_Name << ",,,\n";
    Accounts.close();
    return Given_ID;
}
int Console::Create_Partnership()
{
    system("Clear");
    int Given_ID;
    string Given_Password;
    int Partner_Number;
    Given_ID = Get_ID();
    cout << "Please provide password: ";
    cin >> Given_Password;
    cout << "How many partners are there? ";
    cin >> Partner_Number;
    string Partners_First_Names[Partner_Number];
    string Partners_Last_Names[Partner_Number];
    for(int i=0;i<Partner_Number;i++)
    {
        cout << "Please provide the first name for partner number " << i+1 << " as you would like it to appear on your portfolio statement: ";
        cin >> Partners_First_Names[i];
        cout << "Please provide the last name for partner number " << i+1 << " as you would like it to appear on your portfolio statement: ";
        cin >> Partners_Last_Names[i];
    }
    fstream Accounts;
    Accounts.open("Accounts.csv", fstream::app);
    Accounts << Given_ID << "," << Given_Password << "," << "P" << "," << Partner_Number;
    for(int i=0;i<Partner_Number;i++)
    {
        Accounts << "," << Partners_First_Names[i] << "," << Partners_Last_Names[i];
    }
    Accounts << ",,,\n";
    Accounts.close();
    return Given_ID;
}

int Console::Create_Trust()
{
    system("Clear");
    int Given_ID;
    string Given_Password;
    int Trustee_Number;
    int Beneficiary_Number;
    Given_ID = Get_ID();
    cout << "Please provide password: ";
    cin >> Given_Password;
    cout << "How many beneficiaries are there? ";
    cin >> Beneficiary_Number;
    string Beneficiary_First_Names[Beneficiary_Number];
    string Beneficiary_Last_Names[Beneficiary_Number];
    for(int i=0;i<Beneficiary_Number;i++)
    {
        cout << "Please provide the first name for beneificary number " << i+1 << " as you would like it to appear on your portfolio statement: ";
        cin >> Beneficiary_First_Names[i];
        cout << "Please provide the last name for beneificary number " << i+1 << " as you would like it to appear on your portfolio statement: ";
        cin >> Beneficiary_Last_Names[i];
    }
    cout << "How many trustees are there? ";
    cin >> Trustee_Number;
    string Trustee_First_Names[Beneficiary_Number];
    string Trustee_Last_Names[Beneficiary_Number];
    for(int i=0;i<Trustee_Number;i++)
    {
        cout << "Please provide the first name for trustee number " << i+1 << " as you would like it to appear on your portfolio statement: ";
        cin >> Trustee_First_Names[i];
        cout << "Please provide the last name for trustee number " << i+1 << " as you would like it to appear on your portfolio statement: ";
        cin >> Trustee_Last_Names[i];
    }
    fstream Accounts;
    Accounts.open("Accounts.csv", fstream::app);
    Accounts << Given_ID << "," << Given_Password << "," << "T" << "," << Beneficiary_Number;
    for(int i=0;i<Beneficiary_Number;i++)
    {
        Accounts << "," << Beneficiary_First_Names[i] << "," << Beneficiary_Last_Names[i];
    }
    Accounts << ", " << Trustee_Number;
    for(int i=0;i<Trustee_Number;i++)
    {
        Accounts << "," << Trustee_First_Names[i] << "," << Trustee_Last_Names[i];
    }
    Accounts << ",,,\n";
    Accounts.close();

    return Given_ID;
}

int Console::Create_Company()
{
    system("Clear");
    int Given_ID;
    string Given_Password;
    int Director_Number;
    string Registered_Name;
    Given_ID = Get_ID();
    cout << "Please provide password: ";
    cin >> Given_Password;
    cout << "Please enter your registered name: ";
    cin.ignore(1000, '\n');
    getline(cin, Registered_Name);
    cout << "How many directors are there? ";
    cin >> Director_Number;
    string Director_First_Names[Director_Number];
    string Director_Last_Names[Director_Number];
    for(int i=0;i<Director_Number;i++)
    {
        cout << "Please provide the first name for director number " << i+1 << " as you would like it to appear on your portfolio statement: ";
        cin >> Director_First_Names[i];
        cout << "Please provide the last name for director number " << i+1 << " as you would like it to appear on your portfolio statement: ";
        cin >> Director_Last_Names[i];
    }
    fstream Accounts;
    Accounts.open("Accounts.csv", fstream::app);
    Accounts << Given_ID << "," << Given_Password << "," << "C" << "," << Registered_Name << "," << Director_Number;
    for(int i=0;i<Director_Number;i++)
    {
        Accounts << "," << Director_First_Names[i] << "," << Director_Last_Names[i];
    }
    Accounts << ",,,\n";
    Accounts.close();

    return Given_ID;
}

void Console::Loading()
{
    this_thread::sleep_for(chrono::seconds(2));
    system("Clear"); // Clears terminal
    cout << "Loading." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("Clear"); // Clears terminal
    cout << "Loading.." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("Clear"); // Clears terminal
    cout << "Loading..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    system("Clear"); // Clears terminal
}

int Console::Get_ID()
{
    int ID;
    cout << "Please provide your desired ID (Integers Only): ";
    cin >> ID;
    while(Duplicate_ID(ID))
    {
        cout << "You entered an already Existing ID: Please provide your desired ID (Integers Only): ";
        cin >> ID;
    }
    return ID;
}

int Console::Get_User_Type()
{
    return User_Type;
}

bool Console::Duplicate_ID(int ID)
{
    ifstream Accounts;
    Accounts.open("Accounts.csv");
    string line;
    int Temp_ID;
    string myID;
    while(getline(Accounts, line))
    {
        stringstream ss(line);
        getline(ss,myID,',');
        Temp_ID = stoi(myID);
        if(Temp_ID == ID)
        {
          return true;
        }
    }
    Accounts.close();  
    return false; 
}