#include <stdio.h>

int main(void){

int watt,lumens;

printf("Enter watt value.\n");
scanf("%d",&watt);

switch (watt){
case 15:
    lumens = 125;
    break;
case 25:
    lumens = 215;
    break;
case 40:
    lumens = 500;
    break;
case 60:
    lumens = 880;
    break;
case 75:
    lumens = 1000;
    break;
case 100:
    lumens = 1675;
    break;
default:
    lumens = -1;
    break;
}

printf("The corresponding lumens is: %d.",lumens);
}

