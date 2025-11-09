#include <stdio.h>
#include <string.h>

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

void displayPatientByID(int id)
{
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");
    int found = 0;

    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                  &p.id, p.firstName, p.lastName, p.fullName,
                  &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
    {
        if (p.id == id) {
            printf("\nPatient Found!\n");
            printf("-----------------------------\n");
            printf("ID              : %d\n", p.id);
            printf("Full Name       : %s\n", p.fullName);
            printf("Age             : %d\n", p.age);
            printf("Gender          : %s\n", p.gender);
            printf("Disease         : %s\n", p.disease);
            printf("Doctor Assigned : %s\n", p.doctorAssigned);
            printf("-----------------------------\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No patient found with ID %d\n", id);

    fclose(fp);
}

void updatePatient()
{
    int updateID, found = 0, choice;
    struct Patient p;

    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n====== UPDATE PATIENT ======\n");
    printf("Enter Patient ID to update: ");
    scanf("%d", &updateID);

    displayPatientByID(updateID);

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                  &p.id, p.firstName, p.lastName, p.fullName,
                  &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
    {
        if (p.id == updateID) {
            found = 1;

            struct Patient original = p;

            printf("\nWhich field do you want to update?\n");
            printf("1. Name\n");
            printf("2. Age\n");
            printf("3. Gender\n");
            printf("4. Disease\n");
            printf("5. Doctor Assigned\n");
            printf("6. Cancel\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            getchar();

            switch (choice) {
            case 1:
                printf("Enter new First Name: ");
                scanf("%s", p.firstName);

                printf("Enter new Last Name: ");
                scanf("%s", p.lastName);

                sprintf(p.fullName, "%s %s", p.firstName, p.lastName);
                break;

            case 2:
                printf("Enter new Age: ");
                scanf("%d", &p.age);
                break;

            case 3:
                printf("Enter new Gender: ");
                scanf("%s", p.gender);
                break;

            case 4:
                printf("Enter new Disease: ");
                scanf(" %[^\n]", p.disease);
                break;

            case 5:
                printf("Enter new Doctor Assigned: ");
                scanf(" %[^\n]", p.doctorAssigned);
                break;

            case 6:
                printf("Update cancelled.\n");
                p = original;
                break;

            default:
                printf("Invalid choice! Keeping old data.\n");
                p = original;
            }

            char confirm;
            printf("\nSave changes? (Y/N): ");
            scanf(" %c", &confirm);

            if (!(confirm == 'Y' || confirm == 'y')) {
                p = original; // revert changes
                printf("Update cancelled.\n");
            } else {
                printf("Record Updated Successfully!\n");
            }
        }

        fprintf(temp, "%d,%s,%s,%s,%d,%s,%s,%s\n",
                p.id, p.firstName, p.lastName, p.fullName,
                p.age, p.gender, p.disease, p.doctorAssigned);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (!found)
        printf("\nNo patient found with ID %d\n", updateID);
}

int main()
{
    updatePatient();
    return 0;
}
