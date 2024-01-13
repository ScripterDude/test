// Alexander Peter Olesen, aolse23@student.aau.dk, Cyber- og Computerteknologi
// Eksamensopgave 2: Yatzy med mange terninger. Kan slås med N antal terninger. Spillet er baseret på 15 runder.
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define DICE_SURFACES 6
#define GAMEROUNDS 15
#define BONUS_LIMIT 63
#define FONT_BOLD "\e[1m"   //Tekstformatering virker ikke på alle compilere, men det gør på linux 
#define FONT_REGULAR "\e[m"

// funktionernes protyper.
void welcome_text(); // datatypen void, parameterløs 
int define_dice_amount(); // datatypen int, parameterløs 
void roll_multiple_dice(int N, int *dice_value);  // datatypen void, i den formelle parametrer har vi N som er et inputparameter og er af datatypen int altså et heltal. Derudover har vi dice_value som er en pointer altså en outputparameter 
int process_roll_outcome(char round_name[][10], int N, int *dice_value, int round);//   Datatypen integer
void print_scoreboard(char round_name[][10], int scoreboard_res[]);

//  Top-Down programmering
int main(void) {
    char round_name[][10] = {"1-ere   ", "2-ere   ", "3-ere   ", "4-ere   ", "5-ere   ", "6-ere   ", "Et par  ","To par  ", "Tre ens ", "Fire ens", "Lille   ", "Stor    ", "Fuld Hus", "Chance  ", "YATZY!  "};
    int scoreboard_res[GAMEROUNDS] = {0};

    welcome_text();

    int N = define_dice_amount();
    int dice_value[N];
    srand(time(NULL));

    for (int round = 1; round <= GAMEROUNDS; round++) {
        roll_multiple_dice(N, dice_value);
        scoreboard_res[round - 1] = process_roll_outcome(round_name, N, dice_value, round);
    }

    print_scoreboard(round_name, scoreboard_res);

    return 0;
}

//  Print af overskrift
void welcome_text() {
    printf("|--------  Welcome to Yatzy!   -------|\n\n");
}

// Dialog med bruger hvor N (antal af terninger) defineres
int define_dice_amount() {
    int N = 0;
    int attempts = 0;

    printf("How many dice do you wish to play with?\n");

    for (int count = 0; count < GAMEROUNDS; count++) {
        while (N < 5) {
            scanf("%d", &N);
            attempts += 1;
            if (attempts >= 1 && N < 5) {
                printf("Invalid input, try again. (Has to be at least 5 dice)\n");
            }
        }
    }
    //  "Rolling the dice..." animation
    printf("Rolling the dice");
    for (int i = 0; i < 3; i++) {
        sleep(1);
        printf(".");
    }
    printf("\n");

    return N;
}

// Simulerer terningekast
void roll_multiple_dice(int N, int *dice_value) {
    //Looper N antal gange baseret på brugerinput
    for (int i = 0; i < N; i++) {
        int throw = (rand() + i) % DICE_SURFACES + 1;
        dice_value[i] = throw;
    }
}

// Bearbejder "outputtet" af simulerede terninger på baggrund af runde nr.
int process_roll_outcome(char round_name[][10], int N, int *dice_value, int round) {
    int score = 0;
    int arr[6] = {0};   // Holder styr på hvor mange terninger der har slået mellem 1-6
    int pair1 = 0, pair2 = 0;
    int target;     // Antal ens terninger som der ønskes at søge efter 
    printf("\n%s: ", round_name[round - 1]);

    for (int i = 0; i < N; i++) {
        printf(" %d", dice_value[i]);
    }
    //  Runde 1-6 (Tæller antallet af)
    if (round <= 6) {
        // Process for rounds 1-6: Count the occurrences of the current round number
        for (int i = 0; i < N; i++) {
            if (dice_value[i] == round) {
                score += round;
            }
        }
    } 
    //  Runde 7-15
    else {
        //  Starter med at tælle antal af terninger der har slået 1-6 op i et nyt array (bruges til 7+ cases)
        for (int i = 0; i < N; i++) {
            for (int k = DICE_SURFACES; k >= 1; k--) {
                if (k == dice_value[i]) {
                    arr[k - 1]++;
                }
            }
        }
        //  Overordnet Runde switch til sortering af runder. (fallthrough)
        switch (round) {
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
                //Switch for case 7-10 for at give "target"
                switch (round) {
                    case 7:
                    case 8:
                        target = 2;
                        break;
                    case 9:
                        target = 3;
                        break;
                    case 10:
                        target = 4;
                        break;
                    default:
                        break;
                }
                // Case 7, 9, 10: 
                if (round == 7 || round == 9 || round == 10) {
                    //  Tjekker efter om der er slået målværdien/over "target" og hvis der gør tilføres point, j=terningsum
                    for (int j = DICE_SURFACES; j >= 1; j--) {
                        if (arr[j - 1] >= target) {
                            score += j * target;    
                            break;
                        }
                    }
                } 
                // Case 8: To par
                else if (round == 8) {
                    for (int j = 6; j >= 1; j--) {
                        //finder første højeste par (Ved at tælle oppefra ned)
                        if (arr[j - 1] >= 2 && pair1 == 0) {
                            pair1 = j;
                        } 
                        //finder næsthøjeste par og forsikrer det ikke er par1 ved (else)
                        else if (arr[j - 1] >= 2 && pair2 == 0) {
                            pair2 = j;
                        }
                    }
                    //Tilføre point fra runden (*2 idet pair viser tal og ik summen)
                    if (pair1 != 0 && pair2 != 0) {
                        score += pair1 * 2 + pair2 * 2;
                    }
                }
                // Case 11: Lille (tallene 1-5)
                else if (round == 11) {
                    //  Tjekker om der er 1+ slag af tallene i intervallet 1-5 (bemærk array starter i 0)
                    if (arr[0] >= 1 && arr[1] >= 1 && arr[2] >= 1 && arr[4] >= 1 && arr[4] >= 1) {
                        score += 15;
                    }
                } 
                // Case 12: Stor (tallene 2-6)
                else if (round == 12) {
                    //  Tjekker om der er 1+ slag af tallene i intervallet 2-6 (bemærk array starter i 0)
                    if (arr[1] >= 1 && arr[2] >= 1 && arr[3] >= 1 && arr[4] >= 1 && arr[5] >= 1) {
                        score += 20;
                    }
                } 
                // Case 13: Fuldt Hus (3 ens og 1 par)
                else if (round == 13) {
                    for (int j = DICE_SURFACES; j >= 1; j--) {
                        //  Tjekker om der er 3 ens & par1 ikke er fundet (bemærk pair=3 ens)
                        if (arr[j - 1] >= 3 && pair1 == 0) {
                            pair1 = j;
                        //  Tjekker om der er et par (2) hvis det nuværende tjek ikke er assignet til "pair1 (3ens)"
                        } else if (arr[j - 1] >= 2 && pair2 == 0 && j != pair1) {
                            pair2 = j;
                        }
                    }
                    //  Udregner scoren hvis 3 ens og 1 par er fundet
                    if (pair1 != 0 && pair2 != 0) {
                        score += pair1 * 3 + pair2 * 2;
                    }
                //  Case 14: Chance (alle tal lagt sammen)
                } else if (round == 14) {
                    score += (arr[0] * 1 + arr[1] * 2 + arr[2] * 3 + arr[3] * 4 + arr[4] * 5 + arr[5] * 6);
                } 
                //  Case 15: Yatzy (5 ens)
                else if (round == 15) {
                    //  Tjekker der mindst er 5 slag med ens antal øjne
                    if (arr[0] >= 5 || arr[1] >= 5 || arr[2] >= 5 || arr[3] >= 5 || arr[4] >= 5 || arr[5] >= 5) {
                        score += 50;
                    }
                }
                break;
            default: break;
        }
    }
    //  Printer scoren for runden
    printf(" --  %d", score);
    return score;
}

// Printer selve Scoreboardet
void print_scoreboard(char round_name[][10], int scoreboard_res[]) {
    int bonus = 0;
    int total = 0;

    printf(FONT_BOLD "\n\n\nScore board:" FONT_REGULAR);

    // printer resultat fra runde 1-6
    for (int round = 1; round <= 6; round++) {
        printf("\n%s :  %d", round_name[round - 1], scoreboard_res[round - 1]);
    }

    // Tilfører eventuelt bonus hvis lig/over BONUS_Limit
    if (scoreboard_res[0] + scoreboard_res[1] + scoreboard_res[2] + scoreboard_res[3] + scoreboard_res[4] + scoreboard_res[5] >= BONUS_LIMIT) {
        bonus = 50;
        total = bonus;
    }
    printf("\nBONUS    :  %d\n\n", bonus);

    // printer resultat fra runde 7-15
    for (int round = 7; round <= GAMEROUNDS; round++) {
        printf("\n%s :  %d", round_name[round - 1], scoreboard_res[round - 1]);
    }

    // Udregner TOTALVÆRDIEN
    for (int i = 0; i < GAMEROUNDS; ++i) {
        total += scoreboard_res[i];
    }

    printf(FONT_BOLD"\nTOTAL    :  %d\n"FONT_REGULAR, total);
}