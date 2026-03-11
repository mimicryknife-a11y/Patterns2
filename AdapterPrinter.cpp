#include <iostream>
#include <string>

// Целевой интерфейс (новый ПК ожидает USB)
class USBPrinter {
public:
    virtual std::string printUSB(const std::string& data, int quality) = 0;
};

class USBScanner {
public:
    virtual std::string scanUSB(const std::string& data, int quality) = 0;
};

// Старый принтер с LPT-портом (несовместимый)
class OldLPTPrinter {
public:
    std::string printLPT(const std::string& data, int quality) {
        return "Старый принтер печатает по LPT: " + data + " quality: " + std::to_string(quality);
    }
};

class OldLPTScanner {
public:
    std::string scanLPT(const std::string& data, int quality) {
        return "Старый сканер печатает по LPT: " + data + " quality: " + std::to_string(quality);
    }
};

// Адаптер: Оборачивает старый принтер для USB-интерфейса
class LPTToUSBAdapter : public USBPrinter {
private:
    OldLPTPrinter* oldPrinter;
public:
    LPTToUSBAdapter(OldLPTPrinter* p) : oldPrinter(p) {}
    std::string printUSB(const std::string& data, int quality) override {
        // Адаптируем вызов
        return oldPrinter->printLPT(data + " (адаптировано для USB)", quality);
    }
};

// Адаптер: Оборачивает старый принтер для USB-интерфейса
class LPTToScanerAdapter : public USBScanner {
private:
    OldLPTScanner* oldPrinter;
public:
    LPTToScanerAdapter(OldLPTScanner* p) : oldPrinter(p) {}
    std::string scanUSB(const std::string& data, int quality) override {
        // Адаптируем вызов
        return oldPrinter->scanLPT(data + " (адаптировано для USB)", quality);
    }
};


class UniversalAdapter : public USBScanner, public USBPrinter {
private:
    OldLPTScanner* oldScanner;
    OldLPTPrinter* oldPrinter;
public:
    UniversalAdapter(OldLPTScanner* p1, OldLPTPrinter* p2) : oldScanner(p1), oldPrinter(p2) {}
    UniversalAdapter(OldLPTScanner* p1) : oldScanner(p1) {}
    UniversalAdapter(OldLPTPrinter* p2) : oldPrinter(p2) {}
    std::string printUSB(const std::string& data, int quality) override {
        if (oldPrinter == nullptr)
        {
            return "";
        }
        return oldPrinter->printLPT(data + " (адаптировано для USB)", quality);
    }
    std::string scanUSB(const std::string& data, int quality) override {
        if (oldScanner == nullptr)
        {
            return "";
        }
        return oldScanner->scanLPT(data + " (адаптировано для USB)", quality);
    }
};

/*
Почему Adapter лучше изменения старого класса:
1. старый класс не модифицируется
2. код, который уже использует старый класс, продолжает работать
3. адаптер берет на себя только задачу преобразования интерфейсов, не затрагивая основную логику
*/
int main() {
    OldLPTPrinter oldPrinter;
    USBPrinter* adapter = new LPTToUSBAdapter(&oldPrinter);
    std::cout << adapter->printUSB("Документ", 1) << std::endl;

    OldLPTScanner oldScanner;
    USBScanner* scanner = new LPTToScanerAdapter(&oldScanner);
    std::cout << scanner->scanUSB("Документы", 2) << std::endl;
    delete adapter;

    UniversalAdapter* univAdapter = new UniversalAdapter(&oldPrinter);
    std::cout << univAdapter->scanUSB("Документы", 3) << std::endl;
    return 0;
}