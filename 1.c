#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* ===========================
   STRUCT DEFINITIONS
   =========================== */
struct Patient {
    int id;
    char firstName[30];
    char lastName[30];
    char fullName[60];
    int age;
    char gender[10];
    char disease[50];
    char doctorAssigned[50];
};

struct Doctor {
    int id;
    char firstName[30];
    char lastName[30];
    char fullName[60];
    char specialization[50];
    char timings[30];
};

struct Appointment {
    int patientID;
    int doctorID;
    char date[15];
    char time[10];
};

/* ===========================
   FUNCTION DECLARATIONS
   =========================== */
int checkDuplicateID(int);
void addPatient();
void searchPatient();
void updatePatient();
void deletePatient();
void displayPatientByID(int);

/* ===========================
   MAIN
   =========================== */
int main() {
    return 0;
}

/* ===========================
   CHECK DUPLICATE ID
   =========================== */
int checkDuplicateID(int inputID)
{
    FILE *fp = fopen("patients.txt", "r");
    if (!fp) return 0;

    struct Patient p;

    while (fscanf(fp, "%d,%29[^,],%29[^,],%59[^,],%d,%9[^,],%49[^,],%49[^\n]\n",
                  &p.id, p.firstName, p.lastName, p.fullName,
                  &p.age, p.gender, p.disease, p.doctorAssigned) == 8)
    {
        if (p.id == inputID) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* ===========================
   ADD PATIENT
   =========================== */
void addPatient()
{
    int inputID;
    struct Patient p;

    FILE *fp = fopen("patients.txt", "a");
    if (!fp) { printf("Error opening file!\n"); return; }

    do {
        printf("Enter Patient ID: ");
        scanf("%d", &inputID);

        if (checkDuplicateID(inputID))
            printf("ID already exists! Enter a different ID.\n");
        else break;

    } while (1);

    p.id = inputID;

    printf("First Name: ");
    scanf("%s", p.firstName);

    printf("Last Name: ");
    scanf("%s", p.lastName);

    sprintf(p.fullName, "%s %s", p.firstName, p.lastName);

    printf("Age: ");
    scanf("%d", &p.age);

    printf("Gender: ");
    scanf("%s", p.gender);

    getchar();
    printf("Disease: ");
    scanf("%[^\n]", p.disease);

    getchar();
    printf("Doctor Assigned: ");
    scanf("%[^\n]", p.doctorAssigned);

    char confirm;
    printf("Confirm Add (Y/N): ");
    scanf(" %c", &confirm);

    if (confirm == 'Y' || confirm == 'y') {
        fprintf(fp, "%d,%s,%s,%s,%d,%s,%s,%s\n",
                p.id, p.firstName, p.lastName, p.fullName,
                p.age, p.gender, p.disease, p.doctorAssigned);

        printf("Patient added successfully!\n");
    } else {
        printf("Add cancelled.\n");
    }

    fclose(fp);
}

/* ===========================
   DISPLAY PATIENT BY ID
   =========================== */
void displayPatientByID(int id)
{
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");
    if (!fp) { printf("Error opening file!\n"); return; }

    int found = 0;

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                  &p.id, p.firstName, p.lastName, p.fullName,
                  &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
    {
        if (p.id == id)
        {
            printf("\nPatient Found:\n");
            printf("-----------------------------\n");
            printf("ID: %d\n", p.id);
            printf("Name: %s\n", p.fullName);
            printf("Age: %d\n", p.age);
            printf("Gender: %s\n", p.gender);
            printf("Disease: %s\n", p.disease);
            printf("Doctor: %s\n", p.doctorAssigned);
            printf("-----------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found) printf("No patient found with ID %d\n", id);

    fclose(fp);
}

/* ===========================
   SEARCH PATIENT
   =========================== */
void searchPatient()
{
    int choice, found = 0;
    struct Patient p;
    char name[60];
    int inputId;

    FILE *fp = fopen("patients.txt", "r");
    if (!fp) { printf("Error opening file!\n"); return; }

    printf("\n1. Search by ID\n2. Search by Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter ID: ");
        scanf("%d", &inputId);
        displayPatientByID(inputId);
    }
    else if (choice == 2)
    {
        getchar();
        printf("Enter Name: ");
        scanf("%[^\n]", name);

        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                      &p.id, p.firstName, p.lastName, p.fullName,
                      &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
        {
            if (strstr(p.fullName, name) ||
                strstr(p.firstName, name) ||
                strstr(p.lastName, name))
            {
                printf("\nPatient Found!\n");
                printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDoctor: %s\n",
                       p.id, p.fullName, p.age, p.gender, p.disease, p.doctorAssigned);
                found = 1;
            }
        }
        if (!found) printf("No patient found.\n");
    }
    else printf("Invalid choice!\n");

    fclose(fp);
}

/* ===========================
   UPDATE PATIENT
   =========================== */
void updatePatient()
{
    int targetID, found = 0, choice;
    struct Patient p;

    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) { printf("Error opening file!\n"); return; }

    printf("Enter ID to update: ");
    scanf("%d", &targetID);

    displayPatientByID(targetID);

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                  &p.id, p.firstName, p.lastName, p.fullName,
                  &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
    {
        if (p.id == targetID)
        {
            found = 1;
            struct Patient old = p;

            printf("\n1.Name\n2.Age\n3.Gender\n4.Disease\n5.Doctor\n6.Cancel\nChoice: ");
            scanf("%d", &choice);
            getchar();

            switch (choice)
            {
                case 1:
                    printf("New First Name: "); scanf("%s", p.firstName);
                    printf("New Last Name: "); scanf("%s", p.lastName);
                    sprintf(p.fullName, "%s %s", p.firstName, p.lastName);
                    break;

                case 2:
                    printf("New Age: "); scanf("%d", &p.age); break;

                case 3:
                    printf("New Gender: "); scanf("%s", p.gender); break;

                case 4:
                    printf("New Disease: "); scanf(" %[^\n]", p.disease); break;

                case 5:
                    printf("New Doctor: "); scanf(" %[^\n]", p.doctorAssigned); break;

                case 6:
                    p = old;
                    break;

                default:
                    p = old;
            }

            char confirm;
            printf("Save changes? (Y/N): ");
            scanf(" %c", &confirm);

            if (!(confirm == 'Y' || confirm == 'y'))
                p = old;
        }

        fprintf(temp, "%d,%s,%s,%s,%d,%s,%s,%s\n",
                p.id, p.firstName, p.lastName, p.fullName,
                p.age, p.gender, p.disease, p.doctorAssigned);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found) printf("Updated successfully!\n");
    else printf("No patient found with ID %d\n", targetID);
}

/* ===========================
   DELETE PATIENT (with confirmation)
   =========================== */
void deletePatient()
{
    int deleteID, found = 0;
    struct Patient p, toDelete;

    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) { printf("Error opening file!\n"); return; }

    printf("Enter ID to delete: ");
    scanf("%d", &deleteID);

    /* First pass to show data */
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                  &p.id, p.firstName, p.lastName, p.fullName,
                  &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
    {
        if (p.id == deleteID)
        {
            found = 1;
            toDelete = p;

            printf("\nPatient Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDoctor: %s\n",
                   p.id, p.fullName, p.age, p.gender, p.disease, p.doctorAssigned);
            break;
        }
    }

    if (!found)
    {
        printf("No patient found.\n");
        fclose(fp);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    char confirm;
    printf("Are you sure you want to delete this patient? (Y/N): ");
    scanf(" %c", &confirm);

    if (!(confirm == 'Y' || confirm == 'y'))
    {
        printf("Deletion cancelled.\n");
        fclose(fp);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    /* Second pass to rewrite file */
    rewind(fp);

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                  &p.id, p.firstName, p.lastName, p.fullName,
                  &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
    {
        if (p.id == deleteID) continue;  // skip
        fprintf(temp, "%d,%s,%s,%s,%d,%s,%s,%s\n",
                p.id, p.firstName, p.lastName, p.fullName,
                p.age, p.gender, p.disease, p.doctorAssigned);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    printf("Record deleted successfully!\n");
}
