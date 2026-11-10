/*
 * Parking Slot Management System
 * Data Structure: Singly Linked List
 * Features: Park, remove, display vehicles, show available slots.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SLOTS 10
#define REG_LEN 20

typedef struct Vehicle {
    char registration[REG_LEN];
    int slotNumber;
    struct Vehicle *next;
} Vehicle;

Vehicle *head = NULL;
int occupiedSlots = 0;

/* Read a complete line and remove its trailing newline. */
void readLine(const char *prompt, char *buffer, size_t size) {
    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

/* Portable case-insensitive string comparison. */
int equalsIgnoreCase(const char *a, const char *b) {
    while (*a && *b) {
        if (toupper((unsigned char)*a) != toupper((unsigned char)*b))
            return 0;
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

/* Case-insensitive registration number comparison. */
int registrationExists(const char *registration) {
    Vehicle *current = head;

    while (current != NULL) {
        if (equalsIgnoreCase(current->registration, registration)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

/* Find the first unused slot number. */
int getAvailableSlot(void) {
    int used[MAX_SLOTS + 1] = {0};
    Vehicle *current = head;

    while (current != NULL) {
        if (current->slotNumber >= 1 && current->slotNumber <= MAX_SLOTS)
            used[current->slotNumber] = 1;
        current = current->next;
    }

    for (int i = 1; i <= MAX_SLOTS; i++) {
        if (!used[i])
            return i;
    }
    return -1;
}

void parkVehicle(void) {
    char registration[REG_LEN];

    if (occupiedSlots == MAX_SLOTS) {
        printf("\nParking area is FULL. No slots are available.\n");
        return;
    }

    readLine("Enter vehicle registration number: ", registration, sizeof(registration));

    if (strlen(registration) == 0) {
        printf("Registration number cannot be empty.\n");
        return;
    }

    if (registrationExists(registration)) {
        printf("This vehicle is already parked.\n");
        return;
    }

    Vehicle *newVehicle = (Vehicle *)malloc(sizeof(Vehicle));
    if (newVehicle == NULL) {
        printf("Memory allocation failed. Vehicle was not parked.\n");
        return;
    }

    int slot = getAvailableSlot();
    strcpy(newVehicle->registration, registration);
    newVehicle->slotNumber = slot;
    newVehicle->next = NULL;

    if (head == NULL) {
        head = newVehicle;
    } else {
        Vehicle *current = head;
        while (current->next != NULL)
            current = current->next;
        current->next = newVehicle;
    }

    occupiedSlots++;
    printf("Vehicle parked successfully in slot %d.\n", slot);
}

void removeVehicle(void) {
    char registration[REG_LEN];
    readLine("Enter registration number to remove: ", registration, sizeof(registration));

    if (strlen(registration) == 0) {
        printf("Registration number cannot be empty.\n");
        return;
    }

    Vehicle *current = head;
    Vehicle *previous = NULL;

    while (current != NULL &&
           !equalsIgnoreCase(current->registration, registration)) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Vehicle not found in the parking area.\n");
        return;
    }

    int freedSlot = current->slotNumber;

    if (previous == NULL)
        head = current->next;
    else
        previous->next = current->next;

    free(current);
    occupiedSlots--;

    printf("Vehicle removed successfully. Slot %d is now available.\n", freedSlot);
}

void displayVehicles(void) {
    Vehicle *current = head;

    if (current == NULL) {
        printf("\nNo vehicles are currently parked.\n");
        return;
    }

    printf("\n--------------- PARKED VEHICLES ---------------\n");
    printf("%-12s %-22s\n", "SLOT", "REGISTRATION NUMBER");
    printf("-----------------------------------------------\n");

    while (current != NULL) {
        printf("%-12d %-22s\n", current->slotNumber, current->registration);
        current = current->next;
    }
    printf("-----------------------------------------------\n");
}

void displayAvailability(void) {
    printf("\nTotal parking slots : %d\n", MAX_SLOTS);
    printf("Occupied slots      : %d\n", occupiedSlots);
    printf("Available slots     : %d\n", MAX_SLOTS - occupiedSlots);

    if (occupiedSlots == MAX_SLOTS)
        printf("Status              : PARKING FULL\n");
    else
        printf("Status              : SLOTS AVAILABLE\n");
}

void displayMenu(void) {
    printf("\n========== PARKING SLOT MANAGEMENT ==========\n");
    printf("1. Park a vehicle\n");
    printf("2. Display all parked vehicles\n");
    printf("3. Remove a vehicle\n");
    printf("4. Display available slots\n");
    printf("5. Exit\n");
    printf("=============================================\n");
}

void freeAllVehicles(void) {
    Vehicle *current = head;
    while (current != NULL) {
        Vehicle *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
    occupiedSlots = 0;
}

int main(void) {
    int choice;
    char input[32];

    while (1) {
        displayMenu();
        readLine("Enter your choice: ", input, sizeof(input));
        choice = atoi(input);

        switch (choice) {
            case 1:
                parkVehicle();
                break;
            case 2:
                displayVehicles();
                break;
            case 3:
                removeVehicle();
                break;
            case 4:
                displayAvailability();
                break;
            case 5:
                freeAllVehicles();
                printf("\nThank you for using Parking Slot Management System.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number from 1 to 5.\n");
        }
    }
}
