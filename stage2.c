#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRAINEE_COUNT 8
#define MAX_NAME_LEN 20

// Struct for Trainee
typedef struct {
    char name[MAX_NAME_LEN];
    int id;         // ASCII sum of name
    int ability;    // random ability
} Trainee;

// Struct for Mentor
typedef struct {
    int id;                     // unique mentor ID (1–8)
    char name[MAX_NAME_LEN];   // mentor name
    int menteeIndex;           // index of assigned trainee
} Mentor;

// Convert trainee name to ASCII sum
int parseIntMember(const char *name) {
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        sum += (int)name[i];
    }
    return sum;
}

// Generate random ability between 100 and 1000
int getRandomAbility() {
    return (rand() % 901) + 100;
}

// Initialize trainees with name, ASCII sum, and ability
void initializeTrainees(Trainee trainees[], const char* names[]) {
    for (int i = 0; i < TRAINEE_COUNT; i++) {
        strncpy(trainees[i].name, names[i], MAX_NAME_LEN);
        trainees[i].id = parseIntMember(names[i]);
        trainees[i].ability = getRandomAbility();
    }
}

// Input up to 8 mentors
void inputMentors(Mentor mentors[]) {
    for (int i = 0; i < TRAINEE_COUNT; i++) {
        mentors[i].id = i + 1;
        printf("Enter mentor name for ID %d: ", mentors[i].id);
        scanf("%s", mentors[i].name);
        mentors[i].menteeIndex = -1;
    }
}

// Match each trainee to a mentor (1:1 match using mod logic)
void matchMentoring(Trainee trainees[], Mentor mentors[]) {
    for (int i = 0; i < TRAINEE_COUNT; i++) {
        int mentorIndex = trainees[i].id % TRAINEE_COUNT;

        // If already assigned, find next available mentor (bonus: 1:1 match)
        while (mentors[mentorIndex].menteeIndex != -1) {
            mentorIndex = (mentorIndex + 1) % TRAINEE_COUNT;
        }

        mentors[mentorIndex].menteeIndex = i;
    }
}

// Output all mentor-mentee pairs
void printMatches(Trainee trainees[], Mentor mentors[]) {
    printf("\n--- Mentor-Mentee Matches ---\n");
    for (int i = 0; i < TRAINEE_COUNT; i++) {
        int menteeIndex = mentors[i].menteeIndex;
        if (menteeIndex != -1) {
            printf("Trainee #%d (%s) -> Mentor #%d (%s)\n",
                   menteeIndex + 1, trainees[menteeIndex].name,
                   mentors[i].id, mentors[i].name);
        }
    }
}

int main() {
    srand(time(NULL)); // seed RNG

    // Sample trainee names (can be modified)
    const char* traineeNames[TRAINEE_COUNT] = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Frank", "Grace", "Hannah"
    };

    Trainee trainees[TRAINEE_COUNT];
    Mentor mentors[TRAINEE_COUNT];

    // Step-by-step process
    initializeTrainees(trainees, traineeNames);
    inputMentors(mentors);
    matchMentoring(trainees, mentors);
    printMatches(trainees, mentors);

    return 0;
}
