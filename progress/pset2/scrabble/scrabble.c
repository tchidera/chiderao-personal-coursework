#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

#define DEBUG 1
#define BOOL int
#define TRUE 1
#define FALSE 0

string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string score_of_one = "AEILNORSTU";
string score_of_two = "DG";
string score_of_three = "BCMP";
string score_of_four = "FHVWY";
string score_of_five = "K";
string score_of_eight = "JX";
string score_of_ten = "QZ";
void print_line();
int get_sum(string word, int sum);
string make_upper_case(string word);
BOOL is_a_member_of(char letter, char score_set[]);


int main(int argc, string argv[]) {
    int sum = 0;
    int character_count = strlen(alphabet);
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    int score1 = get_sum(word1, sum);
    int score2 = get_sum(word2, sum);

    if (score1 > score2) {
        printf("Player 1 wins!\n");
    } else if (score1 < score2) {
        printf("Player 2 wins!\n");
    } else if (score1 == score2) {
        printf("Tie!");
    }


}

void print_line() {
    printf("\n");
}

int get_sum(string word, int sum) {
    for (int i = 0; i < strlen(word); i++) {
        if ( ((int) toupper(word[i])) >= 65 && ((int) toupper(word[i])) <= 90) {
            // TODO: LETTERCASE & lettercase should output Tie!
            if (is_a_member_of(word[i], score_of_one)) {
                sum++;
            } else if (is_a_member_of(word[i], score_of_two)) {
                sum = sum + 2;
            } else if (is_a_member_of(word[i], score_of_three)) {
                sum = sum + 3;
            } else if (is_a_member_of(word[i], score_of_four)) {
                sum = sum + 4;
            } else if (is_a_member_of(word[i], score_of_five)) {
                sum = sum + 5;
            } else if (is_a_member_of(word[i], score_of_eight)) {
                sum = sum + 8;
            } else if (is_a_member_of(word[i], score_of_ten)) {
                sum = sum + 10;
            }
        }
    }
    return sum;
}

BOOL is_a_member_of(char letter, string score_set) {
    for (int i = 0; i < strlen(score_set); i++) {
        if (toupper(letter) == score_set[i]) {
            return TRUE;
        }
    }
    return FALSE;
}

