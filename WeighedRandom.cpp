#include <iostream>
#include<stdlib.h>
#include<algorithm> 
#include<cmath>
#include "WeighedRandom.h"
using namespace std;

/**
 * Weighed Random generator initialization
 * @param n Number of outcomes
 * @param a Array of probabilities of the outcomes numbered from 1 to N (discrete probability distribution)
 */
WeighedRandom::WeighedRandom(int n, double* a) 
{ 
    numberOfElements=n;
    range = new double[n+1]; // the number of ranges for n items is always n+1
    
    // Normalization
    double normalization=0;
    int i; 
    
    for (i=0; i<n; i++) normalization=normalization+a[i];
    
    for (i=0; i<n; i++) a[i]=a[i] / normalization;
    
    range[0]=0; // The left range
    
    
    for (i=1; i<n+1; i++ )
       range[i]=range[i-1]+a[i-1];

     
    // Now range[] contains a number of ranges of the [0..1] interval
    // with lengthes according to their probabilities
    // E.g. we have three outcomes A, B è C with their probabilities being 0.3, 0.1 è 0.6,
    // the interval shall be divided by four points:
    //   range[0]=0; range[1]=0.3; range[2]=0.4; range[3]=1; 
}


/**
 * Returns a random integer - one of the numbered outcomes.
 * The discrete distribution is specified in the constructor
 * @return Number of outcome
 */
int WeighedRandom::getRNDResultNumber() 
{
    double rnd01=(double)rand()/(double)((unsigned)RAND_MAX+1);
   
    int n = numberOfElements+1;

    int i=0;
    
    while ( (i<n-1) && !((rnd01>=range[i]) && (rnd01<=range[i+1])) )
      i++;
      
    if (rnd01>=range[n-1]) i=n-2; 

    return i+1; // Outcomes are numbered from 1
   
}

