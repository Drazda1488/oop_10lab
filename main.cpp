#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Money {
public:
    long rubles;
    int kopecks;

    // Конструктор
    Money(long r = 0, int k = 0) {
        rubles = r;
        kopecks = k;
        normalize();
    }

    // Функция для корректировки рублей и копеек
    void normalize() {
        while (kopecks >= 100) {
            rubles++;
            kopecks -= 100;
        }
        while (kopecks < 0) {
            rubles--;
            kopecks += 100;
        }
    }

    // Вывод на экран
    void print() {
        cout << rubles << ",";
        if (kopecks < 10) cout << "0";
        cout << kopecks << " руб." << endl;
    }

    // Ввод с клавиатуры
    void input() {
        cout << "Введите рубли: ";
        cin >> rubles;
        cout << "Введите копейки: ";
        cin >> kopecks;
        normalize();
    }
};

// Функция для сложения денег
Money addMoney(Money a, Money b) {
    Money result;
    result.rubles = a.rubles + b.rubles;
    result.kopecks = a.kopecks + b.kopecks;
    result.normalize();
    return result;
}

// Функция для вычитания денег
Money subtractMoney(Money a, Money b) {
    Money result;
    result.rubles = a.rubles - b.rubles;
    result.kopecks = a.kopecks - b.kopecks;
    result.normalize();
    return result;
}

// Функция для сохранения в файл
void saveToFile(vector<Money> moneyList, string filename) {
    ofstream file(filename);
    for (Money m : moneyList) {
        file << m.rubles << " " << m.kopecks << endl;
    }
    file.close();
    cout << "Данные сохранены в файл!" << endl;
}

// Функция для чтения из файла
vector<Money> readFromFile(string filename) {
    vector<Money> moneyList;
    ifstream file(filename);
    long r;
    int k;
    while (file >> r >> k) {
        moneyList.push_back(Money(r, k));
    }
    file.close();
    return moneyList;
}

// Главное меню
void showMenu() {
    cout << "\n=== Меню ===" << endl;
    cout << "1. Добавить новую запись" << endl;
    cout << "2. Показать все записи" << endl;
    cout << "3. Удалить записи по значению" << endl;
    cout << "4. Увеличить записи на 1.50 руб." << endl;
    cout << "5. Добавить записи после позиции" << endl;
    cout << "6. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    setlocale(LC_ALL, "RU");
    vector<Money> moneyList;
    string filename = "money.txt";
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            Money m;
            m.input();
            moneyList.push_back(m);
            saveToFile(moneyList, filename);
            break;
        }
        case 2: {
            moneyList = readFromFile(filename);
            cout << "\nВсе записи:" << endl;
            for (int i = 0; i < moneyList.size(); i++) {
                cout << i + 1 << ". ";
                moneyList[i].print();
            }
            break;
        }
        case 3: {
            moneyList = readFromFile(filename);
            Money toDelete;
            cout << "Введите значение для удаления:" << endl;
            toDelete.input();

            for (int i = 0; i < moneyList.size(); ) {
                if (moneyList[i].rubles == toDelete.rubles &&
                    moneyList[i].kopecks == toDelete.kopecks) {
                    moneyList.erase(moneyList.begin() + i);
                }
                else {
                    i++;
                }
            }
            saveToFile(moneyList, filename);
            cout << "Удаление завершено!" << endl;
            break;
        }
        case 4: {
            moneyList = readFromFile(filename);
            Money toIncrease;
            cout << "Введите значение для увеличения:" << endl;
            toIncrease.input();

            for (int i = 0; i < moneyList.size(); i++) {
                if (moneyList[i].rubles == toIncrease.rubles &&
                    moneyList[i].kopecks == toIncrease.kopecks) {
                    moneyList[i].rubles += 1;
                    moneyList[i].kopecks += 50;
                    moneyList[i].normalize();
                }
            }
            saveToFile(moneyList, filename);
            cout << "Увеличение завершено!" << endl;
            break;
        }
        case 5: {
            moneyList = readFromFile(filename);
            int pos, k;
            cout << "Введите позицию (1-" << moneyList.size() << "): ";
            cin >> pos;
            cout << "Сколько записей добавить? ";
            cin >> k;

            if (pos < 1 || pos > moneyList.size()) {
                cout << "Неверная позиция!" << endl;
                break;
            }

            for (int i = 0; i < k; i++) {
                Money m;
                cout << "Введите запись " << i + 1 << ":" << endl;
                m.input();
                moneyList.insert(moneyList.begin() + pos + i, m);
            }
            saveToFile(moneyList, filename);
            cout << "Добавление завершено!" << endl;
            break;
        }
        case 6:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 6);

    return 0;
}