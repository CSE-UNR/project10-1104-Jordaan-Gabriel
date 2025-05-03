//ERIN WANTS YOU TO READ AT THE BEGINNING AND WRITE AT THE END!!! DONT DO IT TWICE!!! COSTLY!!! GOOD HABBIT!


//Purpose: Project 10 - Wordup (Off brand Wordle) Extra Credit
//Author: Gabriel van Rijn-Jordaan
//Due date: May 6 2025
//Date Completed

//This program adds random word selection, a scoreboard, and the ability to handle duplicate letters.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define GUESSES_ALLOWED 6
#define WORDSIZE 6 //Including null character
#define WORDSFILE "word_ec.txt"
#define SCOREFILE "score.txt"
#define POSSIBLE_WORD_CAP 99
#define SCORE_HISTORY_SIZE 5
#define MAX_NAME_LEN 32

bool read_random_word_from_file(int wordsize, char to[wordsize], char filename[], int cap);
bool isvalid(int wordsize, char word[wordsize]);
void string_copy(int wordsize, char from[wordsize], char to[wordsize]);
void get_guess(int wordsize, char to[wordsize], int guessnum, int allowed);
void to_lowercase(int wordsize, char word[wordsize]);
void to_caps(int wordsize, char word[wordsize]);
bool check_win(int wordsize, char guess[], char word[]);
void win(int wordsize, char word[wordsize], int guessnum);
void add_string_to_arr(int wordsize, char string[wordsize], char arr[][wordsize], int index);
void display_guesses(int wordsize, char guesses[][wordsize], char word[wordsize], int guessnum);
char* fgetsbetter(char target[], int maxlen, FILE* stream);
void sort_ints_and_matching_strings(int master_arr[], int wordlen1, int wordlen2, char strs1[][wordlen1], char strs2[][wordlen2], int arrs_size);
void log_score(char scorefile[], int score, char word[], int score_size, int namelen, int wordsize);
void show_score(char scorefile[], int score_size, int namelen, int wordsize);

int main(){

    char thisguess[WORDSIZE];
    char guesses [GUESSES_ALLOWED][WORDSIZE];
    char word[WORDSIZE];

    if(read_random_word_from_file(WORDSIZE, word, WORDSFILE, POSSIBLE_WORD_CAP)){return 0;}

    for(int i=0; i<GUESSES_ALLOWED; i++){
        get_guess(WORDSIZE, thisguess, i, GUESSES_ALLOWED);
        to_lowercase(WORDSIZE, thisguess);
        if(check_win(WORDSIZE, thisguess, word)){
            win(WORDSIZE, word, i);
            log_score(SCOREFILE, i+1, word, SCORE_HISTORY_SIZE, MAX_NAME_LEN, WORDSIZE);
            show_score(SCOREFILE, SCORE_HISTORY_SIZE, MAX_NAME_LEN, WORDSIZE);
            return 0;
        }
        else{
            add_string_to_arr(WORDSIZE, thisguess, guesses, i);
            display_guesses(WORDSIZE, guesses, word, i);
        }
    }

    printf("You lost, better luck next time!\n");
    printf("The word was %s", word);

    return 0;
}

bool read_random_word_from_file(int wordsize, char to[wordsize], char filename[], int cap){
    FILE* fileptr = fopen(filename, "r");

    if(fileptr==NULL){
        printf("Sorry, could not get today's word. Try again tomorrow.\n");
        return true;
    }

    char words[cap][wordsize];
    char word[wordsize];

    int i;
    for(i=0; i<cap; i++){


        if(fgetsbetter(word, wordsize+1, fileptr)==NULL){break;}

        for(int letter=0; word[letter]!='\0'; letter++){
            words[i][letter]=word[letter];
        }

        if(!isvalid(wordsize, words[i])){
            break;
        }

    }

    fclose(fileptr);

    srand(time(NULL));

    int random = rand();

    int word_index = random%i;

    string_copy(wordsize, words[word_index], to);

    return false;
}

bool isvalid(int wordsize, char word[wordsize]){
    int returning=true;

    if(word[wordsize-1]!='\0'){
        printf("Your Guess must be %d letters long. ", wordsize-1);
        returning = false;
    }

    for(int i=0; word[i]!='\0'; i++){
        if(!((97<=word[i]&&word[i]<=122)||(65<=word[i]&&word[i]<=90))&&(word[i]!='\0')){
            printf("Your Guess must contain only letters. ");
            return false;
        }
        
    }

    return returning;
}

void string_copy(int wordsize, char from[wordsize], char to[wordsize]){
    int i;
    for(i=0; (from[i]!='\0'); i++){
        to[i]=from[i];
    }
    to[i]='\0';
}

void string_swap(int wordsize, char str1[wordsize], char str2[wordsize]){
    char temp[wordsize];
    string_copy(wordsize, str1, temp);
    string_copy(wordsize, str2, str1);
    string_copy(wordsize, temp, str2);
}

void get_guess(int wordsize, char to[wordsize], int guessnum, int allowed){

    if(guessnum+1==allowed){
        printf("FINAL GUESS: ");
    }
    else{
        printf("GUESS %d! Enter your guess: ", guessnum+1);
    }

    scanf("%s", to);

    while(!isvalid(wordsize, to)){
        printf("\nPlease try again: ");
        scanf("%s", to);
    }

    printf("\n==========================\n");
    for(int i=0; i>wordsize; i++){
        printf("=");
    }

}

void to_lowercase(int wordsize, char word[wordsize]){
    for(int i=0; word[i]!='\0'; i++){
        if(word[i]<=96){
            word[i]+=32;
        }
    }
}

void to_caps(int wordsize, char word[wordsize]){
    for(int i=0; word[i]!='\0'; i++){
        if(word[i]>=91){
            word[i]-=32;
        }
    }
}

bool check_win(int wordsize, char guess[], char word[]){

    bool returning = true;

    for(int i=0; guess[i]!='\0'||word[i]!='\0'; i++){
        if(guess[i]!=word[i]){
            returning = false;
        }
    }

    return returning;
}

void win(int wordsize, char word[wordsize], int guessnum){
    guessnum++;
    to_caps(wordsize, word);
    printf("        %s\n", word);
    if(guessnum==1){
        printf("    You won in 1 guess!\n");
    }
    else{
        printf("    You won in %d guesses!\n", guessnum);
    }

    switch(guessnum){
        case 1:
            printf("        GOATED!\n");
            break;

        case 2:
            printf("        Amazing!\n");
            break;

        case 3:
            printf("        Amazing!\n");
            break;

        case 4:
            printf("        Nice!\n");
            break;
        case 5:
            printf("        Nice!\n");

    }

}

void add_string_to_arr(int wordsize, char string[wordsize], char arr[][wordsize], int index){
    int charindex;
    for(int charindex=0; string[charindex]!='\0'; charindex++){
        arr[index][charindex]=string[charindex];
    }
    arr[index][charindex]='\0';
}

void display_guesses(int wordsize, char guesses[][wordsize], char word[wordsize], int guessnum){
    guessnum++;

    char printing[wordsize-1];
    char carets[wordsize-1];
    bool claimed_by_a_caret[wordsize-1];
    
    for(int guessindex = 0; guessindex<guessnum; guessindex++){
        
        for(int i=0; i<wordsize; i++){claimed_by_a_caret[i] = false;}

        for(int i=0; i<wordsize; i++){
            carets[i]=' ';
        }

        for(int letterindex = 0; letterindex<wordsize-1; letterindex++){

            if(word[letterindex]==guesses[guessindex][letterindex]){
                printing[letterindex]=guesses[guessindex][letterindex]-32;
            }

            else{
                printing[letterindex]=guesses[guessindex][letterindex];

                //for(int i = 0; i<wordsize; i++){
                  //  if((guesses[guessindex][letterindex]==word[i])&&(letterindex!=i)&&(word[i]!=guesses[guessindex][i])){//This insures there will be no duplicate carets by checking for letters that are the same, but have not been guessed.
                    //    carets[letterindex]='^';
                    //}
                //}

                for(int i=0; i<wordsize; i++){
                    if((guesses[guessindex][letterindex]==word[i])&&!claimed_by_a_caret[i]){
                        carets[letterindex]='^';
                        claimed_by_a_caret[i]=true;
                        break;
                    }
                }

            }

        }
        printf("%s\n%s\n\n", printing, carets);
    }
}

char* fgetsbetter(char target[], int maxlen, FILE* stream){
    char* retstream = fgets(target, maxlen, stream);

    if(retstream!=NULL){
        for(int letter = 0; (target[letter]!='\0')&&(letter<maxlen); letter++){
            if(target[letter]=='\n'){
                target[letter]='\0';
            }
        }
    }

    return retstream;

}

void sort_ints_and_matching_strings(int master_arr[], int wordlen1, int wordlen2, char strs1[][wordlen1], char strs2[][wordlen2], int arrs_size){

    bool sorted=false;
    int temp_int;
    char temp_str[wordlen1];

    while(!sorted){
        sorted = true;

        for(int i=0; i<arrs_size-1; i++){
            if(master_arr[i]>master_arr[i+1]){
                temp_int = master_arr[i];
                master_arr[i]=master_arr[i+1];
                master_arr[i+1]=temp_int;

                string_swap(wordlen1, strs1[i], strs1[i+1]);
                string_swap(wordlen2, strs2[i], strs2[i+1]);

                sorted = false;
            }
        }

    }
}

void log_score(char scorefile[], int score, char word[], int score_size, int namelen, int wordsize){
    FILE* scoreptr = fopen(scorefile, "r");
    if(scoreptr==NULL){
        printf("We had some troube retrieving the scoreboard so we could log that, but great job!\n");
        return;
    }

    char names[score_size+1][namelen];
    char words[score_size+1][wordsize];
    int scores[score_size+1];

    for(int i=0; i<score_size; i++){
        fgetsbetter(names[i], namelen, scoreptr);
        fgetsbetter(words[i], namelen, scoreptr);
        fscanf(scoreptr, "%d\n", &scores[i]);
    }

    printf("Enter your name and see if you got on the leaderboard: ");
    scanf("%s", names[score_size]);

    string_copy(wordsize, word, words[score_size]);
    scores[score_size]=score;

    printf("Before sort:");
    for(int i=0; i<score_size; i++){
        fprintf(scoreptr, "%s\n%s\n%d\n", names[i], words[i], scores[i]);
    }

    sort_ints_and_matching_strings(scores, wordsize, namelen, names, words, score_size+1);

    printf("After sort:");
    for(int i=0; i<score_size; i++){
        fprintf(scoreptr, "%s\n%s\n%d\n", names[i], words[i], scores[i]);
    }

    fclose(scoreptr);

    scoreptr = fopen(scorefile, "w");

    if(scoreptr==NULL){
        printf("We had some troube writing to the scoreboard so we could log that, but great job!\n");
        return;
    }

    fclose(scoreptr);

}

void show_score(char scorefile[], int score_size, int namelen, int wordsize){
    FILE* scoreptr = fopen(scorefile, "r");
    if(scoreptr==NULL){
        printf("We had some troube retrieving the scoreboard so we could show it to you, but great job!\n");
        return;
    }

    char name[namelen];
    char word[wordsize];
    int score;

    for(int i=0; i<score_size; i++){
        fgetsbetter(name, namelen, scoreptr);
        fgetsbetter(word, namelen, scoreptr);
        fscanf(scoreptr, "%d\n", &score);

        printf("%s guessed the word \"%s\" in %d guesses.\n", name, word, score);

    }
}