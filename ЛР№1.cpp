#include <iostream>
#include <string>

using namespace std;

// Определение структуры для хранения данных
struct Data {
    string name; // Поле типа string
    int price;     // Поле типа int
    double alc; // Поле типа double

    Data(string n, int p, double a) : name(n), price(p), alc(a) {}
};

// Определение класса для связного списка
class LinkedList {
private:
    struct Drink {
        Data data;       // Данные узла
        Drink* next;     // Указатель на следующий узел

        Drink(Data d) : data(d), next(nullptr) {}
    };

    Drink* head; // Указатель на голову списка

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        while (head != nullptr) {
            Drink* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Добавление элемента в начало списка
    void addToFront(Data data) {
        Drink* newDrink = new Drink(data);
        newDrink->next = head;
        head = newDrink;
    }

    // Добавление элемента в конец списка
    void addToEnd(Data data) {
        Drink* newDrink = new Drink(data);
        if (head == nullptr) {
            head = newDrink;
        } else {
            Drink* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newDrink;
        }
    }

    // Добавление элемента после заданного имени
    void addAfter(string existingName, Data data) {
        Drink* current = head;
        while (current != nullptr && current->data.name != existingName) {
            current = current->next;
        }
        if (current != nullptr) {
            Drink* newDrink = new Drink(data);
            newDrink->next = current->next;
            current->next = newDrink;
        } else {
            cout << "Элемент с именем " << existingName << " не найден." << endl;
        }
    }

    // Добавление элемента перед заданным именем
    void addBefore(string existingName, Data data) {
        if (head == nullptr) {
            cout << "Список пуст." << endl;
            return;
        }

        if (head->data.name == existingName) {
            addToFront(data);
            return;
        }

        Drink* current = head;
        while (current->next != nullptr && current->next->data.name != existingName) {
            current = current->next;
        }
        if (current->next != nullptr) {
            Drink* newDrink = new Drink(data);
            newDrink->next = current->next;
            current->next = newDrink;
        } else {
            cout << "Элемент с именем " << existingName << " не найден." << endl;
        }
    }

    // Удаление элемента по имени
    void deleteByName(string name) {
        if (head == nullptr) {
            cout << "Список пуст." << endl;
            return;
        }

        if (head->data.name == name) {
            Drink* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Drink* current = head;
        while (current->next != nullptr && current->next->data.name != name) {
            current = current->next;
        }
        if (current->next != nullptr) {
            Drink* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            cout << "Элемент с именем " << name << " не найден." << endl;
        }
    }

    // Вывод содержимого списка
    void printList() const {
        Drink* current = head;
        while (current != nullptr) {
            cout << "Название: " << current->data.name << ", Цена: " << current->data.price
                 << ", Процент алкоголя: " << current->data.alc << endl;
            current = current->next;
        }
    }
};

// Функция main со сценарием работы со списком
int main() {
    LinkedList list;

    // Добавляем элементы в список
    list.addToEnd(Data("Джин-тоник", 390, 8.0));
    list.addToEnd(Data("Апероль шприц", 490, 11.0));
    list.addToEnd(Data("Лонг-айленд", 480, 22.0));

    cout << "Содержимое списка:" << endl;
    list.printList();

    // Добавляем элемент в начало списка
    list.addToFront(Data("Ипа", 350, 5.8));
    cout << "\nПосле добавления элемента в начало списка:" << endl;
    list.printList();

    // Добавляем элемент в конец списка
    list.addToEnd(Data("Глинтвейн", 260, 6.0));
    cout << "\nПосле добавления элемента в конец списка:" << endl;
    list.printList();

    // Добавляем элемент после "Джин-тоник"
    list.addAfter("Джин-тоник", Data("Маргарита", 29, 27.5));
    cout << "\nПосле добавления элемента после 'Джин-тоник':" << endl;
    list.printList();

    // Добавляем элемент перед "Ипа"
    list.addBefore("Ипа", Data("Дайкири", 450, 20.0));
    cout << "\nПосле добавления элемента перед 'Ипа':" << endl;
    list.printList();

    // Удаляем элемент с именем "Alice"
    list.deleteByName("Лонг-айленд");
    cout << "\nПосле удаления элемента с именем 'Лонг-айленд':" << endl;
    list.printList();

    return 0;
}
