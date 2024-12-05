#include <iostream>
#include <string>
#include <regex>
using namespace std;

struct TemperatureMeasurements {   //хранение информации об объекте
    string data;
    string place;
    float temp;

    void print() const {

        setlocale(LC_ALL, "RU");
        cout << "TemperatureMeasurements: \n";
        cout << "Дата: " << data << " ";
        cout << "Место: " << place << " ";
        cout << "Температура: " << temp << " °C ";

    }
};

int main() {

    string input = "2005.07.01 Moscow -18.7";
    regex pattern("([\\d]+[\\.][\\d]+[\\.][\\d\\n]+[^\\s])([\\s]+)([a-zA-Z]+)([\\s]+)([-+]?\[\\d.]+)");
    smatch match;

    // Проверяем, соответствует ли строка шаблону
    if (regex_match(input, match, pattern)) {
        // Извлекаем данные из строки
        string data = match[1];
        string place = match[3];
        float temp = stof(match[5]);
        // Создаем объект с извлеченными данными
        TemperatureMeasurements obj{ data, place, temp };
        // Выводим данные объекта
        obj.print();
    }
    else {

        cerr << "Ошибка: Не тот формат строки.\n";
    }

    return 0;
}
