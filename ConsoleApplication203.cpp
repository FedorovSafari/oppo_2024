#include <iostream>
#include <string>
#include <regex>

using namespace std;

// Структура для хранения информации о температурных измерениях
struct TemperatureMeasurements {
    string date;
    string place;
    float temperature;

    void print() const {
        setlocale(LC_ALL, "RU");
        cout << "TemperatureMeasurements: \n";
        cout << "Дата: " << date << " ";
        cout << "Место: " << place << " ";
        cout << "Температура: " << temperature << " °C\n";
    }
};

// Функция для извлечения данных из строки
bool extractData(const string& input, TemperatureMeasurements& measurements) {
    regex pattern("([\\d]+[\\.][\\d]+[\\.][\\d\\n]+[^\\s])([\\s]+)([a-zA-Z]+)([\\s]+)([-+]?\[\\d.]+)");
    smatch match;

    if (regex_match(input, match, pattern)) {
        measurements.date = match[1];
        measurements.place = match[3];
        measurements.temperature = stof(match[5]);
        return true;
    }
    return false;
}

// Функция для обработки входной строки и вывода результата
void processInput(const string& input) {
    TemperatureMeasurements measurements;

    if (extractData(input, measurements)) {
        measurements.print();
    }
    else {
        cerr << "Ошибка: Не тот формат строки.\n";
    }
}

int main() {
    string input = "2017.11.16 London -6.1";
    processInput(input);
    return 0;
}
