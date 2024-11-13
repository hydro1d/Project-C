#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main_menu(); // sourabh
void admin_section(); // sourabh
void user_section();//sourabh
int admin_login();//arni
int user_login();//arni
void user_registration();
void add_menu_item();//alvi
void view_menu();//arni
void delete_menu_item();//alvi
void view_feedback();//alvi
void give_feedback();//alvi
void order_item();//sourabh

int main() {
    main_menu();
    return 0;
}

// Main Menu er code
void main_menu() {
    int choice;
    while (1) {
        system("cls");
        printf("\n***** RESTAURANT MANAGEMENT SYSTEM *****\n");
        printf("1. Admin Section\n");
        printf("2. User Section\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (admin_login()) {
                    admin_section();
                }
                break;
            case 2:
                user_section();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Admin Login er code
int admin_login() {
    char username[20], password[20];
    printf("\nAdmin Login:\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "23235299") == 0) {
        return 1;
    } else {
        printf("Incorrect username or password.\n");
        return 0;
    }
}

// Admin Section er code
void admin_section() {
    int choice;
    while (1) {
        system("cls");
        printf("\n***** ADMIN SECTION *****\n");
        printf("1. View Menu\n");
        printf("2. Add Menu Item\n");
        printf("3. Delete Menu Item\n");
        printf("4. View Feedback\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_menu();
                break;
            case 2:
                add_menu_item();
                break;
            case 3:
                delete_menu_item();
                break;
            case 4:
                view_feedback();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// Add Menu Item er code
void add_menu_item() {
    FILE *menuFile = fopen("menu.txt", "a+");
    if (menuFile == NULL) {
        printf("Error opening menu file.\n");
        return;
    }

    char itemName[50];
    double price;
    int itemCount = 1;

    // Count existing items to assign a new item number
    fseek(menuFile, 0, SEEK_SET);
    while (!feof(menuFile)) {
        if (fgetc(menuFile) == '\n') {
            itemCount++;
        }
    }

    printf("Enter item name: ");
    scanf(" %[^\n]", itemName);
    printf("Enter price: ");
    scanf("%lf", &price);

    fprintf(menuFile, "%d %s %.2f\n", itemCount, itemName, price);
    printf("Item added successfully with item number %d.\n", itemCount);

    fclose(menuFile);
}

// View Menu
void view_menu() {
    FILE *menuFile = fopen("menu.txt", "r");
    if (menuFile == NULL) {
        printf("Menu is empty. Please ask the admin to add items.\n");
        return;
    }

    char line[100];
    printf("Menu:\n");
    while (fgets(line, sizeof(line), menuFile)) {
        printf("%s", line);  // Print each item (line) from the menu file
    }
    fclose(menuFile);
    printf("\nPress any key to return.\n");
    getch();
}

// Delete Menu Item
void delete_menu_item() {
    FILE *menuFile = fopen("menu.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    int itemNumber, currentNumber;
    char itemName[50];
    double price;
    int found = 0;

    if (menuFile == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter item number to delete: ");
    scanf("%d", &itemNumber);

    while (fscanf(menuFile, "%d %s %lf\n", &currentNumber, itemName, &price) != EOF) {
        if (currentNumber != itemNumber) {
            fprintf(tempFile, "%d %s %.2f\n", currentNumber, itemName, price);
        } else {
            found = 1;
        }
    }

    fclose(menuFile);
    fclose(tempFile);

    remove("menu.txt");
    rename("temp.txt", "menu.txt");

    if (found) {
        printf("Item deleted successfully.\n");
    } else {
        printf("Item not found.\n");
    }
}

// View Feedback
void view_feedback() {
    FILE *feedbackFile = fopen("feedback.txt", "r");
    char feedback[1000];

    if (feedbackFile == NULL) {
        printf("No feedback available.\n");
        return;
    }

    printf("Feedbacks:\n");
    while (fgets(feedback, sizeof(feedback), feedbackFile) != NULL) {
        printf("%s", feedback);
    }

    fclose(feedbackFile);
    printf("\nPress any key to return.\n");
    getch();
}

// User Section
void user_section() {
    int choice;
    while (1) {
        system("cls");
        printf("\n***** USER SECTION *****\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                user_registration();
                break;
            case 2:
                if (user_login()) {
                    int user_choice;
                    while (1) {
                        system("cls");
                        printf("\n***** USER MENU *****\n");
                        printf("1. View Menu\n");
                        printf("2. Order\n");
                        printf("3. Give Feedback\n");
                        printf("4. Back to Main Menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &user_choice);

                        switch (user_choice) {
                            case 1:
                                view_menu();
                                break;
                            case 2:
                                order_item();
                                break;
                            case 3:
                                give_feedback();
                                break;
                            case 4:
                                return;
                            default:
                                printf("Invalid choice! Please try again.\n");
                        }
                    }
                }
                break;
            case 3:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

// User Registration
void user_registration() {
    FILE *usersFile = fopen("users.txt", "a");
    char username[20], password[20], name[50], email[50];
    long long int contact;

    printf("Enter Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Email: ");
    scanf("%s", email);
    printf("Enter Contact Number: ");
    scanf("%lld", &contact);
    printf("Set Username: ");
    scanf("%s", username);
    printf("Set Password: ");
    scanf("%s", password);

    fprintf(usersFile, "%s %s %s %lld %s\n", username, password, name, contact, email);
    fclose(usersFile);
    printf("Registration successful! You can now log in.\n");
}

// User Login
int user_login() {
    FILE *usersFile = fopen("users.txt", "r");
    char username[20], password[20];
    char fileUsername[20], filePassword[20], fileName[50], fileEmail[50];
    long long int fileContact;

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (usersFile == NULL) {
        printf("No users registered yet.\n");
        return 0;
    }

    while (fscanf(usersFile, "%s %s %s %lld %s\n", fileUsername, filePassword, fileName, &fileContact, fileEmail) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            printf("Login successful! Welcome %s.\n", fileName);
            fclose(usersFile);
            return 1;
        }
    }

    printf("Incorrect username or password.\n");
    fclose(usersFile);
    return 0;
}

// Order Item
// Order Item
void order_item() {
    int itemNumber, quantity;
    double totalPrice = 0.0;

    view_menu();  // Show menu to user
    printf("\nEnter the item number you wish to order: ");
    scanf("%d", &itemNumber);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    // Find the item in the menu
    FILE *menuFile = fopen("menu.txt", "r");
    if (menuFile == NULL) {
        printf("Error opening menu.\n");
        return;
    }

    int currentItem;
    char itemName[50];
    double price;
    int found = 0;

    // Adjusted fscanf to read the entire line including spaces in item name
    while (fscanf(menuFile, "%d %[^\t] %lf", &currentItem, itemName, &price) != EOF) {
        if (currentItem == itemNumber) {
            totalPrice = price * quantity;
            printf("Order confirmed: %s x%d, Total: %.2f\n", itemName, quantity, totalPrice);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Item number %d not found in the menu.\n", itemNumber);
    }

    fclose(menuFile);
}


// Give Feedback
void give_feedback() {
    FILE *feedbackFile = fopen("feedback.txt", "a");
    char feedback[1000];

    if (feedbackFile == NULL) {
        printf("Error opening feedback file.\n");
        return;
    }

    printf("Enter your feedback: ");
    scanf(" %[^\n]", feedback);

    fprintf(feedbackFile, "%s\n", feedback);
    fclose(feedbackFile);

    printf("Thank you for your feedback!\n");
}

