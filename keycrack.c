#include <stdio.h>
#include <math.h>

void primeFact(int c, int *a, int *b){
	int i = 2;
	for(i=2; i<(c/2); i++){
		if(c%i == 0){
			*a = i;
			*b = c/i;
			return;
		}
	}
	printf("Not a valid RSA Key\n");
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
	int a = 0;
	int b = 0;
	int c = atoi(argv[2]);
	primeFact(c, &a, &b);
	printf("Prime factors: a=%d, b=%d\n", a, b);

        int m = (a-1)*(b-1);
        int e = findE(m);
        int d = findD(e, m);

        printf("c = %d\n", c);
        printf("m = %d\n", m);
        printf("e = %d\n", e);
        printf("d = %d\n", d);

        printf("Public Key: (%d, %d) \n", e, c);
        printf("Private Key: (%d, %d) \n", d, c);
	return 0;
}
