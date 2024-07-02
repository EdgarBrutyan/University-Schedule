#include <iostream>
#include <vector>
#include "Instructor.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <gurobi_c++.h>

using json = nlohmann::json;

#ifndef University_h
#define University_h

class University
{
public:
	void addCourse(const Course& course);

	void addInstructor(const Instructor& instructor);

	void addTimeSlot(const TimeSlot& timeslot);

	void saveState(const std::string& filepath) const;
	
	void loadState(const std::string& filepath);

	void schedule();

	static University& getInstance(); // for SingleTon Design Pattern

private:
	University() {}
	University(University& univer) = delete;

private:
	std::vector<Instructor> _instructors;
	std::vector<TimeSlot> _timeSlots;
	std::vector<Course> _courses;
};

#endif
