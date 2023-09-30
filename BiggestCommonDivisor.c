#include <stdio.h>

int main(void){
int a,b,divisor,res;

//User Input & Check if correct
do{
    printf("Indtast 2 positive heltal\n");
    scanf("%d%d",&a,&b);
} while (a<=0||b<=0);

//Determining highest potential divisor
divisor=(a<b)?a:b;

//Calculating systematicly divisors.
for(divisor;!res;divisor--){
    if (a%divisor==0&&b%divisor==0){
        printf("Den stoerste faelles divisor er %d\n",divisor);
        res=1;
    }
}
return 0;
}