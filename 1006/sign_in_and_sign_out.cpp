#include <utility>
#include <typeinfo>
#include <cstdio>
#include <map>
#include <vector>
#include <iostream>
#include <string>

namespace amor
{
struct time_t
{
    unsigned hour;
    unsigned minute;
    unsigned second;
    unsigned unformattime;
};
} // namespace amor


#define GetInTime(x) x.first
#define GetOutTime(x) x.second
#define GetHomeName(x) x.first
#define GetSchedule(x) x.second

typedef std::pair<amor::time_t, amor::time_t> time_pair;
typedef std::pair<std::string, time_pair> schedule;


int main ()
{
    unsigned schedule_number;
    std::scanf("%ud", &schedule_number);

    std::vector<schedule> schedule_table{schedule_number};


    char door_name[16];
    unsigned time_value;
    schedule s;

    for (size_t i = 0; i < schedule_number; i++)
    {
        std::scanf("%s",door_name);
        GetHomeName(s) = door_name;

        // get in time
        std::scanf("%ud", &time_value);
        GetInTime(GetSchedule(s)).hour = time_value;
        GetInTime(GetSchedule(s)).unformattime = time_value * 10000;
        
        std::getchar();
        
        std::scanf("%ud", &time_value);
        GetInTime(GetSchedule(s)).minute = time_value;
        GetInTime(GetSchedule(s)).unformattime += time_value * 100;
        
        std::getchar();
        std::scanf("%ud", &time_value);
        GetInTime(GetSchedule(s)).second = time_value;
        GetInTime(GetSchedule(s)).unformattime += time_value;
        
        // get out time 
        std::scanf("%ud", &time_value);
        GetOutTime(GetSchedule(s)).hour = time_value;
        GetOutTime(GetSchedule(s)).unformattime = time_value * 10000;
        std::getchar();
        
        std::scanf("%ud", &time_value);
        GetOutTime(GetSchedule(s)).minute = time_value;
        GetOutTime(GetSchedule(s)).unformattime += time_value * 100;
        std::getchar();
        
        std::scanf("%ud", &time_value);
        GetOutTime(GetSchedule(s)).second = time_value;
        GetOutTime(GetSchedule(s)).unformattime += time_value;
        schedule_table[i] = s;
    }
    

    std::vector<std::string> ret;

    std::pair<std::string, unsigned> min;
    std::pair<std::string, unsigned> max;

    min.first =  "";
    min.second = 0;
    max.first = min.first;
    min.second = 235959;
    for(size_t i = 0; i < schedule_number; i++)
    {
        std::string s =  GetHomeName(schedule_table[i]);
        unsigned t1 = GetInTime(GetSchedule(schedule_table[i])).unformattime;
        unsigned t2 = GetOutTime(GetSchedule(schedule_table[i])).unformattime;
        
        if(t1 <= min.second)
        {
            min.second = t1;
            min.first = s;
        }

        if(t2 >= max.second)
        {
            max.second = t2;
            max.first = s;
        }
    }

    std::cout << min.first << " " << max.first;
    return 0;
}