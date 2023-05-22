#include <iostream>
#include <limits>

const int MAX_SERVINGS = 27;
const int MIN_SERVINGS = 2;

double calculate_mg_TCH(double percentage_THCa, double grams_flower);
double calculate_mg_per_serving(double servings, double mg_THC);

int main() {
    double percentage_THCa = 0;
    double grams_flower = 0;
    double mg_THC = 0;
    double servings = 0;

    std::cout << "CannaCalculator\n\n";

    std::cout << "First, enter the percentage of THCa in your cannabis flower.\n"
        << "Then, enter the total number of grams of flower you will use to infuse oil or butter.\n\n";

    while (true) {
        std::cout << "What percentage of THCa is the cannabis flower you are using? ";
        if (std::cin >> percentage_THCa) {
            if (percentage_THCa >= 0 && percentage_THCa <= 100) {
                break;
            }
            else {
                std::cout << "Invalid input. Please enter a percentage between 0 and 100.\n";
            }
        }
        else {
            std::cout << "Invalid input. Please enter a numeric value.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    while (true) {
        std::cout << "How many grams of flower are you using? ";
        if (std::cin >> grams_flower) {
            if (grams_flower > 0) {
                break;
            }
            else {
                std::cout << "Invalid input. Please enter a positive value.\n";
            }
        }
        else {
            std::cout << "Invalid input. Please enter a numeric value.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    mg_THC = calculate_mg_TCH(percentage_THCa, grams_flower);

    std::cout << "\n" << percentage_THCa << "% THCa converts to "
        << static_cast<int>(mg_THC) << "mg THC per " << grams_flower << "g of flower.\n\n";

    for (int i = MIN_SERVINGS; i <= MAX_SERVINGS; i += 2) {
        std::cout << static_cast<int>(calculate_mg_per_serving(i, mg_THC)) << "mg per " << i << " servings\n";
    }

    std::cout << "\n\n";
    system("pause");
}

double calculate_mg_TCH(double percentage_THCa, double grams_flower) {
    return (percentage_THCa * 10) * 0.8 * grams_flower;
}

double calculate_mg_per_serving(double servings, double mg_THC) {
    return mg_THC / servings;
}
