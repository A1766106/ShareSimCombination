#include "Console.h"
#include "Individual.h"
#include "Broker.h"
#include "Company.h"
#include "Trust.h"
#include "Partnership.h"
#include "User.h"
#include "Investor.h"
#include "Portfolio.h"
#include "Share.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    Console UserConsole;
    int Account_ID;
    if(UserConsole.Get_Existing_User() == 1)
    {
        Account_ID = UserConsole.Login();
        if(Account_ID == -1)
        {
            cout << "Login Failed! This Software Will Now Close!" << endl;
            UserConsole.Loading();
        }
        else
        {
            cout << "User ID Number: " << Account_ID << " Succesfully Logged In. " << endl;
            UserConsole.Loading();
        }
    }
    else
    {
        Account_ID = UserConsole.Create_Account();
        cout << "User ID Number " << Account_ID << " Succesfully Created And Logged In! " << endl;
        UserConsole.Loading();
    }

    if(UserConsole.Logged_In())
    {
        system("Clear");
        if(UserConsole.Get_User_Type() == 1 || UserConsole.Get_User_Type() == 2 || UserConsole.Get_User_Type() == 3 || UserConsole.Get_User_Type() == 4)
        {
            cout << "You Will Begin In The Financial Year 2014" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
        if(UserConsole.Get_User_Type() == 0)
        {
            Broker U1(Account_ID);
        }
        else if (UserConsole.Get_User_Type() == 1)
        {
            Individual U1(Account_ID);
        }
        else if (UserConsole.Get_User_Type() == 2)
        {
            Partnership U1(Account_ID);
        }
        else if (UserConsole.Get_User_Type() == 3)
        {
            Trust U1(Account_ID);
        }
        else if (UserConsole.Get_User_Type() == 4)
        {
            Company U1(Account_ID);
        }
        else
        {
        UserConsole.Log_Out(); 
        }
        
    }

    UserConsole.Bye_Message();
    return 0;
}