#include <iostream>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <queue>

constexpr std::int32_t open_time = 8 * 60 * 60;
constexpr std::int32_t last_time = 17 * 60 * 60;
struct queueing_at_bank
{
    std::int32_t customer_arriving_time;
    std::int32_t service_time; // finish
    queueing_at_bank(std::int32_t a, std::int32_t b)
        : customer_arriving_time(a),
          service_time(b)
    {
    }
};

struct window
{
    int total;

    window(int _t) : total(_t) {}

    bool operator<(const window &w) const
    {

        if (total > w.total)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    std::int16_t total_number_of_customers, number_of_windows;
    std::cin >> total_number_of_customers >> number_of_windows;

    std::vector<queueing_at_bank> today;
    std::int32_t h, m, s, p;

    for (size_t i = 0; i < total_number_of_customers; i++)
    {
        std::scanf("%d:%d:%d %d", &h, &m, &s, &p);
        today.push_back({(h * 60 * 60 + m * 60 + s), p * 60});
    }
    std::sort(today.begin(), today.end(), [](const queueing_at_bank &left, const queueing_at_bank &right) {
        return left.customer_arriving_time > right.customer_arriving_time;
    });

    std::int32_t sum = 0;

    queueing_at_bank t(0, 0);
    int cnt = 0;
    std::priority_queue<window> windows;
    for (int i = 0; i < number_of_windows; i++)
    {
        windows.push(window(open_time));
    }

    while (!today.empty())
    {
        t = today.back();
        today.pop_back();
        if (t.customer_arriving_time > last_time)
            break;
        cnt++;

        auto w = windows.top();
        windows.pop();

        if (t.customer_arriving_time < w.total)
        {
            sum += w.total - t.customer_arriving_time;
            w.total += t.service_time;
        }
        else
        {
            w.total = t.customer_arriving_time + t.service_time;
        }
        windows.push(w);
    }
    double result = sum / 60.f / cnt;
    std::cout << std::fixed << std::setprecision(1) << result << std::endl;
    return 0;
}