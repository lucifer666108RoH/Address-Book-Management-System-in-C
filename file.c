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


#include <stdio.h>
#include "file.h"

// Function to save contacts to a file
// This function writes the contacts from the address book to a CSV file
void saveContactsToFile(AddressBook *addressBook) {
    FILE *file = fopen("contacts.csv", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%d\n", addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n", 
                addressBook->contacts[i].name,
                 addressBook->contacts[i].phone,
                 addressBook->contacts[i].email);
    }

    fclose(file);
}
// Function to load contacts from a file
// This function reads contacts from a CSV file and populates the address book
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *file = fopen("contacts.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    fscanf(file, "%d", &addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++) {
        fscanf(file, "%[^,],%[^,],%[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(file);
}
