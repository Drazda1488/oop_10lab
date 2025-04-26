#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Money {
public:
    long rubles;
    int kopecks;

    // �����������
    Money(long r = 0, int k = 0) {
        rubles = r;
        kopecks = k;
        normalize();
    }

    // ������� ��� ������������� ������ � ������
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

    // ����� �� �����
    void print() {
        cout << rubles << ",";
        if (kopecks < 10) cout << "0";
        cout << kopecks << " ���." << endl;
    }

    // ���� � ����������
    void input() {
        cout << "������� �����: ";
        cin >> rubles;
        cout << "������� �������: ";
        cin >> kopecks;
        normalize();
    }
};

// ������� ��� �������� �����
Money addMoney(Money a, Money b) {
    Money result;
    result.rubles = a.rubles + b.rubles;
    result.kopecks = a.kopecks + b.kopecks;
    result.normalize();
    return result;
}

// ������� ��� ��������� �����
Money subtractMoney(Money a, Money b) {
    Money result;
    result.rubles = a.rubles - b.rubles;
    result.kopecks = a.kopecks - b.kopecks;
    result.normalize();
    return result;
}

// ������� ��� ���������� � ����
void saveToFile(vector<Money> moneyList, string filename) {
    ofstream file(filename);
    for (Money m : moneyList) {
        file << m.rubles << " " << m.kopecks << endl;
    }
    file.close();
    cout << "������ ��������� � ����!" << endl;
}

// ������� ��� ������ �� �����
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

// ������� ����
void showMenu() {
    cout << "\n=== ���� ===" << endl;
    cout << "1. �������� ����� ������" << endl;
    cout << "2. �������� ��� ������" << endl;
    cout << "3. ������� ������ �� ��������" << endl;
    cout << "4. ��������� ������ �� 1.50 ���." << endl;
    cout << "5. �������� ������ ����� �������" << endl;
    cout << "6. �����" << endl;
    cout << "�������� ��������: ";
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
            cout << "\n��� ������:" << endl;
            for (int i = 0; i < moneyList.size(); i++) {
                cout << i + 1 << ". ";
                moneyList[i].print();
            }
            break;
        }
        case 3: {
            moneyList = readFromFile(filename);
            Money toDelete;
            cout << "������� �������� ��� ��������:" << endl;
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
            cout << "�������� ���������!" << endl;
            break;
        }
        case 4: {
            moneyList = readFromFile(filename);
            Money toIncrease;
            cout << "������� �������� ��� ����������:" << endl;
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
            cout << "���������� ���������!" << endl;
            break;
        }
        case 5: {
            moneyList = readFromFile(filename);
            int pos, k;
            cout << "������� ������� (1-" << moneyList.size() << "): ";
            cin >> pos;
            cout << "������� ������� ��������? ";
            cin >> k;

            if (pos < 1 || pos > moneyList.size()) {
                cout << "�������� �������!" << endl;
                break;
            }

            for (int i = 0; i < k; i++) {
                Money m;
                cout << "������� ������ " << i + 1 << ":" << endl;
                m.input();
                moneyList.insert(moneyList.begin() + pos + i, m);
            }
            saveToFile(moneyList, filename);
            cout << "���������� ���������!" << endl;
            break;
        }
        case 6:
            cout << "����� �� ���������." << endl;
            break;
        default:
            cout << "�������� �����!" << endl;
        }
    } while (choice != 6);

    return 0;
}