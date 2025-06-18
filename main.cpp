#include <iostream>
#include <iomanip> // For setprecision
#include <string>
using namespace std;

// Structure to hold each laundry package's details
struct Package {
    string packageType;
    string serviceType;
    string duration;
    double charge;
};

// List of available packages
const Package packages[6] {
    {"Package A (Standard Wash) - Clothes, Towels, Bed Sheets", "Self-Service", "2 Days", 5.00},
    {"Package A (Standard Wash) - Clothes, Towels, Bed Sheets", "Door-to-Door", "3 Days", 7.00},
    {"Package A (Standard Wash) - Clothes, Towels, Bed Sheets", "Express Door-to-Door", "Same Day", 10.00},
    {"Package C (Dry Cleaning) - Suits, Dresses, Delicate Fabrics", "Self-Service", "2 Days", 10.00},
    {"Package C (Dry Cleaning) - Suits, Dresses, Delicate Fabrics", "Door-to-Door", "3 Days", 12.00},
    {"Package C (Dry Cleaning) - Suits, Dresses, Delicate Fabrics", "Express Door-to-Door", "Same Day", 15.00},
};

// Function to display package options and confirm user selection afterwards
int displayInputOptions() {
    int selectedOption;
    string confirmation;

    do {
        // Display all 6 package options
        for (int i = 0; i < 6; i++) {
            cout << "-------------------- " << i + 1 << " --------------------" << endl;
            cout << packages[i].packageType << endl;
            cout << "Service Type: " << packages[i].serviceType << endl;
            cout << "Duration: " << packages[i].duration << endl;
            cout << "Charge: RM " << fixed << setprecision(2) << packages[i].charge << "/kg" << endl;
        }

        cout << "-------------------------------------------" << endl;
        cout << "> Please select an option (1-6 or 0 to exit): ";
        cin >> selectedOption;
        //Exit if user enters 0
        if (selectedOption == 0) {
            exit(0);
        }

        // Check for invalid input
        while (selectedOption < 1 || selectedOption > 6) {
            cout << "Invalid selection. Please select an option (1-6 or 0 to exit): ";
            cin >> selectedOption;
        }

        const int i = selectedOption - 1;
        cout << "------------ Chosen Package (" << selectedOption << ") -----------" << endl;
        cout << packages[i].packageType << endl;
        cout << "Service Type: " << packages[i].serviceType << endl;
        cout << "Duration: " << packages[i].duration << endl;
        cout << "Charge: RM " << fixed << setprecision(2) << packages[i].charge << "/kg" << endl;
        cout << "-------------------------------------------" << endl;

        // Confirm package selection
        do {
            cout << "> Confirm? (y/n): ";
            cin >> confirmation;
             
            if (confirmation != "y" && confirmation != "n"){
                cout<<"Invalid data entered, please enter 'y' for yes and 'n' for no."<<endl;
            }
        } while (confirmation != "y" && confirmation != "n");

    } while (confirmation == "n");

    return selectedOption;
}

// Function to calculate and display cost of laundry, delivery and service fee altogether
void calculateAndDisplay(const int chosenPackage, const double laundryWeight, const double deliveryDistance) {
    const double laundryCharge = packages[chosenPackage - 1].charge;
    const double laundryCost = laundryCharge * laundryWeight;

    // Calculate delivery fee based on distance 
    double deliveryFee = 0.0;
    if (deliveryDistance > 3) {
        if (deliveryDistance <= 8) {
            deliveryFee = (deliveryDistance - 3) * 1.5; // RM 1.50 per km after 3 km
        } else {
            deliveryFee = (5 * 1.5) + ((deliveryDistance - 8) * 1.8); // Next 5 km at RM 1.50 + extra at RM 1.80
        }
    }

    // Calculate service charges: 6% for laundry, 8% for delivery
    const double laundryServiceCharges = laundryCost * 0.06;
    const double deliveryServiceCharges = deliveryFee * 0.08;
    const double totalCost = laundryCost + deliveryFee + laundryServiceCharges + deliveryServiceCharges;

    // Display breakdown
    cout << "\n========== Charges Breakdown ===========" << endl;
    cout << "Laundry Cost (" << laundryWeight << " kg x RM " << laundryCharge << "): RM " << fixed << setprecision(2) << laundryCost << endl;
    cout << "Service Charges, 6%: RM " << fixed << setprecision(2) << laundryServiceCharges << endl;

    if (deliveryDistance > 0) {
        cout << "Delivery Fee: RM " << fixed << setprecision(2) << deliveryFee << endl;
        cout << "Delivery Service Charges, 8%: RM " << fixed << setprecision(2) << deliveryServiceCharges << endl;
    }

    cout << "====================" << endl;
    cout << "Total Cost: RM " << fixed << setprecision(2) << totalCost << endl;
    cout << "====================" << endl;
}

int main() {
    double laundryWeight;
    double deliveryDistance = 0.0;

    // Display package menu and get user choice
    const int chosen = displayInputOptions();

    // Ask for laundry weight and validate weight entered
    cout << "> Enter weight of your laundry (KG): ";
    cin >> laundryWeight;
    while (laundryWeight <= 0) {
        cout << "Invalid laundry weight, try again!" << endl;
        cout << "> Enter weight of your laundry (KG): ";
        cin >> laundryWeight;
    }

    // Ask for delivery distance only if it's not a self-service package
    if (chosen != 1 && chosen != 4) {
        cout << "> Enter delivery distance (KM): ";
        cin >> deliveryDistance;
        while (deliveryDistance < 0) {
            cout << "Invalid delivery distance, try again!" << endl;
            cout << "> Enter delivery distance (KM): ";
            cin >> deliveryDistance;
        }
    }

    // Calculate and display the total cost
    calculateAndDisplay(chosen, laundryWeight, deliveryDistance);

    return 0;
}
