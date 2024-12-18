#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include<time.h>


#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"

// Function Prototypesk
void print_line(char ch, int length, const char *color);//sourabh
void display_header(const char *title);//sourabh
void loading_animation();//sourabh
void main_menu();//sourabh
void admin_section();//arni
void user_section();//sourabh
int admin_login();//arni
int user_login();//sourabh
void user_registration();//arni
void add_menu_item();//alvi
void view_menu();//arni
void delete_menu_item();//alvi
void view_feedback();//alvi
void give_feedback();//alvi
void order_item();//sourabh

void print_line(char ch, int length, const char *color) {
    printf("%s", color);
    for (int i = 0; i < length; i++) {
        printf("%c", ch);
    }
    printf(RESET "\n");
}

void display_header(const char *title) {
    system("cls");
    gotoxy(30,1);
    print_line('=', 50, CYAN);
    gotoxy(30,2);
    printf("     %s\t\t%s\n", BOLD, title);
    gotoxy(30,3);
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

COORD coord = {0, 0}; // sets coordinates to 0,0
COORD max_res,cursor_size;
void gotoxy (int x, int y)
{
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    main_menu();
    return 0;
}

void main_menu() {
    system("cls");
    int choice;
    while (1) {
        gotoxy(30,1);
    printf("\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd RESTAURENT MANAGEMENT SYSTEM\xcd\xcd\xcd\xcd\xcd\xcd\xcd");

    gotoxy(30,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(30,5);
        printf("\xDB\xDB\xDB\xDB\xB2 1.ADMIN SECTION   ");

        gotoxy(30,7);
        printf("\xDB\xDB\xDB\xDB\xB2 2.USER SECTION   ");

        gotoxy(30,9);
        printf("\xDB\xDB\xDB\xDB\xB2 3.EXIT   ");

        gotoxy(30,13);
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
                main_menu();
        }
    }
}

int admin_login() {
    char username[20], password[20];
    int attempts = 3;

    while (attempts > 0) {
        system("cls");
        display_header("ADMIN LOGIN");

        gotoxy(30, 5);
        printf("Username: ");
        scanf("%s", username);
        gotoxy(30, 7);
        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
            printf(GREEN "Login successful!\n" RESET);
            Sleep(1000);
            return 1;
        } else {
            printf(RED "Incorrect username or password. Attempts left: %d\n" RESET, --attempts);
            Sleep(1000);
        }
    }
    printf(BOLD "Too many failed attempts. Returning to main menu.\n" RESET);
    Sleep(1500);
    main_menu();
    return 0;
}

void admin_section() {
    system("cls");
    int choice;
    while (1) {
        display_header("ADMIN SECTION");
        gotoxy(30,5);
        printf(CYAN "1. View Menu\n" RESET);
        gotoxy(30,6);
        printf(CYAN "2. Add Menu Item\n" RESET);
        gotoxy(30,7);
        printf(CYAN "3. Delete Menu Item\n" RESET);
        gotoxy(30,8);
        printf(CYAN "4. View Feedback\n" RESET);
        gotoxy(30,9);
        printf( "5. Back to Main Menu\n" );
        gotoxy(30,11);
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
            case 5: main_menu();
                return;
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                getch();
        }
    }
}

void add_menu_item() {
system("cls");
    FILE *menuFile = fopen("menu.txt", "a+");
    if (menuFile == NULL) {
        printf(RED "Error opening menu file.\n" RESET);
        getch();
        return;
    }

    char itemName[50];
    double price;
    int itemCount = 1;

    //extra
    //int itemCount;

    fseek(menuFile, 0, SEEK_SET);
    while (!feof(menuFile)) {
        if (fgetc(menuFile) == '\n') {
            itemCount++;
        }
    }

    display_header("ADMIN SECTION");
    //extraa

    gotoxy(30,4);
    printf(BOLD "Add menu item" RESET);
    gotoxy(30,5);
    printf(YELLOW "Enter item name: " RESET);
    scanf(" %s", itemName);
    gotoxy(30,7);
    printf(YELLOW "Enter price: " RESET);
    scanf("%lf", &price);

    fprintf(menuFile, "%d %s %.2f\n", itemCount, itemName, price);
    printf(GREEN "Item added successfully with item number %d\n" RESET, itemCount);

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
    printf(BLUE "\nMenu:\n" RESET);
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
    display_header("ADMIN SECTION");
    gotoxy(30,4);
    printf(BOLD "Delete Menu Item" RESET);
    gotoxy(30,5);
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
    char name[100];

    if (feedbackFile == NULL) {
        printf(RED "No feedback available.\n" RESET);
        getch();
        return;
    }
    display_header("ADMIN SECTION");
    gotoxy(30,4);
    printf(BOLD "View feedback" RESET);

    printf(CYAN "\nFeedbacks:\n" RESET);
    while (fgets(feedback, sizeof(feedback), feedbackFile) != NULL) {
        printf("%s %s", feedback,name);
    }

    fclose(feedbackFile);
    printf(CYAN "\nPress any key to return.\n" RESET);
    getch();
}

void give_feedback() {
    FILE *feedbackFile = fopen("feedback.txt", "a");
    char feedback[1000];
    char name[100];

    if (feedbackFile == NULL) {
        printf(RED "Error opening feedback file.\n" RESET);
        getch();
        return;
    }

    display_header("USER SECTION");
    printf(BOLD "Give feedback" RESET);

    printf(YELLOW "\nEnter your feedback: " RESET);
    scanf(" %[^\n]", feedback);
        printf(YELLOW "\nEnter your name: " RESET);
    scanf(" %[^\n]", name);

    if (strlen(feedback) > 0) {
        fprintf(feedbackFile, "%s ->says %s\n", feedback,name);
        printf(GREEN "Thank you for your feedback!\n" RESET);
    } else {
        printf(RED "Feedback cannot be empty.\n" RESET);
    }

    fclose(feedbackFile);
    getch();
}

void user_section() {
    system("cls");
    int choice;
    while (1) {
        system("cls");
        display_header("USER SECTION");
        gotoxy(30,5);
        printf(GREEN "1. Register\n" RESET);
        gotoxy(30,6);
        printf(GREEN "2. Login\n" RESET);
        gotoxy(30,7);
        printf( "3. Back to Main Menu\n" );
        gotoxy(30,9);
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
                        gotoxy(30,5);
                        printf(YELLOW "1. View Menu\n" RESET);
                        gotoxy(30,6);
                        printf(YELLOW "2. Order\n" RESET);
                        gotoxy(30,7);
                        printf(YELLOW "3. Give Feedback\n" RESET);
                        gotoxy(30,8);
                        printf( "4. Back to Main Menu\n" );
                        gotoxy(30,10);
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
                                main_menu();
                                break;;
                            default:
                                printf(RED "Invalid choice! Please try again.\n" RESET);
                                getch();
                                user_choice;
                        }
                    }
                }
                break;
            case 3:
                main_menu();
                return;
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
                getch();
                main_menu();
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

    display_header("USER SECTION");
    gotoxy(30,4);
    printf("Login");
    gotoxy(30,5);
    printf(CYAN "Username: " RESET);
    scanf("%s", username);
    gotoxy(30,6);
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
    display_header("USER SECTION");
        gotoxy(30,4);
    printf(BOLD "Registration" RESET);

    gotoxy(30,5);
    printf(CYAN "Enter Name: " RESET);
    scanf(" %[^\n]", name);
    gotoxy(30,6);
    printf(CYAN "Enter Email: " RESET);
    scanf("%s", email);
    gotoxy(30,7);
    printf(CYAN "Enter Contact Number: " RESET);
    scanf("%lld", &contact);
    gotoxy(30,8);
    printf(CYAN "Set Username: " RESET);
    scanf("%s", username);
    gotoxy(30,9);
    printf(CYAN "Set Password: " RESET);
    scanf("%s", password);

    fprintf(usersFile, "%s %s %s %lld %s\n", username, password, name, contact, email);
    fclose(usersFile);
    printf(GREEN "Registration successful! You can now log in.\n" RESET);
}

typedef struct {
    int itemNumber;
    char itemName[50];
    double price;
    int quantity;
    double total;
} CartItem;


void print_receipt(CartItem cart[], int itemCount, double totalPrice, double discount, const char* customerInfo) {
    printf("\n \xcd\xcd\xcd\xcd\xcd Receipt \xcd\xcd\xcd\xcd\xcd \n");
    for (int i = 0; i < itemCount; i++) {
        printf("%s x%d: %.2f BDT\n", cart[i].itemName, cart[i].quantity, cart[i].total);
    }
    if (discount > 0) {
        printf(GREEN "\nStudent discount applied: %.2f BDT\n" RESET, discount);
    }
    printf(GREEN "Total amount: %.2f BDT\n" RESET, totalPrice);
    printf("Customer Info: %s\n", customerInfo);  // Print customer details
    Sleep(10000);  // Sleep for 10 seconds
}

void order_item() {
    int itemNumber, quantity;
    double totalPrice = 0.0;
    int orderMore = 1;
    CartItem cart[100];  // Assuming a max of 100 items in the cart
    int itemCount = 0;  // Track the number of items in the cart
    double discount = 0.0;
    char customerInfo[200];  // To store customer details for the receipt

    display_header("USER SECTION");

    printf(BOLD "Order Item" RESET);
    while (orderMore) {
        view_menu();
        printf("\nEnter the item number you wish to order: ");
        scanf("%d", &itemNumber);

        printf("\nEnter quantity: ");
        scanf("%d", &quantity);

        FILE *menuFile = fopen("menu.txt", "r");
        if (menuFile == NULL) {
            printf(RED "Error opening menu.\n" RESET);
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

                // Add item to cart
                cart[itemCount].itemNumber = itemNumber;
                strcpy(cart[itemCount].itemName, itemName);
                cart[itemCount].price = price;
                cart[itemCount].quantity = quantity;
                cart[itemCount].total = itemTotal;
                itemCount++;

                //printf(GREEN "\n %s x%d, Total: %.2lf BDT\n" RESET, itemName, quantity, itemTotal);
                found = 1;
                break;
            }
        }

        fclose(menuFile);

        if (!found) {
            printf(RED "\nItem number %d not found in the menu.\n" RESET, itemNumber);
            printf(RED "Please try again.\n" RESET);
            continue;
        }

        printf(CYAN "\nDo you want to order more? (1 for Yes, 0 for No): " RESET);
        scanf("%d", &orderMore);
    }

    // Student discount section
    char isStudent;
    printf(CYAN "\nAre you a student? (Y/N): " RESET);
    scanf(" %c", &isStudent);

    if (isStudent == 'Y' || isStudent == 'y') {
        char studentId[20];
        printf(CYAN "Please provide your Student ID: " RESET);
        scanf("%s", studentId);
        discount = totalPrice * 0.10;  // 10% discount
        totalPrice -= discount;  // Apply discount
        printf(GREEN "\nStudent discount applied (10%% off).\n" RESET);

        // Prepare customer info for receipt
        snprintf(customerInfo, sizeof(customerInfo), "Student ID: %s", studentId);
    } else {
        char name[50], name2[50], contact[20];
        printf(CYAN "Please provide your First name: " RESET);
        scanf(" %s", name);
        printf(CYAN "Please provide your Last name: " RESET);
        scanf(" %s", name2);
        printf(CYAN "Please provide your contact number: " RESET);
        scanf(" %s", contact);

        // Prepare customer info for receipt
        snprintf(customerInfo, sizeof(customerInfo), "\nName: %s %s, \nContact: %s", name, name2, contact);
    }

    // Print the receipt with customer info
    print_receipt(cart, itemCount, totalPrice, discount, customerInfo);

    printf(MAGENTA "Thank you for ordering!\n" RESET);
    printf(CYAN "\nPress any key to return to the main menu..." RESET);
    getchar();  // To capture the key press
    Sleep(10000);  // Wait for a moment before going back
    main_menu(); // Assuming this is defined elsewhere in your program
}

