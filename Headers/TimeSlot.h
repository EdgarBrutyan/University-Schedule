#include <iostream>

#ifndef TimeSlot_h
#define TimeSlot_h

class TimeSlot {
public:
	void displayInfo() const;

	const std::string getDay() const;

	const std::string getStartTime() const;

	const std::string getEndTime() const;

public:
	explicit TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime);

private:
	std::string _day;
	std::string _startTime;
	std::string _endTime;
};

#endif


