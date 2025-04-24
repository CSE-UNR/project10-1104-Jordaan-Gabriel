//Purpose: Project 10 - Wordup (Off brand Wordle)
//Author: Gabriel van Rijn-Jordaan
//Due date: May 6 2025
//Date Completed

#include <stdio.h>
#include <stdbool.h>

#define GUESSES_ALLOWED 6
#define WORDSIZE 6 //Including null character
#define FILENAME "word.txt"

bool read_word_from_file(int wordsize, char to[wordsize], char filename[]);
bool isvalid(int wordsize, char word[wordsize]);
void string_copy(int wordsize, char from[wordsize], char to[wordsize]);
void get_guess(int wordsize, char to[wordsize], int guessnum, int allowed);
void to_lowercase(int wordsize, char word[wordsize]);
void to_caps(int wordsize, char word[wordsize]);
int check_win(int wordsize, char guess[], char word[]);
void win(int wordsize, char word[wordsize], int guessnum);
void add_string_to_arr(int wordsize, char string[wordsize], char arr[][wordsize], int index);
void display_guesses(int wordsize, char guesses[][wordsize], char word[wordsize], int guessnum);

int main(){

    char thisguess[WORDSIZE];
    char guesses [GUESSES_ALLOWED][WORDSIZE];
    char word[WORDSIZE];

    if(read_word_from_file(WORDSIZE, word, FILENAME)){return 0;}

    for(int i=0; i<GUESSES_ALLOWED; i++){
        get_guess(WORDSIZE, thisguess, i, GUESSES_ALLOWED);
        to_lowercase(WORDSIZE, thisguess);
        if(check_win(WORDSIZE, thisguess, word)){
            win(WORDSIZE, word, i);
            return 0;
        }
        else{
            add_string_to_arr(WORDSIZE, thisguess, guesses, i);
            display_guesses(WORDSIZE, guesses, word, i);
        }
    }

    printf("You lost, better luck next time!\n");

    return 0;
}

bool read_word_from_file(int wordsize, char to[wordsize], char filename[]){
    FILE* fileptr = fopen(filename, "r");

    if(fileptr==NULL){
        printf("Sorry, could not get today's word. Try again tomorrow.");
        return true;
    }

    fgets(to, wordsize, fileptr);

    fclose(fileptr);

    return false;
}

bool isvalid(int wordsize, char word[wordsize]){
    int returning=true;

    if(word[wordsize-1]!='\0'){
            printf("Your Guess must be %d letters long. ", wordsize-1);
            returning = false;
        }

    for(int i=0; i<wordsize-1; i++){
        
        if(!((97<=word[i]&&word[i]<=122)||(65<=word[i]&&word[i]<=90))){
            printf("Your Guess must contain only letters. ");
            return false;
        }
        
    }

    return returning;
}

void string_copy(int wordsize, char from[wordsize], char to[wordsize]){
    for(int i=0; i<wordsize; i++){
        to[i]=from[i];
    }
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
    for(int i=0; i<wordsize; i++){
        if(word[i]<=96){
            word[i]+=32;
        }
    }
}

void to_caps(int wordsize, char word[wordsize]){
    for(int i=0; i<wordsize; i++){
        if(word[i]>=91){
            word[i]-=32;
        }
    }
}

int check_win(int wordsize, char guess[], char word[]){

    bool returning = true;

    for(int i=0; i<wordsize-1; i++){
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
    for(int charindex=0; charindex<wordsize; charindex++){
        arr[index][charindex]=string[charindex];
    }
}

void display_guesses(int wordsize, char guesses[][wordsize], char word[wordsize], int guessnum){
    guessnum++;

    char printing[wordsize];
    char carets[wordsize];

    for(int guessindex = 0; guessindex<guessnum; guessindex++){
        for(int i=0; i<wordsize; i++){
            carets[i]=' ';
        }

        for(int letterindex = 0; letterindex<wordsize-1; letterindex++){
            if(word[letterindex]==guesses[guessindex][letterindex]){
                printing[letterindex]=guesses[guessindex][letterindex]-32;
            }
            else{
                printing[letterindex]=guesses[guessindex][letterindex];
                for(int i = 0; i<wordsize; i++){
                    if((guesses[guessindex][letterindex]==word[i])&&(letterindex!=i)){
                        carets[letterindex]='^';
                    }
                }
            }

        }
        printf("%s\n%s\n\n", printing, carets);
    }
}