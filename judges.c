#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define BUFFER_SIZE 1024
#define INFO_ITEMS 7

char judges_array[MAX_JUDGES][BUFFER_SIZE];

void display_judge_info(char *data, int index) {
    char *items[INFO_ITEMS];
    char *token = strtok(data, ",");
    int count = 0;

    while (token != NULL && count < INFO_ITEMS) {
        while (*token == ' ') token++;  // Remove leading space
        items[count++] = token;
        token = strtok(NULL, ",");
    }

    if (count != INFO_ITEMS) {
        printf("The input items are incorrect. Please enter them again.\n");
        return;
    }

    printf("[Judge %d]\n", index + 1);
    printf("Name: %s\n", items[0]);
    printf("Gender: %s\n", items[1]);
    printf("Affiliation: %s\n", items[2]);
    printf("Title: %s\n", items[3]);
    printf("Expertise: %s\n", items[4]);
    printf("Email: %s\n", items[5]);
    printf("Phone: %s\n", items[6]);
    printf("-----------------------------------\n");
}

int main() {
    char project_name[100];
    int total_judges;
    int selected_members;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);

    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // clear leftover newline

    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0'; // remove newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    for (int i = 0; i < total_judges;) {
        printf("Judge %d: ", i + 1);
        fgets(judges_array[i], BUFFER_SIZE, stdin);
        judges_array[i][strcspn(judges_array[i], "\n")] = '\0'; // remove newline

        // Count commas to validate correct format
        int comma_count = 0;
        for (int j = 0; judges_array[i][j]; j++) {
            if (judges_array[i][j] == ',') {
                comma_count++;
            }
        }

        if (comma_count != 6) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue; // retry same judge
        }

        i++; // move to next judge only if input was correct
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char choice;
    printf("\"%s\" Should we check the judge information? (Y/N): ", project_name);
    scanf(" %c", &choice); // space before %c to skip newline

    if (choice == 'N') {
        printf("Program terminated.\n");
        return 0;
    }

    printf("####################################\n");
    printf("#        Display Judge Data        #\n");
    printf("####################################\n");

    for (int i = 0; i < total_judges; i++) {
        char copy[BUFFER_SIZE];
        strcpy(copy, judges_array[i]);
        display_judge_info(copy, i);
    }

    return 0;
}
