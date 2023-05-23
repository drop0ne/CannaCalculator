#include <iostream>
#include <limits>
#include <Windows.h>

class CannaCalculator {
private:
    double percentage_THCa;
    double grams_flower;
    double mg_THC;
    double customLoss;

    HANDLE hConsole; // Handle to the console output device

    enum Color {
        DEFAULT = 7,
        BLACK = 0,
        DARK_GREEN = 2,
        GREEN = 2,
        BRIGHT_GREEN = 10,
        BLUE = 1,
        BRIGHT_RED = 12,
        RED = 4,
        LIGHT_BLUE = 3,
        ICE_BLUE = 9,
        TEAL_BLUE = 11,
        WHITE = 7,
        BRIGHT_WHITE = 15,
        GRAY = 8,
        PURPLE = 5,
        YELLOW = 6,
        HIGHLIGHT_WITH_BLUE_BLUE = 19,
        HIGHLIGHT_WITH_BLUE_BLUE2 = 25,
        HIGHLIGHT_BLUE_WHITE = 23,
        CHECK = 27
    };

public:
    CannaCalculator() : percentage_THCa(0), grams_flower(0), mg_THC(0), customLoss(0) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void run() {
        setTextColor(GREEN);
        std::cout << "CannaCalculator\n\n";
        setTextColor(WHITE);

        std::cout << "First, enter the percentage of THCa in your cannabis flower.\n"
            << "Then, enter the total number of grams of flower you will use to infuse oil or butter.\n\n";

        bool enableLoss = getPercentage();
        getGrams();

        mg_THC = calculate_mg_THC(percentage_THCa, grams_flower, enableLoss, customLoss); // Calculate total THC in milligrams

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
            //setScreenColor("color 8");  //Set old text to gray
            setTextColor(GREEN);
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
                clearInputBuffer();
            }
        }

        while (true) {
            setScreenColor("color 8");  //Set old text to gray
            setTextColor(WHITE);
            std::cout << "\nWhat percentage of THCa is the cannabis flower you are using? ";
            setTextColor(GREEN);
            try {
                if (std::cin >> percentage_THCa) {
                    if (percentage_THCa >= 0 && percentage_THCa <= 100) {
                        break;
                    }
                    else {
                        throw std::out_of_range("Invalid input. Please enter a percentage between 0 and 100.");
                    }
                }
                else {
                    throw std::runtime_error("Invalid input. Please enter a numeric value.");
                }
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
                clearInputBuffer();
            }
        }

        return enableLoss;
    }

    void getGrams() {
        while (true) {
            std::cout << "How many grams of flower are you using? ";
            try {
                if (std::cin >> grams_flower) {
                    if (grams_flower > 0) {
                        break;
                    }
                    else {
                        throw std::out_of_range("Invalid input. Please enter a positive value.");
                    }
                }
                else {
                    throw std::runtime_error("Invalid input. Please enter a numeric value.");
                }
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
                clearInputBuffer();
            }
        }
    }

    double getCustomLoss() {
        double loss;
        while (true) {
            std::cout << "Enter Custom Loss as a decimal number. For example, 0.8 is 20%: ";
            try {
                if (std::cin >> loss) {
                    if (loss >= 0 && loss <= 1) {
                        break;
                    }
                    else {
                        throw std::out_of_range("Invalid input. Please enter a decimal number between 0 and 1.");
                    }
                }
                else {
                    throw std::runtime_error("Invalid input. Please enter a numeric value.");
                }
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
                clearInputBuffer();
            }
        }
        return loss;
    }

    double calculate_mg_THC(double percentage_THCa, double grams_flower, bool enableLoss, double enableCustomLoss) {
        double percentLoss = 0.8; // Default loss is 20%

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

    void setTextColor(int color) {
        SetConsoleTextAttribute(hConsole, color);
    }

    void setScreenColor(const char* color) {
        system(color);
    }

    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(9223372036854775807, '\n');  //Hard limit of buffer for x64
    }
};

int main() {
    CannaCalculator calculator;
    calculator.run();

    return 0;
}
