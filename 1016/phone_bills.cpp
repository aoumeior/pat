#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#define ll long long
#define eps 1e-8
#define INF 0x7FFFFFFF

using namespace std;

// 24小时话费
int cents_per_min[24] = {0};

// 时间结构体
struct CallTime
{
    int month, day, hour, minute;
};

// 通话记录结构体
struct CallRecord
{
    string name;
    CallTime call_time;
    bool online; // 记录类型 1上线 0下线
};

bool cmp(CallRecord r1, CallRecord r2)
{
    if (r1.name == r2.name)
    {
        // return r1.call_time < r2.call_time
        if (r1.call_time.day < r2.call_time.day)
            return true;
        else if (r1.call_time.day > r2.call_time.day)
            return false;

        if (r1.call_time.hour < r2.call_time.hour)
            return true;
        else if (r1.call_time.hour > r2.call_time.hour)
            return false;

        if (r1.call_time.minute < r2.call_time.minute)
            return true;
        else if (r1.call_time.minute > r2.call_time.minute)
            return false;
    }
    return r1.name < r2.name;
}

// 求出两个时间的分钟差
int time_sub(CallTime t1, CallTime t2)
{
    int min1, min2;
    min1 = t1.day * 24 * 60 + t1.hour * 60 + t1.minute;
    min2 = t2.day * 24 * 60 + t2.hour * 60 + t2.minute;
    return abs(min1 - min2);
}

// 求出某个电话记录的话费
int phone_cost(CallTime t1, CallTime t2)
{
    int ret = 0;
    while (!(t1.day == t2.day && t1.hour == t2.hour && t1.minute == t2.minute))
    {
        if (t1.day == t2.day && t1.hour == t2.hour)
        {
            ret += cents_per_min[t1.hour] * (t2.minute - t1.minute);
            t1.minute = t2.minute;
        }
        else
        {
            ret += cents_per_min[t1.hour] * (60 - t1.minute);
            t1.minute = 0;
            if (t1.hour == 23)
            {
                t1.hour = 0;
                t1.day++;
            }
            else
            {
                t1.hour++;
            }
        }
    }
    return ret;
}

int main()
{
    // 输入cents per minute
    for (int i = 0; i < 24; i++)
    {
        cin >> cents_per_min[i];
    }
    // 输入记录个数
    int n;
    cin >> n;
    // 对每条记录进行存储
    vector<CallRecord> records;
    for (int i = 0; i < n; i++)
    {
        // 将输入信息先存放到record里
        CallRecord record;
        string name, call_time, type;
        cin >> name >> call_time >> type;
        record.name = name;
        const char *s = call_time.data();
        sscanf(s, "%d:%d:%d:%d", &record.call_time.month, &record.call_time.day, &record.call_time.hour, &record.call_time.minute);
        if (type == "on-line")
            record.online = true;
        else
            record.online = false;
        // 将记录存入vector
        records.push_back(record);
    }

    // 按照先字母表，后时间前后进行排序
    sort(records.begin(), records.end(), cmp);

    int sum = 0;                   // 记录总开销
    bool last_online = false;      // 记录上一条记录是否是online
    CallTime begin_time, end_time; // 一条通话记录的开始和结束时间
    map<string, int> idx;          // 建立顾客姓名和姓名编号的映射
    int name_cnt = 0;              // 顾客姓名数量
    for (int i = 0; i < n; i++)
    {
        CallRecord record = records[i];
        // 如果是上线记录，则记录开始电话的时间
        if (record.online)
        {
            begin_time = record.call_time;
            last_online = true;
        }
        // 如果是下线记录，且上条记录是上线记录
        else if (last_online && !record.online)
        {
            end_time = record.call_time;
            last_online = false;
            // 计算分钟数和花费数
            int minutes = time_sub(begin_time, end_time);
            int rec_cost = phone_cost(begin_time, end_time);
            sum += rec_cost;
            // 第一次时打印名字
            if (idx[record.name] == 0)
            {
                idx[record.name] = ++name_cnt;
                cout << record.name << " ";
                printf("%02d\n", record.call_time.month);
            }
            // 打印通话记录
            printf("%02d:%02d:%02d ", begin_time.day, begin_time.hour, begin_time.minute);
            printf("%02d:%02d:%02d ", end_time.day, end_time.hour, end_time.minute);
            printf("%d $%.2lf\n", minutes, 1.0 * rec_cost / 100);
        }

        bool customer_end = false;
        if (i == n - 1)
            customer_end = true;
        else if (record.name != records[i + 1].name)
            customer_end = true;
        if (customer_end)
        {
            if (sum != 0)
                printf("Total amount: $%.2lf\n", 1.0 * sum / 100);
            sum = 0;
            last_online = false;
        }
    }
    return 0;
}