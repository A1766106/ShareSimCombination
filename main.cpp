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
        cout << "You Will Begin In Year 2014" << endl;
        this_thread::sleep_for(chrono::seconds(2));
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
            Partnership U1(Account_ID);
        }
        else
        {
        UserConsole.Log_Out(); 
        }
        
    }

    // while(UserConsole.Logged_In())
    // { 
    //     if(UserConsole.Get_User_Type() != 0)
    //     {
    //         system("Clear");
    //         string Option;
    //         cout << "Please select the number correlating to the function you wish to utilise: " << endl;
    //         cout << "1 - Advance A Year" << endl;
    //         cout << "2 - View Yearly Change Statement (Only For 2015 Onwards) " << endl;
    //         cout << "3 - Print CSV File of Portfolio (Only for 2015 Onwards) " << endl;
    //         cout << "4 - Research Stock" << endl;
    //         cout << "5 - Add Broker" << endl;
    //         cout << "6 - Remove Broker" << endl;
    //         cout << "7 - Get Recommendations" << endl;
    //         cout << "8 - Buy Stocks" << endl;
    //         cout << "9 - Sell Stocks " << endl;
    //         cout << "0 - Log Out" << endl;
    //         cin >> Option;
    //         while (Option != "0" && Option != "1" && Option != "2" && Option != "3" && Option != "4" && Option != "5" && Option != "6" && Option != "7" && Option != "8" && Option != "9")
    //         {
    //             system("Clear");
    //             cout << "You didnt use a valid number! Please try again! " << endl;
    //             this_thread::sleep_for(chrono::seconds(1));
    //             system("Clear");
    //             string Option;
    //             cout << "Please select the number correlating to the function you wish to utilise: " << endl;
    //             cout << "1 - Advance A Year" << endl;
    //             cout << "2 - View Yearly Change Statement (Only For 2015 Onwards) " << endl;
    //             cout << "3 - Print CSV File of Portfolio (Only for 2015 Onwards) " << endl;
    //             cout << "4 - Research Stock" << endl;
    //             cout << "5 - Add Broker" << endl;
    //             cout << "6 - Remove Broker" << endl;
    //             cout << "7 - Get Recommendations" << endl;
    //             cout << "8 - Buy Stocks" << endl;
    //             cout << "9 - Sell Stocks " << endl;
    //             cout << "0 - Log Out" << endl;
    //         cin >> Option;
    //         }
    //         if(Option == "0")
    //         {
    //             UserConsole.Log_Out();
    //         }
    //         else if(Option == "1")
    //         {
    //             U1.Go
    //         }
    //         else if(Option == "2")
    //         {

    //         }
    //         else if(Option == "3")
    //         {
                
    //         }
    //         else if(Option == "4")
    //         {
                
    //         }
    //         else if(Option == "5")
    //         {
                
    //         }
    //         else if(Option == "6")
    //         {
                
    //         }
    //         else if(Option == "7")
    //         {
                
    //         }
    //         else if(Option == "8")
    //         {
                
    //         }
    //         else if(Option == "9")
    //         {
                
    //         }
    //     }
    //     else
    //     {
    //         system("Clear");
    //         string Option;
    //         cout << "Please select the number correlating to the function you wish to utilise: " << endl;
    //         cout << "1 - Change Commission" << endl;
    //         cout << "2 - Add Client" << endl;
    //         cout << "3 - Remove Client" << endl;
    //         cout << "4 - View Clients" << endl;
    //         cout << "0 - Log Out" << endl;
    //         cin >> Option;
    //         while (Option != "0" && Option != "1" && Option != "2" && Option != "3" && Option != "4")
    //         {
    //             system("Clear");
    //             cout << "You didnt use a valid number! Please try again! " << endl;
    //             this_thread::sleep_for(chrono::seconds(1));
    //             cout << "Please select the number correlating to the function you wish to utilise: " << endl;
    //             cout << "1 - Change Commission" << endl;
    //             cout << "2 - Add Client" << endl;
    //             cout << "3 - Remove Client" << endl;
    //             cout << "4 - View Clients" << endl;
    //             cout << "0 - Log Out" << endl;
    //             cin >> Option;
    //         }
    //                 if(Option == "0")
    //                 {
    //                     UserConsole.Log_Out();
    //                 }
    //                 else if(Option == "1")
    //                 {

    //                 }
    //                 else if(Option == "2")
    //                 {

    //                 }
    //                 else if(Option == "3")
    //                 {
                        
    //                 }
    //                 else if(Option == "4")
    //                 {
                        
    //                 }
    //     }
    // }
    UserConsole.Bye_Message();
    return 0;
}