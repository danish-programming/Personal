#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 10
#define MAX_NAME_LEN 30
#define DAYS_IN_WEEK 6

// Define exercise types
const char *cardio[] = {"Running", "Cycling", "Fast Walking"};
const char *full_body[] = {"Push-ups", "Squats"};
const char *lower_body[] = {"Leg Press", "Leg Curl"};
const char *upper_body[] = {"Pull-ups", "Chin-ups"};
const char *core[] = {"Plank", "Crunches"};

const char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Member structure
typedef struct {
    char real_name[MAX_NAME_LEN];
    char nickname[MAX_NAME_LEN];
    char routine[DAYS_IN_WEEK][2][MAX_NAME_LEN]; // [day][0]=cardio, [1]=strength/core
} Member;

Member milliways_members[MAX_MEMBERS] = {
    {"Alice", "Ace"},
    {"Bob", "Bobby"},
    {"Charlie", "Chuck"}
};
int member_count = 3;

// Shared function to display members
void displayMemberList() {
    printf("\n--- Milliways Members ---\n");
    for (int i = 0; i < member_count; i++) {
        printf("%d. %s (%s)\n", i + 1, milliways_members[i].real_name, milliways_members[i].nickname);
    }
}

// Function to set workout routine
void setExerciseRoutine() {
    int choice, day, cardio_choice, strength_choice;
    int core_used = 0;

    displayMemberList();
    printf("Select a member by number: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > member_count) {
        printf("Invalid member.\n");
        return;
    }

    Member *member = &milliways_members[choice - 1];

    printf("\nSetting workout routine for %s (%s)\n", member->real_name, member->nickname);
    for (day = 0; day < DAYS_IN_WEEK; day++) {
        printf("\n--- %s ---\n", days[day]);

        // Cardio
        printf("Select a Cardio Exercise:\n");
        for (int i = 0; i < 3; i++) {
            printf("%d. %s\n", i + 1, cardio[i]);
        }
        printf("Enter choice: ");
        scanf("%d", &cardio_choice);
        strcpy(member->routine[day][0], cardio[cardio_choice - 1]);

        // Strength/Core
        printf("Select a Strength/Core Exercise:\n");
        printf("1. Full-body: Push-ups\n2. Full-body: Squats\n");
        printf("3. Lower-body: Leg Press\n4. Lower-body: Leg Curl\n");
        printf("5. Upper-body: Pull-ups\n6. Upper-body: Chin-ups\n");
        if (core_used == 0) {
            printf("7. Core: Plank\n8. Core: Crunches\n");
        }
        printf("Enter choice: ");
        scanf("%d", &strength_choice);

        switch (strength_choice) {
            case 1: strcpy(member->routine[day][1], "Push-ups"); break;
            case 2: strcpy(member->routine[day][1], "Squats"); break;
            case 3: strcpy(member->routine[day][1], "Leg Press"); break;
            case 4: strcpy(member->routine[day][1], "Leg Curl"); break;
            case 5: strcpy(member->routine[day][1], "Pull-ups"); break;
            case 6: strcpy(member->routine[day][1], "Chin-ups"); break;
            case 7:
                if (core_used == 0) {
                    strcpy(member->routine[day][1], "Plank");
                    core_used = 1;
                } else {
                    printf("Core already used this week! Choose another.\n");
                    day--; // repeat this day
                    continue;
                }
                break;
            case 8:
                if (core_used == 0) {
                    strcpy(member->routine[day][1], "Crunches");
                    core_used = 1;
                } else {
                    printf("Core already used this week! Choose another.\n");
                    day--; // repeat this day
                    continue;
                }
                break;
            default:
                printf("Invalid choice. Try again.\n");
                day--; // repeat this day
                continue;
        }
    }

    printf("\nWorkout routine set for %s.\n", member->real_name);
}

// Function to view workout routine
void getExerciseRoutine() {
    char name[MAX_NAME_LEN];
    int found = 0;

    printf("\nEnter member's real name: ");
    scanf("%s", name);

    for (int i = 0; i < member_count; i++) {
        if (strcmp(milliways_members[i].real_name, name) == 0) {
            printf("\n--- Workout Routine for %s (%s) ---\n", milliways_members[i].real_name, milliways_members[i].nickname);
            for (int j = 0; j < DAYS_IN_WEEK; j++) {
                printf("%s: Cardio - %s | Strength/Core - %s\n", days[j],
                       milliways_members[i].routine[j][0],
                       milliways_members[i].routine[j][1]);
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Member not found.\n");
    }
}
int main() {
    char choice;

    while (1) {
        printf("\n--- Milliways Training Stage 1 ---\n");
        printf("A. Show Member List\n");
        printf("C. Set Basic Workout Routine\n");
        printf("D. View Basic Workout Routine\n");
        printf("E. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice); // Note the space before %c to clear input buffer

        switch (choice) {
            case 'A':
                displayMemberList();
                break;
            case 'C':
                setExerciseRoutine();
                break;
            case 'D':
                getExerciseRoutine();
                break;
            case 'E':
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
