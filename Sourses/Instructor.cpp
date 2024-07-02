#include "Instructor.h"

Instructor::Instructor(const std::string& name, const std::vector<TimeSlot>& availability, const std::vector<Course>& preferredCourses)
    : _name(name), _availability(availability), _preferredCourses(preferredCourses) {}

const std::string Instructor::getName() const {
    return _name;
}

const std::vector<TimeSlot>& Instructor::getAvailability() const {
    return _availability;
}

const std::vector<Course>& Instructor::getPrefferedCourses() const {
    return _preferredCourses;
}

void Instructor::displayInfo() const {
    std::cout << "Instructor: " << _name << std::endl;
    std::cout << "Availability:" << std::endl;
    for (const auto& slot : _availability) {
        slot.displayInfo();
    }
    std::cout << "Preferred Courses:" << std::endl;
    for (const auto& course : _preferredCourses) {
        course.displayInfo();
    }
}