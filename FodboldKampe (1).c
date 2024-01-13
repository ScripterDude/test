// Alexander Peter Olesen, aolse23@student.aau.dk, Cyber- og Computerteknologi
// Eksamensopgave 3: 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Symbolske konstanter
#define NAME_MAX 5
#define NUMBER_OF_TEAMS 12
#define NUMBER_OF_MATCHES 89
//Tekstformatering virker ikke på alle compilere, men det gør på linux 
#define FONT_BOLD "\e[1m"   
#define FONT_REGULAR "\e[m"





//  Prototyper
void file_pointer_check(FILE *f);
void file_read(FILE *f);
void proces_file();
int elm_cmp(void const *p1, void const*p2);
void sort_array();
void print_scoreboard();


// Deklaration af match-array
struct match {
    char ugedag[NAME_MAX],home_team[NAME_MAX],away_team[NAME_MAX];
    int day,month,home_score,away_score,spectators;
    double tid;
};

typedef struct match match; 
match match_array[NUMBER_OF_MATCHES];


//  Deklaration af hold-array
struct hold {
    char name[NAME_MAX]; int point, scored_goals, scored_goals_against,goal_difference;
};
typedef struct hold hold;
hold team_array[NUMBER_OF_TEAMS] = {
    {"FCN", 0, 0, 0},
    {"VB", 0, 0, 0},
    {"HIF", 0, 0, 0},
    {"BIF", 0, 0, 0},
    {"VFF", 0, 0, 0},
    {"AGF", 0, 0, 0},
    {"OB", 0, 0, 0},
    {"LBK", 0, 0, 0},
    {"FCM", 0, 0, 0},
    {"RFC", 0, 0, 0},
    {"FCK", 0, 0, 0},
    {"SIF", 0, 0, 0},
};


// Mainfunktion (Topdown)
int main(void){
    FILE *f = fopen("kampe-2023-2024.txt","r");
    file_pointer_check(f);
    file_read(f);
    proces_file();
    sort_array();
    print_scoreboard();
    fclose(f);
    return 0;
}



//  Fejlhåndtering ved filåbning
void file_pointer_check(FILE *f){
    if ( f== NULL){
        printf("filen kunne ikke åbnes");
        exit(EXIT_FAILURE);
    }
}

//  Indlæser filindhold
void file_read(FILE *f){
    int scanres = 12;
    //  For løkke som iterer gennem alle linjer i tekstfil
    for (int line = 0; line < NUMBER_OF_MATCHES; line++){
        if(scanres=(fscanf(f,"%5s %2d %*c %2d %lf %5s %*c %5s %d %*c %d %d\n",&match_array[line].ugedag, &match_array[line].day, &match_array[line].month, &match_array[line].tid, &match_array[line].home_team, &match_array[line].away_team,&match_array[line].home_score,&match_array[line].away_score,&match_array[line].spectators))){
        }
    }
}

// Behandler indholdet af filen
void proces_file(){
    //  Iteration af alle kampene
    for (int match_index = 0; match_index < NUMBER_OF_MATCHES; match_index++){

        int home_team_index = -1;
        int away_team_index = -1;

        //  Iteration af holdene
        for(int team_index=0;team_index<NUMBER_OF_TEAMS;team_index++){ 
            //  Finder hjemmehold i arrayet
            if (strcmp(team_array[team_index].name, match_array[match_index].home_team) == 0){
                home_team_index = team_index;
            }
            //  Finder udehold i arrayet
            if (strcmp(team_array[team_index].name, match_array[match_index].away_team) == 0){
                away_team_index = team_index;
            }
        }
        // Case hjemmeholdet har vundet
        if (match_array[match_index].home_score > match_array[match_index].away_score){
            team_array[home_team_index].point += 3;
        }
        // Case udeholdet har vundet
        else if (match_array[match_index].home_score < match_array[match_index].away_score){
            team_array[away_team_index].point += 3;
        }
        // Case uafgjort kamp
        else{
            team_array[home_team_index].point += 1;
            team_array[away_team_index].point += 1;
        }
        //  Tildeler mål
        team_array[home_team_index].scored_goals += match_array[match_index].home_score;
        team_array[home_team_index].scored_goals_against += match_array[match_index].away_score;

        team_array[away_team_index].scored_goals += match_array[match_index].away_score;
        team_array[away_team_index].scored_goals_against += match_array[match_index].home_score;
    }
    //  Udregner af maalforskel
    for (int j = 0; j < NUMBER_OF_TEAMS; j++){
        team_array[j].goal_difference=team_array[j].scored_goals-team_array[j].scored_goals_against;
    }
}

//  Sorterteringsgrundlag
int elm_cmp(void const *p1, void const*p2) {
    const hold *holdp1 = (const hold*)p1;
    const hold *holdp2 = (const hold*)p2;

    // Primær sortering (Point)
    if (holdp2->point != holdp1->point) {
        return holdp2->point - holdp1->point;
    }
    // Sekundær sortering (maalforskel)
    return holdp2->goal_difference - holdp1->goal_difference;
}

// Sortering udførelse
void sort_array() {
   qsort(team_array,NUMBER_OF_TEAMS,sizeof(team_array[0]),elm_cmp);
}

// Udskriver kamp resultaterne
void print_scoreboard() {
    printf(FONT_BOLD"Hold      Point  Maal   Maal-mod\n"FONT_REGULAR);
    printf("--------------------------------\n");
    for(int i=0;i<NUMBER_OF_TEAMS;i++) {
        printf("%-5s %6d %6d %6d\n",team_array[i].name, team_array[i].point, team_array[i].scored_goals, team_array[i].scored_goals_against);
    }
}