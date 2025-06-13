#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 20
#define MAX_MENTORS 8
#define MAX_TRAUMA 100
#define MAX_RESPONSE 100
#define MAX_COUNSELING 20

// Trainee list (reuse from previous code)
const char *traineeNicknames[MAX_TRAINEES] = {
    "Sky", "Luna", "Ray", "Nova", "Sol", "Kai", "Echo", "Zane",
    "Mira", "Ash", "Ivy", "Leo", "Aria", "Finn", "Jade", "Nico",
    "Quinn", "Sage", "Rey", "Skye"
};

int traineeAbilities[MAX_TRAINEES];
int traineeIds[MAX_TRAINEES];

// Mentor struct
struct Mentor {
    int id;
    char name[20];
    int menteeId;
};

struct Mentor mentors[MAX_MENTORS];
int mentorCount = 0;

// Trauma struct
struct Trauma {
    char nickname[20];
    int age;
    char description[MAX_TRAUMA];
};

struct Trauma traumaList[MAX_TRAINEES];
int traumaCount = 0;

// Counseling Question struct
struct Question {
    int id;
    char content[150];
};

const struct Question questions[5] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

// Counseling session struct
struct Counseling {
    char nickname[20];
    char question[150];
    char response[MAX_RESPONSE];
};

struct Counseling sessions[MAX_COUNSELING];
int sessionCount = 0;

int parseIntMember(const char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i] != '\0'; i++) {
        sum += nickname[i];
    }
    return sum;
}

int getRandomAbility() {
    return rand() % 901 + 100; // 100 to 1000
}

void initializeTrainees() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        traineeIds[i] = parseIntMember(traineeNicknames[i]);
        traineeAbilities[i] = getRandomAbility();
    }
}

void inputMentors() {
    printf("Enter mentor names (up to 8):\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        printf("Mentor %d: ", i + 1);
        scanf("%s", mentors[i].name);
        mentors[i].id = i + 1;
        mentors[i].menteeId = -1; // initially unset
        mentorCount++;
    }
}

void matchMentoring() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int mentorId = (traineeIds[i] % MAX_MENTORS);
        mentors[mentorId].menteeId = traineeIds[i];
        printf("Trainee %s (ID %d) matched with Mentor %s (ID %d)\n",
               traineeNicknames[i], traineeIds[i], mentors[mentorId].name, mentors[mentorId].id);
    }
}

int findTraineeAge(const char *nickname) {
    // Dummy ages assigned for simplicity
    for (int i = 0; i < MAX_TRAINEES; i++) {
        if (strcmp(traineeNicknames[i], nickname) == 0)
            return 18 + (i % 5);
    }
    return -1;
}

void inputTraumaData() {
    char nickname[20];
    char description[MAX_TRAUMA];

    while (1) {
        printf("Enter nickname (or 'exit' to return): ");
        scanf("%s", nickname);
        if (strcmp(nickname, "exit") == 0) break;

        int age = findTraineeAge(nickname);
        age != -1 ? printf("Enter trauma description: ") : printf("Nickname not found. Try again.\n");

        if (age != -1) {
            getchar(); // clear buffer
            fgets(description, MAX_TRAUMA, stdin);
            description[strcspn(description, "\n")] = '\0';

            strcpy(traumaList[traumaCount].nickname, nickname);
            traumaList[traumaCount].age = age;
            strcpy(traumaList[traumaCount].description, description);
            traumaCount++;
        }
    }
}

void counselingSession() {
    if (traumaCount == 0) {
        printf("No trauma data found.\n");
        return;
    }

    printf("Members with trauma:\n");
    for (int i = 0; i < traumaCount; i++) {
        printf("%d. %s\n", i + 1, traumaList[i].nickname);
    }

    int choice;
    printf("Select a member by number: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > traumaCount) {
        printf("Invalid choice.\n");
        return;
    }

    char selected[20];
    strcpy(selected, traumaList[choice - 1].nickname);

    for (int i = 0; i < 3; i++) {
        int qIndex = rand() % 5;
        char response[MAX_RESPONSE];
        printf("Q: %s\n", questions[qIndex].content);
        printf("A: ");
        getchar();
        fgets(response, MAX_RESPONSE, stdin);
        response[strcspn(response, "\n")] = '\0';

        while (strlen(response) == 0 || strlen(response) > 100) {
            printf("Response must be 1-100 characters. Try again: ");
            fgets(response, MAX_RESPONSE, stdin);
            response[strcspn(response, "\n")] = '\0';
        }

        strcpy(sessions[sessionCount].nickname, selected);
        strcpy(sessions[sessionCount].question, questions[qIndex].content);
        strcpy(sessions[sessionCount].response, response);
        sessionCount++;
    }
}

void viewCounseling() {
    if (sessionCount == 0) {
        printf("No counseling sessions completed.\n");
        return;
    }

    char name[20];
    printf("Enter nickname to view session: ");
    scanf("%s", name);

    for (int i = 0; i < traumaCount; i++) {
        if (strcmp(name, traumaList[i].nickname) == 0) {
            printf("\nNickname: %s\nAge: %d\nTrauma: %s\n", traumaList[i].nickname, traumaList[i].age, traumaList[i].description);
            for (int j = 0; j < sessionCount; j++) {
                if (strcmp(sessions[j].nickname, name) == 0) {
                    printf("Q: %s\nA: %s\n", sessions[j].question, sessions[j].response);
                }
            }
            return;
        }
    }
    printf("No session found for %s.\n", name);
}

void overcomeTrauma() {
    int choice;
    do {
        printf("\nTrauma Management Menu:\n1. Input Trauma Data\n2. Counseling Session\n3. View Counseling\n4. Back\nSelect: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: inputTraumaData(); break;
            case 2: counselingSession(); break;
            case 3: viewCounseling(); break;
        }
    } while (choice != 4);
}

void menu() {
    int choice;
    do {
        printf("\nMain Menu:\n1. Match Mentoring\n2. Trauma Management\n3. Exit\nSelect: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: matchMentoring(); break;
            case 2: overcomeTrauma(); break;
        }
    } while (choice != 3);
}

int main() {
    srand(time(NULL));
    initializeTrainees();
    inputMentors();
    menu();
    return 0;
}
