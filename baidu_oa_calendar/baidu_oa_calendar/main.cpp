#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class ConflictedTimeWindow {
public:
    ConflictedTimeWindow(const string& start_date, const string& end_date, const set<int>& conflicted_event_ids) : start_date_(start_date), end_date_(end_date), conflicted_event_ids_(conflicted_event_ids) {}
    
    string start_date() { return start_date_; }
    string end_date() { return end_date_; }
    set<int> conflicted_event_ids() { return conflicted_event_ids_; }
    
private:
    string start_date_;
    string end_date_;
    set<int> conflicted_event_ids_;
};

class Event {
public:
    Event(const int id, const string& start_date, const string& end_date) : id_(id), start_date_(start_date), end_date_(end_date) {}
    
    int id() { return id_; };
    string start_date() { return start_date_; }
    string end_date() { return end_date_; }
    
private:
    int id_;
    string start_date_;
    string end_date_;
};

struct Point {
    int id;
    bool isStart;
    Point(int i, bool s) : id(i), isStart(s) {}
};

class Calendar {
private:
    vector<pair<string, Point>> points;
    //map<tm, string> dict;
    
public:
    // Should allow multiple events to be scheduled over the same time window.
    void Schedule(Event* event) {
        /*struct tm timeDate;
         memset(&timeDate,0,sizeof(struct tm));
         strptime(event->start_date().c_str(),"%Y-%m-%d %H:%M", &timeDate);
         points[timeDate].emplace_back(Point{event->id(), true});
         dict[timeDate] = event->start_date();
         
         strptime(event->end_date().c_str(),"%Y-%m-%d %H:%M", &timeDate);
         points[timeDate].emplace_back(Point{event->id(), false});
         dict[timeDate] = event->end_date();
         */
        points.emplace_back(event->start_date(), Point(event->id(), 1));
        points.emplace_back(event->end_date(), Point(event->id(), 0));
        
    }
    
    vector<ConflictedTimeWindow> FindConflictedTimeWindows() {
        // IMPLEMENT ME
        vector<ConflictedTimeWindow> res;
        set<int> curid;
        sort(points.begin(), points.end(), [](const pair<string, Point>& p1, const pair<string, Point>& p2){
            if(p1.first != p2.first) return p1.first < p2.first;
            else {
                return p1.second.isStart < p2.second.isStart;
            }
        });
        string preTime;
        for(auto p : points) {
            string curTime = p.first;
            if(curid.size() > 1) {
                res.emplace_back(preTime, curTime, curid);
            }
            if(p.second.isStart) curid.insert(p.second.id);
            else curid.erase(p.second.id);
            preTime = curTime;
        }
        return res;
    }
};

// Helper Function for logging
string ToString(const set<int>& input) {
    ostringstream sstream;
    sstream << "[";
    bool has_data = false;
    for (set<int>::iterator it = input.begin(); it != input.end(); ++it) {
        has_data = true;
        sstream << *it;
        sstream << ", ";
    }
    string output = sstream.str();
    if (has_data) {
        output = output.substr(0, output.length() - 2);
    }
    return output + "]";
}

#ifndef __main__
#define __main__

int main(int argc, char* argv[]) {
    Calendar calendar;
    
    calendar.Schedule(new Event(1, "2014-01-01 10:00", "2014-01-01 11:00"));
    calendar.Schedule(new Event(2, "2014-01-01 11:00", "2014-01-01 12:00"));
    calendar.Schedule(new Event(3, "2014-01-01 12:00", "2014-01-01 13:00"));
    
    calendar.Schedule(new Event(4, "2014-01-02 10:00", "2014-01-02 11:00"));
    calendar.Schedule(new Event(5, "2014-01-02 09:30", "2014-01-02 11:30"));
    calendar.Schedule(new Event(6, "2014-01-02 08:30", "2014-01-02 12:30"));
    
    calendar.Schedule(new Event(7, "2014-01-03 10:00", "2014-01-03 11:00"));
    calendar.Schedule(new Event(8, "2014-01-03 09:30", "2014-01-03 10:30"));
    calendar.Schedule(new Event(9, "2014-01-03 09:45", "2014-01-03 10:45"));
    
    vector<ConflictedTimeWindow> conflicted_time_windows = calendar.FindConflictedTimeWindows();
    for (size_t i = 0; i < conflicted_time_windows.size(); ++i) {
        cout << conflicted_time_windows[i].start_date() << "-" << conflicted_time_windows[i].end_date() << ToString(conflicted_time_windows[i].conflicted_event_ids()) << endl;
    }
    // should print something like the following
    // 2014-01-02 09:30-2014-01-02 10:00[5, 6]
    // 2014-01-02 10:00-2014-01-02 11:00[4, 5, 6]
    // 2014-01-02 11:00-2014-01-02 11:30[5, 6]
    // 2014-01-03 09:45-2014-01-03 10:00[8, 9]
    // 2014-01-03 10:00-2014-01-03 10:30[7, 8, 9]
    // 2014-01-03 10:30-2014-01-03 10:45[7, 9]
}

#endif
