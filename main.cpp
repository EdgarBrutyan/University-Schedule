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