#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bit>
#include <bitset>
#include <string>

using edge_set = std::vector<uint16_t>;
using adjacency_list = std::vector<edge_set>;

class dfs {
public:
    dfs(const adjacency_list &aj)
    : aj_(aj),
    vb_(false, aj_.size())
    {
    } 
    void operator()(int n)
    {
        vb_[n] = true;
        for (int i = 1; i <= aj_.size(); i++)
        {
            if (vb_[i] == false && aj_[n][i] == 1)
            {
                operator ()(i);
            }
        }
    }
    void reset() const
    {
        vb_ = (std::vector<bool>(false, aj_.size()));
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

    for (size_t i = 0; i < be_concerned_city; i++)
    {
        uint16_t concerned_id, fix_highways = 0;
        std::cin >> concerned_id;

        dfs ds {al};
    }
    return 0;
}