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



#include "contact.h"
#include "auth.h"


int main() {
    AddressBook addressBook;  

    if (!authenticate()) {
        return 0;  // Exit if authentication fails
    }

    int choice;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook); // Save contacts to file and exit
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
