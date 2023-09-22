#include <iostream>
#include <limits>
#include <Windows.h>

class ErrorHandler {
private:
    bool errorFlag;

public:
    ErrorHandler() : errorFlag(false) {}

    void setErrorFlag(bool flag) {
        errorFlag = flag;
    }

    bool getErrorFlag() const {
        return errorFlag;
    }
};

class WindowsAPIHandler {
private:
    WORD originalConsoleAttributes; // Variable to store original console attributes

public:
    WindowsAPIHandler() {
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
        originalConsoleAttributes = consoleInfo.wAttributes; // Save original console attributes
    }

    void setTextColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void setScreenColor(const char* color) {
        system(color);
    }

    ~WindowsAPIHandler() {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalConsoleAttributes); // Restore original console attributes
    }
};

class InputOutputHandler : public ErrorHandler, public WindowsAPIHandler {
public:
    void clearInputBuffer() {
        std::cin.sync();
        std::cin.clear();
        std::cin.ignore(100, '\n'); // Hard coded maximum value (100)
    }
};

int main() {
    double percentage_THCa = 0;
    double grams_flower = 0;
    double mg_THC = 0;
    double customLoss = 0;

    InputOutputHandler ioHandler;

    // Save original console attributes
    const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD originalConsoleAttributes = consoleInfo.wAttributes;

    while (true) {
        ioHandler.setTextColor(2);
        std::cout << "CannaCalculator\n\n";
        ioHandler.setTextColor(7);

        std::cout << "First, enter the percentage of THCa in your cannabis flower.\n"
            << "Then, enter the total number of grams of flower you will use to infuse oil or butter.\n\n";

        bool enableLoss = false;
        char response{};

        while (true) {
            std::cout << "Would you like me to account for loss of THC during the infusing process? (y/n): ";
            ioHandler.setTextColor(2);
            if (std::cin >> response) {
                if (response == 'y' || response == 'Y') {
                    enableLoss = true;
                    std::cout << "\nThe default loss is 20% THC\n";

                    std::cout << "Would you like to use a custom percentage? (y/n): ";
                    std::cin >> response;
                    if (response == 'y' || response == 'Y') {
                        customLoss = 0;

                        while (true) {
                            std::cout << "Enter Custom Loss as a decimal number. For example, 0.8 is 20%: ";
                            try {
                                if (std::cin >> customLoss) {
                                    if (customLoss >= 0 && customLoss <= 1) {
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
                                ioHandler.clearInputBuffer();
                            }
                        }
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
                ioHandler.clearInputBuffer();
            }
        }

        while (true) {
            ioHandler.setTextColor(7);
            std::cout << "\nWhat percentage of THCa is the cannabis flower you are using? ";
            ioHandler.setTextColor(2);
            try {
                double tempPercentage;
                if (std::cin >> tempPercentage) {
                    if (tempPercentage >= 0 && tempPercentage <= 100) {
                        percentage_THCa = tempPercentage;
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
                ioHandler.clearInputBuffer();
            }
        }

        while (true) {
            std::cout << "How many grams of flower are you using? ";
            try {
                double tempGrams;
                if (std::cin >> tempGrams) {
                    if (tempGrams > 0) {
                        grams_flower = tempGrams;
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
                ioHandler.clearInputBuffer();
            }
        }

        double percentLoss = 0.8;

        if (customLoss > 0) {
            percentLoss = customLoss;
        }

        if (enableLoss) {
            mg_THC = (percentage_THCa * 10) * percentLoss * grams_flower;
        }
        else {
            mg_THC = (percentage_THCa * 10) * grams_flower;
        }

        ioHandler.setTextColor(7);
        std::cout << "\n" << percentage_THCa << "% THCa converts to "
            << static_cast<int>(mg_THC) << "mg THC per " << grams_flower << "g of flower.\n\n";

        for (int i = 2; i <= 27; i += 2) {
            std::cout << static_cast<int>(mg_THC / i) << "mg per " << i << " servings\n";
        }

        std::cout << "\n\n";

        while (true) {
            std::cout << "Do you want to reset or exit the program? (reset/exit): ";
            std::string response;
            std::cin >> response;

            if (response == "reset") {
                percentage_THCa = 0;
                grams_flower = 0;
                mg_THC = 0;
                customLoss = 0;
                break;
            }
            else if (response == "exit") {
                SetConsoleTextAttribute(hConsole, originalConsoleAttributes); // Restore original console attributes before exiting
                return 0;
            }
            else {
                std::cout << "Invalid input. Please enter 'reset' or 'exit'.\n";
            }
        }
    }

    return 0;
}