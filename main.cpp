/*
 * MIT LICENSE @ WAN ISA
 */

#include <iostream>

using namespace std;

struct Package {
    string package;
    string serviceType;
    string duration;
    float charge;
};

const Package packages[6] {
    {"Package A (Standard Wash) - Clothes, Towels, Bed Sheets", "Self-Service", "2 Days", 5.00},
    {"Package A (Standard Wash) - Clothes, Towels, Bed Sheets", "Door-to-Door", "3 Days", 7.00},
    {"Package A (Standard Wash) - Clothes, Towels, Bed Sheets", "Express Door-to-Door", "Same day", 10.00},
    {"Package C (Dry Cleaning) - Suits, Dresses, Delicate Fabrics", "Self-Service", "2 Days", 10.00},
    {"Package C (Dry Cleaning) - Suits, Dresses, Delicate Fabrics", "Door-to-Door", "3 Days", 12.00},
    {"Package C (Dry Cleaning) - Suits, Dresses, Delicate Fabrics", "Express Door-to-Door", "Same Day", 15.00},
};

int displayInputOptions() {
    int selectedOption;

    for (int i = 0; i < 6; i++) {
        cout << "-------------------- " << i + 1 << " --------------------" << endl;
        cout << packages[i].package << endl;
        cout << "Service Type: " << packages[i].serviceType << endl;
        cout << "Duration: " << packages[i].duration << endl;
        cout << format("Charge: RM {}/kg", packages[i].charge) << endl;
    }

    cout << "-------------------------------------------" << endl;
    cout << "Please select an option (1-6): ";
    cin >> selectedOption;

    return selectedOption;
}

void calculateAndDisplay(int chosenPackage, float laundryWeight, float deliveryDistance) {

    const float laundryCharge = packages[chosenPackage - 1].charge;

    const float laundryCost = laundryCharge * laundryWeight;
    const float deliveryFee = deliveryDistance < 5 ? 0 : (deliveryDistance < 8 ? deliveryDistance * 1.5 : deliveryDistance * 1.8);
    const float laundryServiceCharges = laundryCost * 0.06;
    const float deliveryServiceCharges = deliveryFee * 0.08;
    const float totalCost = laundryCost + deliveryFee + laundryServiceCharges + deliveryServiceCharges;

    cout << "========== Charges Breakdown ===========" << endl;

    cout << format("Laundry Cost ({} kg x RM {}): RM {}", laundryWeight, laundryCharge, laundryCost) << endl;
    cout << format("Service Charges, 6%: RM {}", laundryServiceCharges) << endl;
    deliveryDistance != 0 && cout << format("Delivery Fee: RM {}", deliveryFee) << endl;
    deliveryDistance != 0 && cout << format("Delivery Service Charges, 8%: RM {}", deliveryServiceCharges) << endl;

    cout << "====================" << endl;
    cout << format("Total Cost: RM {}", totalCost) << endl;
    cout << "====================" << endl;
}

int main() {
    float laundryWeight;
    float deliveryDistance;

    const int chosen = displayInputOptions();

    cout << "Enter weight of your laundry (KG): ";
    cin >> laundryWeight;

    if (chosen != 1 && chosen != 4) {
        cout << "Enter delivery distance (KM): ";
        cin >> deliveryDistance;
    }

    calculateAndDisplay(chosen, laundryWeight, deliveryDistance);
}