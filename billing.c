#include <stdio.h>
#include <string.h>

void generateBill() {
    char patientName[50], doctorName[50], staffName[50], paymentMethod[10];
    int patientID, days, roomChoice, doctorChoice, testChoice;
    float roomCharge = 0, docFee = 0, testFee = 0;
    float subtotal, tax, discount, total;
    float amountReceived = 0, amountReturned = 0;

    const char *rooms[] = {"General Ward", "Semi-Private Room", "Private Room", "ICU"};
    float roomPrices[] = {2000, 3500, 5000, 10000};

    const char *doctors[] = {"Dr. Smith", "Dr. Johnson", "Dr. Williams", "Dr. Brown"};
    float doctorFees[] = {1500, 2000, 1800, 2200};

    const char *tests[] = {"No Lab Test", "Blood Test", "X-Ray", "MRI", "CT Scan"};
    float testPrices[] = {0, 500, 1000, 5000, 7000};

    printf("Enter Patient ID: ");
    scanf("%d", &patientID);

    printf("Enter Patient Name: ");
    scanf(" %[^\n]", patientName);

    printf("Enter Billing Staff Name: ");
    scanf(" %[^\n]", staffName);

    printf("\nSelect Room Type:\n");
    for (int i = 0; i < 4; i++) {
        printf("  %d. %s (%.2f per day)\n", i + 1, rooms[i], roomPrices[i]);
    }
    printf("Enter choice (1-4): ");
    scanf("%d", &roomChoice);
    if(roomChoice < 1 || roomChoice > 4) {
        printf("Invalid room choice. Exiting...\n");
        return;
    }
    roomCharge = roomPrices[roomChoice - 1];

    printf("Enter Number of days stayed: ");
    scanf("%d", &days);
    if(days < 0) {
        printf("Invalid number of days. Exiting...\n");
        return;
    }

    printf("\nSelect Doctor:\n");
    for (int i = 0; i < 4; i++) {
        printf("  %d. %s (Fee: %.2f)\n", i + 1, doctors[i], doctorFees[i]);
    }
    printf("Enter choice (1-4): ");
    scanf("%d", &doctorChoice);
    if(doctorChoice < 1 || doctorChoice > 4) {
        printf("Invalid doctor choice. Exiting...\n");
        return;
    }
    docFee = doctorFees[doctorChoice - 1];
    strcpy(doctorName, doctors[doctorChoice - 1]);

    printf("\nSelect Lab Test:\n");
    for (int i = 0; i < 5; i++) {
        printf("  %d. %s (Charges: %.2f)\n", i + 1, tests[i], testPrices[i]);
    }
    printf("Enter choice (1-5): ");
    scanf("%d", &testChoice);
    if(testChoice < 1 || testChoice > 5) {
        printf("Invalid test choice. Exiting...\n");
        return;
    }
    testFee = testPrices[testChoice - 1];

    subtotal = (roomCharge * days) + docFee + testFee;

    printf("\nSubtotal (before tax and discount): %.2f\n", subtotal);

    tax = subtotal * 0.05;  
    discount = 500;          
    if (discount > subtotal)
        discount = subtotal;

    total = subtotal + tax - discount;

    printf("\nEnter Payment Method (C for Cash / K for Card): ");
    scanf(" %[^\n]", paymentMethod);

    if (paymentMethod[0] == 'C' || paymentMethod[0] == 'c') {
        printf("Enter Amount Received: ");
        scanf("%f", &amountReceived);

        if (amountReceived < 0) {
            printf("\nError: Negative amount received not allowed!\n");
            return;
        }

        if (amountReceived >= total) {
            amountReturned = amountReceived - total;
        } else {
            printf("\nWarning: Amount received is less than total bill!\n");
            amountReturned = 0;
        }
    }

    printf("\n-----------------------------------------\n");
    printf("             HOSPITAL BILL\n");
    printf("-----------------------------------------\n");
    printf("Patient ID: %d\n", patientID);
    printf("Patient Name: %s\n", patientName);
    printf("Doctor: %s\n", doctorName);
    printf("Billing Staff: %s\n", staffName);
    printf("-----------------------------------------\n");
    printf("Room Charges (%d days - %s):     %.2f\n", days, rooms[roomChoice - 1], roomCharge * days);
    printf("Consultation Fee:                 %.2f\n", docFee);
    printf("Lab Tests (%s):                  %.2f\n", tests[testChoice - 1], testFee);
    printf("-----------------------------------------\n");
    printf("Subtotal:                       %.2f\n", subtotal);
    printf("Tax (5%%):                       %.2f\n", tax);
    printf("Discount:                       %.2f\n", discount);
    printf("-----------------------------------------\n");
    printf("Total Bill:                     %.2f\n", total);
    printf("-----------------------------------------\n");
    printf("Payment Method: %s\n", paymentMethod);

    if (paymentMethod[0] == 'C' || paymentMethod[0] == 'c') {
        printf("Amount Received:                %.2f\n", amountReceived);
        printf("Amount Returned:                %.2f\n", amountReturned);
        printf("Payment Status: Paid in Cash\n");
    } else if (paymentMethod[0] == 'K' || paymentMethod[0] == 'k') {
        printf("Payment Status: Paid by Card\n");
    } else {
        printf("Payment Status: Invalid Method Entered\n");
    }

    printf("-----------------------------------------\n");
    printf("Thank you for choosing our hospital!\n");
    printf("-----------------------------------------\n");
}

int main() {
    generateBill();
    return 0;
}





