#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mainmenu(void);
void adminLogin(void);
void userLogin(void);
void userRegistration(void);
void viewMenu(void);
void addMenu(void);
void deleteMenu(void);
void viewFeedback(void);
void orderSnack(void);
void giveFeedback(void);

int adminAuthenticated = 0;

// Main function
int main() {
    mainmenu();
    return 0;
}

void mainmenu(void) {
    int select;
    while (1) {
        system("cls");
        printf("========== RESTAURANT MANAGEMENT SYSTEM ==========\n");
        printf("1. Admin Section\n");
        printf("2. User Section\n");
        printf("3. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &select);

        switch (select) {
            case 1:
                adminLogin();
                break;
            case 2:
                userLogin();
                break;
            case 3:
                exit(0);
                break;
            default:
                printf("Invalid input! Please enter a valid option.\n");
                getchar();  // Pause to show the error
        }
    }
}

// Admin login function
void adminLogin(void) {
    char username[20], password[20];

    printf("\nAdmin Login:\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "23235299") == 0) {
        printf("\nLogin successful.\n");
        adminAuthenticated = 1;
        int choice;
        while (1) {
            printf("\nAdmin Section:\n");
            printf("1. View Menu\n");
            printf("2. Add Menu Item\n");
            printf("3. Delete Menu Item\n");
            printf("4. View Feedback\n");
            printf("5. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    viewMenu();
                    break;
                case 2:
                    addMenu();
                    break;
                case 3:
                    deleteMenu();
                    break;
                case 4:
                    viewFeedback();
                    break;
                case 5:
                    return;
                default:
                    printf("Invalid input! Please enter a valid option.\n");
            }
        }
    } else {
        printf("Incorrect username or password.\n");
    }
}

// User login and registration
void userLogin(void) {
    char username[20], password[20];
    int choice;

    printf("\nUser Section:\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\nUser Login:\n");
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
            printf("\nLogin successful.\n");
            while (1) {
                printf("\nUser Section:\n");
                printf("1. View Menu\n");
                printf("2. Order Snack\n");
                printf("3. Give Feedback\n");
                printf("4. Back to Main Menu\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1:
                        viewMenu();
                        break;
                    case 2:
                        orderSnack();
                        break;
                    case 3:
                        giveFeedback();
                        break;
                    case 4:
                        return;
                    default:
                        printf("Invalid input! Please enter a valid option.\n");
                }
            }
            break;
        case 2:
            userRegistration();
            break;
        default:
            printf("Invalid input! Please enter a valid option.\n");
    }
}

void userRegistration(void) {
    char name[50], email[50], contact[15], username[20], password[20];

    printf("\nUser Registration:\n");
    printf("Name: ");
    scanf("%s", name);
    printf("Email: ");
    scanf("%s", email);
    printf("Contact Number: ");
    scanf("%s", contact);
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    printf("Registration successful! You can now log in.\n");
}

// View menu
void viewMenu(void) {
    FILE *menuFile;
    char line[256];

    menuFile = fopen("menu.txt", "r");
    if (menuFile == NULL) {
        printf("Error opening menu file.\n");
        return;
    }

    printf("\nCurrent Menu:\n");
    while (fgets(line, sizeof(line), menuFile)) {
        printf("%s", line);
    }
    fclose(menuFile);
}

// Add menu item
void addMenu(void) {
    FILE *menuFile;
    char itemName[50];
    double price;

    menuFile = fopen("menu.txt", "a");
    if (menuFile == NULL) {
        printf("Error opening menu file.\n");
        return;
    }

    printf("\nEnter new menu item name: ");
    scanf("%s", itemName);
    printf("Enter price: ");
    scanf("%lf", &price);

    fprintf(menuFile, "%s - %.2f Taka\n", itemName, price);
    fclose(menuFile);

    printf("Item added successfully.\n");
}

// Delete menu item
void deleteMenu(void) {
    // Simplified code, assumes each item occupies a single line in the menu.txt file
    printf("\nDelete menu item function not implemented.\n");
}

// Order snacks
void orderSnack(void) {
    int choice, quantity;
    double total = 0;
    char line[256];
    FILE *menuFile;

    menuFile = fopen("menu.txt", "r");
    if (menuFile == NULL) {
        printf("Error opening menu file.\n");
        return;
    }

    printf("\nAvailable Snacks:\n");
    while (fgets(line, sizeof(line), menuFile)) {
        printf("%s", line);
    }
    fclose(menuFile);

    printf("\nEnter the item number you want to order: ");
    scanf("%d", &choice);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // For demonstration, assume each item costs 100 * choice value Taka
    total = 100 * choice * quantity;

    printf("Your total amount is: %.2f Taka\n", total);
}

// Give feedback
void giveFeedback(void) {
    FILE *feedbackFile;
    char feedback[256];

    feedbackFile = fopen("feedback.txt", "a");
    if (feedbackFile == NULL) {
        printf("Error opening feedback file.\n");
        return;
    }

    printf("\nEnter your feedback: ");
    getchar();  // Clear newline character left by previous scanf
    fgets(feedback, sizeof(feedback), stdin);

    fprintf(feedbackFile, "%s", feedback);
    fclose(feedbackFile);

    printf("Thank you for your feedback!\n");
}

// View feedback (admin only)
void viewFeedback(void) {
    FILE *feedbackFile;
    char feedback[256];

    feedbackFile = fopen("feedback.txt", "r");
    if (feedbackFile == NULL) {
        printf("Error opening feedback file.\n");
        return;
    }

    printf("\nFeedbacks:\n");
    while (fgets(feedback, sizeof(feedback), feedbackFile)) {
        printf("%s", feedback);
    }
    fclose(feedbackFile);
}

