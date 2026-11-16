/* Hospital Patient Management System
 * Menu-driven program using a linked list and file handling.
 * Features: admit, display, search, update, discharge (with bill), auto save/load.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "patients.dat"
#define DAILY_CHARGE 1500.0   /* room charge per day (change as you like) */

/* One node of the linked list = one admitted patient */
struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    char doctor[50];
    int days;                 /* number of days admitted so far */
    struct Patient *next;
};

struct Patient *head = NULL;  /* start of the list */

/* Find a patient by ID; returns NULL if not found */
struct Patient *find(int id) {
    struct Patient *cur = head;
    while (cur != NULL) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

/* Admit a new patient (added at the end of the list) */
void admitPatient(void) {
    struct Patient *p = (struct Patient *)malloc(sizeof(struct Patient));
    if (p == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Patient ID: ");
    scanf("%d", &p->id);
    if (find(p->id) != NULL) {
        printf("A patient with this ID already exists.\n");
        free(p);
        return;
    }
    printf("Name: ");
    scanf(" %49[^\n]", p->name);
    printf("Age: ");
    scanf("%d", &p->age);
    printf("Disease: ");
    scanf(" %49[^\n]", p->disease);
    printf("Doctor assigned: ");
    scanf(" %49[^\n]", p->doctor);
    p->days = 1;
    p->next = NULL;

    if (head == NULL) {
        head = p;
    } else {
        struct Patient *cur = head;
        while (cur->next != NULL) cur = cur->next;
        cur->next = p;
    }
    printf("Patient admitted.\n");
}

void displayAll(void) {
    if (head == NULL) {
        printf("No patients admitted.\n");
        return;
    }
    printf("\n%-6s %-18s %-5s %-18s %-18s %-5s\n",
           "ID", "Name", "Age", "Disease", "Doctor", "Days");
    int count = 0;
    struct Patient *cur = head;
    while (cur != NULL) {
        printf("%-6d %-18s %-5d %-18s %-18s %-5d\n",
               cur->id, cur->name, cur->age, cur->disease, cur->doctor, cur->days);
        count++;
        cur = cur->next;
    }
    printf("Total patients: %d\n", count);
}

void searchPatient(void) {
    int id;
    printf("Enter patient ID: ");
    scanf("%d", &id);
    struct Patient *p = find(id);
    if (p == NULL) {
        printf("Patient not found.\n");
        return;
    }
    printf("ID: %d\nName: %s\nAge: %d\nDisease: %s\nDoctor: %s\nDays admitted: %d\n",
           p->id, p->name, p->age, p->disease, p->doctor, p->days);
}

/* Change the disease, doctor and number of days of a patient */
void updatePatient(void) {
    int id;
    printf("Enter patient ID to update: ");
    scanf("%d", &id);
    struct Patient *p = find(id);
    if (p == NULL) {
        printf("Patient not found.\n");
        return;
    }
    printf("New disease: ");
    scanf(" %49[^\n]", p->disease);
    printf("New doctor: ");
    scanf(" %49[^\n]", p->doctor);
    printf("Days admitted so far: ");
    scanf("%d", &p->days);
    printf("Record updated.\n");
}

/* Remove the patient from the list and print the bill */
void dischargePatient(void) {
    int id;
    printf("Enter patient ID to discharge: ");
    scanf("%d", &id);

    struct Patient *cur = head, *prev = NULL;
    while (cur != NULL && cur->id != id) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) {
        printf("Patient not found.\n");
        return;
    }

    printf("\n--- Discharge Bill ---\n");
    printf("Patient: %s (ID %d)\n", cur->name, cur->id);
    printf("Days admitted: %d\n", cur->days);
    printf("Total bill: Rs. %.2f\n", cur->days * DAILY_CHARGE);

    if (prev == NULL) head = cur->next;   /* discharging the first patient */
    else prev->next = cur->next;
    free(cur);
    printf("Patient discharged.\n");
}

/* Save all patients to a binary file */
void saveToFile(void) {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        printf("Could not save file.\n");
        return;
    }
    struct Patient *cur = head;
    while (cur != NULL) {
        fwrite(cur, sizeof(struct Patient), 1, fp);
        cur = cur->next;
    }
    fclose(fp);
}

/* Load patients from the file when the program starts */
void loadFromFile(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) return;   /* first run: no file yet */

    struct Patient temp;
    struct Patient *tail = NULL;
    while (fread(&temp, sizeof(struct Patient), 1, fp) == 1) {
        struct Patient *p = (struct Patient *)malloc(sizeof(struct Patient));
        *p = temp;
        p->next = NULL;
        if (head == NULL) head = p;
        else tail->next = p;
        tail = p;
    }
    fclose(fp);
}

void freeList(void) {
    while (head != NULL) {
        struct Patient *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    int choice;
    loadFromFile();

    do {
        printf("\n--- Hospital Patient Management ---\n");
        printf("1. Admit patient\n2. Display all patients\n3. Search patient\n");
        printf("4. Update patient\n5. Discharge patient\n6. Save and exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {   /* handle non-number input */
            printf("Invalid input.\n");
            while (getchar() != '\n');
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1: admitPatient(); break;
            case 2: displayAll(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: dischargePatient(); break;
            case 6: saveToFile(); printf("Saved. Bye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 6);

    freeList();
    return 0;
}
