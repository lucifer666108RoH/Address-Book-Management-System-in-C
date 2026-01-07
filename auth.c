// Name        : Anudeep R
// Date        : 04/07/2025
// Sample Input:
//   Name: John Doe
//   Phone: 9876543210
//   Email: john@gmail.com
//
// Sample Output:
//   Contact saved successfully!
//   Total Contacts: 1
//
// Description:
//   A simple Address Book program in C to store and manage contacts.
//   It allows users to create new contacts by entering name, phone number, and email.
//   The program validates phone number (must be 10 digits, numeric, and unique) and email
//   (must be lowercase, contain exactly one '@', end with '.com', and not be duplicate).
//
//   The validation is done using basic string functions and control statements.
//   The code uses arrays and loops — written in a beginner-friendly way.
//
//   This project helps in understanding structures, string handling, validation logic,
//   and basic user interaction in C programming.


// auth.c
#include <stdio.h>
#include <string.h>
#include "auth.h"

#define USERNAME "admin"
#define PASSWORD "1234"
// Function to authenticate the user
// This function prompts the user for a username and password
// It checks the entered credentials against predefined values
// If the credentials match, it grants access; otherwise, it denies access
// The username is "admin" and the password is "1234"
int authenticate() {
    char username[20], password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Access granted.\n");
        return 1;
    } else {
        printf("Access denied. Invalid credentials.\n");
        return 0;
    }
}
