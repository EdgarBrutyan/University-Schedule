<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>University Timetabling System</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
        }
        h1, h2, h3 {
            color: #2c3e50;
        }
        pre {
            background-color: #ecf0f1;
            padding: 10px;
            border-radius: 5px;
            overflow: auto;
        }
        code {
            background-color: #ecf0f1;
            padding: 2px 4px;
            border-radius: 3px;
        }
    </style>
</head>
<body>
    <h1>University Timetabling System</h1>

    <h2>Описание</h2>
    <p>Проект "University Timetabling System" предназначен для автоматического составления расписания занятий в университете. Система распределяет курсы по временным слотам и назначает преподавателей на курсы, учитывая их доступность и предпочтения.</p>

    <h2>Основные возможности</h2>
    <ul>
        <li><strong>Учёт временных слотов для курсов</strong>: Каждый курс назначается в определённое время.</li>
        <li><strong>Назначение преподавателей</strong>: Преподаватели назначаются на курсы с учётом их доступности и предпочтений.</li>
        <li><strong>Сохранение и загрузка состояния</strong>: Состояние системы можно сохранить в JSON файл и загрузить из него.</li>
        <li><strong>Оптимизация расписания</strong>: Система использует оптимизационный алгоритм для поиска наилучшего расписания, удовлетворяющего всем жёстким и максимальному числу мягких условий.</li>
    </ul>

    <h2>Структура классов</h2>

    <h3>TimeSlot</h3>
    <p>Представляет временной слот для расписания курсов.</p>
    <ul>
        <li><strong>Атрибуты</strong>:
            <ul>
                <li><code>day</code> (string): День недели.</li>
                <li><code>startTime</code> (string): Время начала.</li>
                <li><code>endTime</code> (string): Время окончания.</li>
            </ul>
        </li>
        <li><strong>Методы</strong>:
            <ul>
                <li><code>displayInfo()</code>: Вывод информации о временном слоте.</li>
                <li>Геттеры: <code>getDay()</code>, <code>getStartTime()</code>, <code>getEndTime()</code>.</li>
            </ul>
        </li>
    </ul>

    <h3>Course</h3>
    <p>Представляет курс, который нужно запланировать.</p>
    <ul>
        <li><strong>Атрибуты</strong>:
            <ul>
                <li><code>courseName</code> (string): Название курса.</li>
                <li><code>preferredTimeSlots</code> (list of TimeSlot): Предпочтительные временные слоты.</li>
            </ul>
        </li>
        <li><strong>Методы</strong>:
            <ul>
                <li><code>displayInfo()</code>: Вывод информации о курсе.</li>
                <li>Геттеры: <code>getCourseName()</code>, <code>getPreferredTimeSlots()</code>.</li>
            </ul>
        </li>
    </ul>

    <h3>Instructor</h3>
    <p>Представляет преподавателя, который может вести курсы.</p>
    <ul>
        <li><strong>Атрибуты</strong>:
            <ul>
                <li><code>name</code> (string): Имя преподавателя.</li>
                <li><code>availability</code> (list of TimeSlot): Доступные временные слоты.</li>
                <li><code>preferredCourses</code> (list of Course): Предпочтительные курсы.</li>
            </ul>
        </li>
        <li><strong>Методы</strong>:
            <ul>
                <li><code>displayInfo()</code>: Вывод информации о преподавателе.</li>
                <li>Геттеры: <code>getName()</code>, <code>getAvailability()</code>, <code>getPreferredCourses()</code>.</li>
            </ul>
        </li>
    </ul>

    <h3>University</h3>
    <p>Представляет комбинацию курсов, преподавателей и временных слотов.</p>
    <ul>
        <li><strong>Атрибуты</strong>:
            <ul>
                <li><code>courses</code> (list of Course): Курсы.</li>
                <li><code>instructors</code> (list of Instructor): Преподаватели.</li>
                <li><code>timeSlots</code> (list of TimeSlot): Временные слоты.</li>
            </ul>
        </li>
        <li><strong>Методы</strong>:
            <ul>
                <li><code>addCourse(Course course)</code>: Добавление курса.</li>
                <li><code>addInstructor(Instructor instructor)</code>: Добавление преподавателя.</li>
                <li><code>addTimeSlot(TimeSlot timeSlot)</code>: Добавление временного слота.</li>
                <li><code>saveState(const std::string& filename)</code>: Сохранение состояния в JSON файл.</li>
                <li><code>loadState(const std::string& filename)</code>: Загрузка состояния из JSON файла.</li>
                <li><code>schedule()</code>: Составление расписания с использованием оптимизационного алгоритма.</li>
                <li><code>getInstance()</code>: Получение единственного экземпляра (реализация паттерна Singleton).</li>
            </ul>
        </li>
    </ul>

    <h2>Установка и использование</h2>

    <h3>Требования</h3>
    <ul>
        <li>Компилятор C++ (например, GCC или MSVC)</li>
        <li><a href="https://www.gurobi.com/">Gurobi Optimizer</a> (для использования оптимизационного алгоритма)</li>
        <li>Библиотека JSON for Modern C++ (например, nlohmann/json)</li>
    </ul>

    <h3>Установка Gurobi</h3>
    <ol>
        <li><a href="https://www.gurobi.com/downloads/gurobi-optimizer/">Скачайте Gurobi</a>.</li>
        <li>Следуйте инструкциям по установке для вашей операционной системы.</li>
        <li>Убедитесь, что переменные среды настроены правильно (например, <code>GRB_LICENSE_FILE</code>).</li>
    </ol>

    <h3>Компиляция и запуск</h3>
    <ol>
        <li>Клонируйте репозиторий или скачайте исходный код.</li>
        <li>Настройте проект, добавив необходимые библиотеки и заголовочные файлы (например, <code>nlohmann/json.hpp</code>).</li>
        <li>Скомпилируйте проект с использованием вашего компилятора. Убедитесь, что Gurobi правильно подключен и включён в ваш проект.</li>
        <li>Запустите программу.</li>
    </ol>

    <h3>Пример использования</h3>
    <pre><code>int main() {
    University& uni = University::getInstance();

    // Добавление временных слотов
    uni.addTimeSlot(TimeSlot("Monday", "09:00", "10:30"));
    uni.addTimeSlot(TimeSlot("Monday", "10:45", "12:15"));
    // ...

    // Добавление курсов
    Course course1("Mathematics", { /* preferred time slots */ });
    uni.addCourse(course1);
    // ...

    // Добавление преподавателей
    Instructor instructor1("Dr. Smith", { /* availability */ }, { /* preferred courses */ });
    uni.addInstructor(instructor1);
    // ...

    // Составление расписания
    uni.schedule();

    // Сохранение расписания
    uni.saveState("university_schedule.json");

    return 0;
}
</code></pre>

    <h3>Тестирование</h3>
    <p>Для тестирования функциональности кода, можно использовать предоставленные примеры и создать собственные сценарии тестирования, добавляя различные курсы, временные слоты и преподавателей.</p>
</body>
</html>

