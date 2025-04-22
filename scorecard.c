#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define NUM_CANDIDATES 6
#define NUM_CATEGORIES 5
#define MAX_NAME_LEN 50

// Categories
const char *category_names[NUM_CATEGORIES] = {
    "Music Proficiency", "Dance", "Vocal", "Visual", "Expression"
};

// Candidate info
char candidate_names[NUM_CANDIDATES][MAX_NAME_LEN] = {
    "Jiyeon Park",
    "Ethan Smith",
    "Helena Silva",
    "Liam Wilson",
    "Sophia Zhang",
    "Noah Kim"
};

// Unique 6-digit IDs (non-duplicate)
int candidate_ids[NUM_CANDIDATES] = {
    101234, 102345, 103456, 104567, 105678, 106789
};

// Scores per candidate per category
int scores[NUM_CANDIDATES][NUM_CATEGORIES];

// Function to get scores from the judge
void input_scores() {
    printf("++++++++++++++++++++++++++++++++++++\n");

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("Candidate: %s\n", candidate_names[i]);

        for (int j = 0; j < NUM_CATEGORIES; j++) {
            int score;

            while (1) {
                printf("%s (10~100): ", category_names[j]);
                if (scanf("%d", &score) != 1 || score < 10 || score > 100) {
                    printf("Invalid score. Try again.\n");
                    while (getchar() != '\n'); // clear input
                } else {
                    scores[i][j] = score;
                    break;
                }
            }
        }
        printf("------------------------------------\n");
    }
}

// Function to show entered scores
void review_scores() {
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Submission completed.\nPlease review your input!\n");
    printf("------------------------------------\n");

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int total = 0;
        for (int j = 0; j < NUM_CATEGORIES; j++) {
            total += scores[i][j];
        }
        printf("%s: %d\n", candidate_names[i], total);
    }
}

// Function to modify scores
void modify_scores() {
    char name[MAX_NAME_LEN];
    int id, found;

    while (1) {
        printf("\nEnter candidate name to modify (or type 'exit'): ");
        scanf(" %[^\n]", name);

        if (strcmp(name, "exit") == 0) break;

        printf("Enter candidate ID: ");
        scanf("%d", &id);

        found = 0;
        for (int i = 0; i < NUM_CANDIDATES; i++) {
            if (strcmp(name, candidate_names[i]) == 0 && candidate_ids[i] == id) {
                found = 1;
                printf("Modifying scores for %s\n", name);
                for (int j = 0; j < NUM_CATEGORIES; j++) {
                    int score;
                    while (1) {
                        printf("%s (10~100): ", category_names[j]);
                        if (scanf("%d", &score) != 1 || score < 10 || score > 100) {
                            printf("Invalid score. Try again.\n");
                            while (getchar() != '\n');
                        } else {
                            scores[i][j] = score;
                            break;
                        }
                    }
                }
                break;
            }
        }
        if (!found) {
            printf("Candidate not found.\n");
        }
    }
}

// Function to show top 4 candidates
void select_top_4() {
    int total_scores[NUM_CANDIDATES];
    int ranks[NUM_CANDIDATES];

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int total = 0;
        for (int j = 0; j < NUM_CATEGORIES; j++) {
            total += scores[i][j];
        }
        total_scores[i] = total;
        ranks[i] = i;
    }

    // Simple sorting (descending)
    for (int i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (int j = i + 1; j < NUM_CANDIDATES; j++) {
            if (total_scores[ranks[j]] > total_scores[ranks[i]]) {
                int temp = ranks[i];
                ranks[i] = ranks[j];
                ranks[j] = temp;
            }
        }
    }

    // Print result
    printf("=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");
    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");

    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidate_names[ranks[i]]);
    }
}

// Main program
int main() {
    char judge_name[MAX_NAME_LEN];
    char expertise[MAX_NAME_LEN];
    char choice;

    printf("####################################\n");
    printf("#     Audition Evaluation Entry    #\n");
    printf("####################################\n");

    printf("> Judge Name: ");
    scanf(" %[^\n]", judge_name);
    printf("> Expertise: ");
    scanf(" %[^\n]", expertise);

    while (1) {
        input_scores();
        review_scores();

        printf("Would you like to submit? (Y/N): ");
        scanf(" %c", &choice);

        if (choice == 'Y' || choice == 'y') {
            printf("***Final submission completed.***\n");
            break;
        } else {
            modify_scores(); // allow updates
        }
    }

    select_top_4(); // show final results
    return 0;
}
