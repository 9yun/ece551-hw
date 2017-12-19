#include <stdio.h>
#include <stdlib.h>
struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;
double balance(int x,double y,double z){
       double a=y/12;
       z=z*(1+a)+x;
       return z;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired){
     double current_balance=initial;
     for(int Age=startAge;Age<startAge+working.months;Age++){
     int wAge_year=Age/12;
     int wAge_month=Age%12;
     printf("Age %3d month %2d you have $%.2lf\n",wAge_year,wAge_month,current_balance);
     current_balance=balance(working.contribution, working.rate_of_return,current_balance); 
 }
     for(int Age=startAge+working.months;Age<startAge+working.months+retired.months;Age++){
     int rAge_year=Age/12;
     int rAge_month=Age%12;
     printf("Age %3d month %2d you have $%.2lf\n",rAge_year,rAge_month,current_balance);
     current_balance=balance(retired.contribution, retired.rate_of_return,current_balance);
 }
}
int main(){
   retire_info working;
   retire_info retired;
   working.months=489;
   working.rate_of_return=0.045;
   working.contribution=1000;
   retired.months=384;
   retired.rate_of_return=0.01;
   retired.contribution=-4000;
   retirement(327,21345,working,retired);
   return EXIT_SUCCESS;
}
