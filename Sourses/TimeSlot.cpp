#include "./TimeSlot.h"

TimeSlot::TimeSlot(const std::string& day, const std::string& startTime, const std::string& endTime)
	:_day(day), _startTime(startTime), _endTime(endTime) {}

const std::string TimeSlot::getDay() const
{
	return _day;
}

const std::string TimeSlot::getStartTime() const
{
	return _startTime;
}

const std::string TimeSlot::getEndTime() const
{
	return _endTime;
}

void TimeSlot::displayInfo() const
{
	std::cout << "day :" << _day << std::endl;
	std::cout << "start :" << _startTime << std::endl;
	std::cout << "end :" << _endTime << std::endl;
}