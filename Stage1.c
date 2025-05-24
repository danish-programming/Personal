#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STAGE_COUNT 8
#define MEMBER_COUNT 5
#define TEST_COUNT 7

// Member info: [Name, Nickname]
char *milliways_members[MEMBER_COUNT][2] = {
    {"Hyekyung", "hkk"},
    {"Goeun", "gee"},
    {"Woncheol", "wc"},
    {"Youngjin", "yj"},
    {"Arthur", "art"}
};

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

char stageResults[STAGE_COUNT] = {'N','N','N','N','N','N','N','N'};

float health_scores[MEMBER_COUNT][TEST_COUNT];

// Function declarations
void showMainMenu();
void trainingMenuLoop();
void evaluateStage(int index);
int canAccessStage(int index);
int stages1And2Passed();
void printStageStatus();
void fitnessMenu();
void setHealth();
void getHealth();

int main() {
    char input;
    while (1) {
        showMainMenu();
        printf("\nEnter your choice (1-3), or Q to quit: ");
        scanf(" %c", &input);
        getchar();
        input = tolower(input);

        if (input == 'q') {
            printf("Exiting program...\n");
            break;
        } else if (input == '1') {
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

void showMainMenu() {
    printf("\n========== Main Menu ==========\n");
    printf("1. Audition Management\n");
    printf("2. Training\n");
    printf("3. Debut\n");
}

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
        getchar();
        input = tolower(input);

        if (input == 'q') break;
        if (input >= '1' && input <= '8') {
            index = input - '1';
            if (canAccessStage(index)) {
                if (index == 0) {
                    fitnessMenu();
                } else if (stageResults[index] == 'P') {
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

int canAccessStage(int index) {
    if (index == 0) return 1;
    if (index == 1 && stageResults[0] == 'P') return 1;
    if (index >= 2 && stages1And2Passed()) return 1;
    return 0;
}

int stages1And2Passed() {
    return (stageResults[0] == 'P' && stageResults[1] == 'P');
}

void printStageStatus() {
    printf("\nCurrent Stage Status:\n");
    for (int i = 0; i < STAGE_COUNT; i++) {
        printf("Stage %d: %c  ", i + 1, stageResults[i]);
    }
    printf("\n");
}

void fitnessMenu() {
    char choice;
    while (1) {
        printf("\n[Stage 1: Physical Strength & Knowledge]\n");
        printf("A. Enter Fitness Data\n");
        printf("B. View Fitness Data\n");
        printf("Q. Return to Training Menu\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar();
        choice = tolower(choice);

        if (choice == 'a') setHealth();
        else if (choice == 'b') getHealth();
        else if (choice == 'q') break;
        else printf("Invalid choice. Please try again.\n");
    }
}

void setHealth() {
    char input[256];
    printf("\nEnter fitness data (nickname,7 scores):\n");
    for (int i = 0; i < MEMBER_COUNT; i++) {
        printf("%s (%s): ", milliways_members[i][0], milliways_members[i][1]);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0; // Remove newline

        char *token = strtok(input, ",");
        int memberIndex = -1;
        for (int j = 0; j < MEMBER_COUNT; j++) {
            if (strcmp(token, milliways_members[j][1]) == 0) {
                memberIndex = j;
                break;
            }
        }

        if (memberIndex == -1) {
            printf("Nickname not found. Skipping.\n");
            continue;
        }

        for (int k = 0; k < TEST_COUNT; k++) {
            token = strtok(NULL, ",");
            if (token != NULL) {
                health_scores[memberIndex][k] = atof(token);
            } else {
                health_scores[memberIndex][k] = 0;
            }
        }
    }
    printf("All fitness data recorded.\n");
    stageResults[0] = 'P';
}

void getHealth() {
    char nickname[50];
    printf("\nEnter member nickname to view fitness data: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < MEMBER_COUNT; i++) {
        if (strcmp(nickname, milliways_members[i][1]) == 0) {
            printf("\nMember: %s (%s)\n", milliways_members[i][0], nickname);
            printf("1-Mile Run: %.2f mins\n", health_scores[i][0]);
            printf("Speed Sprint: %.2f secs\n", health_scores[i][1]);
            printf("Push-ups (30): %.2f mins\n", health_scores[i][2]);
            printf("Squats (50): %.2f mins\n", health_scores[i][3]);
            printf("Arm Strength (50 Push-ups): %.2f mins\n", health_scores[i][4]);
            printf("Swimming (400m): %.2f mins\n", health_scores[i][5]);
            printf("Weightlifting (Bodyweight multiplier): %.2f\n", health_scores[i][6]);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Nickname not found.\n");
    }
}

