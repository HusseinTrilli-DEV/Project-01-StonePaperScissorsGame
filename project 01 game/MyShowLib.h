#pragma once
#include <iostream>
using namespace std;

namespace MyShow
{
    void ResetScreen()
    {
        system("cls");
        system("color 0F");
    }

    string Tabs(short NumberOftabs)
    {
        string t = "";
        for (int i = 1; i < NumberOftabs; i++)
        {
            t = t + "\t";
            // cout << t;
        }
        return t;
    }

    void ShowGameOverScreen()
    {
        cout << Tabs(2) << "---------------------------------------------------------\n\n";
        cout << Tabs(2) << "            +++ G a m e O v e r +++\n";
        cout << Tabs(2) << "---------------------------------------------------------\n\n";

    }
}