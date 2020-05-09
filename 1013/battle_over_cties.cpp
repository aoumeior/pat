#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <string>

using edge_set = std::vector<uint16_t>;
using adjacency_list = std::vector<edge_set>;

class dfs
{
public:
    dfs(const adjacency_list &aj)
        : aj_(aj),
          vb_(aj.size(), false)
    {
    }
    void operator()(int n)
    {
        vb_[n] = true;
        for (const int &i : aj_[n])
        {
            if (vb_[i] == false)
            {
                operator()(i);
            }
        }
    }

    size_t get_false()
    {
        int count = 0;
        std::for_each(vb_.begin(), vb_.end(), [&count](bool t) {
            if (t == false)
            {
                count++;
            }
        });
        return count;
    }

    bool get_vb_n(size_t n) const
    {
        return vb_[n];
    }
    void set_point_visit_open(size_t n) const
    {
        vb_[n] = true;
    }
    void set_point_visit_close(size_t n) const
    {
        vb_[n] = false;
    }
    void reset() const
    {
        vb_ = (std::vector<bool>(aj_.size(), false));
    }

private:
    const adjacency_list &aj_;
    mutable std::vector<bool> vb_;
};

int main()
{
    std::uint16_t city_number;
    std::uint16_t remaining_highways;
    std::uint16_t be_concerned_city;

    std::cin >> city_number >> remaining_highways >> be_concerned_city;

    adjacency_list al(city_number);

    for (size_t i = 0; i < remaining_highways; i++)
    {
        uint16_t a, b;
        std::cin >> a >> b;
        al[a - 1].push_back(b - 1);
        al[b - 1].push_back(a - 1);
    }

    dfs ds{al};
    for (size_t i = 0; i < be_concerned_city; i++)
    {
        uint16_t concerned_id;
        std::cin >> concerned_id;
        uint16_t cnt = 0;

        ds.set_point_visit_open(concerned_id - 1);
        for (size_t j = 0; j < city_number; j++)
        {
            if (ds.get_vb_n(j) == false)
            {
                ds(j);
                cnt++;
            }
        }
        printf("%d\n", cnt - 1);
        ds.reset();
    }
    return 0;
}