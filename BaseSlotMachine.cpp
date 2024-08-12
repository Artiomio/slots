#include <iostream>
#include <stdlib.h>
#include <algorithm> 
#include <cmath>
#include "BaseSlotMachine.h"
#include "LeverBalancer.h"
using namespace std;

 
    

/**
 * Constructor of our slot-machine
 * @param numberOfLinesInWinTable number of lines in the pay table
 * @param numberOfColumnsInWinTable number of columns in the pay table
 * @param winTable Pay table array
 * 
 */
BaseSlotMachine::BaseSlotMachine(int numberOfLinesInWinTable, int numberOfColumnsInWinTable, double* winTable )
{

    moneyLeft = 0;
    lastWin = 0;
    totalWin = 0;
    
    
    BaseSlotMachine::winTable = winTable;
    RETURN_RATE = 0.99;
    HIT = 0.2;
    PROB_OF_LOSS=1-HIT;
    
    NUMBER_OF_COLUMNS_IN_WIN_TABLE = numberOfColumnsInWinTable;
    NUMBER_OF_LINES_IN_WIN_TABLE =  numberOfLinesInWinTable;
    

    // probabilities table with one additional element for the loss-combination
    double* probTable= new double[NUMBER_OF_COLUMNS_IN_WIN_TABLE * NUMBER_OF_LINES_IN_WIN_TABLE + 1]; 
    
    
    // Finding probabilities that correspond to winTable and HIT and RETURN_RATE
    LeverBalancer balancer(NUMBER_OF_COLUMNS_IN_WIN_TABLE * NUMBER_OF_LINES_IN_WIN_TABLE,
        RETURN_RATE, HIT ,winTable,probTable);
    
    
   
    balancer.balance();

    //additional loss element, which in our initial problem was set to 0.8 
    probTable[NUMBER_OF_COLUMNS_IN_WIN_TABLE * NUMBER_OF_LINES_IN_WIN_TABLE]=PROB_OF_LOSS; 

    // New random generator 
    weighedRandomGenerator = new WeighedRandom  (NUMBER_OF_COLUMNS_IN_WIN_TABLE * NUMBER_OF_LINES_IN_WIN_TABLE + 1,
                                                probTable);        
    
    


    screen = new int[NUMBER_OF_LINES_IN_WIN_TABLE * NUMBER_OF_COLUMNS_IN_WIN_TABLE];

        
} // end of constructor



/**
 * Run one game of our slot-machine
 * @return number of money credits won
 */
double BaseSlotMachine::playOneGame()
{
    int t = weighedRandomGenerator->getRNDResultNumber();  
    
    lastCombinationNumber = t; // counting from 1


    moneyLeft = moneyLeft + winTable[t-1] - 1;
    totalWin += winTable[t-1];
    
    lastWin = winTable[t-1];
    return winTable[t-1];
    
}

/**
 * Printing the 3x5 screen of our slot-machine
 */
void BaseSlotMachine::print()
{
    // Here numberOfSymbol = ((N-1) mod 9) + 1  -- N=[1..27]
    // rankOfCombination = 3 + [(N-1)/9]
    // the table is extended by the loss of the bet of -1   
    
    int n = lastCombinationNumber;
    
    
    int rankOfCombination = 3 + (int)((n-1)/9); // [3..]
    int numberOfSymbol = numberOfSymbol = ((n-1) % 9) + 1; //[1..9]

    if (n==(NUMBER_OF_COLUMNS_IN_WIN_TABLE * NUMBER_OF_LINES_IN_WIN_TABLE+1)) 
    {
        
        // sorry, this time you lose
        
        
        // choosing a random symbol for roll number 1
        screen[5] = rnd(1,9);
        screen[6] = rndWithout(screen[5],1,9); // now it's definitely a lost-situation
        
        for (int i =7 ; i < 10; i++) 
            screen[i] = rnd(1,9);
    }
    else
    {
        
        for (int i = 5; i < 5 + rankOfCombination ; i++)
        {
            screen[i] = numberOfSymbol;
        }
        
        
        
    
        // now we have to break in with another symbol so that the screen won't show another winning combination
        if (rankOfCombination!=5) 
        {
            screen[5+rankOfCombination]=rndWithout(numberOfSymbol,1,9);
            for (int i = 5+ rankOfCombination +1; i < 10; i++)
            {
                screen[i] = rnd(1,9);
            }
        }
        
    }
    
    // filling the rest of the matrix - the first and the last lines
    
    
    for (int i = 0; i < 5; i++) 
    {
        if (screen[i+5]>1) 
            screen[i] = screen[i+5]-1;
        else
            screen[i]=9;
            
        if (screen[i+5]<9)
            screen[10+i] = screen[i+5]+1;
        else
            screen[10+i]=1;
            
    }
    
    
    
    cout<<endl;
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 5; j++)
      {
          cout<<"  "<<screen[i*5+j];
      }
      cout<<endl;
      
    }
    
}


int BaseSlotMachine::rndWithout(int toBeExcluded, int a, int b)
{
    
    int res;
    do
      res = a + (rand() % (b - a + 1));
    while (res == toBeExcluded);
    return res;
}


int BaseSlotMachine::rnd(int a, int b) // [a,b]
{
    return a + (rand() % (b - a + 1));
}




