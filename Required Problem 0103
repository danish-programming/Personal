#include <stdio.h>
#include <stdlib.h>

// Max candidates
#define NUM_CANDIDATES 6

// Declare arrays
char names[NUM_CANDIDATES][50];
int birthYear[NUM_CANDIDATES];
int birthMonth[NUM_CANDIDATES];
int birthDay[NUM_CANDIDATES];
char gender[NUM_CANDIDATES];
char emails[NUM_CANDIDATES][50];
char nationalities[NUM_CANDIDATES][30];
float bmi[NUM_CANDIDATES];
char primarySkills[NUM_CANDIDATES][30];
char secondarySkills[NUM_CANDIDATES][50];
int topik[NUM_CANDIDATES];
char mbti[NUM_CANDIDATES][10];
char introductions[NUM_CANDIDATES][300];

int calculateAge(int y, int m, int d) {
    int currentYear = 2025, currentMonth = 4, currentDay = 14;
    int age = currentYear - y;
    if (currentMonth < m || (currentMonth == m && currentDay < d)) {
        age--;
    }
    return age;
}

int main() {
    char groupName[50];
    char ch;
    int i = 0;

    // Get group name using getchar
    printf("Enter audition group name (e.g., Milliways): ");
    while ((ch = getchar()) != '\n' && i < 49) {
        groupName[i++] = ch;
    }
    groupName[i] = '\0';  // end string

    // Input screen
    printf("####################################\n");
    printf("[%s] Audition Candidate Data Entry\n", groupName);
    printf("####################################\n");

    int count = 0;
    while (count < NUM_CANDIDATES) {
        printf("Entering information for candidate %d.\n", count + 1);
        printf("---------------------------------\n");

        printf("1. Name: ");
        scanf(" %[^\n]", names[count]);

        printf("2. Date of Birth (YYYY/MM/DD format): ");
        scanf("%d/%d/%d", &birthYear[count], &birthMonth[count], &birthDay[count]);

        printf("3. Gender (F for Female, M for Male): ");
        scanf(" %c", &gender[count]);

        printf("4. Email: ");
        scanf(" %[^\n]", emails[count]);

        printf("5. Nationality: ");
        scanf(" %[^\n]", nationalities[count]);

        printf("6. BMI: ");
        scanf("%f", &bmi[count]);

        printf("7. Primary Skill: ");
        scanf(" %[^\n]", primarySkills[count]);

        printf("8. Secondary Skill: ");
        scanf(" %[^\n]", secondarySkills[count]);

        printf("9. Korean Proficiency Level (TOPIK): ");
        scanf("%d", &topik[count]);

        printf("10. MBTI: ");
        scanf(" %[^\n]", mbti[count]);

        printf("11. Introduction: ");
        getchar();  // consume newline
        fgets(introductions[count], 300, stdin);

        printf("=================================\n");
        count++;
    }

    // Output screen
    printf("####################################\n");
    printf("[%s] Audition Candidate Data Review\n", groupName);
    printf("####################################\n");

    printf("=============================================================================================================\n");
    printf("Name (Age)          | DOB       | G | Email                 | Nationality | BMI  | Primary | Secondary        | TOPIK  | MBTI |\n");
    printf("=============================================================================================================\n");

    for (i = 0; i < NUM_CANDIDATES; i++) {
        int age = calculateAge(birthYear[i], birthMonth[i], birthDay[i]);

        // Show Korean proficiency
        char *koreanLevel;
        if (topik[i] == 0) koreanLevel = "Native";
        else if (topik[i] == 1) koreanLevel = "Beginner";
        else if (topik[i] == 2) koreanLevel = "Basic";
        else if (topik[i] == 3) koreanLevel = "Intermediate";
        else if (topik[i] == 4) koreanLevel = "Advanced";
        else koreanLevel = "Fluent";

        printf("%-18s (%2d) | %04d%02d%02d | %c | %-21s | %-11s | %.1f | %-8s | %-16s | %-7s | %-4s |\n",
               names[i], age, birthYear[i], birthMonth[i], birthDay[i],
               gender[i], emails[i], nationalities[i],
               bmi[i], primarySkills[i], secondarySkills[i],
               koreanLevel, mbti[i]);

        printf("-------------------------------------------------------------------------------------------------------------\n");
        printf("%s", introductions[i]);
        printf("-------------------------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
