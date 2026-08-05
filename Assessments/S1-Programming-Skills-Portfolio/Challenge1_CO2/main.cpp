#include <iostream>
#include <string>
#include <iomanip>

// User input function for distance in miles
double getDistance() {
    double distance = 0.0;
    while (true) {
        std::cout << "Enter the journey distance (in miles): ";
        if (std::cin >> distance && distance > 0) {
            return distance;
        }
        std::cout << "Invalid input. Please enter a positive number.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

// User input function for fuel type (1 = Petrol, 2 = Diesel)
int getFuelType() {
    int choice = 0;
    while (true) {
        std::cout << "Select fuel type:\n";
        std::cout << "1. Petrol\n";
        std::cout << "2. Diesel\n";
        std::cout << "Enter choice (1 or 2): ";
        if (std::cin >> choice && (choice == 1 || choice == 2)) {
            return choice;
        }
        std::cout << "Invalid selection. Please enter 1 or 2.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

// Function to calculate total CO2 emission in kg
double calculateCO2(double distanceMiles, int fuelType) {
    const double CONSUMPTION_PER_100_MILES = 9.66;
    const double PETROL_CO2_PER_LITRE = 2.31;
    const double DIESEL_CO2_PER_LITRE = 2.68;

    double totalLitres = (distanceMiles / 100.0) * CONSUMPTION_PER_100_MILES;
    
    if (fuelType == 1) {
        return totalLitres * PETROL_CO2_PER_LITRE;
    } else {
        return totalLitres * DIESEL_CO2_PER_LITRE;
    }
}

int main() {
    std::cout << "=== Journey CO2 Emission Calculator ===\n\n";

    double distance = getDistance();
    int fuelType = getFuelType();
    
    double totalCO2 = calculateCO2(distance, fuelType);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n----------------------------------------\n";
    std::cout << "Total CO2 Emissions: " << totalCO2 << " kg\n";
    std::cout << "----------------------------------------\n";

    return 0;
}