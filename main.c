#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define LINESIZE 512

void repeatCharacters(char *text, char *translation);
void expand(char *text);
void sameSizeSets(char *text, char *translation);
void readFile(char *text, char *translation);
void escapeCharacters(char *text);
int containsChar(char *text, int c);

/*
Repeats the last character in translation to match the string length of text.
*/
void repeatCharacters(char *text, char *translation) {
    int textLen, translationLen;
    char temp;
    textLen = strlen(text);
    translationLen = strlen(translation);
    temp = translation[translationLen - 1];
    if (textLen > translationLen) {
        while(translationLen < textLen) {
            translation[translationLen] = temp;
            translationLen++;
        }
    }
}

/*
Checks if a string contains a character
*/
int containsChar(char *text, int c) {
    size_t i;
    for(i = 0; i < strlen(text); i++) {
        if(text[i] == c) {
            return 1;
        }
    }
    return 0;
}

/*
Expands characters in a given range.
*/
void expand(char *text) {
    int i, k = 0;
    int len = strlen(text);
    char a, temp[LINESIZE];

    for (i = 1; i < len - 1; i++) {
        if (text[i] == '-') {
            if (text[i - 1] < text[i + 1]) {
                for(a = text[i - 1]; a < text[i + 1]; a++) {
                    temp[k] = a;
                    k++;
                }
                i++;
            }
            temp[k] = text[i];
            k++;
        } else if(text[i] != '-' && text[i + 1] != '-') {
            temp[k] = text[i];
            k++;
            i++;
        }
    }
    if(text[len - 2] != '-') {
        temp[k] = text[len - 1];
        k++;
    }
    temp[k] = '\0';
    if(containsChar(text, '-') == 1) {
        strcpy(text, temp);
    }
    if(strlen(text) > LINESIZE) {
        fprintf(stderr, "Length of text is too long.");
        exit(1);
    }
}

/*
Truncates the larger-sized set to match the length of the second set.
*/
void sameSizeSets(char *text, char *translation) {
    char temp[LINESIZE];
    size_t i;
    if(strlen(text) > strlen(translation)) {
        for(i = 0; i < strlen(translation); i++) {
            temp[i] = text[i];
        }
        strcpy(text, temp);
    } else if(strlen(translation) > strlen(text)) {
        for(i = 0; i < strlen(text); i++) {
            temp[i] = translation[i];
        }
        strcpy(translation, temp);
    }
}

/*
Reads characters from text and translation starting at the end and replaces character in text with corresponding characters in translation.
*/
void readFile(char *text, char *translation) {
    int i;
    char c;
    while((c = getchar()) != EOF) {
        for (i = strlen(text); i > 0; i--) {
            if(c == text[i - 1]) {
                c = translation[i - 1];
                break;
            }
        }
        putchar(c);
    }
}

/*
Checks for escape characters in input and outputs the correct character into the file.
*/
void escapeCharacters(char *text) {
    int i;
    int len = strlen(text);
    for (i = 0; i < len; i++) {
        if (text[i] == '\\') {
            if(text[i + 1] == '\\') {
                text[i] = '\\';
                strcpy(&text[i + 1], &text[i + 2]);
            } else if(text[i + 1] == 'a') {
                text[i] = '\a';
                strcpy(&text[i + 1], &text[i + 2]);
            } else if(text[i + 1] == 'b') {
                text[i] = '\b';
                strcpy(&text[i + 1], &text[i + 2]);
            } else if(text[i + 1] == 'f') {
                text[i] = '\f';
                strcpy(&text[i + 1], &text[i + 2]);
            } else if(text[i + 1] == 'n') {
                text[i] = '\n';
                strcpy(&text[i + 1], &text[i + 2]);
            } else if(text[i + 1] == 'r') {
                text[i] = '\r';
                strcpy(&text[i + 1], &text[i + 2]);
            } else if(text[i + 1] == 't') {
                text[i] = '\t';
                strcpy(&text[i + 1], &text[i + 2]);
            } else if(text[i + 1] == 'v') {
                text[i] = '\v';
                strcpy(&text[i + 1], &text[i + 2]);
            } else if(text[i + 1] == '\'') {
                text[i] = '\'';
                strcpy(&text[i + 1], &text[i + 2]);
            } else if(text[i + 1] == '\"') {
                text[i] = '\"';
                strcpy(&text[i + 1], &text[i + 2]);
            }
        }
    }
}

/*
This program translates characters read from standard input, writing the result to standard output.
It is a simplified version of the tr program available in Unix systems.
*/
int main (int argc, char *argv[]) {
    char argv1[LINESIZE];
    char argv2[LINESIZE];
    char *check = argv[1];
    char *repeat = "-e";
    if(argc == 3) {
        strcpy(argv1, argv[1]);
        strcpy(argv2, argv[2]);
        expand(argv1);
        escapeCharacters(argv1);
        expand(argv2);
        escapeCharacters(argv2);
        sameSizeSets(argv1, argv2);
        readFile(argv1, argv2);
    } else if(argc == 4) {
        if(strcmp(check, repeat) == 0) {
            strcpy(argv1, argv[2]);
            strcpy(argv2, argv[3]);
            expand(argv1);
            escapeCharacters(argv1);
            expand(argv2);
            escapeCharacters(argv2);
            repeatCharacters(argv1, argv2);
            sameSizeSets(argv1, argv2);
            readFile(argv1, argv2);
        }
    }
    return 0;
}
