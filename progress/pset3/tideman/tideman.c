#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define DEBUG 1

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int is_valid(pair graph[], int starting_pair_index, int pair_index);
int there_is_cycle(graph, starting_pair_index, pair_index);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        // Produces array of candidates
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        // if (DEBUG)
        // print the ballot
        if (DEBUG) {
            printf("This voter's ballot is [");
            for (int id = 0; id < candidate_count; id++) {
                if (id == 0) {
                    printf("%s ", candidates[ranks[id]]);
                } else if (id == (candidate_count-1)) {
                    printf(" %s", candidates[ranks[id]]);
                } else {
                    printf(" %s ", candidates[ranks[id]]);
                }
            }
            printf("]\n");
        }

        printf("\n");
        record_preferences(ranks);
        printf("The preference matrix is currently: \n");
        printf("\n");
        for (int k = 0; k < MAX; k++) {
            for (int l = 0; l < MAX; l++) {
                printf("%i ", preferences[k][l]);
            }
            printf("\n");
        }

        printf("\n");
    }

    add_pairs();
    if (DEBUG) {
        printf("pairs is currently:\n ");
        for (int jd = 0; jd < pair_count; jd++) {
            printf("(%i, %i)", pairs[jd].winner, pairs[jd].loser);
        }
        printf("\n");
    }
    sort_pairs();
    if (DEBUG) {
        printf("pairs is currently:\n ");
        for (int jd = 0; jd < pair_count; jd++) {
            printf("(%i, %i)", pairs[jd].winner, pairs[jd].loser);
        }
        printf("\n");
    }
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            if (DEBUG) {
                printf("rank is %i\n", rank);
                printf("ranks[%i] is currently %i\n", rank, i);
            }
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (i < j) {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (preferences[i][j] >= 1) {
                if (preferences[i][j] > preferences[j][i]) {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
    int counter = pair_count;
    while (counter != 1) {
        for (int i = 0; i < counter-1; i++) {
            if ((preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]) <
                (preferences[pairs[i+1].winner][pairs[i+1].loser] - preferences[pairs[i+1].loser][pairs[i+1].winner])) {
                    pair temp = pairs[i];
                    pairs[i] = pairs[i+1];
                    pairs[i+1] = temp;
                }
        }
        counter--;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    int start = 0;

    //fill array
    for (int i = 0; i < pair_count; i++) {
        locked[pairs[i].winner][pairs[i].loser] = 1;
    }

    if (DEBUG) {
        printf("(JUST) printing the array, and not removing any circularity\n");
        for (int i = 0; i < candidate_count; i++) {
            for (int j = 0; j < candidate_count; j++) {
                printf("%i ", locked[i][j]);
            }
            printf("\n");
        }
    }

    printf("done debugging, now for the real attempt\n");
    // clear locked
    for (int i = 0; i < 0; i++) {
        for (int j = 0; j < 0; j++) {
            locked[i][j] = 0;
        }
    }
// ------------------------------------------------------------------------------------
    // add pair
    for (int i = 0; i < pair_count; i++) {
        locked[pairs[i].winner][pairs[i].loser] = 1;
    }
// ------------------------------------------------------------------------------------

    if (DEBUG) {
        printf("(FINAL) locked pairs\n");
        for (int i = 0; i < candidate_count; i++) {
            for (int j = 0; j < candidate_count; j++) {
                printf("%i ", locked[i][j]);
            }
            printf("\n");
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

