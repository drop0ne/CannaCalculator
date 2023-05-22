#include <iostream>
#include <limits>

class CannaCalculator {
private:
    double percentage_THCa;
    double grams_flower;
    double mg_THC;
    double customLoss;

public:
    CannaCalculator() : percentage_THCa(0), grams_flower(0), mg_THC(0), customLoss(0) {}

    void run() {
        std::cout << "CannaCalculator\n\n";

        std::cout << "First, enter the percentage of THCa in your cannabis flower.\n"
            << "Then, enter the total number of grams of flower you will use to infuse oil or butter.\n\n";

        bool enableLoss = getPercentage();
        getGrams();

        mg_THC = calculate_mg_TCH(percentage_THCa, grams_flower, enableLoss, customLoss); // Calculate total THC in milligrams

        std::cout << "\n" << percentage_THCa << "% THCa converts to "
            << static_cast<int>(mg_THC) << "mg THC per " << grams_flower << "g of flower.\n\n";

        for (int i = MIN_SERVINGS; i <= MAX_SERVINGS; i += 2) {
            std::cout << static_cast<int>(calculate_mg_per_serving(i, mg_THC)) << "mg per " << i << " servings\n";
        }

        std::cout << "\n\n";
        system("pause");
    }

private:
    static constexpr int MAX_SERVINGS = 27;
    static constexpr int MIN_SERVINGS = 2;

    bool getPercentage() {
        char response{};
        bool enableLoss = false;

        while (true) {
            std::cout << "Would you like me to account for loss of THC during the infusing process? (y/n): ";
            if (std::cin >> response) {
                if (response == 'y' || response == 'Y') {
                    enableLoss = true;
                    std::cout << "\nThe default loss is 20% THC\n";

                    std::cout << "Would you like to use a custom percentage? (y/n): ";
                    std::cin >> response;
                    if (response == 'y' || response == 'Y') {
                        customLoss = getCustomLoss();
                    }
                    break;
                }
                else if (response == 'n' || response == 'N') {
                    break;
                }
                else {
                    std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
                }
            }
            else {
                std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        while (true) {
            std::cout << "\nWhat percentage of THCa is the cannabis flower you are using? ";
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

        return enableLoss;
    }

    void getGrams() {
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
    }

    double getCustomLoss() {
        double loss;
        while (true) {
            std::cout << "Enter Custom Loss as a decimal number. For example, 0.8 is 20%: ";
            if (std::cin >> loss) {
                if (loss >= 0 && loss <= 1) {
                    break;
                }
                else {
                    std::cout << "Invalid input. Please enter a decimal number between 0 and 1.\n";
                }
            }
            else {
                std::cout << "Invalid input. Please enter a numeric value.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        return loss;
    }

    double calculate_mg_TCH(double percentage_THCa, double grams_flower, bool enableLoss, double enableCustomLoss) {
        double percentLoss = 0.8;  //This is 20%

        if (enableCustomLoss > 0) {
            percentLoss = enableCustomLoss;
        }

        if (enableLoss) {
            return (percentage_THCa * 10) * percentLoss * grams_flower; // Apply loss factor to the calculation
        }

        return (percentage_THCa * 10) * grams_flower; // Calculate THC without loss
    }

    double calculate_mg_per_serving(double servings, double mg_THC) {
        return mg_THC / servings; // Calculate THC per serving
    }
};

int main() {
    CannaCalculator calculator;
    calculator.run();

    return 0;
}
