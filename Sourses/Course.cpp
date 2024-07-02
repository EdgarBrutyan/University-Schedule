#include "Course.h"

Course::Course(const std::string& courseName, std::vector<TimeSlot>& preferredTimeSlots)
    : _courseName(courseName), _preferredTimeSlots(preferredTimeSlots) {}

void Course::displayInfo() const {
    std::cout << "Course: " << _courseName << std::endl;
    std::cout << "Preferred TimeSlots:" << std::endl;
    for (const auto& slot : _preferredTimeSlots) {
        slot.displayInfo();
    }
}

const std::vector<TimeSlot>& Course::getPrefferedTimeSlots() const 
{
    return _preferredTimeSlots;
}

const std::string Course::getCourseName() const
{
    return _courseName;
}