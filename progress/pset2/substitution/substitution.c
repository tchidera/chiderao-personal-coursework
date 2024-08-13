#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

#define BOOL int
#define TRUE 1
#define FALSE 0
#define DEBUG 0

char encryptcharacter(char character, string key, string alphabet);
BOOL isaletter(char character);

int main(int argc, string argv[]) {
    string userkey = argv[1];
    // Handle lack of key
    if (argc == 1) {
        printf("One must enter a key\n");
        return 1;
    }

    // Check for invalid characters
    for (int i = 0; i < strlen(userkey); i++) {
        if (!(toupper(userkey[i]) >= 65 && toupper(userkey[i]) <= 90) || userkey[i] == ' ') {
            printf("One must only type alphabetical characters\n");
            return 1;
        }
    }

    // Check for any dupicates
    for (int i = 0; i < strlen(userkey)-1; i++) {
        if (DEBUG)
            printf("i is now %i\n", i);
        for (int j = i+1; j < strlen(userkey); j++) {
            if (DEBUG)
                printf("j is now %i\n", j);
            if (userkey[i] == userkey[j]) {
                if (DEBUG)
                    printf("plaintext[i] = %i, plaintext[j] = %i\n", i, j);
                printf("One can not have duplicate characters\n");
                return 1;
            }
        }
    }

    if (strlen(userkey) < 26 || strlen(userkey) > 26 || argc > 2) {
        printf("Key must be 26 letters\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


    if (DEBUG) {
        // Test first character in plaintext
        printf("ciphertext: %c\n", encryptcharacter(plaintext[0], userkey, alphabet));
    }

    // print ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++) {
        printf("%c", encryptcharacter(plaintext[i], userkey, alphabet));
    }
    printf("\n");


    return 0;
}

char encryptcharacter(char character, string key, string alphabet) {
    char encryptedcharacter = 0;

    if (isaletter(character) == FALSE) {
        return character;
    }

    for (int i = 0; i < strlen(alphabet); i++) {
        if (toupper(character) == toupper(alphabet[i])) {
            encryptedcharacter = key[i];
        }
    }

    // Convert to lower or uppercase
    if (islower(character)) {
        encryptedcharacter = tolower(encryptedcharacter);
    } else if (isupper(character)) {
        encryptedcharacter = toupper(encryptedcharacter);
    }

    return encryptedcharacter;
}

BOOL isaletter(char character) {
    if (toupper(character) >= 65 && toupper(character) <= 90) {
        return TRUE;
    }
    return FALSE;
}
