#include <stdio.h>
#include <cs50.h>



void print_hash() {
    printf("#");
}

void print_space() {
    printf(" ");
}

void print_newline() {
    printf("\n");
}

void print_gap() {
    printf("  ");
}


void print_row(int length, int offset, int left_hash, int right_hash, int initial_left_hash, int initial_right_hash) {
    // Initialize variabes
    int row_length = (length * 2) + 2;
    int i = 0;
    for (i = 0; i < row_length; i++) {
        if ((i >= left_hash) && (i <= initial_left_hash)) {
            print_hash();
        }
        else {
            if (!((i >= initial_right_hash) && (i <= row_length))) {
                print_space();
            }
        }
        if ((i >= initial_right_hash) && (i <= right_hash)) {
            print_hash();
        }
    }
    //printf(" i : %i, offs: %i, lhash: %i, rhash: %i", i, offset, left_hash, right_hash);
}

int main(void) {
    int height = 0;
    do {
        height = get_int("Height: ");

    // Fix range
    } while (!((height >= 1) && (height <=8)));

    int offset = height - 1;
    // The number indexes that precede the gap
    int initial_left_hash = offset;
    int initial_right_hash = initial_left_hash + 3;
    int left_hash = offset;
    int right_hash = left_hash + 3;

    //printf("The height is: %i\n", height);

    for (int i = 0; i < height; i++) {
        print_row(height, offset, left_hash, right_hash, initial_left_hash, initial_right_hash);
        print_newline();
        offset--; // Offset decrements to zero, where you print the fully hash array w/ spaces
        left_hash = left_hash - 1; // Left hash decrease by 2
        right_hash = right_hash + 1; // Right hash increases by 2

    }

}
