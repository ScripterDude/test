// Alexander Peter Olesen, aolse23@student.aau.dk, Cyber- og Computerteknologi
// Eksamensopgave 1: En regnemaskine på kommandolinjen. Lommeregner med binære og unære regneoperationer.
#include <stdio.h>
#include <math.h>

// Funktions prototyper
void scan_data(char *operator, double *operand);
void do_next_op(char *operator, double *operand, double *accumulator, char *running);
void run_calculator(double *accumulator,char *operator);
void help_list();

// Topdown main funktion
int main (void){
    char operator;
    double operand, accumulator = 0;
    char is_running = 1;  
    printf("Welcome to Alexanders calculator program:\nType h for help\n\n");
    // Loop af Topdown indtil operator input = 'q'
    while(is_running){                                             //0 Tjekker is_running
        scan_data(&operator,&operand);                            //1 Scanner brugerinput (operator og evt operand)
        do_next_op(&operator,&operand,&accumulator,&is_running); //2 Laver den matematiske operation 
        run_calculator(&accumulator,&operator);                 //3 Printer det akkumulerede resultat 
    } 
    return 0;
}

// Brugerinput funktion
void scan_data(char *operator, double *operand){
    int binary_operator = 0, unary_operator = 0; //Hensigten er at skale boolsk variable
 
    //  Inputvalidering ved brug af while løkken indtil gyldig operator
    while (binary_operator == 0 && unary_operator == 0){
        printf("Enter operator:\n");
        scanf(" %c", operator);
 
        // Sorterer operatertypen
        if (*operator== '+' || *operator== '-' || *operator== '*' || *operator== '/' || *operator== '^'){
            binary_operator = 1;
        }
        else if (*operator== '!' || *operator== '%' || *operator== '#' || *operator== 'q'|| *operator== 'h'|| *operator== 'r'){
            unary_operator = 1;
        }
    }
 
    // Operand input hvis operatortypen er binær
    if (binary_operator){
        printf("Enter operand:\n");
        scanf("%lf", operand);
    }
}

// Matematisk operation funktion
void do_next_op(char *operator, double *operand, double *accumulator, char *is_running){
    switch (*operator) {                                                                                      
        // Binære operatorer 
        case '+': *accumulator += *operand; break;
        case '-': *accumulator -= *operand; break;
        case '*': *accumulator *= *operand; break;
        case '/': *accumulator = (*operand!=0) ? *accumulator / *operand : *accumulator; break; // forhindrer division med nul
        case '^': *accumulator = pow(*accumulator,*operand); break;
        // Unære operatorer
        case '#': *accumulator = (*accumulator>=0) ? sqrt(*accumulator) : *accumulator; break; // forhindrer at finde kvadratroden af et negativt tal
        case '%': *accumulator *= -1; break;
        case '!': *accumulator = (*accumulator==0) ? *accumulator: 1 / *accumulator; break;
        case 'r': *accumulator = 0; break;
        case 'q': *is_running = 0; break; // Slutter programmet ved at stoppe løkken i main
        case 'h': help_list();
    }
}

// Printer foreløbige og endelige resultat
void run_calculator(double *accumulator,char *operator){
    if (*operator!='q' && *operator!='h'){
        printf("Result so far: %lf\n", *accumulator);
    }
    else if (*operator=='q'){
        printf("The Final result: %lf\n", *accumulator);
    }
    
}
//Printer hjælpeliste over gyldige oepratorer
void help_list(){
    printf("     list of valid operators:\n"
           "+    for addition\n"
           "-    for subttraction\n"
           "*    for multiplcation\n"
           "/    for division\n"
           "^    for the power of operand\n"
           "#    to find the square root\n"
           "%%    to invert sign\n"
           "!    to divide by 1\n"
           "q    to end and display final result\n"
           "r    to reset accumulator\n");
}