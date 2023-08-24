#include <iostream>
#include <stdlib.h>
#include <algorithm> 
#include <cmath>
#include "LeverBalancer.h"
using namespace std;

/**
 *Constructor of balancer
 *@param numberOfElements number of x's - variables to be found
 *@param LinearSum Linear sum of the system
 *@param Sum of all x's
 *@param dishCoefficients linear coefficients
 *@param dest result array 
 */
LeverBalancer::LeverBalancer(int numberOfElements,
                double LinearSum, double totalMass,
                double* dishCoefficients, double* dest)
{
  min_error = 0.00000001;
 
  n = numberOfElements;
  a = dishCoefficients;
  x = dest;
  M = totalMass; M0 = M;
  A = LinearSum; A0 = A;
}

/**
 * Checks if the system has positive solutions
 * @return true if the sysem can be balanced (has positive solutions), false if otherwise
 */
bool LeverBalancer::isSolvable()
{
    if (findMinFromN(0)<=A/M && findMaxFromN(0)>=A/M ) return true;
    else return false;
}


/**
 * Set the least descernible difference used while comparing two numbers
 * @param min_error Minimum discernible difference
 */
void LeverBalancer::setMinError(double min_error)
{
    LeverBalancer::min_error = min_error;
}




/**
 * Finds max value in the array of coefficients starting from N
 * @param l Number to start search from
 */
double LeverBalancer::findMaxFromN(int l)
{
    double temp=a[l];
    for (int i = l; i < n; i++) 
    {
        if (temp<a[i]) temp=a[i];
    }
    return temp;
}


/**
 * Finds min value in the array of coefficients starting from N
 * @param l Number to start search from
 */
double LeverBalancer::findMinFromN(int l)
{
    double temp=a[l];
    for (int i = l; i < n; i++) 
    {
        if (temp>a[i]) temp=a[i];
    }
    return temp;
}




/**
 *Balances the system specified in the constructor or, in other words,
 *finds, if it's possible, positive x1,x2,...,xn satisfying the system
 *  a1*x1+a2*x2+...+aN*xN = A 
 *  x1+x2+...+xN=M
 */
bool LeverBalancer::balance()
{
     if (! isSolvable()) return false;
    
    for (int i=0; i<n-1; i++)
    {
   
        double a_min = findMinFromN(i+1);// max and min without current
        double a_max = findMaxFromN(i+1);
         
         
         
        double min_x, max_x; 
         
        if (a[i]<A/M) // => M*a[i]-A <0 in case a[i] is to the left from the mass-center 
        {
            if (a_min<=A/M) min_x = 0; // we can always make the left part overweigh by concentrating all the mass left during the next step
            else
              min_x = (M*a_min - A) / (a_min-a[i]);
              
            max_x = (A - M* a_max)/ (a[i] - a_max);
        }

         
         
        if (a[i]>A/M) // Meaning we are to the right of the mass-center
        {
            if (a_max>=A/M)
                min_x = 0;
            else 
                min_x = (A - a_max * M) / (a[i] - a_max);

            max_x = (A - a_min * M) / (a[i] - a_min); // This is positive as the system is assumed to have positive solutions

        }

        
        //In case we are to choose the range [min_x, max_x] while a[i] is in the center
        if (a[i]==A/M || (abs(a[i]-A/M)<min_error) )    
        {
            
            // in the center
            min_x = 0;
            max_x= M; 
        }


        x[i]=min_x+(max_x-min_x)/2;
        

        A = A - a[i]*x[i];
        M = M - x[i];
       
       
    }

    x[n-1] = M;
    //Now the system is left with only one variable which must be "<<M;



    double testSum=0;
    double testM=0;


    bool allPositive=true;
    for (int i = 0; i < n; i++) {
        testSum+=a[i]*x[i];
        testM+=x[i];
        if (x[i]<0)
        {
            allPositive=false;
            return false;
        }
    }


    if (abs(testM-M0)<min_error && abs(testSum-A0)<min_error && allPositive==true)
        return true;
    else
        return false;

}



