#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <stdexcept>



using namespace std;

struct TemperatureMeasurements {   // хранение информации об объекте
    string data;
    string place;
    float temp;

    void print() const {

        cout << "TemperatureMeasurements: \n";
        cout << "Дата: " << data << " ";
        cout << "Место: " << place << " ";
        cout << "Температура: " << temp << " °C\n";
    }

    void saveToFile(const string& filename) const {
        ofstream outFile(filename, ios::app);
        if (outFile.is_open()) {
            outFile << "TemperatureMeasurements: \n";
            outFile << "Дата: " << data << " ";
            outFile << "Место: " << place << " ";
            outFile << "Температура: " << temp << " °C\n";
            outFile.close();
        }
        else {
            cerr << "Ошибка: Не удалось открыть файл для записи.\n";
        }
    }
};

int main() {

    locale::global(std::locale("Russian"));

    // Массив строк для хранения входных данных
    string inputs[] = {
        "2019.04.17 'London' 33,66",
        "2020.01.10 'California' -27,11",
        "2021.12.11 'Paris' 1,77",
        "2100.13.43 'Mars' -110,336",
        "3204.01.01 'Saturn' -1000,56"
    };

    regex pattern("([\\d]+[\\.][\\d]+[\\.][\\d\\n]+[^\\s])([\\s]+)('[a-zA-Z]+')([\\s]+)([-+]?\[\\d,]+)");
    smatch match;

    for (const string& input : inputs) {
        // Проверяем, соответствует ли строка шаблону
        if (regex_match(input, match, pattern)) {
            string data = match[1];
            string place = match[3];
            float temp;

            try {
                temp = stof(match[5]);
            }
            catch (const invalid_argument& e) {
                cerr << "Temperature conversion error: " << e.what() << "\n";
                continue; // Пропускаем эту итерацию
            }
            catch (const out_of_range& e) {
                cerr << "Error: temperature is out of the acceptable range: " << e.what() << "\n";
                continue; // Пропускаем эту итерацию
            }

            TemperatureMeasurements obj{ data, place, temp };

            obj.print();
            obj.saveToFile("temperature_measurements.txt");
        }
        else {
            cerr << "Error: Wrong string format: " << input << "\n";
        }
    }

    return 0;
}
