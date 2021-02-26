/* Name: Zekai Zhang (zekaiz2) 
Partner: hz39, zw53
Introduction: This program first asks the user to enter a row index. Then it calculates all coefficients in that row and use the standard function printf to print out the coefficients.
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int row;

    printf("Enter a row index: "); // print prompt
    scanf("%d",&row); // enter index from user

    /* declare integer variables: coeff is the coefficient to be printed
    k and i are counters. */
    unsigned long coeff, k, i;
    
    /* the outer for loop calculates the coefficient under each counter k. */
    for( k = 0; k <= row; k++){
        if (k == 0){ // directly set coeff to 1 when k = 0.
            coeff = 1;
            printf("%ld ", coeff); // print the coefficient
        }
        else{
            /* the inner for loop calculates the division in the ∏ function. */
            unsigned long  coeff = 1; // init both numerator and denominator to char16_t
            for( i = 1; i <= k; i++){ // loop until i > k
                coeff *= row + 1 - i; // calculate the numerator
                coeff /= i; // calculate the denominator
            }
            
            printf("%ld ", coeff); // print the coefficient
        }
    }
    
    return 0;
}
