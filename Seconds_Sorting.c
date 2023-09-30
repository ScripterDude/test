#include <stdio.h>

#define SEC_TO_MIN 60
#define SEC_TO_HOUR 3600
#define SEC_TO_DAY 86400
#define SEC_TO_WEEK 604800

int inputSec,Weeks,Days,Hours,Min,Sec;

int main(void) {
  
  // Get the time in seconds
  printf("Indtast et antal sekunder.\n ");
  scanf("%d",&inputSec);

  // Calculation
  Weeks = inputSec/SEC_TO_WEEK;
  Days = (inputSec%SEC_TO_WEEK)/SEC_TO_DAY;
  Hours = (inputSec%SEC_TO_DAY)/SEC_TO_HOUR;
  Min = (inputSec%SEC_TO_HOUR)/SEC_TO_MIN;
  Sec = inputSec%SEC_TO_MIN;

  // Display results
  printf("%d uger, %d dage, %d timer, %d minutter og %d sekunder.\n",Weeks,Days,Hours,Min,Sec);

  return 0;
}