#include <utility>
#include <typeinfo>
#include <cstdio>
#include <map>
#include <vector>
#include <iostream>

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
        GetInTime(GetSchedule(s)).unformattime = time_value * 10,000;
        
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
        GetOutTime(GetSchedule(s)).unformattime = time_value * 10,000;
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
    bool inner_status = true;
    for (size_t i = 0; i < schedule_number; i++)
    {
        for (size_t j = i + 1; j < schedule_number; j++)
        {
            if(inner_status)
            {
                
                if(schedule_table[j].second.first.unformattime > schedule_table[i].second.second.unformattime)
                {
                    ret.push_back(schedule_table[i].first);
                    ret.push_back(schedule_table[j].first);
                }else
                {
                    break;
                }
            }
            inner_status = false;
            
            if(j + 1 >= schedule_number)
            {
                inner_status = true;
                break;
            }
            if(schedule_table[j].second.second.unformattime > schedule_table[j +1].second.first.unformattime)
            {
                ret.pop_back();
                ret.push_back(schedule_table[j+1].first);
            }
            else
            {
                inner_status = true;
                i = j-1;
                break;
            }
            
        }
    }
    
    if(ret.size() == 0){ return 0; }
    std::cout << *ret.begin();
    for(auto i = ret.begin()+1; i < ret.end(); i++ )
    {
        if(ret.size())
        std::cout<<" "<< *i<< std::endl;
        if(++i != ret.end())
        {
            std::cout << *i;
        }else
        {
            break;
        }
        
    }
    return 0;
}