// To familiar with additive inverse. (Lab-3)(2081-03-17)

#include<stdio.h>
void main(){
    int a,b,i;
    printf("Enter 2 numbers: ");
    scanf("%d%d",&a,&b);
    for(i=0;i<b;i++){
        if(((a+i)%b)==0)
            break;
    }
    printf("Additive inverse of %d is: %d",a,i);
}
