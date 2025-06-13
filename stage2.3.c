#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_MEMBERS 10
#define MAX_MENTORS 8
#define MAX_TRAUMA 10
#define MAX_COUNSELING 30

// --- Structs ---
typedef struct {
    char nickname[20];
    int age;
    int asciiSum;
    int ability;
} Trainee;

typedef struct {
    int id;
    char name[20];
    int menteeIndex;
} Mentor;

typedef struct {
    char nickname[20];
    int age;
    char trauma[100];
} Trauma;

typedef struct {
    int id;
    char question[100];
} Question;

typedef struct {
    char nickname[20];
    char question[100];
    char response[101];
} Counseling;

typedef struct {
    char keyword[10];
    char message[300];
} EasterEgg;

// --- Global Variables ---
Trainee trainees[MAX_MEMBERS];
Mentor mentors[MAX_MENTORS];
Trauma traumaList[MAX_TRAUMA];
Question questions[5] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};
Counseling counselingList[MAX_COUNSELING];
int counselingCount = 0;

// --- Function Prototypes ---
int parseIntMember(char *nickname);
int getRandomAbility();
void initTrainees();
void inputMentors();
void matchMentoring();
void printMatches();
void overcomeTrauma();
void find_easter_egg();
int isRightChar(char expected, char actual);
int isEasterEgg(char *input);
void convertToBinary(char ch, char *binary);
void shuffleKeywordAndBinary(char *keyword);

// --- Utility Functions ---
int parseIntMember(char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i] != '\0'; i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

int getRandomAbility() {
    return rand() % 901 + 100;
}

void initTrainees() {
    char *names[MAX_MEMBERS] = {"Alex", "Bella", "Cody", "Daisy", "Eli", "Fay", "George", "Hana", "Ivan", "Jin"};
    for (int i = 0; i < MAX_MEMBERS; i++) {
        strcpy(trainees[i].nickname, names[i]);
        trainees[i].age = 18 + i;
        trainees[i].asciiSum = parseIntMember(trainees[i].nickname);
        trainees[i].ability = getRandomAbility();
    }
}

void inputMentors() {
    for (int i = 0; i < MAX_MENTORS; i++) {
        mentors[i].id = i + 1;
        sprintf(mentors[i].name, "Mentor%d", i + 1);
        mentors[i].menteeIndex = -1;
    }
}

void matchMentoring() {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        int id = i % MAX_MENTORS;
        mentors[id].menteeIndex = i;
    }
    printMatches();
}

void printMatches() {
    printf("\nMentoring Matches:\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        if (mentors[i].menteeIndex >= 0) {
            printf("Trainee: %s (Index: %d) -> Mentor: %s (ID: %d)\n",
                   trainees[mentors[i].menteeIndex].nickname,
                   mentors[i].menteeIndex,
                   mentors[i].name, mentors[i].id);
        }
    }
}

// --- Trauma & Counseling Functions ---
void overcomeTrauma() {
    int choice;
    char nickname[20], traumaText[100];
    do {
        printf("\n1. Input Trauma\n2. Counseling Session\n0. Back\n> ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            while (1) {
                printf("\nEnter nickname: ");
                fgets(nickname, sizeof(nickname), stdin);
                nickname[strcspn(nickname, "\n")] = '\0';
                int found = 0;
                for (int i = 0; i < MAX_MEMBERS; i++) {
                    if (strcmp(nickname, trainees[i].nickname) == 0) {
                        found = 1;
                        strcpy(traumaList[i].nickname, nickname);
                        traumaList[i].age = trainees[i].age;
                        printf("Enter trauma: ");
                        fgets(traumaText, sizeof(traumaText), stdin);
                        traumaText[strcspn(traumaText, "\n")] = '\0';
                        strcpy(traumaList[i].trauma, traumaText);
                        break;
                    }
                }
                found ? printf("Trauma recorded.\n") : printf("Nickname not found. Try again.\n");
                printf("Continue trauma input? (y/n): ");
                char again;
                scanf(" %c", &again);
                getchar();
                if (tolower(again) != 'y') break;
            }
        } else if (choice == 2) {
            printf("Available members with trauma:\n");
            for (int i = 0; i < MAX_TRAUMA; i++) {
                if (strlen(traumaList[i].nickname) > 0)
                    printf("%s\n", traumaList[i].nickname);
            }
            printf("Select nickname: ");
            fgets(nickname, sizeof(nickname), stdin);
            nickname[strcspn(nickname, "\n")] = '\0';
            for (int i = 0; i < 3; i++) {
                int qIndex = rand() % 5;
                char response[101];
                printf("Q%d: %s\n> ", questions[qIndex].id, questions[qIndex].question);
                fgets(response, sizeof(response), stdin);
                response[strcspn(response, "\n")] = '\0';
                while (strlen(response) == 0 || strlen(response) > 100) {
                    printf("Invalid. Retry: ");
                    fgets(response, sizeof(response), stdin);
                    response[strcspn(response, "\n")] = '\0';
                }
                strcpy(counselingList[counselingCount].nickname, nickname);
                strcpy(counselingList[counselingCount].question, questions[qIndex].question);
                strcpy(counselingList[counselingCount].response, response);
                counselingCount++;
            }
            printf("\nCounseling Completed for %s\n", nickname);
        }
    } while (choice != 0);
}

// --- Easter Egg Functions ---
void convertToBinary(char ch, char *binary) {
    for (int i = 7; i >= 0; i--) {
        binary[7 - i] = ((ch >> i) & 1) + '0';
    }
    binary[8] = '\0';
}

int isRightChar(char expected, char actual) {
    return expected == actual;
}

int isEasterEgg(char *input) {
    return strcmp(input, "specter") == 0;
}

void find_easter_egg() {
    EasterEgg egg = {"specter", "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."};
    printf("<<Arthur's Easter Egg>>\n");
    char bin[8][9];
    for (int i = 0; i < 7; i++) {
        convertToBinary(egg.keyword[i], bin[i]);
    }
    printf("Enter characters for these binary (reversed):\n");
    for (int i = 6; i >= 0; i--) {
        printf("%s => ", bin[i]);
        char ch;
        scanf(" %c", &ch);
        if (!isRightChar(egg.keyword[i], ch)) {
            printf("Wrong input. Try again later.\n");
            return;
        }
    }
    char word[10];
    printf("\nCombine the characters to form the word: ");
    scanf("%s", word);
    if (isEasterEgg(word)) {
        printf("\n##Easter Egg Discovered!$$\n%s\n", egg.message);
    } else {
        printf("Wrong word. Returning to menu.\n");
    }
}

// --- Menu ---
void showMenu() {
    char input[20];
    while (1) {
        printf("\n[II. Training > 2. Self-Management and Teamwork]\n");
        printf("A. Mentoring\nB. Trauma Management\nQ. Quit\n> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcasecmp(input, "A") == 0) {
            matchMentoring();
        } else if (strcasecmp(input, "B") == 0) {
            overcomeTrauma();
        } else if (strcasecmp(input, "Arthur") == 0) {
            find_easter_egg();
        } else if (strcasecmp(input, "Q") == 0) {
            break;
        } else {
            printf("Invalid input. Try again.\n");
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    initTrainees();
    inputMentors();
    showMenu();
    return 0;
}
