#include <iostream>
#include <cstdlib> 

#include "MyInPutLib.h";
#include "MyShowLib.h";

using namespace std;
using namespace MyInPut;
using namespace MyShow;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName = "";


};

struct stGameResults
{
    short GameRounds = 0;        // Number of rounds played.
    short Player1WinTimes = 0;   // Count of Player1's wins.
    short ComputerWinTimes = 0;  // Count of Computer's wins.
    short DrawTimes = 0;         // Number of rounds that ended in a draw.
    enWinner GameWinner;         // Stores the overall game winner.
    string WinnerName = "";      // Name of the game winner.
};


string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner " };
    return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    // If both choices are the same, it's a draw.
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    // Determine the winner based on game rules.
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;  
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break; 
    }
    return enWinner::Player1;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");//green
        break;

    case enWinner::Computer:
        system("color 4F");//red
        cout << "\a";
        break;

   default:
        system("color 6F");//yellow
        break;
    }
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber+1 << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes) return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes) return enWinner::Computer;
    else return enWinner::Draw;
}

stGameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

enGameChoice ReadPlayer1Choice()
{
    short Choice=1;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 0; GameRound < HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound+1 << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        //
        if (RoundInfo.Winner == enWinner::Player1)
            PlayerWinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }
    return FillGameResults(HowManyRounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << "--------------------[Game Results]-----------------\n\n";
    cout << Tabs(2) << "Game Rounds           :" << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player Won Times      :" << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Won Times    :" << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw Times            :" << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Finsl Winner          :" << GameResults.WinnerName << endl;
    cout << Tabs(2) << "------------------------------------------------------------";
   
    SetWinnerScreenColor(GameResults.GameWinner);
}

void StartGame()
{
  
    char PlayAgain='Y';

    do
    {
        MyShow::ResetScreen();
        stGameResults GameResults = PlayGame(ShowHowManyRound());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << "\nDo you want to play again? (y/n): " << endl;
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');

  
}

int main()
{
  srand((unsigned)time(NULL));

  StartGame();
    
 return 0;
}