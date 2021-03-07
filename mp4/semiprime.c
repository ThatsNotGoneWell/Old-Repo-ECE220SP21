#include <stdlib.h>
#include <stdio.h>



/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
	   return 0; //here should return 0 because this number is not prime
        }
    }
    return 1; //here should return 1 because this number is prime
}


/*
 * Name: Zekai Zhang (netid: zekaiz2)
 * Partner: hz39, zw53
 * Introduction: There are many errors in the provided code. In function is_prime, 
 * the return value should be flipped. In the semiprime function below, in the second for 
 * loop, k should be the division of i and j, or it will print incorrect output. Finally, add 
 * return 1 to make sure the function will return a result.
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
		    k = i/j; //should be division instead of modulo
                    if (is_prime(k) && (k>=j)) { // should be checking if k>=j
                        printf("%d ", i);
		 ret = 1; 
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
