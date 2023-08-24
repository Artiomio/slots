/**
 * Finder of positive solutions x1,x2,..xN for the given a1,a2,..,aN, A, M,
 * satisfying the two equations:
 *   a1*x1+a2*x2+...+aN*xN = A 
 *   x1+x2+...+xN=M
 *  
 * The problem can be seen as balancing a lever
 */
class LeverBalancer
{
    public:
    
    double min_error;// = 0.00000001;
    

    /**
     * Constructor of lever balancer
     * @param numberOfElements number of x's - variables to be found
     * @param LinearSum Linear sum of the system
     * @param Sum of all x's
     * @param dishCoefficients linear coefficients
     * @param dest result array 
     */
    LeverBalancer(int numberOfElements,
                     double LinearSum, double totalMass,
                    double* dishCoefficients, double* dest);


    /**
     * Checks if the linear system has positive solutions
     * @return true if the sysem can be balanced (has positive solutions), false if otherwise
     */
    bool isSolvable();



    /**
     * Set the least descernible difference used while comparing two numbers
     * @param min_error Minimum discernible difference
     */
    void setMinError(double min_error);




    private:
    
    int n;
    double* a;
    double* x;
    double A, A0;
    double M, M0;
    
    
    
    /**
     * Finds max value in the array of coefficients starting from N
     * @param l Number to start search from
     */
    double findMaxFromN(int l);



    /**
     * Finds min value in the array of coefficients starting from N
     * @param l Number to start search from
     */
    double findMinFromN(int l);



   public:
    

    /**
     *Balances the system specified in the constructor or, in other words,
     *finds, if it's possible, positive x1,x2,...,xn satisfying the system
     *  a1*x1+a2*x2+...+aN*xN = A 
     *  x1+x2+...+xN=M
     */
    bool balance();


};    