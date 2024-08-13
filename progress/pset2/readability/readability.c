#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


#define DEBUG 0
#define BOOL int
#define TRUE 1
#define FALSE 0
#define MAX_GRADE_LEVEL 16
#define MIN_GRADE_LEVEL 1

float toPositiveFloat(float number);
void printGradeLevel(int gradeLevel);
int getNumberOfSentences(string text);
int getNumberOfLetters(string text);
int getNumberOfWords(string text);


int main(int argc, string argv[]) {
    // WRITE DOWN CODE YOU KNOW WILL COMPILE
    int gradeLevel = 1;
    int numberOfLetters = 1;
    int numberOfSentences = 1;
    int numberOfWords = 1;


    if (DEBUG) {
        printf("Testing toPositiveFloat()\n");
        printf("toPositiveFloat(-15) outputs %f\n", toPositiveFloat(-15));
    }

    string text = get_string("Text: ");

    if (DEBUG) {
        printf("Your text has %i sentences\n", getNumberOfSentences(text));
        printf("your text has %i letters\n", getNumberOfLetters(text));
        printf("your text has %i words\n", getNumberOfWords(text));
    }

    numberOfLetters = getNumberOfLetters(text);
    numberOfSentences = getNumberOfSentences(text);
    numberOfWords = getNumberOfWords(text);

    float avgNumOfLetPerWord = (float)numberOfLetters / (float)numberOfWords;
    float avgNumOfSentPerWord = (float)numberOfSentences / (float)numberOfWords;
    float avgNumOfLetPerOneHundredWords = avgNumOfLetPerWord * 100;
    float avgNumOfSentencesPerOneHundredWords = avgNumOfSentPerWord * 100;
    float colemanLiauIndex = 0.0588 * (float)avgNumOfLetPerOneHundredWords - 0.296 * (float)avgNumOfSentencesPerOneHundredWords - 15.8;

    gradeLevel = round(colemanLiauIndex);

    if (DEBUG) {
        printf("The Coleman Liau index is %f\n", colemanLiauIndex);
    }

    if (gradeLevel >= MAX_GRADE_LEVEL) {
        printf("Grade 16+\n");
    } else if (gradeLevel < MIN_GRADE_LEVEL) {
        printf("Before Grade 1\n");
    } else {
        printf("Grade %i\n", gradeLevel);
    }



}

float toPositiveFloat(float number) {
    if (number > 0 || number == 0) {
        return number;
    } else {
        float tempValue = number * - 2;
        number = number + tempValue;
        return number;
    }
}

void printGradeLevel(int gradeLevel) {
    printf("Grade %i", gradeLevel);
}

int getNumberOfSentences(string text) {
    int sentenceCount = 0;
    BOOL isSentence = FALSE;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] == '.') {
            if (text[i+1] == '\0') {
                sentenceCount++;
            } else if (text[i+1] == ' ') {
                sentenceCount++;
            } else if (text[i+1] == '.') {
                if (text[i+2] == '\0') {
                    sentenceCount++;
                } else if (text[i+2] == ' ') {
                    sentenceCount++;
                } else if (text[i+2] == '.') {
                    if (text[i+3] == '\0') {
                        sentenceCount++;
                    } else if (text[i+3] == ' ') {
                        sentenceCount++;
                    } else if (text[i+3] == '.') {
                        sentenceCount++;
                    }
                }
            }
        } else if (text[i] == '?') {
            if (text[i+1] == '"') {
                isSentence = FALSE;
            } else if (text[i+1] == ' ') {
                sentenceCount++;
            }
        } else if (text[i] == '!') {
            sentenceCount++;
        }
    }

    return sentenceCount;
}

int getNumberOfLetters(string text) {
    // TODO check if this function works
    int letterCount = 0;
    for (int i = 0; i < strlen(text); i++) {
        if (text[i] >= 65 && text[i] <= 122) {
            letterCount++;
        }
    }
    return letterCount;
}

int getNumberOfWords(string text) {
    int wordCount = 0;
    for (int i =  0; i < strlen(text); i++) {
        if (text[i] == ' ') {
            wordCount++;
        }
    }
    wordCount++;
    return wordCount;
}

