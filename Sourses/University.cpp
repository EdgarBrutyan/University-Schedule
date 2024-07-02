#include "University.h"

University& University::getInstance()
{
    static University instance;
    return instance;
}

void University::addCourse(const Course& course) {
    _courses.push_back(course);
}

void University::addInstructor(const Instructor& instructor) {
    _instructors.push_back(instructor);
}

void University::addTimeSlot(const TimeSlot& timeSlot) {
    _timeSlots.push_back(timeSlot);
}

void University::saveState(const std::string& filename = "Schedule.json") const {
    json j;
    for (const auto& course : _courses) {
        json course_json;
        course_json["courseName"] = course.getCourseName();

        for (const auto& slot : course.getPrefferedTimeSlots()) {
            course_json["preferredTimeSlots"].push_back({ {"day", slot.getDay()}, {"startTime", slot.getStartTime()}, {"endTime", slot.getEndTime()} });
        }
        j["courses"].push_back(course_json);
    }

    for (const auto& instructor : _instructors) {
        json instructor_json;
        instructor_json["name"] = instructor.getName();
        for (const auto& slot : instructor.getAvailability()) {
            instructor_json["availability"].push_back({ {"day", slot.getDay() }, {"startTime", slot.getStartTime() }, {"endTime", slot.getEndTime()} });
        }
        for (const auto& course : instructor.getPrefferedCourses()) {
            instructor_json["preferredCourses"].push_back(course.getCourseName());
        }
        j["instructors"].push_back(instructor_json);
    }

    for (const auto& slot : _timeSlots) {
        j["timeSlots"].push_back({ {"day", slot.getDay()}, {"startTime", slot.getStartTime()}, {"endTime", slot.getEndTime()} });
    }

    std::ofstream file(filename);
    file << j.dump(4);
}

void University::loadState(const std::string& filename) {
    std::ifstream file(filename);
    json j;
    file >> j;

    _courses.clear();
    _instructors.clear();
    _timeSlots.clear();

    for (const auto& course_json : j["courses"]) {
        std::vector<TimeSlot> preferredTimeSlots;
        for (const auto& slot_json : course_json["preferredTimeSlots"]) {
            preferredTimeSlots.emplace_back(slot_json["day"], slot_json["startTime"], slot_json["endTime"]);
        }
        _courses.emplace_back(course_json["courseName"], preferredTimeSlots);
    }

    for (const auto& instructor_json : j["instructors"]) {
        std::vector<TimeSlot> availability;
        for (const auto& slot_json : instructor_json["availability"]) {
            availability.emplace_back(slot_json["day"], slot_json["startTime"], slot_json["endTime"]);
        }
        std::vector<Course> preferredCourses;
        for (const auto& courseName : instructor_json["preferredCourses"]) {
            auto it = find_if(_courses.begin(), _courses.end(), [&](const Course& c) { return c.getCourseName() == courseName; });
            if (it != _courses.end()) {
                preferredCourses.push_back(*it);
            }
        }
        _instructors.emplace_back(instructor_json["name"], availability, preferredCourses);
    }

    for (const auto& slot_json : j["timeSlots"]) {
        _timeSlots.emplace_back(slot_json["day"], slot_json["startTime"], slot_json["endTime"]);
    }
}

void University::schedule() {

    try {

        GRBEnv env = GRBEnv(true);
        env.start();

        GRBModel model = GRBModel(env);

        std::map<std::tuple<int, int, int>, GRBVar> x;

        for (int c = 0; c < _courses.size(); ++c) 
        {
            for (int t = 0; t < _timeSlots.size(); ++t) 
            {
                for (int i = 0; i < _instructors.size(); ++i) 
                {
                    x[std::make_tuple(c, t, i)] = model.addVar(0.0, 1.0, 0.0, GRB_BINARY);
                }
            }
        }

        for (int c = 0; c < _courses.size(); ++c) {
            GRBLinExpr expr = 0;
            for (int t = 0; t < _timeSlots.size(); ++t) 
            {
                for (int i = 0; i < _instructors.size(); ++i) 
                {
                    expr += x[std::make_tuple(c, t, i)];
                }
            }
            model.addConstr(expr == 1);
        }

        for (int t = 0; t < _timeSlots.size(); ++t) 
        {
            for (int i = 0; i < _instructors.size(); ++i) 
            {
                GRBLinExpr expr = 0;
                for (int c = 0; c < _courses.size(); ++c) 
                {
                    expr += x[std::make_tuple(c, t, i)];
                }

                model.addConstr(expr <= 1);
            }
        }

        for (int c = 0; c < _courses.size(); ++c) 
        {
            for (int t = 0; t < _timeSlots.size(); ++t) 
            {
                for (int i = 0; i < _instructors.size(); ++i) 
                {
                    bool available = false;
                    for (const auto& slot : _instructors[i].getAvailability()) {
                        if (slot.getDay() == _timeSlots[t].getDay() && slot.getStartTime() == _timeSlots[t].getStartTime() 
                            && slot.getEndTime() == _timeSlots[t].getEndTime()) {
                            available = true;
                            break;
                        }
                    }
                    if (!available) {
                        model.addConstr(x[std::make_tuple(c, t, i)] == 0);
                    }
                }
            }
        }

        for (int c = 0; c < _courses.size(); ++c) 
        {
            for (int t = 0; t < _timeSlots.size(); ++t) 
            {
                for (int i = 0; i < _instructors.size(); ++i) 
                {
                    bool preferred = false;
                    for (const auto& course : _instructors[i].getPrefferedCourses()) {
                        if (course.getCourseName() == _courses[c].getCourseName()) {
                            preferred = true;
                            break;
                        }
                    }
                    if (!preferred) {
                        model.addConstr(x[std::make_tuple(c, t, i)] == 0);
                    }
                }
            }
        }

        GRBLinExpr obj = 0;
        for (int c = 0; c < _courses.size(); ++c) 
        {
            for (int t = 0; t < _timeSlots.size(); ++t) 
            {
                for (int i = 0; i < _instructors.size(); ++i) 
                {
                    bool preferredTimeSlot = false;
                    for (const auto& slot : _courses[c].getPrefferedTimeSlots()) 
                    {
                        if (slot.getDay() == _timeSlots[t].getDay() && slot.getStartTime() == _timeSlots[t].getStartTime() 
                            && slot.getEndTime() == _timeSlots[t].getEndTime()) {
                            preferredTimeSlot = true;
                            break;
                        }
                    }
                    bool preferredInstructor = false;
                    for (const auto& course : _instructors[i].getPrefferedCourses()) {
                        if (course.getCourseName() == _courses[c].getCourseName()) {
                            preferredInstructor = true;
                            break;
                        }
                    }
                    if (!preferredTimeSlot || !preferredInstructor) {
                        obj += x[std::make_tuple(c, t, i)];
                    }
                }
            }
        }

        model.setObjective(obj, GRB_MINIMIZE);
        model.optimize();

        for (int c = 0; c < _courses.size(); ++c) 
        {
            for (int t = 0; t < _timeSlots.size(); ++t) 
            {
                for (int i = 0; i < _instructors.size(); ++i) 
                {
                    if (x[std::make_tuple(c, t, i)].get(GRB_DoubleAttr_X) == 1) {
                        std::cout << "Course " << _courses[c].getCourseName() << " is scheduled at " << _timeSlots[t].getDay() << " "
                            << _timeSlots[t].getStartTime() << " - " << _timeSlots[t].getEndTime()
                            << " with Instructor " << _instructors[i].getName() << std::endl;
                    }
                }
            }
        }
    }
    catch (GRBException e) {
        std::cout << "Error code = " << e.getErrorCode() << std::endl;
        std::cout << e.getMessage() << std::endl;
    }
    catch (...) {
        std::cout << "Exception during optimization" << std::endl;
    }
}