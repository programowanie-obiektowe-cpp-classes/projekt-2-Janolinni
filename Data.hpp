#include "Data.h"
#include <iomanip>
#include <cmath>

// Konstruktor
Data::Data(int d, int m, int r) : dzien(d), miesiac(m), rok(r) {}

// Metody
void Data::wyswietlStandardowy() const {
    std::cout << dzien << "/" << miesiac << "/" << rok << "\n";
}

void Data::wyswietlISO() const {
    std::cout << rok << "-" << std::setw(2) << std::setfill('0') << miesiac
              << "-" << std::setw(2) << std::setfill('0') << dzien << "\n";
}

void Data::przesun(int dni, int miesiace, int lata) {
    rok += lata; //dodanie lat do roku
    miesiac += miesiace; //dodanie miesiecy do miesiaca
    while (miesiac > 12) {
        miesiac -= 12;
        rok++; //jesli przekroczymy grudzien dodajemy rok ale odejmujemy 12 miesiecy
    }
    while (miesiac < 1) {
        miesiac += 12;
        rok--; //jezeli cofniemy sie przed styczen odejmujemy rok ale dodajemy 12 miesiecy
    }

    dzien += dni;
    while (dzien > dniWMiesiacu(miesiac, rok)) {
        dzien -= dniWMiesiacu(miesiac, rok);
        miesiac++;
        if (miesiac > 12) {
            miesiac = 1;
            rok++;
        }
    }
    while (dzien < 1) {
        miesiac--;
        if (miesiac < 1) {
            miesiac = 12;
            rok--;
        }
        dzien += dniWMiesiacu(miesiac, rok);
    }
}

int Data::roznicaDni(const Data& d1, const Data& d2) {
    int dni1 = d1.rok * 365 + d1.dzien; //ilosc dni wynikajaca z lat plus obecny dzien
    for (int i = 1; i < d1.miesiac; ++i) 
        dni1 += dniWMiesiacu(i, d1.rok); //dni wynikajace z miesiecy w roku dodane iteracyjnie po miesiacach

    int dni2 = d2.rok * 365 + d2.dzien;
    for (int i = 1; i < d2.miesiac; ++i)
        dni2 += dniWMiesiacu(i, d2.rok);

    return std::abs(dni1 - dni2);
}

// Operatory
bool Data::operator==(const Data& inna) const {
    return dzien == inna.dzien && miesiac == inna.miesiac && rok == inna.rok; 
}

bool Data::operator<(const Data& inna) const {
    if (rok != inna.rok) return rok < inna.rok;
    if (miesiac != inna.miesiac) return miesiac < inna.miesiac;
    return dzien < inna.dzien;  //sposob na rozroznienie miesiecy dwoch dat

}

// Narzędzia
bool Data::czyPrzestepny(int rok) {
    return (rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0); //podzielnosc roku przez 4, 100, 400
}

int Data::dniWMiesiacu(int miesiac, int rok) {
    static const int dni[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //zbior ilosci dni
    if (miesiac == 2 && czyPrzestepny(rok)) return 29; //jesli rok jest przystepny, zamiast 28 mamy 29
    return dni[miesiac - 1];
}

// DataSwieta implementacja
std::vector<std::string> DataSwieta::swieta;
std::vector<Data> DataSwieta::datySwiateczne;

DataSwieta::DataSwieta(int d, int m, int r) : Data(d, m, r) {}

bool DataSwieta::czySwieto() const {
    for (const auto& data : datySwiateczne) {
        if (*this == data) return true;
    }
    return false;
}

void DataSwieta::dodajSwieto(const Data& data, const std::string& nazwa) {
     for (const auto& istnieje : datySwiateczne) {
        if (istnieje == data) {
            std::cout << "Święto już istnieje: " << nazwa << "\n";
            return;
        }
    }
    datySwiateczne.push_back(data);
    swieta.push_back(nazwa);
}

// Przesunięcie daty o tygodnie
void Data::przesunTygodnie(int tygodnie) {
    przesun(tygodnie * 7, 0, 0);
}

// Obliczanie dnia tygodnia (algorytm Zeller's Congruence)
std::string Data::dzienTygodnia() const {
    static const std::string dniTygodnia[] = {"Sobota", "Niedziela", "Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek"};

    int m = miesiac;
    int y = rok;

    if (m == 1 || m == 2) { // Przesunięcie stycznia i lutego na rok poprzedni - Jeśli miesiąc to styczeń lub luty, przesuwamy je na 13 i 14 poprzedniego roku

        m += 12;
        y -= 1;
    }

    int k = y % 100;   // Rok w bieżącym stuleciu
    int j = y / 100;   // Wiek
    int h = (dzien + (13 * (m + 1)) / 5 + k + (k / 4) + (j / 4) - (2 * j)) % 7;

    return dniTygodnia[(h + 7) % 7]; // Zabezpieczenie przed ujemnymi wartościami
}