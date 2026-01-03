#pragma once

#include <iostream>
using namespace std;

namespace MyInPut
{
    int RandomNumber(int From, int To)
    {
       
        int randNum = rand() % (To - From + 1) + From;
        return randNum; 
    }

    int ShowHowManyRound()
    {
        int Rounds = 1;
        do
        {
            cout << "How Many Questuions do you need to to answer ?";
            cin >> Rounds;

        } while (Rounds > 10 || Rounds < 1);

        return Rounds;

    }

    float ReadFloatNumber()
    {
        float Number;  // Variable to store user input.

        // Prompt the user to enter a floating-point number.
        cout << "Please enter a float number? ";
        cin >> Number;  // Read input from the user.

        return Number;  // Return the input number.
    }

    int ReadNumberOnly() 
    {

        int Number;  
        cout << "Please enter a number?" << endl;  
        cin >> Number;
        while (cin.fail())
        { // user didn't input a number 
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   
            cout << "Invalid Number, Enter a valid one:" << endl;   
            cin >> Number;   
        }
        return Number;
    }

}