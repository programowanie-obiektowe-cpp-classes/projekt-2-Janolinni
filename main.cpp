#include "Data.h"
#include "Data.hpp"

int main() {
    Data data1(15, 1, 2025);
    Data data2(25, 12, 2025);

    // Wyświetlanie dat
    std::cout << "Data 1: ";
    data1.wyswietlStandardowy();
    std::cout << "Data 2: ";
    data2.wyswietlISO();

    // Przesunięcie daty
    std::cout << "Przesuwanie daty 1 o 50 dni:\n";
    data1.przesun(50, 0, 0);
    data1.wyswietlStandardowy();

    // Różnica dni
    int roznica = Data::roznicaDni(data1, data2);
    std::cout << "Różnica dni między datami: " << roznica << " dni.\n";

    // Święta
    DataSwieta::dodajSwieto(Data(25, 12, 2025), "Boże Narodzenie");
    DataSwieta dataSwieta(25, 12, 2025);
    if (dataSwieta.czySwieto()) {
        std::cout << "Data 25.12.2025 to święto!\n";
    } else {
        std::cout << "Data 25.12.2025 to nie jest święto.\n";
    }

    // Przesunięcie o tygodnie
    std::cout << "Data początkowa: ";
    data1.wyswietlStandardowy();
    data1.przesunTygodnie(3); // Przesunięcie o 3 tygodnie
    std::cout << "Data po przesunięciu o 3 tygodnie: ";
    data1.wyswietlStandardowy();

    // Wyświetlenie dnia tygodnia
    std::cout << "Dzień tygodnia dla daty: " << data1.dzienTygodnia() << "\n";

    return 0;
}