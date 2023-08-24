/**
 * WeighedRandom generator
 * Generator of distributed random numbers
 * getRNDResultNumber - returns an integer - the number of the outcome.
 * 
 */
class WeighedRandom
{

  private: 
      double* range;
      int numberOfElements;

  public: 
   

   
   
  /**
   * Weighed Random generator initialization
   * @param n Number of outcomes
   * @param a Array of probabilities of the outcomes numbered from 1 to N (discrete probability distribution)
   */
   WeighedRandom(int n, double* a);



   /**
    * Returns a random integer - one of the numbered outcomes.
    * The discrete distribution is specified in the constructor
    * @return Number of outcome
    */
   int getRNDResultNumber();

};
