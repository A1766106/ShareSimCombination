#include "Share.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

Share::Share()
{
    Ticker = "CBA";
    Name = "CBA";
    Current_Year = 2014;
    Current_Price = 0;
    Units = 0;
    Prices = Get_Prices();
    Value = 0;
    Cost_Base = 0;

}

Share::Share(string Ticker, int Current_Year)
{
    this->Ticker = Ticker;
    int Continue = 1;
    while(!Check_Valid_Ticker(Ticker, Current_Year) && Continue == 1)
    {
        cout << "Please re enter the ticker as the company information wasnt found (Or enter \"Stop\" to stop searching): ";
        cin >> Ticker;
        this->Ticker = Ticker;
        if(Ticker == "Stop")
        {
            Continue = 0;
        }
        Name = "N/A";
    }
    Prices = Get_Prices();
    this->Current_Year = Current_Year;
    Name = Find_Name(Current_Year);
    Value = 0;
    Cost_Base = 0;
    Units = 0;
    Current_Price = Get_Current_Price();

}

Share::Share(std::string Ticker, int Current_Year, int Units)
{
    this->Ticker = Ticker;
    while(!Check_Valid_Ticker(Ticker, Current_Year))
    {
        cout << "Please re enter the ticker as the company information wasnt found: ";
        cin >> Ticker;
        this->Ticker = Ticker;
    }
    Prices = Get_Prices();
    this->Current_Year = Current_Year;
    Name = Find_Name(Current_Year);
    Current_Price = Get_Current_Price();
    this->Units = Units;
    Value = Get_Current_Price() * Units;
    Cost_Base = Get_Current_Price() * Units;
    Current_Price = Get_Current_Price();
}

string Share::Get_Ticker()
{
    return Ticker;
}

string Share::Get_Name()
{
    return Name;
}

int Share::Get_Current_Year()
{
    return Current_Year;
}

double Share::Get_Current_Price()
{
    return Get_Price(Current_Year);
}

int Share::Get_Units()
{
    return Units;
}

void Share::Sell_Units(int Sold_Units)
{
    Units = Units - Sold_Units;
}

bool Share::Check_Valid_Ticker(std::string Ticker, int Current_Year)
{
    string i_string = to_string(Current_Year);
    string FileToBeOpened = i_string + ".csv";

    ifstream Information;
    Information.open(FileToBeOpened);

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
        return false;
    }
    string Temp_Ticker;
    string line;
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_Ticker, ',');
            if(Temp_Ticker == Ticker)
            {
                return true;
                break;
            }
    }
     Information.close();
    return false;

}

double Share::Get_Price(int Year)
{
    double Price = 0;
    string i_string = to_string(Year);
    string FileToBeOpened = i_string + ".csv";

    ifstream Information;
    Information.open(FileToBeOpened);

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    
    string Temp_Ticker;
    string Temp_Price;
    double Another_Temp_Price;
    string Temp_Name;
    string line;

    while(getline(Information, line)){
        stringstream ss(line);
        getline(ss, Temp_Ticker, ',');
        getline(ss, Temp_Name, ',');
        getline(ss, Temp_Price,',');
        if(Temp_Ticker == Get_Ticker())
        {
            
            Price = stod(Temp_Price);
            break;
        }
    }
    Information.close();
    return Price;
}

void Share::Set_Current_Year(int Increase)
{
    Current_Year = Current_Year + Increase;
}

double *Share::Get_Prices()
{
    double *Prices = new double[9];
    for(int i=2014;i<2023;i++)
    {
        Prices[i-2014] = Get_Price(i);
    }    
    return Prices;
}

std::string Share::Find_Name(int Year)
{
    string Name = "Not Found";
    if(Year != 2020)
    {
        string i_string = to_string(Year);
        string FileToBeOpened = i_string + ".csv";

        ifstream Information;
        Information.open(FileToBeOpened);

        if(!Information.is_open()){
            cout << "File wasnt found and openned " << endl;
        }
        string Temp_Ticker;
        string Temp_Price;
        string Temp_Name;
        string line;

        while(getline(Information, line)){
            stringstream ss(line);
            getline(ss, Temp_Ticker, ',');
            getline(ss, Temp_Name, ',');
            getline(ss, Temp_Price,',');
            if(Temp_Ticker == Ticker)
            {
                Name = Temp_Name;
                break;
            }
        }
        Information.close();
        return Name;
    }
    else
    {
        ifstream Information;
        Information.open("ASX_Companies.csv");

        if(!Information.is_open()){
            cout << "File wasnt found and openned " << endl;
        }
        string Temp_Ticker;
        string Temp_Price;
        string Temp_Name;
        string line;

        while(getline(Information, line)){
            stringstream ss(line);
            getline(ss, Temp_Ticker, ',');
            getline(ss, Temp_Name, ',');
            getline(ss, Temp_Price,',');
            if(Temp_Ticker == Ticker)
            {
                Name = Temp_Name;
                break;
            }
        }
        Information.close();
        return Name;
    }
    return Name;
}

void Share::Increase_Units(int Units)
{
    this->Units += Units;
    Cost_Base += Units*Get_Current_Price();
}

Share::~Share()
{
    delete Prices;
}