#include <iostream>
#include <vector>
#include "./TimeSlot.h"


#ifndef Course_h
#define Course_h

class Course {
public:
    void displayInfo() const;

    const std::string getCourseName() const;

    const std::vector<TimeSlot>& getPrefferedTimeSlots() const;

public:
	Course(const std::string& courseName, std::vector<TimeSlot>& preferredTimeSlots);

private:
    std::string _courseName;
	std::vector<TimeSlot> _preferredTimeSlots;
};

#endif
