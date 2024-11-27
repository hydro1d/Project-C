#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

// ANSI Color Codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"

// Function Prototypes
void print_line(char ch, int length, const char *color);
void display_header(const char *title);
void loading_animation();
void main_menu();
void admin_section();
void user_section();
int admin_login();
int user_login();
void user_registration();
void add_menu_item();
void view_menu();
void delete_menu_item();
void view_feedback();
void give_feedback();
void order_item();

void print_line(char ch, int length, const char *color) {
    printf("%s", color);
    for (int i = 0; i < length; i++) {
        printf("%c", ch);
    }
    printf(RESET "\n");
}

void display_header(const char *title) {
    system("cls");
    print_line('=', 50, CYAN);
    printf("%s\t\t%s\n", BOLD, title);
    print_line('=', 50, CYAN);
}

void loading_animation() {
    printf(BLUE "Loading" RESET);
    for (int i = 0; i < 5; i++) {
        Sleep(500);
        printf(BLUE "." RESET);
    }
    printf("\n");
}

int main() {
    main_menu();
    return 0;
}

void main_menu() {
    int choice;
    while (1) {
        display_header("RESTAURANT MANAGEMENT SYSTEM");
        printf(GREEN "1. Admin Section\n" RESET);
        printf(YELLOW "2. User Section\n" RESET);
        printf(RED "3. Exit\n" RESET);
        printf(CYAN "Enter your choice: " RESET);
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
                printf(MAGENTA "Exiting the system. Thank you!\n" RESET);
                exit(0);
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                getch(); // Pause
        }
    }
}

int admin_login() {
    char username[20], password[20];
    display_header("ADMIN LOGIN");
    printf(CYAN "Username: " RESET);
    scanf("%s", username);
    printf(CYAN "Password: " RESET);
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "23235299") == 0) {
        printf(GREEN "Login successful!\n" RESET);
        Sleep(1000);
        return 1;
    } else {
        printf(RED "Incorrect username or password.\n" RESET);
        getch();
        return 0;
    }
}

void admin_section() {
    int choice;
    while (1) {
        display_header("ADMIN SECTION");
        printf(YELLOW "1. View Menu\n" RESET);
        printf(GREEN "2. Add Menu Item\n" RESET);
        printf(RED "3. Delete Menu Item\n" RESET);
        printf(CYAN "4. View Feedback\n" RESET);
        printf(MAGENTA "5. Back to Main Menu\n" RESET);
        printf(CYAN "Enter your choice: " RESET);
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
                printf(RED "Invalid choice! Please try again.\n" RESET);
                getch();
        }
    }
}

void add_menu_item() {
    FILE *menuFile = fopen("menu.txt", "a+");
    if (menuFile == NULL) {
        printf(RED "Error opening menu file.\n" RESET);
        getch();
        return;
    }

    char itemName[50];
    double price;
    int itemCount = 1;

    fseek(menuFile, 0, SEEK_SET);
    while (!feof(menuFile)) {
        if (fgetc(menuFile) == '\n') {
            itemCount++;
        }
    }

    printf(YELLOW "Enter item name: " RESET);
    scanf(" %[^\n]", itemName);
    printf(YELLOW "Enter price: " RESET);
    scanf("%lf", &price);

    fprintf(menuFile, "%d %s %.2f\n", itemCount, itemName, price);
    printf(GREEN "Item added successfully with item number %d.\n" RESET, itemCount);

    fclose(menuFile);
    getch();
}

void view_menu() {
    FILE *menuFile = fopen("menu.txt", "r");
    if (menuFile == NULL) {
        printf(RED "Menu is empty. Please ask the admin to add items.\n" RESET);
        getch();
        return;
    }

    char line[100];
    printf(BLUE "Menu:\n" RESET);
    while (fgets(line, sizeof(line), menuFile)) {
        printf("%s", line);
    }
    fclose(menuFile);
    printf(CYAN "\nPress any key to return.\n" RESET);
    getch();
}

void delete_menu_item() {
    FILE *menuFile = fopen("menu.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");
    int itemNumber, currentNumber;
    char itemName[50];
    double price;
    int found = 0;

    if (menuFile == NULL || tempFile == NULL) {
        printf(RED "Error opening file.\n" RESET);
        getch();
        return;
    }

    printf(YELLOW "Enter item number to delete: " RESET);
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
        printf(GREEN "Item deleted successfully.\n" RESET);
    } else {
        printf(RED "Item not found.\n" RESET);
    }
    getch();
}

void view_feedback() {
    FILE *feedbackFile = fopen("feedback.txt", "r");
    char feedback[1000];

    if (feedbackFile == NULL) {
        printf(RED "No feedback available.\n" RESET);
        getch();
        return;
    }

    printf(BLUE "Feedbacks:\n" RESET);
    while (fgets(feedback, sizeof(feedback), feedbackFile) != NULL) {
        printf("%s", feedback);
    }

    fclose(feedbackFile);
    printf(CYAN "\nPress any key to return.\n" RESET);
    getch();
}

void give_feedback() {
    FILE *feedbackFile = fopen("feedback.txt", "a");
    char feedback[1000];

    if (feedbackFile == NULL) {
        printf(RED "Error opening feedback file.\n" RESET);
        getch();
        return;
    }

    printf(YELLOW "Enter your feedback: " RESET);
    scanf(" %[^\n]", feedback);

    if (strlen(feedback) > 0) {
        fprintf(feedbackFile, "%s\n", feedback);
        printf(GREEN "Thank you for your feedback!\n" RESET);
    } else {
        printf(RED "Feedback cannot be empty.\n" RESET);
    }

    fclose(feedbackFile);
    getch();
}

void user_section() {
    int choice;
    while (1) {
        display_header("USER SECTION");
        printf(GREEN "1. Register\n" RESET);
        printf(YELLOW "2. Login\n" RESET);
        printf(RED "3. Back to Main Menu\n" RESET);
        printf(CYAN "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                user_registration();
                break;
            case 2:
                if (user_login()) {
                    int user_choice;
                    while (1) {
                        display_header("USER MENU");
                        printf(GREEN "1. View Menu\n" RESET);
                        printf(YELLOW "2. Order\n" RESET);
                        printf(MAGENTA "3. Give Feedback\n" RESET);
                        printf(RED "4. Back to Main Menu\n" RESET);
                        printf(CYAN "Enter your choice: " RESET);
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
                                printf(RED "Invalid choice! Please try again.\n" RESET);
                                getch();
                        }
                    }
                }
                break;
            case 3:
                return;
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                getch();
        }
    }
}

int user_login() {
    char username[20], password[20], stored_username[20], stored_password[20];
    FILE *userFile = fopen("users.txt", "r");

    if (userFile == NULL) {
        printf(RED "No users registered yet. Please register first.\n" RESET);
        getch();
        return 0;
    }

    display_header("USER LOGIN");
    printf(CYAN "Username: " RESET);
    scanf("%s", username);
    printf(CYAN "Password: " RESET);
    scanf("%s", password);

    while (fscanf(userFile, "%s %s\n", stored_username, stored_password) != EOF) {
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            fclose(userFile);
            printf(GREEN "Login successful!\n" RESET);
            Sleep(1000);
            return 1;
        }
    }

    fclose(userFile);
    printf(RED "Incorrect username or password.\n" RESET);
    getch();
    return 0;
}

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

void order_item() {
    int itemNumber, quantity;
    double totalPrice = 0.0;
    int orderMore = 1;

    while (orderMore) {
        view_menu();
        printf("\nEnter the item number you wish to order: ");
        scanf("%d", &itemNumber);
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        FILE *menuFile = fopen("menu.txt", "r");
        if (menuFile == NULL) {
            printf("Error opening menu.\n");
            getch();
            return;
        }

        int currentItem;
        char itemName[50];
        double price;
        int found = 0;

        while (fscanf(menuFile, "%d %s %lf", &currentItem, itemName, &price) != EOF) {
            if (currentItem == itemNumber) {
                double itemTotal = price * quantity;
                totalPrice += itemTotal;
                printf("\nOrder confirmed: %s x%d, Subtotal: %.2f\n", itemName, quantity, itemTotal);
                found = 1;
                break;
            }
        }

        fclose(menuFile);

        if (!found) {
            printf("\nItem number %d not found in the menu.\n", itemNumber);
        }

        printf("\nDo you want to order more? (1 for Yes, 0 for No): ");
        scanf("%d", &orderMore);
    }

    printf("\nYour total order amount is: %.2f\n", totalPrice);
    printf("Thank you for ordering!\n");
    printf("\nPress any key to return to the main menu...");
    getch();
}
