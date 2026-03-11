# UI Factory Pattern Example

## Описание
Создает UI-элементы (кнопки и скроллбары) для разных операционных систем.

## Структура
- **Button, ScrollBar** — абстрактные продукты
- **WinButton, WinScrollBar** — продукты для Windows
- **MacButton, MacScrollBar** — продукты для macOS
- **LinuxButton, LinuxScrollBar** — продукты для linuxOS
- **UIFactory** — абстрактная фабрика
- **WinFactory, MacFactory, LinuxFactory** — конкретные фабрики

## Как работает
1. Выбирается нужная фабрика через ввож (WinFactory/MacFactory/LinuxFactory)
2. Фабрика создает семейство связанных продуктов
3. Все созданные элементы автоматически совместимы друг с другом

## Пример вывода
```
Windows Кнопка и Windows Скроллбар
```
