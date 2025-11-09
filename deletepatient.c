#include<stdio.h>
struct Patient
{
    int id;
    char firstName[30];
    char lastName[30];
    char fullName[60];
    int age;
    char gender[10];
    char disease[50];
    char doctorAssigned[50];
};
struct Doctor
{
    int id;
    char firstName[30];
    char lastName[30];
    char fullName[60];
    char specialization[50];
    char timings[30];
};
struct Appointment
{
    int patientID;
    int doctorID;
    char date[15];
    char time[10];
};
void displayPatientByID(int id)
{
    struct Patient p;
    FILE *fp = fopen("patients.txt", "r");
    int found = 0;

    if (!fp)
    {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                  &p.id, p.firstName, p.lastName, p.fullName,
                  &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
    {
        if (p.id == id)
        {
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

void deletePatient()
{
    int deleteID, found = 0;
    struct Patient p, toDelete;

    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n====== DELETE PATIENT ======\n");
    printf("Enter Patient ID to delete: ");
    scanf("%d", &deleteID);

    // First pass: SEARCH + DISPLAY
    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                  &p.id, p.firstName, p.lastName, p.fullName,
                  &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
    {
        if (p.id == deleteID)
        {
            found = 1;
            toDelete = p;

            printf("\nPatient Found!\n");
            printf("-----------------------------\n");
            printf("ID              : %d\n", toDelete.id);
            printf("Full Name       : %s\n", toDelete.fullName);
            printf("Age             : %d\n", toDelete.age);
            printf("Gender          : %s\n", toDelete.gender);
            printf("Disease         : %s\n", toDelete.disease);
            printf("Doctor Assigned : %s\n", toDelete.doctorAssigned);
            printf("-----------------------------\n");
            break;
        }
    }

    if (!found) {
        printf("\nNo patient found with ID %d\n", deleteID);
        fclose(fp);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    // Ask for confirmation
    char confirm;
    printf("\nAre you sure you want to DELETE this patient? (Y/N): ");
    scanf(" %c", &confirm);

    if (!(confirm == 'Y' || confirm == 'y')) {
        printf("\nDeletion Cancelled.\n");
        fclose(fp);
        fclose(temp);
        remove("temp.txt");
        return;
    }

    // SECOND PASS: copy all except deleted one
    rewind(fp);  // go back to start of file

    while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
        &p.id, p.firstName, p.lastName, p.fullName,
        &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
    {
        if (p.id == deleteID)
            continue;  // skip the one being deleted

        fprintf(temp, "%d,%s,%s,%s,%d,%s,%s,%s\n",
                p.id, p.firstName, p.lastName, p.fullName,
                p.age, p.gender, p.disease, p.doctorAssigned);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    printf("\nRecord Deleted Successfully!\n");
}

int main(){
    deletePatient();
    return 0;
}