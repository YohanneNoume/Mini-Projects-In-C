#include "election.h"

void displayMenu() {
    printf("\nMini-Voting System\n");
    printf("1. Student Panel\n");
    printf("2. Admin Panel\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    char choice;
    while (1) {
        displayMenu();
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                studentPanel();
                break;
            case '2':
                adminPanel();
                break;
            case '3':
                printf("Exiting the system.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
    return 0;
}
