#include <cstdio>
#include <cstdint>
#include <cinttypes>
#include <set>
#include <algorithm>
#include <vector>

class Dfs
{
private:
    const std::vector<std::vector<std::uint32_t>> &graph_;
    std::vector<bool> visit_;
    std::uint32_t unicom_subgraph_ = 0;

public:
    Dfs(const std::vector<std::vector<std::uint32_t>> &graph) : graph_(graph),
                                                                visit_(graph.size(), false)
    {
    }

public:
    std::uint32_t get_unicom_subgraph() const
    {
        return unicom_subgraph_;
    }
    void operator()(std::uint32_t start = 0)
    {

        dfs(start);
        unicom_subgraph_++;

        for (size_t i = 0; i < visit_.size(); i++)
        {
            if (visit_[i] == false)
            {
                dfs(i);
                unicom_subgraph_++;
            }
        }
    }

public:
    void dfs(std::uint32_t node)
    {
        if (!visit_[node])
        {
            visit_[node] = true;
            for (size_t i = 0; i < graph_[node].size(); i++)
            {
                dfs(graph_[node][i]);
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    std::uint32_t number_of_nodes;
    std::scanf("%" SCNu32, &number_of_nodes);
    std::uint32_t init_node_number = 1;

    std::vector<std::vector<std::uint32_t>> aj(1);

    std::uint32_t left, right;
    for (size_t i = 0; i < number_of_nodes - 1; i++)
    {
        std::scanf("%" SCNu32 " %" SCNu32, &left, &right);

        if (init_node_number < left)
        {
            while (true)
            {
                aj.emplace_back();
                init_node_number++;

                if (init_node_number == left)
                {
                    break;
                }
            }
        }

        if (init_node_number < right)
        {
            while (true)
            {
                aj.emplace_back();
                init_node_number++;

                if (init_node_number == right)
                {
                    break;
                }
            }
        }

        aj[left - 1].push_back(right - 1);
        aj[right - 1].push_back(left - 1);
    }

    Dfs dfs(aj);
    dfs();

    if (dfs.get_unicom_subgraph() != 1)
    {
        std::printf("Error: %" PRIu32 " components", dfs.get_unicom_subgraph());
    }

    return 0;
}