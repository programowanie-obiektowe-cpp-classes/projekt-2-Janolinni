#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <vector>

class Data {
protected:
    int dzien;
    int miesiac;
    int rok;

public:
    // Konstruktor
    Data(int d = 1, int m = 1, int r = 2000);

    // Metody
    void wyswietlStandardowy() const;
    void wyswietlISO() const;
    void przesun(int dni, int miesiace, int lata);
    static int roznicaDni(const Data& d1, const Data& d2);

    // Operator przeciążenia
    bool operator==(const Data& inna) const;
    bool operator<(const Data& inna) const;

    // Walidacja i narzędzia
    static bool czyPrzestepny(int rok);
    static int dniWMiesiacu(int miesiac, int rok);

    void przesunTygodnie(int tygodnie); // Przesunięcie daty o tygodnie
    std::string dzienTygodnia() const; // Zwracanie dnia tygodnia
};

// Dziedziczenie dla operacji na świętach
class DataSwieta : public Data {
private:
    static std::vector<std::string> swieta;
    static std::vector<Data> datySwiateczne;

public:
    DataSwieta(int d, int m, int r);
    bool czySwieto() const;
    static void dodajSwieto(const Data& data, const std::string& nazwa);
};

#endif