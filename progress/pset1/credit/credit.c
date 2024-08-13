#include <stdio.h>
#include <cs50.h>


#define DEBUG 0

void print_line() {
    printf("\n");
}

int find_card_length(long card_number) {
    long quotient = card_number;
    int n = 0;
    while (quotient >= 1) {
        quotient = quotient / 10;
        n++;
    }
    if (DEBUG)
        printf("The length of the card is: %i ", n);

    return n;
}

int is_card_length_valid(int card_length) {
    if (card_length == 16) {
        return 1;
    } else if (card_length == 15) {
        return 1;
    } else if (card_length == 13) {
        return 1;
    } else {
        return 0;
    }
}

int get_first_sum(long card_number) {
    // FIRST SUM IS BEING FIXED
    long modulus = 100;
    long subtracted_remainder = 0;
    long remainder = 0;
    long temporary_remainder = 0;
    long previous_remainder = 0;
    int x = 10;
    int next_digit = 0;
    int first_sum = 0;
    // iterate over the card
    while (remainder != card_number) { // Condition works
        // Get remainder
        remainder = card_number % modulus;

        if (DEBUG)
            printf("%ld MOD %ld is %ld\n", card_number, modulus, remainder);


        subtracted_remainder = remainder - previous_remainder;
        if (DEBUG)
            printf("The subtracted remainder is: %ld\n", subtracted_remainder);

        // Fix the x equation
        // One must solve sub remain - x = next digit
        next_digit = subtracted_remainder / (modulus / 10);
        // printf("modulus is: %ld\n", modulus);
        //   printf("Next digit is %i\n", next_digit);
        next_digit = next_digit * 2;
        if (next_digit >= 10) {
            // work on the branching that occurs when next digit is greater than zero
            int x1 = 1;
            int x2 = 0;
            x2 = next_digit % 10;
            next_digit = x1 + x2;
            first_sum = first_sum + (next_digit);
        //       printf("The first sum is currently: %i\n", first_sum);
        } else {
            first_sum = first_sum + (next_digit);
        //       printf("The first sum is currently: %i\n", first_sum);
        }

        previous_remainder = remainder;
        modulus = modulus * 100;
      //  printf("\n");
    }
    if (DEBUG) {
        printf("The first sum is: %i", first_sum);
        print_line();
        print_line();
    }
    return first_sum;
}

int get_second_sum(long card_number, int first_sum) {
    int second_sum = first_sum;
    long modulus = 10;
    long subtracted_remainder = 0;
    long remainder = 0;
    long temporary_remainder = 0;
    long previous_remainder = 0;
    int x = 10;
    int next_digit = 0;

    // Iterate over the card
    while (remainder != card_number) {
        remainder = card_number % modulus;
      //  printf("%ld MOD %ld is %ld\n", card_number, modulus, remainder);


        subtracted_remainder = remainder - previous_remainder;
    //     printf("The subtracted remainder is: %ld\n", subtracted_remainder);
        next_digit = subtracted_remainder / (modulus / 10);
        //   printf("modulus is: %ld\n", modulus);
        //   printf("Next digit is %i\n", next_digit);
        second_sum = second_sum + next_digit;
        //   printf("second sum is: %i",second_sum);

        previous_remainder = remainder;
        modulus = modulus * 100;
     //   printf("\n");
    }
    if (DEBUG) {
        printf("The second sum is: %i", second_sum);
        print_line();
        print_line();
    }
    return second_sum;
}



int give_checksum(long card_number) {
    int checksum = 0;

    return checksum;
}

int give_first_two_digits(long card_number) {
    // COMPLETE THIS FUNCTION!
    long modulus = 10;
    int digit_one = 0;
    int digit_two = 0;
    int two_digits = 0;
    long subtracted_remainder = 0;
    long remainder = 0;
    long previous_remainder = 0;
    int card_length = find_card_length(card_number);
    int index = (card_length - 1);
    int last_index = 0;
    int second_to_last_index = 1;
    int next_digit = 0;

    // Iterate over the card
    while (remainder != card_number) {
        remainder = card_number % modulus;

     //   printf("%ld MOD %ld is %ld\n", card_number, modulus, remainder);

        subtracted_remainder = remainder - previous_remainder;

     //   printf("The subtracted remainder is: %ld\n", subtracted_remainder);

        next_digit = subtracted_remainder / (modulus / 10);

      //  printf("modulus is: %ld\n", modulus);
      //  printf("Next digit is %i\n", next_digit);
        if (index == second_to_last_index ) {
            digit_two = next_digit;
      //      printf("Digit two is: %i", digit_two);
        } else if (index == last_index) {
            digit_one = next_digit;
      //      printf("Digit one is %i:", digit_one);
        }

        previous_remainder = remainder;

        // Incrementation
        modulus = modulus * 10;
        index--;
     //   printf("This index is now %i\n", index);
    }

    two_digits = (digit_one * 10) + digit_two;

    return two_digits;
}



int main(void) {
    // TODO 5673598276138003 should output INVALID but outputs nothing
    long card_number = get_long("Number: ");
    if (is_card_length_valid(find_card_length(card_number))) {
        // FIXME
        if (DEBUG) {
            printf("The card length is valid\n");
            printf("\n");
        }

        int checksum = get_second_sum(card_number, get_first_sum(card_number));
        if (checksum % 10 == 0) {
            int first_two_digits = give_first_two_digits(card_number);

            if (first_two_digits == 34 || first_two_digits == 37) {
                if (find_card_length(card_number) == 15) {
                    printf("AMEX\n");
                } else {
                    printf("INVALID\n");
                }
            } else if (first_two_digits >= 40 && first_two_digits <= 49) {
                if ( (find_card_length(card_number) == 13) || (find_card_length(card_number) == 16) ) {
                    printf("VISA\n");
                } else {
                    printf("INVALID\n");
                }
            } else if (first_two_digits >= 51 && first_two_digits <= 55) {
                if ( find_card_length(card_number) == 16 ) {
                    printf("MASTERCARD\n");
                } else {
                    printf("INVALID\n");
                }
            } else {
                printf("INVALID\n");
            }
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }



}
