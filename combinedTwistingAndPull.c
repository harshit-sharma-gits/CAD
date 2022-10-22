/* This program is to calculate the diameter `d` for a circulat shaft under
 * combined twisting moment `T` and axial pull `P`
 * 
 * Variables to input:
 *    Axial Pull `P` (in N)
 *    Twisting Moment `T` (in N-m)
 *    Factor of Safety
 *    Maximum Yield Strength `sigmaYT` (in N/m^2)
 * 
 * This program uses Maximum Shear Stress Theory of Failure, and Regula Falsi
 * Approximation Method to calculate the result.
 * 
 * Copyright 2022, Harshit Sharma <harshits908@gmail.com>
 *                 Aastha Chauhan <aastha4139@gmail.com>
 * Distributed under the terms of MIT License.
 */

#include <stdio.h>
#include <math.h>

#define PI 3.14159265

#define MAX_ITER 1000000

float f(float P, float d, float T, float sigmaYT, float FOS)
{
    float result = ((pow(d,6)*pow(sigmaYT,2))/(4*FOS*FOS)) -
                    ((4*P*P*d*d)/(PI*PI)) -
                    ((256*T*T)/(PI*PI));

    return result;
}


void calcInitialGuesses(float* a, float* b, float P, float T, float sigmaYT, float FOS)
{
    *a = 0;
    for (int i=1 ; i<=100 ; ++i)
    {
        *b = (double)i;
        if ( f(P, *a, T, sigmaYT, FOS) * f(P, *b, T, sigmaYT, FOS) < 0)
            return;
    }
}


int main() {
    
    printf("Program to find diameter of a shaft under combined twisting moment T and axial pull P\n\n");
    
    float sigmaYT, P, T, FOS;
    
    printf("Enter pulling force (in N): ");
    scanf("%f", &P);
    
    printf("Enter twisting moment (in N-m): ");
    scanf("%f", &T);
    
    printf("Enter Factor of Safety: ");
    scanf("%f", &FOS);
    
    printf("Enter Maximum Yield Strength (in N/m^2): ");
    scanf("%f", &sigmaYT);
    
    float a = 0, b = 1;
    
    calcInitialGuesses(&a, &b, P, T, sigmaYT, FOS);
    
    printf("\n\nInitial guesses taken for diameter are %f meter and %f meter for Regula-Falsi Method", a, b);
    
    float result = a;          // Let the initial result be a
    
    /*
    **  NOW THE LOOP FOR REGULA FALSI METHOD
    */
    
    for (int i=0; i < MAX_ITER; ++i)
    {
        
        result = (a*f(P, b, T, sigmaYT, FOS) - b*f(P, a, T, sigmaYT, FOS)) / (f(P, b, T, sigmaYT, FOS) - f(P, a, T, sigmaYT, FOS));
 
        // Check if the above found point is root
        if (f(P, result, T, sigmaYT, FOS) == 0)
            break;
 
        // Decide the side to repeat the steps
        else if (f(P, result, T, sigmaYT, FOS) * f(P, a, T, sigmaYT, FOS) < 0)
            b = result;
        else
            a = result;
    }
    
    printf("\n\nThe diameter of the shaft must be %f meter", result);

    return 0;
}
