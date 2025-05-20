#include <stdio.h>
#include <ctype.h>  // For tolower()

// Define the number of training stages
#define STAGE_COUNT 8

// Declare training menu using 1D array of strings
char *trainingMenu[] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

// Store the result for each stage: 'N' = Not attempted, 'P' = Passed, 'F' = Failed
char stageResults[STAGE_COUNT] = {'N','N','N','N','N','N','N','N'};

// Function declarations
void showMainMenu();
void trainingMenuLoop();
void evaluateStage(int index);
int canAccessStage(int index);
int stages1And2Passed();
void printStageStatus();

int main() {
    char input;

    while (1) {
        showMainMenu();

        printf("\nEnter your choice (1-3), or Q to quit: ");
        scanf(" %c", &input);
        getchar(); // Clear newline character from buffer

        input = tolower(input);

        if (input == 'q' || input == '0') {
            printf("Exiting program...\n");
            break;
        }

        if (input == '1') {
            printf("\n[Audition Management Selected]\n\n");
        } else if (input == '2') {
            trainingMenuLoop();
        } else if (input == '3') {
            printf("\n[Debut Selected]\n\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Show main menu options
void showMainMenu() {
    printf("\n========== Main Menu ==========\n");
    printf("1. Audition Management\n");
    printf("2. Training\n");
    printf("3. Debut\n");
}

// Training menu with loop
void trainingMenuLoop() {
    char input;
    int index;

    while (1) {
        printf("\n========== Training Menu ==========\n");
        printStageStatus();

        for (int i = 0; i < STAGE_COUNT; i++) {
            printf("%s [Status: %c]\n", trainingMenu[i], stageResults[i]);
        }

        printf("Select a stage number (1-8) to evaluate, or Q to return: ");
        scanf(" %c", &input);
        getchar(); // Clear newline

        input = tolower(input);

        if (input == 'q' || input == '0') {
            break;
        }

        if (input >= '1' && input <= '8') {
            index = input - '1'; // Convert char to index (0–7)
            if (canAccessStage(index)) {
                if (stageResults[index] == 'P') {
                    printf("This stage is already passed. You cannot repeat it.\n");
                } else {
                    evaluateStage(index);
                }
            } else {
                printf("You must pass Stage 1 and 2 before accessing this stage.\n");
            }
        } else {
            printf("Invalid stage number. Try again.\n");
        }
    }
}

// Ask user to enter evaluation result
void evaluateStage(int index) {
    char choice;

    printf("Would you like to enter the evaluation result? (Y/N): ");
    scanf(" %c", &choice);
    getchar();

    if (tolower(choice) == 'y') {
        printf("Did you pass the certification? (Y/N): ");
        scanf(" %c", &choice);
        getchar();

        if (tolower(choice) == 'y') {
            stageResults[index] = 'P';
            printf("Result recorded: PASSED.\n");
        } else {
            stageResults[index] = 'F';
            printf("Result recorded: FAILED.\n");
        }
    } else {
        printf("Returning to Training Menu.\n");
    }
}

// Check if the user can access the selected stage
int canAccessStage(int index) {
    if (index == 0) return 1; // Stage 1 always accessible
    if (index == 1 && stageResults[0] == 'P') return 1; // Stage 2 needs Stage 1
    if (index >= 2 && stages1And2Passed()) return 1; // Stage 3–8 needs Stage 1 & 2
    return 0;
}

// Check if both Stage 1 and 2 are passed
int stages1And2Passed() {
    return (stageResults[0] == 'P' && stageResults[1] == 'P');
}

// Show a summary of stage status
void printStageStatus() {
    printf("\nCurrent Stage Status:\n");
    for (int i = 0; i < STAGE_COUNT; i++) {
        printf("Stage %d: %c  ", i + 1, stageResults[i]);
    }
    printf("\n");
}
