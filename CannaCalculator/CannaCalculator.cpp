#include <iostream>

const int MAX_SERVINGS = 27;
const int MIN_SERVINGS = 2;

// Calculates the total amount of THC in milligrams
double calculate_mg_TCH(double percentage_THCa, double grams_flower);

// Calculates the amount of THC per serving in milligrams
double calculate_mg_per_serving(double servings, double mg_THC);

int main() {
    double percentage_THCa = 0;
    double grams_flower = 0;
    double mg_THC = 0;
    double servings = 0;

    std::cout << "CannaCalculator\n\n\n";

    // Prompt the user for the percentage of THCa in their cannabis flower and the amount of flower they will use
    std::cout << "First, enter the percentage of THCa in your cannabis flower.\n"
        << "Then, enter the total number of grams of flower you will use to infuse oil or butter.\n\n\n\n";

    std::cout << "What percentage of THCa is the cannabis flower you are using? ";
    std::cin >> percentage_THCa;

    std::cout << "\nHow many grams of flower are you using?  ";
    std::cin >> grams_flower;

    // Calculate the total amount of THC in milligrams
    mg_THC = calculate_mg_TCH(percentage_THCa, grams_flower);

    // Display the amount of THC per gram of flower used
    std::cout << "\n" << percentage_THCa << "% THCa converts to "
        << static_cast<int>(mg_THC) << "mg THC per " << grams_flower << "g of flower.\n\n";

    // Calculate and display the amount of THC per serving for a range of serving sizes
    for (int i = MIN_SERVINGS; i <= MAX_SERVINGS; i += 2) {
        std::cout << static_cast<int>(calculate_mg_per_serving(i, mg_THC)) << "mg per " << i << " servings\n";
    }

    std::cout << "\n\n";
    system("pause");
}

// Calculates the total amount of THC in milligrams
double calculate_mg_TCH(double percentage_THCa, double grams_flower) {
    return (percentage_THCa * 10) * 0.8 * grams_flower;
}

// Calculates the amount of THC per serving in milligrams
double calculate_mg_per_serving(double servings, double mg_THC) {
    return mg_THC / servings;
}