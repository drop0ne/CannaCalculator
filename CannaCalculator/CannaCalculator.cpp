#include <iostream>
#include <limits>
#include <Windows.h>
#include <string>

enum class ConsoleColor : int {
    // Foreground (Text) Colors
    Black = 0,
    Blue = 1,
    Green = 2,
    Aqua = 3,
    Red = 4,
    Purple = 5,
    Yellow = 6,
    White = 7,
    Gray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightAqua = 11,
    LightRed = 12,
    LightPurple = 13,
    LightYellow = 14,
    BrightWhite = 15,

    // Background Colors
    BgBlack = 0,
    BgBlue = 1,
    BgGreen = 2,
    BgAqua = 3,
    BgRed = 4,
    BgPurple = 5,
    BgYellow = 6,
    BgWhite = 7
};

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

    void clearInputBuffer() {
        std::cin.sync();
        std::cin.clear();
        while (std::cin.get() != '\n') {
            // Keep reading and discarding characters until a newline is encountered
        }
    }
};

class WindowsAPIHandler {
private:
    WORD originalConsoleAttributes;
    HANDLE hConsole;

public:
    WindowsAPIHandler() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole == INVALID_HANDLE_VALUE) {
            setErrorMessageColor();
            std::cerr << "Error: Unable to get console handle." << std::endl;
            exit(1);
        }

        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        if (!GetConsoleScreenBufferInfo(hConsole, &consoleInfo)) {
            setErrorMessageColor();
            std::cerr << "Error: Unable to get console screen buffer info." << std::endl;
            exit(1);
        }

        originalConsoleAttributes = consoleInfo.wAttributes;
    }

    void setTextColor(int textColor, int backgroundColor) { // Bitwise left shifts the background color bits to the exspected location in the 8 bit binary that is sent to the OS: Bits 0-3: Background color - Bits 4 - 7: Foreground(text) color
        if (!SetConsoleTextAttribute(hConsole, textColor | backgroundColor << 4)) {
            std::cerr << "Error: Unable to set console text attribute." << std::endl;
            exit(1);
        }
    }

    void grayOutAllText() {
        system("color 8");
    }

    void setScreenColor(const char* color) {
        system(color);
    }

    void setErrorMessageColor() {
        setTextColor(12, 0); // Set error messages to red
    }

    void setUserInputColor() {
        setTextColor(10, 0); // Set user input to green
    }

    void setSystemOutputColor() {
        setTextColor(7, 0); // Set system output to default color
    }

    void cls() {
        system("cls");
    }

    ~WindowsAPIHandler() {
        SetConsoleTextAttribute(hConsole, originalConsoleAttributes);
    }
};

class InputOutputHandler : public ErrorHandler, public WindowsAPIHandler {
public:
    double getDoubleInput(const std::string& prompt, double minValue, double maxValue) {
        double value;
        while (true) {
            setSystemOutputColor();
            std::cout << prompt;
            try {
                setUserInputColor();
                if (std::cin >> value) {
                    if (value >= minValue && value <= maxValue) {
                        return value;
                    }
                    else {
                        setErrorMessageColor();
                        throw std::out_of_range("Invalid input. Please enter a value between " + std::to_string(minValue) + " and " + std::to_string(maxValue) + ".");
                    }
                }
                else {
                    setErrorMessageColor();
                    throw std::runtime_error("Invalid input. Please enter a numeric value.");
                }
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
                clearInputBuffer();
            }
        }
    }
};


/////////////////////////////  MAIN

int main() {
    double percentage_THCa = 0;
    double grams_flower = 0;
    double mg_THC = 0;
    double customLoss = 0;

    InputOutputHandler ioHandler;

    const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD originalConsoleAttributes = consoleInfo.wAttributes;

    while (true) {
        ioHandler.cls();
        ioHandler.setTextColor(10, 0);
        std::cout << "CannaCalculator\n\n";
        ioHandler.setSystemOutputColor();
        std::cout << "First, enter the percentage of THCa in your cannabis flower.\n"
            << "Then, enter the total number of grams of flower you will use to infuse oil or butter.\n\n";

        bool enableLoss = false;
        char response{};
        
        // START User Input
        while (true) {
            ioHandler.setSystemOutputColor(); // Set system color
            std::cout << "Would you like me to account for loss of THC during the infusing process? (y/n): ";

            ioHandler.setUserInputColor(); // Set user input color
            if (std::cin >> response) {
                ioHandler.grayOutAllText();
                if (response == 'y' || response == 'Y') {
                    enableLoss = true;
                    ioHandler.setSystemOutputColor(); // Set system output color
                    std::cout << "\nThe default loss is 20% THC\n";

                    ioHandler.setSystemOutputColor(); // Set user input color
                    std::cout << "Would you like to use a custom percentage? (y/n): ";
                    ioHandler.setUserInputColor();
                    std::cin >> response;
                    if (response == 'y' || response == 'Y') {
                        customLoss = 0;

                        while (true) {
                            ioHandler.setSystemOutputColor();
                            std::cout << "Enter Custom Loss as a decimal number. For example, 0.8 is 20%: ";
                            try {
                                ioHandler.setUserInputColor();
                                if (std::cin >> customLoss) {
                                    if (customLoss >= 0 && customLoss <= 1) {
                                        break;
                                    }
                                    else {
                                        ioHandler.setErrorMessageColor();
                                        throw std::out_of_range("Invalid input. Please enter a decimal number between 0 and 1.");
                                    }
                                }
                                else {
                                    ioHandler.setErrorMessageColor();
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
                    ioHandler.setErrorMessageColor();
                    std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
                }
            }
            else {
                ioHandler.setErrorMessageColor();
                std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
                ioHandler.clearInputBuffer();
            }
        }

        while (true) {
            ioHandler.setSystemOutputColor();
            std::cout << "\nWhat percentage of THCa is the cannabis flower you are using? ";
            ioHandler.setTextColor(2, 0);
            try {
                double tempPercentage;
                ioHandler.setUserInputColor();
                if (std::cin >> tempPercentage) {
                    if (tempPercentage >= 0 && tempPercentage <= 100) {
                        percentage_THCa = tempPercentage;
                        break;
                    }
                    else {
                        ioHandler.setErrorMessageColor();
                        throw std::out_of_range("Invalid input. Please enter a percentage between 0 and 100.");
                    }
                }
                else {
                    ioHandler.setErrorMessageColor();
                    throw std::runtime_error("Invalid input. Please enter a numeric value.");
                }
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
                ioHandler.clearInputBuffer();
            }
        }

        while (true) {
            ioHandler.setSystemOutputColor();
            std::cout << "How many grams of flower are you using? ";
            try {
                double tempGrams;
                ioHandler.setUserInputColor();
                if (std::cin >> tempGrams) {
                    if (tempGrams > 0) {
                        grams_flower = tempGrams;
                        break;
                    }
                    else {
                        ioHandler.setErrorMessageColor();
                        throw std::out_of_range("Invalid input. Please enter a positive value.");
                    }
                }
                else {
                    ioHandler.setErrorMessageColor();
                    throw std::runtime_error("Invalid input. Please enter a numeric value.");
                }
            }
            catch (const std::exception& e) {
                std::cout << e.what() << "\n";
                ioHandler.clearInputBuffer();
            }
        }
        // END User Input
        // 
        // Perform calculations
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
        // END Calculations
        //
        // OUTPUT RESULT
        ioHandler.grayOutAllText();
        ioHandler.setTextColor(3, 0);
        std::cout << "\n" << percentage_THCa << "% THCa converts to "
            << static_cast<int>(mg_THC) << "mg THC per " << grams_flower << "g of flower.\n\n";

        ioHandler.setSystemOutputColor();
        for (int i = 2; i <= 27; i += 2) {
            std::cout << static_cast<int>(mg_THC / i) << "mg per " << i << " servings\n";
        }

        std::cout << "\n\n";
        // 
        // END OF PROGRAM LOGIC
        //
        while (true) {
            ioHandler.setSystemOutputColor();
            std::cout << "Do you want to reset or exit the program? (reset/exit): ";
            std::string response;
            ioHandler.setUserInputColor();
            std::cin >> response;

            if (response == "reset") {
                percentage_THCa = 0;
                grams_flower = 0;
                mg_THC = 0;
                customLoss = 0;
                break;
            }
            else if (response == "exit") {
                ioHandler.setSystemOutputColor();
                SetConsoleTextAttribute(hConsole, originalConsoleAttributes);
                return 0;
            }
            else {
                ioHandler.setErrorMessageColor();
                std::cout << "Invalid input. Please enter 'reset' or 'exit'.\n";
            }
        }
    }

    return 0;
}