#include <iostream>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <iomanip>

constexpr std::int16_t open_time = 8 * 60 * 60;

struct queueing_at_bank
{
    std::int16_t customer_arriving_time;
    std::int16_t service_time;
    queueing_at_bank(std::int16_t a, std::int16_t b)
        : customer_arriving_time(a),
          service_time(b)
    {
    }
};

int main()
{
    std::int16_t total_number_of_customers, number_of_windows;
    std::cin >> total_number_of_customers >> number_of_windows;

    std::vector<queueing_at_bank> today;
    std::int16_t h, m, s, p, customer_arriving_time;

    for (size_t i = 0; i < total_number_of_customers; i++)
    {
        std::scanf("%d:%d:%d %d", &h, &m, &s, &p);
        customer_arriving_time = h * 60 * 60 + m * 60 + s * 60 - open_time;
        today.push_back({customer_arriving_time, p});
    }
    std::sort(today.begin(), today.end(), [](const queueing_at_bank &left, const queueing_at_bank &right) {
        return left.customer_arriving_time > right.customer_arriving_time;
    });

    std::uint32_t sum = 0;
    std::uint16_t number = number_of_windows;
    std::uint16_t last_finish = 0;

    queueing_at_bank t(0, 0);
    for (; today.empty(); today.pop_back())
    {
        t = today.back();
        number--;
        if (number == 0)
        {
            sum += (last_finish - t.customer_arriving_time > 0 ? last_finish - t.customer_arriving_time : 0) 
                    + t.service_time > 60 ? 60 * 60 : t.service_time * 60;
            last_finish =((last_finish - t.customer_arriving_time > 0 )? last_finish : t.customer_arriving_time) + t.service_time > 60 ? 60 * 60 : t.service_time * 60;
            number = number_of_windows - 1;
            continue;
        }
        if(t.customer_arriving_time >)
        last_finish = std::max(((std::int32_t)t.customer_arriving_time > 0 ? (std::int32_t)t.customer_arriving_time : 0) + t.service_time * 60, (std::int32_t)last_finish);

    }
    std::cout << std::fixed << std::setprecision(1) << sum / 60 / customer_arriving_time;
    return 0;
}