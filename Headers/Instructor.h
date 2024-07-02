#include <iostream>
#include <vector>
#include "TimeSlot.h"
#include "Course.h"

#ifndef Instructor_h
#define Instructor_h

class Instructor
{

public:
	void displayInfo() const;

	const std::string getName() const;

    const std::vector<TimeSlot>& getAvailability() const;

	const std::vector<Course>& getPrefferedCourses() const;

public:
	explicit Instructor(const std::string& name, const std::vector<TimeSlot>& availability, const std::vector<Course>& preferredCourses);

private:
	std::string _name;
	std::vector<TimeSlot> _availability; 
	std::vector<Course> _preferredCourses;
};

#endif
