#include <iostream>
#include <string>

using namespace std;

// Абстрактные продукты (семейство UI-элементов)
class Button {
public:
    virtual string render() = 0;
    virtual void interact() = 0;
};

class ScrollBar {
public:
    virtual string render() = 0;
    virtual void interact() = 0;
};

class CheckBox  {
public:
    virtual std::string render() = 0;
    virtual void interact() = 0;
};

// Конкретные продукты для Windows
class WinButton : public Button {
public:
    std::string render() override { return "Windows Кнопка"; }
    void interact() { cout << "win кнопка нажата!" << endl; };
};

class WinScrollBar : public ScrollBar {
public:
    std::string render() override { return "Windows Скроллбар"; }
    void interact() { cout << "win лист проскролился!" << endl; };
};

class WinCheckBox : public CheckBox {
public:
    std::string render() override { return "Windows Чекбокс"; }
    void interact() {
        enabled = !enabled;
        cout << "Чекбокс win переключён (статус: " << enabled << ")" << endl;
    };
private:
    bool enabled = false;
};

// Конкретные продукты для macOS
class MacButton : public Button {
public:
    std::string render() override { return "macOS Кнопка"; }
    void interact() { cout << "mac кнопка нажата!" << endl; };
};

class MacScrollBar : public ScrollBar {
public:
    std::string render() override { return "macOS Скроллбар"; }
    void interact() { cout << "mac лист проскролился!" << endl; };
};

class MacCheckBox : public CheckBox {
public:
    std::string render() override { return "macOS Чекбокс"; }
    void interact() {
        enabled = !enabled;
        cout << "Чекбокс max переключён (статус: " << enabled << ")" << endl;
    };
private:
    bool enabled = false;
};

// Конкретные продукты для linuxOS
class LinuxButton : public Button {
public:
    std::string render() override { return "linuxOS Кнопка"; }
    void interact() { cout << "linux кнопка нажата!" << endl; };
};

class LinuxScrollBar : public ScrollBar {
public:
    std::string render() override { return "linuxOS Скроллбар"; }
    void interact() { cout << "lunux лист проскролился!" << endl; };
};

class LinuxCheckBox : public CheckBox {
public:
    std::string render() override { return "linuxOS Чекбокс"; }
    void interact() { 
        enabled = !enabled;
        cout << "Чекбокс linux переключён (статус: " << enabled << ")" << endl;
    };
private:
    bool enabled = false;
};

// Абстрактная фабрика
class UIFactory {
public:
    virtual Button* createButton() = 0;
    virtual ScrollBar* createScrollBar() = 0;
    virtual CheckBox* createCheckBox() = 0;
};

// Конкретные фабрики
class WinFactory : public UIFactory {
public:
    Button* createButton() override { return new WinButton(); }
    ScrollBar* createScrollBar() override { return new WinScrollBar(); }
    CheckBox* createCheckBox() override { return new WinCheckBox(); }
};

class MacFactory : public UIFactory {
public:
    Button* createButton() override { return new MacButton(); }
    ScrollBar* createScrollBar() override { return new MacScrollBar(); }
    CheckBox* createCheckBox() override { return new MacCheckBox(); }
};

class LinuxFactory : public UIFactory {
public:
    Button* createButton() override { return new LinuxButton(); }
    ScrollBar* createScrollBar() override { return new LinuxScrollBar(); }
    CheckBox* createCheckBox() override { return new LinuxCheckBox(); }
};

/*
Почему Abstract Factory лучше отдельных фабрик:
1. все созданные объекты будут из одного семейства (нельзя случайно смешать Windows-кнопку с Mac-скролбаром)
2. логика создания целого семейства продуктов собрана в одном месте
3. добавление новой платформы требует создания только новой фабрики
*/
int main() {
    setlocale(0, "");

    // Выбираем фабрику по платформе
    UIFactory* factory = new LinuxFactory();  // Или MacFactory, WinFactory

    string name;
    cout << "введите название системы (win, linux, max): ";
    cin >> name;

    switch (name.at(0))
    {
    case 'w':
        factory = new WinFactory();
        break;
    case 'm':
        factory = new MacFactory();
        break;
    }

    Button* btn = factory->createButton();
    ScrollBar* sb = factory->createScrollBar();
    CheckBox* cb = factory->createCheckBox();
    cout << btn->render() << " и " << sb->render() << " и " << cb->render() << endl;
    delete btn; delete sb; delete cb; delete factory;
    return 0;
}