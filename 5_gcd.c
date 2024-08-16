// Method:2 GCD 
// To familiar with GCD with euclidean algorithm.  2081-03-17 (Lab-5)

#include<stdio.h>

int gcd(int a,int b) {
    if(b==0)
        return a;

    else
        return gcd(b,a%b);

}
int main() {
    int a,b;

    printf("Enter two integers: ");
    scanf("%d%d",&a,&b);
    printf("GCD of %d and %d is: %d\n",a,b,gcd(a,b));

}