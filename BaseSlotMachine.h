#include"WeighedRandom.h"
/**
 * Base Slot machine
 * 
 */
class BaseSlotMachine
{
    public:
    
    double RETURN_RATE; 
    double HIT;
    
    int* screen;
    
    
    // numberOfSymbol is ((N-1) mod 9) + 1  -- N=[1..9]
    // rankOfCombination is 3 + [(N-1)/9]  -- [3..5]

    double* winTable;
    double PROB_OF_LOSS;
    int NUMBER_OF_LINES_IN_WIN_TABLE;
    int NUMBER_OF_COLUMNS_IN_WIN_TABLE;
    WeighedRandom* weighedRandomGenerator;
    
    int lastCombinationNumber;
    double lastWin;
    double moneyLeft;
    double totalWin;
    
    
   /**
    * Constructor of the slot-machine
    * @param numberOfLinesInWinTable number of lines in the pay table
    * @param numberOfColumnsInWinTable number of columns in the pay table
    * @param winTable Pay table array
    * 
    */
    BaseSlotMachine(int numberOfLinesInWinTable, int numberOfColumnsInWinTable, double* winTable );
    
    
    
    /**
     * Run one game of the slot-machine
     * @return number of money credits won
     */
    double playOneGame();



    
    /**
     * Printing the 3x5 screen of the slot-machine
     */
    void print();
    
    private:

    int rndWithout(int toBeExcluded, int a, int b);

    int rnd(int a, int b); // [a,b]
    
};
