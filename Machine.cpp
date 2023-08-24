#include <iostream>
#include<stdlib.h>
#include<algorithm> 
#include<cmath>
#include "BaseSlotMachine.h"
using namespace std;


 
int main(int argc, char* argv[])
{
    
    
    
    double winTable[]={3,	5,	7,	9,	12,	15,	20,	30,	50,     // three-fold combinations for S1, S2,...S9
                15,	30,	50,	60,	75,	90,	120,150,200,    // four-fold combinations for S1, S2,...S9
                45,	75,	150,250,350,500,750,1000,2000, 0}; // five-fold combinations for S1, S2,...S9
                  

    int NUMBER_OF_LINES_IN_WIN_TABLE = 3;
    int NUMBER_OF_COLUMNS_IN_WIN_TABLE = 9;
    
    double* probTable= new double[28]; // probabilities
    
    BaseSlotMachine* slotMachine = new BaseSlotMachine(3,9,winTable);
    double RETURN_RATE = slotMachine->RETURN_RATE;
    
    
    
    
    double money=0;
    double moneyWon=0;
    int n_try=100000000;
    

    std::cout << "Running test "<< std::endl;
    std::cout << "   ";
    
    double deviationSubsum = 0;
    double win;
    
    int noWinGames=0;
    
    for (int i=0; i<n_try; i++)
    {
        if (i % (n_try/100)==0)
    	{
  	        if ((100*(float)i/(float)n_try)>9) std::cout<<"\b";
	    	std::cout<<"\b\b"<<(100*(float)i/(float)n_try)<<"%";
    		std::cout << std::flush;
    	}
 
        slotMachine->playOneGame();
        win = slotMachine->lastWin;
        if (win==0) noWinGames++;
        money = money + win - 1;
        moneyWon += win;
        
        deviationSubsum += (0.9 - win)*(0.9 - win);
        
    }
    
    cout << endl<<"Ready"<< std::endl;
    cout << "------------------- Here are our statistics: -------------------" << std::endl;
    cout << "Games played: "<< n_try<<endl;
    cout<<"Return rate = "<<slotMachine->totalWin/n_try<<endl;
    cout<<"Money left = "<<slotMachine->moneyLeft<<endl;
    
    
    double deviation = sqrt(deviationSubsum / n_try);
    cout<<"Standard deviation = " << deviation << endl;
    cout<<"There have been "<<noWinGames<<" lost games (out of "<<n_try<<" games)"<<endl;
    std::cout << "----------------------------------------------------------------" <<endl<<endl;
   
    
    cout << "Press ENTER to continue";
    char temp = cin.get();
    cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
    
    
    
    
    
    cout<<endl<<"Now starting our game"<<endl;
    slotMachine->moneyLeft=100;
    slotMachine->totalWin=0;
    
    
    int n = 0;
    while (true){
        n++;
        cout << "----------------------------------------------------------------" <<endl<<endl;
        cout << "Your money: "<< slotMachine->moneyLeft<<endl;
        cout << "Totally won: "<< slotMachine->totalWin<<endl;
        cout << "Average winnings: "<< slotMachine->totalWin / n << endl;
        cout << "Press ENTER to play (and bet $1)";
        cout <<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
        char temp = cin.get();        
        
        if (slotMachine->playOneGame()>0)
        {
            cout<<endl<<"You Win!!! Your prize is "<<"$"<<slotMachine->lastWin<<endl;
        }
        else
        {
            cout<<endl<<"Sorry you lose!"<<endl;
        }
    
     
        slotMachine->print();


    }
    return 0;
}

