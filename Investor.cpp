#include "Investor.h"
#include "User.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>

using namespace std;

void Investor::Display_Options()
{
    while(Logged_In == 1)
    { 
        {
            system("Clear");
            string Option;
            cout << "Please select the number correlating to the function you wish to utilise: " << endl;
            cout << "1 - Advance A Year" << endl;
            cout << "2 - View Yearly Change Statement (Only For 2015 Onwards) " << endl;
            cout << "3 - Print CSV File of Portfolio (Only for 2015 Onwards) " << endl;
            cout << "4 - Research Stock" << endl;
            cout << "5 - Add Broker" << endl;
            cout << "6 - Remove Broker" << endl;
            cout << "7 - Get Recommendations" << endl;
            cout << "8 - Buy Stocks" << endl;
            cout << "9 - Sell Stocks " << endl;
            cout << "0 - Log Out" << endl;
            cin >> Option;
            while (Option != "0" && Option != "1" && Option != "2" && Option != "3" && Option != "4" && Option != "5" && Option != "6" && Option != "7" && Option != "8" && Option != "9")
            {
                system("Clear");
                cout << "You didnt use a valid number! Please try again! " << endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("Clear");
                string Option;
                cout << "Please select the number correlating to the function you wish to utilise: " << endl;
                cout << "1 - Advance A Year" << endl;
                cout << "2 - View Yearly Change Statement (Only For 2015 Onwards) " << endl;
                cout << "3 - Print CSV File of Portfolio (Only for 2015 Onwards) " << endl;
                cout << "4 - Research Stock" << endl;
                cout << "5 - Add Broker" << endl;
                cout << "6 - Remove Broker" << endl;
                cout << "7 - Get Recommendations" << endl;
                cout << "8 - Buy Stocks" << endl;
                cout << "9 - Sell Stocks " << endl;
                cout << "0 - Log Out" << endl;
            cin >> Option;
            }
            if(Option == "0")
            {
                Logged_In = 0;
            }
            else if(Option == "1")
            {
                system("Clear");
                Investors_Portfolio->Increase_Current_Year();
            }
            else if(Option == "2")
            {
                if(Current_Year == Investors_Portfolio->Get_Year())
                {
                    system("Clear");
                    cout << "Sorry this option isn't avaliable when you are in the 2014 Financial Year! " << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    system("Clear");
                }
                else {
                    Display_Portfolio();
                }
                
            }
            else if(Option == "3")
            {
                if(Current_Year == Investors_Portfolio->Get_Year())
                {
                    system("Clear");
                    cout << "Sorry this option isn't avaliable when you are in the 2014 Financial Year! " << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    system("Clear");
                }
                else {
                    Print();
                }
            }

            else if(Option == "4")
            {
                system("Clear");
                string Given_Ticker;
                cout << "Please provide the Ticker of the stock you would like the current price of: ";
                cin >> Given_Ticker;
                Share Temp_Share(Given_Ticker,Current_Year);
                if(Temp_Share.Get_Name() != "N/A")
                {
                    cout << "Stock Name: " << Temp_Share.Get_Name() << endl;
                    cout << "Current price: " << Temp_Share.Get_Price(Investors_Portfolio->Get_Year()) << endl;
                    cout << "Press enter to return to main page" << endl;
                    cin.ignore();
                    cin.get();
                }
            }
            else if(Option == "5")
            {
                int Temp_ID;
                system("Clear");
                cout << "What is the ID of the broker whos recommendations you would like to see? ";
                cin >> Temp_ID;
                while(!Broker_ID_Confirmation(Temp_ID) && Temp_ID != -1)
                {
                    system("Clear");
                    cout << "Invalid ID Entered! " << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    cout << "What is the ID of the broker whos recommendations you would like to see? (Or enter -1 to stop trying to add broker): ";
                    cin >> Temp_ID;
                }
                if(Broker_ID_Confirmation(Temp_ID))
                {
                    system("Clear");
                    Set_Broker(Temp_ID);
                    cout << "Broker Set!!!" << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }
            }
            else if(Option == "6")
            {
                system("Clear");
                Remove_Broker();
            }
            else if(Option == "7")
            {
                Get_Recommendations();
            }
            else if(Option == "8")
            {
                system("Clear");
                Buy();
            }
            else if(Option == "9")
            {
                system("Clear");
                Sell();
            }
        }           
    }
}

void Investor::Get_Recommendations()
{
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
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            Int_Temp_ID = stoi(Temp_ID);
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Type, ',');
            getline(ss, Temp_Nothing, ',');
            if(Int_Temp_ID == Broker_ID)
            {
                Information.close();
                getline(ss, Temp_Recommendation[0], ',');
                getline(ss, Temp_Recommendation[1], ',');
                getline(ss, Temp_Recommendation[2], ',');
                break;
            }
    }
    Information.close(); 
    system("Clear");
    cout << "Your brokers recommendations are as follows:" << endl;
    for(int i=0;i<3;i++)
    {
        cout << Temp_Recommendation[i] << endl;
    }
    cout << "Press enter to return to main page" << endl;
    cin.ignore();
    cin.get();
}

bool Investor::Check_Balace(int Transaction)
{
    if(Transaction > Balance)
    {
        return true;
    }
    return false;
}

void Investor::Change_Balance(int Transaction)
{
    Balance = Balance + Transaction;
}

void Investor::Display_Portfolio()///////////////////////////////////////////////
{
    Investors_Portfolio->Display_Portfolio();
}

void Investor::Buy()
{
    string Temp_Ticker;
    int Temp_Units;
    cout << "Whats the ticker of the stock you wish to buy? (Case Sensitive) ";
    cin >> Temp_Ticker;
    cout << "How many units would you like to buy? ";
    cin >> Temp_Units;
    Share Temp_Share;
    if(Temp_Share.Check_Valid_Ticker(Temp_Ticker,Current_Year))
    {
        Investors_Portfolio->Buy_Share(Temp_Ticker, Current_Year, Temp_Units);
    }
    else
    {
        cout << "That was an invalid ticker!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
    
}

void Investor::Sell()
{
    string Temp_Ticker;
    int Temp_Units;
    cout << "Whats the ticker of the stock you wish to Sell? (Case Sensitive) ";
    cin >> Temp_Ticker;
    cout << "How many units would you like to Sell? ";
    cin >> Temp_Units;
    Investors_Portfolio->Sell_Share(Temp_Ticker, Current_Year, Temp_Units);

}

bool Investor::Broker_ID_Confirmation(int ID)
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
    string Temp_Type;
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_ID, ',');
            Int_Temp_ID = stoi(Temp_ID);
            getline(ss, Temp_Nothing, ',');
            getline(ss, Temp_Type, ',');
            if(Int_Temp_ID == ID && Temp_Type == "B")
            {
                Information.close();
                return true; 
                break;
            }
    }
    Information.close(); 
    return false;
}

void Investor::Go_To_Next_Financial_Year()
{
    Current_Year++;
}

void Investor::Set_Broker(int ID)
{
    Broker_ID = ID;
}

void Investor::Remove_Broker()
{
    cout << "Broker Removed!!!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    Broker_ID = 0;
}

double Investor::Get_Balance()
{
    return Balance;
}

void Investor::Print()
{
    system("Clear");
    cout << "Your report has been printed to your file. " << endl;
    this_thread::sleep_for(chrono::seconds(2));
}