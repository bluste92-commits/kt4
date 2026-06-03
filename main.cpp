#include <iostream>
#include <string>
#include <iomanip>

// Перечисления для типов и платформ
enum GameType { RPG, STRATEGY, RACING, FLIGHT_SIM, OTHER };
enum Platform { PC, MOBILE, GAMEPAD, CROSSPLATFORM };

// Требование 3: Вложенная структура для характеристик игры
struct GameSpecs {
    Platform platform;
    GameType type;
};

// Основная структура
struct Game {
    std::string title;
    std::string developer;
    double subscriptionPrice;
    long long audienceSize;
    GameSpecs specs; // Вложенная структура
};

// --- Вспомогательные функции для вывода ENUM в виде текста ---
std::string typeToString(GameType type) {
    switch (type) {
    case RPG: return "RPG";
    case STRATEGY: return "Strategy";
    case RACING: return "Racing";
    case FLIGHT_SIM: return "Flight Sim";
    default: return "Other";
    }
}

std::string platformToString(Platform platform) {
    switch (platform) {
    case PC: return "PC";
    case MOBILE: return "Mobile";
    case GAMEPAD: return "Gamepad";
    case CROSSPLATFORM: return "Crossplatform";
    }
    return "Unknown";
}

// Требование 1 & 6: Оберточная функция для вывода данных в виде таблицы
void printGamesTable(const Game* games, int size, const std::string& tableTitle) {
    std::cout << "\n=== " << tableTitle << " ===\n";
    if (size == 0) {
        std::cout << "Нет данных для отображения.\n";
        return;
    }

    std::cout << std::left
        << std::setw(20) << "Название"
        << std::setw(15) << "Разработчик"
        << std::setw(12) << "Подписка"
        << std::setw(15) << "Аудитория"
        << std::setw(15) << "Платформа"
        << std::setw(15) << "Тип" << "\n";
    std::cout << std::string(92, '-') << "\n";

    for (int i = 0; i < size; ++i) {
        std::cout << std::left
            << std::setw(20) << games[i].title
            << std::setw(15) << games[i].developer
            << std::setw(12) << games[i].subscriptionPrice
            << std::setw(15) << games[i].audienceSize
            << std::setw(15) << platformToString(games[i].specs.platform)
            << std::setw(15) << typeToString(games[i].specs.type) << "\n";
    }
}

// Подзадача: Вывод данных по конкретной игре
void printConcreteGame(const Game* games, int size, const std::string& title) {
    for (int i = 0; i < size; ++i) {
        if (games[i].title == title) {
            std::cout << "\nИнформация об игре \"" << title << "\":\n";
            std::cout << "Разработчик: " << games[i].developer << "\n";
            std::cout << "Стоимость подписки: $" << games[i].subscriptionPrice << "\n";
            std::cout << "Аудитория: " << games[i].audienceSize << " пользователей\n";
            std::cout << "Платформа: " << platformToString(games[i].specs.platform) << "\n";
            std::cout << "Тип: " << typeToString(games[i].specs.type) << "\n";
            return;
        }
    }
    std::cout << "\nИгра с названием \"" << title << "\" не найдена.\n";
}

// Подзадача: Функция изменения игры
void editGame(Game& game, std::string newTitle, double newPrice, long long newAudience) {
    game.title = newTitle;
    game.subscriptionPrice = newPrice;
    game.audienceSize = newAudience;
}

// Подзадача: Фильтрация авиасимуляторов (аудитория >= 1 млн)
int filterFlightSims(const Game* source, int sourceSize, Game* dest) {
    int count = 0;
    for (int i = 0; i < sourceSize; ++i) {
        if (source[i].specs.type == FLIGHT_SIM && source[i].audienceSize >= 1000000) {
            dest[count] = source[i];
            count++;
        }
    }
    return count; // возвращаем размер нового массива
}

// Подзадача: Фильтрация стратегий для PC
int filterPcStrategies(const Game* source, int sourceSize, Game* dest) {
    int count = 0;
    for (int i = 0; i < sourceSize; ++i) {
        if (source[i].specs.type == STRATEGY && source[i].specs.platform == PC) {
            dest[count] = source[i];
            count++;
        }
    }
    return count;
}

// Требование 5: Алгоритм сортировки пузырьком (по поддерживаемым платформам)
void bubbleSortByPlatform(Game* games, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            // Сравниваем численные значения enum Platform
            if (games[j].specs.platform > games[j + 1].specs.platform) {
                Game temp = games[j];
                games[j] = games[j + 1];
                games[j + 1] = temp;
            }
        }
    }
}

// Подзадача: Вывод 3 самых дорогих игр
void printTop3Expensive(const Game* games, int size) {
    // Создаем копию массива, чтобы не испортить исходный порядок
    Game tempArray[20];
    for (int i = 0; i < size; ++i) {
        tempArray[i] = games[i];
    }

    // Сортируем пузырьком по убыванию цены подписки
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (tempArray[j].subscriptionPrice < tempArray[j + 1].subscriptionPrice) {
                Game temp = tempArray[j];
                tempArray[j] = tempArray[j + 1];
                tempArray[j + 1] = temp;
            }
        }
    }

    // Выводим топ-3 через оберточную функцию
    printGamesTable(tempArray, (size < 3 ? size : 3), "3 САМЫХ ДОРОГИХ ИГРЫ");
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Требование 4: Ввод данных в виде инициализации массива структур (20 записей)
    // Обратите внимание на двойные фигурные скобки в конце — это инициализация вложенной структуры specs
    Game db[20] = {
        {"Witcher 3", "CD Projekt", 0.0, 50000000, {PC, RPG}},
        {"Dota 2", "Valve", 0.0, 12000000, {PC, STRATEGY}},
        {"MS Flight Sim", "Asobo", 9.99, 2500000, {PC, FLIGHT_SIM}},
        {"IL-2 Sturmovik", "1C", 14.99, 1100000, {GAMEPAD, FLIGHT_SIM}},
        {"StarCraft II", "Blizzard", 0.0, 3000000, {PC, STRATEGY}},
        {"CS:GO", "Valve", 0.0, 30000000, {PC, OTHER}},
        {"Cyberpunk 2077", "CD Projekt", 0.0, 25000000, {PC, RPG}},
        {"GTA V", "Rockstar", 0.0, 160000000, {CROSSPLATFORM, OTHER}},
        {"Flight Theory", "Buildil", 1.99, 500000, {MOBILE, FLIGHT_SIM}},
        {"Age of Empires IV", "Relic", 39.99, 1500000, {PC, STRATEGY}},
        {"X-Plane 12", "Laminar", 59.99, 1050000, {PC, FLIGHT_SIM}},
        {"NFS Most Wanted", "EA", 0.0, 10000000, {GAMEPAD, RACING}},
        {"Clash Royale", "Supercell", 0.0, 100000000, {MOBILE, STRATEGY}},
        {"Forza Horizon 5", "Playground", 49.99, 30000000, {GAMEPAD, RACING}},
        {"Civilization VI", "Firaxis", 29.99, 8000000, {PC, STRATEGY}},
        {"Skyrim", "Bethesda", 0.0, 60000000, {CROSSPLATFORM, RPG}},
        {"War Thunder", "Gaijin", 0.0, 40000000, {PC, FLIGHT_SIM}},
        {"PUBG", "Krafton", 0.0, 75000000, {PC, OTHER}},
        {"FIFA 23", "EA", 69.99, 20000000, {GAMEPAD, OTHER}},
        {"Diablo IV", "Blizzard", 69.99, 9000000, {PC, RPG}}
    };

    // 1. Вывод исходной базы
    printGamesTable(db, 20, "ИСХОДНАЯ БАЗА КОМПЬЮТЕРНЫХ ИГР");

    // 2. Перепись авиасимуляторов (>= 1 млн) в другой массив
    Game flightSims[20]; // Выделяем массив с запасом
    int flightSimsCount = filterFlightSims(db, 20, flightSims);

    // Сортировка пузырьком по платформам
    bubbleSortByPlatform(flightSims, flightSimsCount);

    // Вывод через оберточную функцию
    printGamesTable(flightSims, flightSimsCount, "АВИАСИМУЛЯТОРЫ ОТ 1 МЛН (ОТСОРТИРОВАНЫ ПУЗЫРЬКОМ)");

    // 3. Вывод данных по конкретной игре
    printConcreteGame(db, 20, "MS Flight Sim");

    // 4. Изменение игры
    std::cout << "\n>>> Изменяем данные для игры 'Dota 2'...";
    for (int i = 0; i < 20; ++i) {
        if (db[i].title == "Dota 2") {
            editGame(db[i], "Dota 2 Reborn", 4.99, 15000000);
            break;
        }
    }
    printConcreteGame(db, 20, "Dota 2 Reborn");

    // 5. Вывод 3 самых дорогих игр
    printTop3Expensive(db, 20);

    // 6. Отдельный массив для стратегий на PC
    Game pcStrategies[20];
    int pcStrategiesCount = filterPcStrategies(db, 20, pcStrategies);
    printGamesTable(pcStrategies, pcStrategiesCount, "СТРАТЕГИИ ДЛЯ PC");

    return 0;
}