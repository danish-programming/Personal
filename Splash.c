#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For sleep function

#define WIDTH 50  // Smaller width for better view

void print_splash_screen(const char *name, const char *date) {
    system("cls");  // Clear the screen (works for Windows, use "clear" for Linux/macOS)

    // Print top border
    for (int i = 0; i < WIDTH; i++) {
        printf("+");
    }
    printf("\n");

    // Print the main message, split into multiple lines
    printf("Magrathea, where a shining planet is created in a wasteland\n");
    printf("with no grass, a place where \n");
    printf("and gems are polished by the hands of experts.\n");
    printf("Welcome to Magrathea.\n");

    // Print bottom border
    for (int i = 0; i < WIDTH; i++) {
        printf("+");
    }
    printf("\n");

    // Print user and date
    printf("[User]: %s [Execution Time]: %s\n", name, date);
}

int main() {
    char name[100];
    char date[20];

    // Ask for user input
    printf("Please enter the current date in the \"yyyy-mm-dd\" format: ");
    scanf("%s", date);
    printf("Please enter your name: ");
    scanf("%s", name);

    // Success message after input
    printf("**The input has been processed successfully.**\n");

    // Wait for 3 seconds before clearing the screen and displaying the splash
    sleep(3);

    // Show the splash screen
    print_splash_screen(name, date);

    return 0;  // Make sure to close the main function properly
}
