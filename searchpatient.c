#include<stdio.h>
#include<ctype.h>
#include<string.h>

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


void searchPatient()
{
    int choice, found = 0, inputId;
    struct Patient p;
    char name[60];
    printf("\n====== SEARCH PATIENT ======\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    FILE *fp = fopen("patients.txt", "r");
    if (!fp)
    {
        printf("Error opening file!\n");
        return;
    }
    if (choice == 1)
    {
        printf("Enter the patient ID to search: ");
        scanf("%d", &inputId);
        getchar();
        displayPatientByID(inputId);
    }
    else if (choice == 2)
    {
        getchar();
        printf("Enter the patient's name to search: ");
        scanf("%[^\n]%*c", name);
        while (fscanf(fp, "%d,%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^\n]\n",
                      &p.id, p.firstName, p.lastName, p.fullName,
                      &p.age, p.gender, p.disease, p.doctorAssigned) != EOF)
        {
            if (strstr(p.fullName, name) != NULL ||
                strstr(p.firstName, name) != NULL ||
                strstr(p.lastName, name) != NULL)
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
            }
        }
        if (!found)
            printf("No patient found with this name %s\n", name);
    }
    else
        printf("Invalid choice! Please enter 1 or 2.\n");
    fclose(fp);
}

int main(){
    searchPatient();
    return 0;
}