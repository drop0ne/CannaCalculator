#include "myCustomCode.h"


    MyCustomCode::MyCustomCode(HANDLE hwdCOLOR) {
    }

    MyCustomCode::~MyCustomCode() {
    }


    void MyCustomCode::clearScreen() {
        system("cls");
        return;
    }
    void MyCustomCode::setScreenColor(const char* cCode) {
        system(cCode);
        return;
    }
    void MyCustomCode::systemCommand(const char* cCode) {
        system(cCode);
        return;
    }
    void MyCustomCode::pause() {
        system("pause");
        return;
    }
    void MyCustomCode::set_text_color(int color_choice) {
        SetConsoleTextAttribute(this->color, color_choice);
        return;
    }
    void MyCustomCode::print(int output) {
        std::cout << output << "\n";
        return;
    }
    void MyCustomCode::print(std::string output) {
        std::cout << output;
        return;
    }
    void MyCustomCode::print(std::string output_1, int output_2) {
        std::cout << output_1 << " ";
        set_text_color(8);
        std::cout << output_2;
        return;
    }
    void MyCustomCode::print(std::string output1, int output2, std::string output3) {
        std::cout << output1 << output2 << output3;
        return;
    }
    char MyCustomCode::user_input() {
        char data{};
        std::cin >> data;
        return data;
    }