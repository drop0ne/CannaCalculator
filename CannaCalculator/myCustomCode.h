#pragma once
#include "libraries.h"

using namespace std::chrono_literals;
#define interface_type_data HANDLE color
#define interface_data color
// Function prototype for the function we want to call from the DLL
typedef int (*DLL_FUNC)();


enum color_name_to_cCode
{
    default_color = 7, black = 0, dark_green = 2, green = 2, bright_green = 10, blue = 1, bright_red = 12, red = 4, light_blue = 3, ice_blue = 9, teal_blue = 11, white = 7, bright_white = 15, gray = 8, purple = 5, yellow = 6, highlight_with_blue_blue = 19, highlight_with_blue_blue2 = 25, highlight_blue_white = 23, check = 27
};


class MyCustomCode {
private:
    HANDLE color; ///< A handle to the console output device
    char userSelection{}; ///< A variable for storing user input

public:
    MyCustomCode(HANDLE hwdCOLOR);
    virtual ~MyCustomCode();
    void clearScreen();
    void setScreenColor(const char* cCode);
    void systemCommand(const char* cCode);
    void pause();
    void set_text_color(int color_choice);
    void print(int output);
    void print(std::string output);
    void print(std::string output_1, int output_2);
    void print(std::string output1, int output2, std::string output3);
    char user_input();
};
