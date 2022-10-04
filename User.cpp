#include "User.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

string User::Get_Account_Type()
{
    return Account_Type;
}
void User::Set_Account_Type()
{
    Account_Type = "N/A";
    ifstream Information;
    Information.open("Accounts.csv");

    if(!Information.is_open()){
        cout << "File wasnt found and openned " << endl;
    }
    string Temp_Account_Number;
    int Int_Temp_Account_Number;
    string Temp_Password;
    string Temp_Account_Type;
    string line;
    while(getline(Information, line))
    {
            stringstream ss(line);
            getline(ss, Temp_Account_Number, ',');
            getline(ss, Temp_Password, ',');
            getline(ss, Temp_Account_Type, ',');
            Int_Temp_Account_Number = stoi(Temp_Account_Number);
            if(Int_Temp_Account_Number == this->Account_Number)
            {
                Account_Type = Temp_Account_Type;
                break;
            }
    }
    Information.close();
}