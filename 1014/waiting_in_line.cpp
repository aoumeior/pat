#include <bits/stdc++.h>

struct Person
{
    int id = 0;
    int server_time = 0;
    int begin_time = 0;
    int end_time = -1;
};

int main()
{
    int window_number;
    int max_queue_number;
    int customers_number;
    int customer_queries_number;
    std::cin >> window_number >> max_queue_number >> customers_number >> customer_queries_number;

    std::vector<std::queue<Person>> line{window_number + 1};
    std::queue<Person> wait;
    std::vector<Person> Per{customers_number + 1};

    for (int i = 1; i <= customers_number; ++i)
    {
        std::cin >> Per[i].server_time;
        Per[i].id = i;
        if (i <= window_number)
        {
            Per[i].end_time = Per[i].server_time;
        }
        if (i <= window_number * max_queue_number)
        {
            line[(i - 1) % window_number + 1].push(Per[i]);
        }
        else
        {
            wait.push(Per[i]);
        }
    }
    int customers_number_count = customers_number;
    int now_time = 0;
    constexpr int close_time = 9 * 60;
    while (now_time < close_time && customers_number_count)
    {
        now_time++;
        for (int i = 1; i <= window_number; ++i)
        {
            if (line[i].empty())
            {
                continue;
            }
            const Person &head = line[i].front();
            if (head.end_time <= now_time || head.end_time > close_time)
            {
                line[i].pop();
                customers_number_count--;
                auto &t = line[i].front();
                t.begin_time = head.end_time;
                t.end_time = head.end_time + t.server_time;

                Per[head.id].begin_time = head.begin_time;
                Per[head.id].end_time = head.end_time;
                if (!wait.empty())
                {
                    line[i].push(wait.front());
                    wait.pop();
                }
            }
        }
    }
    int query_id;
    for (int i = 1; i <= customer_queries_number; ++i)
    {
        std::cin >> query_id;
        if (Per[query_id].end_time == -1)
        {
            std::cout << "Sorry" << std::endl;
        }
        else
        {
            std::printf("%02d:%02d\n", Per[query_id].end_time / 60 + 8, Per[query_id].end_time % 60);
        }
    }
    return 0;
}