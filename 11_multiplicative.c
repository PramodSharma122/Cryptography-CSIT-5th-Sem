// 

#include<stdio.h>
int gcd(int a,int b,int* x,int* y);
void modInverse(int a, int m){
    int x,y;
    int g=gcd(a,m,&x,&y);
    if(g!=1)
        printf("Inverse doesn't exist");
    else{
        int res=(x%m+m)%m;
        printf("Modular multiplicative inverse is %d",res);
    }
}
int gcd(int a,int b,int* x,int* y){
    if(a==0){
        *x=0,*y=1;
        return b;
    }
    int x1,y1;
    int g=gcd(b%a,a,&x1,&y1);
    *x=y1-(b/a)*x1;
    *y=x1;
    return g;
}
int main(){
    int a=3,m=7;
    modInverse(a,m);
    return 0;
}