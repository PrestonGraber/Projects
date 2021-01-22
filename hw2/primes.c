/* File: primes.c */
/* Author: Britton Wolfe */
/* Date: July 16, 2009 */
/* This program outputs all the primes in the range given */
/* by the command line arguments */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(int argc, const char** argv){

    int lowerBound, upperBound;

    if(argc != 3){
        fprintf(stderr, "USAGE: %s lowerBound upperBound\n", argv[0]);
       
        return -1;
    }
  
    lowerBound = atoi(argv[1]);
    upperBound = atoi(argv[2]);
  
    if(lowerBound < 1 || upperBound < 1){
        fprintf(stderr, "ERROR: both the lowerBound (%d) and the upperBound (%d)"
	          " must be positive.\n", lowerBound, upperBound);
        return -2;
    }

    int isItPrime;

    if(lowerBound < 2){

        lowerBound++;
    }
    for(int i = lowerBound ; i <= upperBound; i++){

        isItPrime = 1;

        for(int j = 2; j<= i/2; j++){

            if(i%j == 0){
                isItPrime = 0;
                break;
            }
        }
        if(isItPrime == 1){
            printf("%d,\n ", i);
        }
    }    
    return 0;
}

