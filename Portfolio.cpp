#include "Portfolio.h"
#include "Share.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std;

Portfolio::Portfolio()
{
    User_Shares = new Share[20];
    Share_Count = 0;
    Current_Year = 2014;
    cout << "How much cash would you like to start with? ";
    cin >> Cash;
    while(Cash < 0)
    {
        cout << "You entered a negative balance! What would you like your starting balance to be? ";
        cin >> Cash;
    }
}

int Portfolio::Get_Share_Count()
{
    return Share_Count;
}

void Portfolio::Buy_Share(std::string Ticker, int Current_Year, int Units)
{
    if(!Reached_Share_Max())
    {
        Share Temp_Share(Ticker,Current_Year);
        if(Cash > (Temp_Share.Get_Price(Current_Year)*Units))
        {
            int Index_For_Stock = Find_Stock_Index(Ticker);
            if(Index_For_Stock == Share_Count)
            {
                User_Shares[Share_Count] = Share(Ticker, Current_Year, Units);
                cout << "You have bought " << User_Shares[Share_Count].Get_Name() << endl;
                this_thread::sleep_for(chrono::seconds(2));
                Cash = Cash - (User_Shares[Share_Count].Get_Price(Current_Year)*Units);
                Share_Count++;
            }
            else
            {
                int Temp_Units = User_Shares[Index_For_Stock].Get_Units();
                User_Shares[Index_For_Stock] = Share(Ticker, Current_Year, Units+Temp_Units);
                Cash = Cash - (User_Shares[Index_For_Stock].Get_Price(Current_Year)*Units);
                cout << "You have bought " << User_Shares[Index_For_Stock].Get_Name() << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
        }
        else
        {
            cout << "You dont have enough money to buy this! " << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
    else
    {
        cout << "You have reached the maximum amount of shares!!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

}

void Portfolio::Sell_Share(std::string Ticker, int Current_Year, int Units)
{
    int Stock_Found = 0;
    for(int i=0;i<Share_Count;i++)
    {
        if(User_Shares[i].Get_Ticker() == Ticker)
        {
            if(User_Shares[i].Get_Units() < Units)
            {
                cout << "You dont have enough units to sell!! " << endl;
                this_thread::sleep_for(chrono::seconds(1));
                Stock_Found = 1;
            }
            else
            {
                cout << "You sold " << User_Shares[i].Get_Name() << endl;
                this_thread::sleep_for(chrono::seconds(2));
                Cash = Cash + (User_Shares[i].Get_Price(Current_Year)*Units);
                User_Shares[i].Sell_Units(Units);
                Stock_Found = 1;
            }
        }
    }
    if (Stock_Found == 0)
    {
        cout << "You dont own this stock or you entered the ticker incorrectly!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

bool Portfolio::Reached_Share_Max()
{
    if(Share_Count > 20)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

void Portfolio::Display_Portfolio()
{
    system("Clear");
    cout << "Your Portfolio is as Follows, Please Note Figures Have Been Rounded For Ease" << endl;
    string temp;
    for(int i=0;i<Share_Count;i++)
    {
        int Temp_Units = User_Shares[i].Get_Units();
        int Temp_Current_Price = User_Shares[i].Get_Price(Current_Year);
        int Temp_Previous_Price = User_Shares[i].Get_Price(Current_Year-1);
        cout << i+1 << " - Name: " << User_Shares[i].Get_Name() << " Current Stock Price: $" << User_Shares[i].Get_Price(Current_Year) << " Last Years Stock Price: $" << User_Shares[i].Get_Price(Current_Year-1) << " Units Held: " << User_Shares[i].Get_Units() << " Current Market Value: $"; 
        cout << Temp_Units * Temp_Current_Price << " 12 Month Stock Change: $" << (Temp_Units*Temp_Current_Price) - (Temp_Units*Temp_Previous_Price) << endl;
    }
    cout << "Your Bank Balance is furthermore: $" << Cash << endl;
    cout << "Press enter to return to main page" << endl;
    cin.ignore();
    cin.get();

}

void Portfolio::Increase_Current_Year()
{
    if(Reached_Year_Upper_Bound())
    {
        Current_Year++;
        for(int i=0;i<Share_Count;i++)
        {
            User_Shares[i].Set_Current_Year(Current_Year);
        }
        cout << "You have advanced forward into year " << Current_Year << endl;
        this_thread::sleep_for(chrono::seconds(3));
    }
    else
    {
        cout << "You cant advance any further you have reached the upper limit!" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void Portfolio::Decrease_Current_Year()
{
    if(Reached_Year_Lower_Bound())
    {
        Current_Year--;
        cout << "You have advanced backward into year " << Current_Year << endl;
        for(int i=0;i<Share_Count;i++)
        {
            User_Shares[i].Set_Current_Year(Current_Year);
        }
    }
    else
    {
        cout << "You cant advance any further into the past you have reached the lower limit!" << endl;
    }
}

bool Portfolio::Reached_Year_Upper_Bound()
{
    if(Current_Year >= 2022)
    {
        return false;
    }
    return true;
}

bool Portfolio::Reached_Year_Lower_Bound()
{
    if(Current_Year <= 2014)
    {
        return false;
    }
    return true;
}

int Portfolio::Find_Stock_Index(std::string Ticker)
{
    int Index = Share_Count;
    for(int i=0;i<Share_Count;i++)
    {
        if(User_Shares[i].Get_Ticker() == Ticker)
        {
            Index = i;
        }
    }
    return Index;
}

int Portfolio::Get_Year()
{
    return Current_Year;
}

int Portfolio::Units(int Share_Number)
{
    return User_Shares[Share_Number].Get_Units();
}

int Portfolio::Current_Price(int Share_Number)
{
    return User_Shares[Share_Number].Get_Price(Current_Year);
}
int Portfolio::Previous_Price(int Share_Number)
{
    return User_Shares[Share_Number].Get_Price(Current_Year-1);
}

std::string Portfolio::Name(int Share_Number)
{
    return User_Shares[Share_Number].Get_Name();
}

double Portfolio::Get_Cash()
{
    return Cash;
}

Portfolio::~Portfolio() ///////////////////////////////////////// Need to fix destructor error
{
    // delete User_Shares;
}