#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

template <typename T1, typename T2>
class Pair {
public:
    Pair() {}
    Pair(const T1& first, const T2& second) : first(first), second(second) {}

    void displayPair() const {
        std::cout << first << ": " << second << std::endl;
    }

    void savePairToFile(std::ofstream& outFile) const {
        outFile << first << " " << second << " ";
    }

private:
    T1 first;
    T2 second;
};

template <typename T>
class Grades {
public:
    void inputGrades() {
        std::cout << "Введите оценки по предметам:" << std::endl;

        std::cout << "Количество предметов: ";
        std::cin >> numSubjects;

        subjectGrades.resize(numSubjects);

        for (int i = 0; i < numSubjects; ++i) {
            std::cout << "Оценка за предмет " << i + 1 << ": ";
            std::cin >> subjectGrades[i];
        }

        calculateAverageGrade();
    }

    void displayGrades() const {
        std::cout << "Оценки по предметам: ";
        for (int grade : subjectGrades) {
            std::cout << grade << " ";
        }
        std::cout << std::endl;

        std::cout << "Средний балл: " << averageGrade << std::endl;
    }

    void saveGradesToFile(std::ofstream& outFile) const {
        outFile << numSubjects << " ";
        for (int grade : subjectGrades) {
            outFile << grade << " ";
        }
        outFile << std::endl;
    }

private:
    int numSubjects;
    std::vector<T> subjectGrades;
    double averageGrade;

    void calculateAverageGrade() {
        if (numSubjects == 0) {
            averageGrade = 0.0;
            return;
        }

        T sum = 0;
        for (T grade : subjectGrades) {
            sum += grade;
        }

        averageGrade = static_cast<double>(sum) / numSubjects;
    }
};

class Product {
public:
    Product(const std::string& Name, const double& Price, const int& Quantity)
        : Name(Name), Price(Price), Quantity(Quantity) {}

    ~Product() {}
    
    const std::string& getName() const {
        return Name;
    }

    const double& getPrice() const {
        return Price;
    }
    
    const int& getQuantity() const {
		return Quantity;
	}

    void setName(const std::string& newName) {
        Name = newName;
    }

   
    void setPrice(const double& newPrice) {
        Price = newPrice;
    }
    
    void setQuantity(const int& newQuantity) {
        Quantity = newQuantity;
	}

    void displayInfo() const {
        std::cout << "Продукт: " << Name << ", Цена: " << Price << " Кол-во: " << Quantity;
        grades.displayGrades();
    }

    void inputGrades() {
        grades.inputGrades();
    }
    void saveToFile(std::ofstream& outFile) const {
    	outFile << Name << " " << Price << " " << Quantity << " ";
        grades.saveGradesToFile(outFile);
    }


private:
    std::string Name;
    double Price;
    int Quantity;
    Grades<int> grades;  // Изменил на Grades<int> для использования целочисленных оценок

};
void saveProductsToFile(const std::vector<Product*>& products, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Введите имя файла." << std::endl;
        return;
    }

    for (const auto* product : products) {
        product->saveToFile(outFile);
    }

    outFile.close();
}
int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<Product*> products;

    int choice;
    std::string filename;

    do {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить продукт" << std::endl;
        std::cout << "2. Найти продукт" << std::endl;
        std::cout << "3. Сохранить в файл" << std::endl;
        std::cout << "4. Выход" << std::endl;

        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string Name;
                double Price;
                int Quantity;

                std::cout << "Введите данные продукта:" << std::endl;
                std::cout << "Название: ";
                std::cin >> Name;
                std::cout << "Цена: ";
                std::cin >> Price;
                std::cout << "Кол-во: ";
                std::cin >> Quantity;

                products.push_back(new Product(Name, Price, Quantity));
                products.back()->inputGrades();

                break;
            }
            case 2: {
                std::string Name;
                std::cout << "Введите данные продукта для поиска:" << std::endl;
                std::cout << "Продукт: ";
                std::cin >> Name;

                auto it = std::find_if(products.begin(), products.end(), [&](const Product* product) {
                    return product->getName() == Name;
                });

                if (it != products.end()) {
                    (*it)->displayInfo();
                } else {
                    std::cout << "Продукт не найден." << std::endl;
                }

                break;
            }
             case 3: {
                std::cout << "Введите название файла: ";
                std::cin >> filename;
                saveProductsToFile(products, filename);
                break;
            }
            case 4:
                std::cout << "Выход." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор." << std::endl;
        }
    } while (choice != 4);

    for (const auto* product : products) {
        delete product;
    }

    return 0;
}
