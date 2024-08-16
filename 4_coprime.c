// To familiar with co-prime (relatively prime).  2081-03-17 (Lab-4)

#include<stdio.h>

int gcd(int a,int b) {
    if(b==0)
        return a;

    else
        return gcd(b,a%b);

}
int main() {
    int a,b,i,gcd;

    printf("Enter two integers: ");
    scanf("%d%d",&a,&b);
    for(i=1;i<=a;i++){
        if(a%i==0 && b%i==0)
        gcd=i;
    }
    if(gcd==1){
        printf("CO-Prime numbers");
    }
    else
        printf("Not CO-Prime numbers");

}