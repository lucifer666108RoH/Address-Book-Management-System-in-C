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
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


// Function to list all contacts in the address book
// This function sorts the contacts alphabetically by name and then prints them
void listContacts(AddressBook *addressBook) 
{
    int i,j;
    for ( i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for ( j = i + 1; j < addressBook->contactCount; j++) 
        {
            if (strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0) 
            {
                // Swap contacts[i] and contacts[j]
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }
    for (int i = 0; i < addressBook->contactCount; i++) {
        printf("\nName: %s, Phone: %s, Email: %s\n", 
               addressBook->contacts[i].name, 
               addressBook->contacts[i].phone, 
               addressBook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
saveContactsToFile(addressBook); // Save contacts to file
exit(EXIT_SUCCESS); // Exit the program
} 

int number_validation(AddressBook *addressBook, char number[11]) {
    // Check if the number is 10 digits long and contains only digits
    if (strlen(number) !=  10) {
        printf("Invalid number length. It should be 10 digits.\n");
        return 0; // Invalid length
    }
    for (int i = 0; i < 10; i++) {
        if (number[i] < '0' || number[i] > '9') {
            printf("Invalid character in number. It should contain only digits.\n");
            return 0; // Contains non-digit character
        }
    }
    return 1; // Valid number
}
int email_validation(AddressBook *addressBook, char email[20]) {
    int i;
    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] >= 'A' && email[i] <= 'Z') {
            printf("Email should not contain capital letters.\n");
            return 0;
        }
    }

    // 2. Check for exactly one '@'
    int at_count = 0;
    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            at_count++;
        }
    }

    if (at_count != 1) {
        printf("Email should contain exactly one '@'.\n");
        return 0;
    }

    // 3. Use strstr() to find ".com"
    int dotcom_count = 0;
    char *pos = email;
    while ((pos = strstr(pos, ".com")) != NULL) {
        dotcom_count++;
        pos += 4; // move past ".com" to check for more
    }

    if (dotcom_count != 1) {
        printf("Email should contain '.com' only once.\n");
        return 0;
    }

    // 4. Check if it ends with ".com"
    int len = strlen(email);
    if (len < 4 || strcmp(&email[len - 4], ".com") != 0) {
        printf("Email should end with '.com'.\n");
        return 0;
    }

    return 1; // Email is valid
}
// Function to create a new contact in the address book
// This function prompts the user for contact details and adds the contact to the address book
// It takes the address book as a parameter
// It validates the phone number and email before adding the contact
void createContact(AddressBook *addressBook)
{
    printf("Enter the name of the contact: ");
    // Read the name from the user
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
    /* Define the logic to create a Contacts */

    char number[11];
    int res,valid = 0;
    do {
        printf("Enter a 10-digit phone number: ");
        scanf("%s", number);

        res = number_validation(addressBook, number);
        for(int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].phone, number) == 0) {
                printf("This phone number already exists. Please enter a different number.\n");
                res = 0; // Reset res to 0 to prompt for re-entry
                break; // Exit the loop if a duplicate is found
            }
        }
        if (res == 0) {
            printf("Please enter a valid 10-digit phone number.\n");
        } else {
            strcpy(addressBook->contacts[addressBook->contactCount].phone, number);
             // Increment contact count after successful addition
        }
    } while (res != 1); // Validate the number
    char mail[20];
    do
    {
        printf("Enter email ID: ");
        scanf("%s", mail);
        valid = email_validation(addressBook, mail);
        for(int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].email, mail) == 0) {
                printf("This email already exists. Please enter a different email.\n");
                valid = 0; // Reset res to 0 to prompt for re-entry
                break; // Exit the loop if a duplicate is found
            }
        }
        if (valid == 0) {
            printf("Please enter a valid email ID.\n");
        } else {
            strcpy(addressBook->contacts[addressBook->contactCount].email, mail);
          // Increment contact count after successful addition
        }
    } while (valid != 1);
      addressBook->contactCount++; 
}

// Function to search for a contact by name
int search_name(AddressBook *addressBook, char *name) {
    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
            printf("Contact found: Name: %s, Phone: %s, Email: %s\n", 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            found = 1; // Set found flag to true 
        }
    }
    if(!found) {
            printf("Contact not found.\n");
            return -1; // Contact not found
    }
}
int search_phone(AddressBook *addressBook, char *phone) {
    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0) {
            printf("Contact found: Name: %s, Phone: %s, Email: %s\n", 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            found = 1; // Set found flag to true
            return i; // Return the index of the found contact
        }
            
        }
    if(!found) {
        printf("Contact not found.\n"); 
        return -1; // Contact not found
    }
    }
int search_email(AddressBook *addressBook, char *email) {
    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, email) == 0) {
            printf("Contact found: Name: %s, Phone: %s, Email: %s\n", 
                   addressBook->contacts[i].name, 
                   addressBook->contacts[i].phone, 
                   addressBook->contacts[i].email);
            found = 1; // Set found flag to true
            return i; // Return the index of the found contact
        }
        }
    if(!found) {
        printf("Contact not found.\n");
        return -1; // Contact not found
    }
}
// Function to search for a contact in the address book
// This function allows the user to search for a contact by name, phone number, or email   
void searchContact(AddressBook *addressBook) 
{
    int choice;
    printf("\n search meanu\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email\n");
    printf("4. Back to Main Menu\n");
    do{
    printf("Enter your choice: ");
    char sname[20];
    char sphone[11];
    char semail[20];
    scanf("%d", &choice);   
    switch (choice) {
        case 1:
            printf("Enter search name\n");
            scanf(" %[^\n]", sname); // Read the name to search
            search_name(addressBook, sname);
            break; // Implement search by name logic
        case 2:
            printf("Enter search phone number\n");      
            scanf("%s", sphone); // Read the phone number to search
            search_phone(addressBook, sphone);
            break; // Implement search by phone number logic
        case 3:
            printf("Enter search email\n"); 
            scanf("%s", semail); // Read the email to search
            search_email(addressBook, semail);
            break; // Implement search by email logic
        case 4:
            printf("Returning to Main Menu...\n");  
            return; // Back to main menu
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }while(choice != 4);
}
int searchename(AddressBook *addressBook, char *name) {
    int search = 0,serial = 1,choice;
    int found_index[100]; // Array to store indices of found contacts
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].name, name) == 0) {
          printf("%d) Contact found: Name: %s, Phone: %s, Email: %s\n",serial, 
                 addressBook->contacts[i].name, 
                 addressBook->contacts[i].phone, 
                 addressBook->contacts[i].email);
            search = 1; // Return the index of the found contact
            found_index[serial - 1] = i; // Store the index of the found contact
            serial++;
        }
    }
    if (search == 0) {
        printf("Contact not found.\n");
        return -1; // Contact not found
    }
    printf("Enter the serial number of the contact you want to edit or delete: ");
    scanf("%d", &choice);
    if (choice < 1 || choice >= serial) {
        printf("Invalid choice. Please try again.\n");
        return -1; // Invalid choice
    }
    return found_index[choice - 1]; // Return the index of the found contact based on user choice   
}
// Function to edit a contact field in the address book
// This function allows the user to edit a specific field of a contact (name, phone number, or email)
// It takes the address book and the index of the contact to be edited as parameters
int edit_contact_field(AddressBook *addressBook, int index) 
{
    int choice;
    printf("Choose the field to edit:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("4. Back to Search Menu\n"); 
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        char newName[20];
        switch (choice) {
            case 1:
                printf("Enter new name: ");
                scanf(" %[^\n]",newName);
                strcpy(addressBook->contacts[index].name, newName);
                break;
            case 2: {
                char newPhone[11];
                int res;
                do {
                    printf("Enter new 10-digit phone number: ");
                    scanf("%s", newPhone);
                    res = number_validation(addressBook, newPhone);
                    for(int i = 0; i < addressBook->contactCount; i++) {
                        if (strcmp(addressBook->contacts[i].phone, newPhone) == 0 && i != index) {
                            printf("This phone number already exists. Please enter a different number.\n");
                            res = 0; // Reset res to 0 to prompt for re-entry
                            break; // Exit the loop if a duplicate is found
                        }
                    }
                    if (res == 0) {
                        printf("Please enter a valid 10-digit phone number.\n");
                    } else {
                        strcpy(addressBook->contacts[index].phone, newPhone);
                    }
                } while (res != 1); // Validate the number
                break;
            }
            case 3: {
                char newEmail[20];
                int res;
                do {
                    printf("Enter new email ID: ");
                    scanf("%s", newEmail);
                    res = email_validation(addressBook, newEmail);
                    for(int i = 0; i < addressBook->contactCount; i++) {
                        if (strcmp(addressBook->contacts[i].email, newEmail) == 0 && i != index) {
                            printf("This email already exists. Please enter a different email.\n");
                            res = 0; // Reset res to 0 to prompt for re-entry
                            break; // Exit the loop if a duplicate is found
                        }
                    }
                    if (res == 0) {
                        printf("Please enter a valid email ID.\n");
                    } else {
                        strcpy(addressBook->contacts[index].email, newEmail);
                    }
                } while (res != 1); // Validate the email
                break;
            }
            case 4:
                printf("Return main meanu");
                break; // Back to search menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice < 1 || choice > 4);
    printf("Contact updated successfully.\n");
    printf("Updated Contact: Name: %s, Phone: %s, Email: %s\n", 
           addressBook->contacts[index].name, 
           addressBook->contacts[index].phone, 
           addressBook->contacts[index].email);
    return 0; // Return 0 to indicate successful edit
}
// Function to edit a contact in the address book
// This function allows the user to edit a contact by name, phone number, or email
void editContact(AddressBook *addressBook)
{
    printf("\n Edit meanu\n");
    printf("1. Edit by Name\n");    
    printf("2. Edit by Phone Number\n");
    printf("3. Edit by Email\n");
    printf("4. Back to Main Menu\n");
    int choice;
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                char name[20];
                printf("Enter the name to edit: ");
                scanf(" %[^\n]", name); // Read the name to search
                int index = search_name(addressBook, name);
                if (index != -1) {
                    edit_contact_field(addressBook, index);
                }
                break; // Implement edit by name logic
            }
            case 2: {
                char phone[11];
                printf("Enter the phone number to edit: ");
                scanf("%s", phone); // Read the phone number to search
                int index = search_phone(addressBook, phone);
                if (index != -1) {
                    edit_contact_field(addressBook, index);
                }
                break; // Implement edit by phone number logic
            }
            case 3: {
                char email[20];
                printf("Enter the email to edit: ");
                scanf("%s", email); // Read the email to search
                int index = search_email(addressBook, email);
                if (index != -1) {
                    edit_contact_field(addressBook, index);
                }
                break; // Implement edit by email logic
            }
            case 4:
                printf("Returning to Main Menu...\n");
                return; // Back to main menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice < 1 || choice > 4);
    /* Define the logic for Editcontact */

}
//contact delition
// Function to delete a contact from the address book
void deleteContact(AddressBook *addressBook)
{

    printf("\n Delete meanu\n");
    printf("1. Delete by Name\n");  
    printf("2. Delete by Phone Number\n");
    printf("3. Delete by Email\n");
    printf("4. Back to Main Menu\n");
    int choice;
    do {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                char name[20];
                printf("Enter the name to delete: ");
                scanf(" %[^\n]", name); // Read the name to search
                int index = searchename(addressBook, name);
                if (index != -1) {
                    // Shift contacts to delete the found contact
                    for (int i = index; i < addressBook->contactCount - 1; i++) {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--; // Decrease contact count
                    printf("Contact deleted successfully.\n");
                }
                break; // Implement delete by name logic
            }
            case 2: {
                char phone[11];
                printf("Enter the phone number to delete: ");
                scanf("%s", phone); // Read the phone number to search
                int index = search_phone(addressBook, phone);
                if (index != -1) {
                    // Shift contacts to delete the found contact
                    for (int i = index; i < addressBook->contactCount - 1; i++) {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--; // Decrease contact count
                    printf("Contact deleted successfully.\n");
                }
                break; // Implement delete by phone number logic
            }
            case 3: {
                char email[20];
                printf("Enter the email to delete: ");
                scanf("%s", email); // Read the email to search
                int index = search_email(addressBook, email);
                if (index != -1) {
                    // Shift contacts to delete the found contact
                    for (int i = index; i < addressBook->contactCount - 1; i++) {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--; // Decrease contact count
                    printf("Contact deleted successfully.\n");
                }
                break; // Implement delete by email logic
            }
            case 4:
                printf("Returning to Main Menu...\n");
                return; // Back to main menu
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice < 1 || choice > 4);
    printf("\n saving after deletion successfully.....\n");
}