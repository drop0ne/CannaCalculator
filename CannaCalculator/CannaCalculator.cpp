// Autor Jacob Dougherty - drop0ne
// Started 2/27/2023
// I reserve all rights

#include <iostream>

double converter(double percent_THCa, double gramsFLOWER);
double mg_serving(double servings, double mgTHC);

int main() {
    double THCa{};
    double gramsFLOWER{};
    double mgTHC{};
    double servings{0};
    char responce{};

    std::cout << " CannaCalculator\n\n\n";

    std::cout << " First enter the % percentage THCa of your Cannabis Flower \n Then Enter the total number of grams of flower you are going to use to infuse our choice of oil or butter\n\n\n\n";

    std::cout << " What Percentage, THCa, is the Cannabis Flower you are using?: ";
    std::cin >> THCa;

    std::cout << "\n How many GRAMS of FLOWER are you using?:  ";
    std::cin >> gramsFLOWER;

    mgTHC = converter(THCa, gramsFLOWER);

    std::cout << "\n " << THCa << "% THCa Converts to\n " << floor(mgTHC) << "mg THC /per " << gramsFLOWER << "g of FLOWER\n\n";
    
    {
        std::cout << " Convert to serving? Y/N: ";
        std::cin >> responce;
        if (responce != 'y') {
            return 0;
        }
    }

    do {
        servings = servings + 2;
        std::cout << "\n " << floor(mg_serving(servings, mgTHC)) << "mg per " << servings << " Servings";

    } while (servings < 27);

    std::cout << "\n";
    system("pause");
}

double converter(double percent_THCa, double gramsFLOWER) {
    return ((percent_THCa * 10) * .8) * gramsFLOWER;
}

double mg_serving(double servings, double mgTHC) {
    return mgTHC / servings;
}