#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void sort_candidates_by_votes(candidate list_of_candidates[], int end_point);
void print_candidates(candidate list[], int length);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Iterate over each candidate
    for (int i = 0; i < candidate_count; i++) {
        // Check if candidate's name matches given name
        if (strcmp(name, candidates[i].name) == 0) {
            // If yes, increment candidate's votes and return true
            candidates[i].votes++;
            return true;
        }
    }
    // If no match, return false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Find the maximum number of votes
    sort_candidates_by_votes(candidates, candidate_count);
    if (DEBUG) {
        print_candidates(candidates, candidate_count);
    }
    // Find maximum amount of votes
    int maximum = candidates[candidate_count-1].votes;
    if (DEBUG) {
        printf("maximum = %i\n", maximum);
    }

    // print all winners
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == maximum) {
            printf("%s\n", candidates[i].name);
        }
    }
}

void sort_candidates_by_votes(candidate list_of_candidates[], int end_point) {
    // TODO Finish sorting function

    // Base case
    if (end_point != 1) {
        for (int i = 0; i < end_point-1; i++) {
            if (list_of_candidates[i].votes > list_of_candidates[i+1].votes) {
                // swap variables
                candidate temp = list_of_candidates[i];
                list_of_candidates[i] = list_of_candidates[i+1];
                list_of_candidates[i+1] = temp;
            }
        }
        end_point--;
        sort_candidates_by_votes(list_of_candidates, end_point);
    }
}

void print_candidates(candidate list[], int length) {
    for (int i = 0; i < length; i++) {
        printf("(%s : %i) ", list[i].name, list[i].votes);
    }
    printf("\n");
}
