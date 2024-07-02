# University Timetabling System

## Описание
Проект "University Timetabling System" предназначен для автоматического составления расписания занятий в университете. Система распределяет курсы по временным слотам и назначает преподавателей на курсы, учитывая их доступность и предпочтения.

## Основные возможности
* **Учёт временных слотов для курсов**: Каждый курс назначается в определённое время.
* **Назначение преподавателей**: Преподаватели назначаются на курсы с учётом их доступности и предпочтений.
* **Сохранение и загрузка состояния**: Состояние системы можно сохранить в JSON файл и загрузить из него.
* **Оптимизация расписания**: Система использует оптимизационный алгоритм для поиска наилучшего расписания, удовлетворяющего всем жёстким и максимальному числу мягких условий.

## Структура классов

### TimeSlot
Представляет временной слот для расписания курсов.

**Атрибуты**:
* `day` (string): День недели.
* `startTime` (string): Время начала.
* `endTime` (string): Время окончания.

**Методы**:
* `displayInfo()`: Вывод информации о временном слоте.
* Геттеры: `getDay()`, `getStartTime()`, `getEndTime()`.

### Course
Представляет курс, который нужно запланировать.

**Атрибуты**:
* `courseName` (string): Название курса.
* `preferredTimeSlots` (list of TimeSlot): Предпочтительные временные слоты.

**Методы**:
* `displayInfo()`: Вывод информации о курсе.
* Геттеры: `getCourseName()`, `getPreferredTimeSlots()`.

### Instructor
Представляет преподавателя, который может вести курсы.

**Атрибуты**:
* `name` (string): Имя преподавателя.
* `availability` (list of TimeSlot): Доступные временные слоты.
* `preferredCourses` (list of Course): Предпочтительные курсы.

**Методы**:
* `displayInfo()`: Вывод информации о преподавателе.
* Геттеры: `getName()`, `getAvailability()`, `getPreferredCourses()`.

### University
Представляет комбинацию курсов, преподавателей и временных слотов.

**Атрибуты**:
* `courses` (list of Course): Курсы.
* `instructors` (list of Instructor): Преподаватели.
* `timeSlots` (list of TimeSlot): Временные слоты.

**Методы**:
* `addCourse(Course course)`: Добавление курса.
* `addInstructor(Instructor instructor)`: Добавление преподавателя.
* `addTimeSlot(TimeSlot timeSlot)`: Добавление временного слота.
* `saveState(const std::string& filename)`: Сохранение состояния в JSON файл.
* `loadState(const std::string& filename)`: Загрузка состояния из JSON файла.
* `schedule()`: Составление расписания с использованием оптимизационного алгоритма.
* `getInstance()`: Получение единственного экземпляра (реализация паттерна Singleton).

## Установка и использование

### Требования
* Компилятор C++ (например, GCC или MSVC)
* [Gurobi Optimizer](https://www.gurobi.com/) (для использования оптимизационного алгоритма)
* Библиотека JSON for Modern C++ (например, nlohmann/json)

### Установка Gurobi
1. [Скачайте Gurobi](https://www.gurobi.com/downloads/).
2. Следуйте инструкциям по установке для вашей операционной системы.
3. Убедитесь, что переменные среды настроены правильно (например, `GRB_LICENSE_FILE`).

### Компиляция и запуск
1. Клонируйте репозиторий или скачайте исходный код.
2. Настройте проект, добавив необходимые библиотеки и заголовочные файлы (например, `nlohmann/json.hpp`).
3. Скомпилируйте проект с использованием вашего компилятора. Убедитесь, что Gurobi правильно подключен и включён в ваш проект.
4. Запустите программу.

### Пример использования
```cpp
#include "./University.h"
#include <vector>

using namespace std;

int main() {

    University& university = University::getInstance();

    TimeSlot slot1("Monday", "09:00", "11:00");
    TimeSlot slot2("Tuesday", "10:00", "12:00");

    university.addTimeSlot(slot1);
    university.addTimeSlot(slot2);

    vector<TimeSlot> preferredSlots1 = { slot1 };
    Course course1("Math", preferredSlots1);
    university.addCourse(course1);

    vector<TimeSlot> availability1 = { slot1, slot2 };
    vector<Course> preferredCourses1 = { course1 };
    Instructor instructor1("Aramyan", availability1, preferredCourses1);
    university.addInstructor(instructor1);
    university.schedule();
    university.saveState("Schedule.json");

    return 0;
}
