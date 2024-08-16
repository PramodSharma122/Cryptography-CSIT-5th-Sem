// To familiar with fermat's theorem.
// To test number is prime or not (Lab 6) 2081-03-17

#include<stdio.h>
#include<math.h>
int pow1(int a,int b, int M){
    int x;
    x=pow(a,b);
    x=x%M;

    return x;
}

int gcd(int a, int b){
    if(a==0)
        return b;
    else
        return gcd(b%a,a);
}

int modInverse(int a,int m){
    if(gcd(a,m)==1)
        return pow1(a,m-2,m);
    else{
        printf("Not co prime");
        return -1;
    }
}

int main(){
    int a=3,m=7;
    printf("%d",modInverse(a,m));
    return 0;
}
