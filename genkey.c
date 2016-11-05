#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int prime(int n)
{
    int i,j,count=0;

    if (n == 1) {
        return 2;
    }
    for(i=3;i<=10000;i+=2)
    {
        int isPrime=1;
        int jMax = sqrt(i);
        for(j=3;j<=jMax;j+=2)
        {
            if(i%j==0)
            {
                isPrime=0;
                break;
            }
        }
        if(isPrime)
        {
            if(++count==n)
            {
                return i;
            }
        }
    }
    return 0;
}

int GCD(int a, int b)
{
    int temp;
    while (b != 0)
    {
        temp = a % b;

        a = b;
        b = temp;
    }
    return a;
}

int findE(int phi){
        int i = 2;
        for(i=2; i<phi; i++){
                if(GCD(i, phi)==1){
                        return i;
                }
        }
        return -1;
}

int findD(int e, int phi){
        int d = 1;
        for(d=1; d<10000; d++){
                if((e*d)%phi == 1){
                        return d;
                }
        }
        return -1;
}

int main(int argc, char* argv[]){
	int firstNum = atoi(argv[1]);
        int secondNum = atoi(argv[2]);
	/*
        printf("Enter nth prime to compute: ");
        scanf("%d", &firstNum);
        printf("Enter mth prime to compute: ");
        scanf("%d", &secondNum);
        printf("Results\n");*/

        int firstPrime = prime(firstNum);
        int secondPrime = prime(secondNum);
        int c = firstPrime*secondPrime;
        int m = (firstPrime-1)*(secondPrime-1);
        int e = findE(m);
        int d = findD(e, m);

        printf("%dth prime = %d\n", firstNum, firstPrime);
        printf("%dth prime = %d\n", secondNum, secondPrime);
        printf("c = %d\n", c);
        printf("m = %d\n", m);
        printf("e = %d\n", e);
        printf("d = %d\n", d);

        printf("Public Key: (%d, %d) \n", e, c);
        printf("Private Key: (%d, %d) \n", d, c);
	return 0;
}
