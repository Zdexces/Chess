#include "horizon.h"

const std::string samples[6] = { "\nHorizon, engage.\n", "\nSimurgh Silhouette, online.\n", "\nCompleted calculating the possible engagement time.\n", "\nEngagement results: successful. Farewell, Boss.\n", "\nMission complete. Simurgh Silhouette, offline.\n", "\nCalculated time is due. Farewell, Boss.\n" };

std::random_device seed;
std::default_random_engine engine(seed());
std::uniform_int_distribution <int> selector(0, 2);
int set_sel = selector(engine);

/**
 * @brief Приветствие пользователя одной из 3 случайных фраз.
 *
 */

void greet() {
    std::cout << samples[set_sel] << std::endl;
}

/**
 * @brief Прощание с пользователем фразой, соответствующей с приветственной фразой.
 *
 */

void farewell() {
    std::cout << samples[set_sel + 3] << std::endl;
}

/**
 * @brief Рекурсивная функция обработки пользовательского ввода.
 *
 * Возвращает саму себя до тех пор, пока не будет введен ответ Y/y(да) или N/n(нет).
 *
 * @param query Строка обращения к пользователю, зависит от контекста вызова.
 * @param use_ignore Флажок на использование std :: cin.ignore(std :: numeric_limits <std :: streamsize> :: max(), '\n') до и после захвата ответа пользователя.
 * @return true Пользорватель ответил "Да" на вопрос в @param query.
 * @return false Пользорватель ответил "Нет" на вопрос в @param query.
 */

bool handle_mistype_input(std::string query, bool use_ignore) {
    std::cout << query;
    char feedback = 'a';
    std::cin.clear();
    if (use_ignore) {
        std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
    }
    std::cin >> feedback;
    if (!use_ignore) {
        std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
    }
    if (feedback == 'y' || feedback == 'Y') {
        return 1;
    }
    else if (feedback == 'n' || feedback == 'N') {
        return 0;
    }
    else {
        return handle_mistype_input("Stop playing around, Human. Go back?(y/n)\n", use_ignore); //fucking genius...old version down below:
    }
}
/**     oh wow..old vers:
handle_mistype_input("Stop playing around, Human. Go back?(y/n)\n");
return 8;
*/