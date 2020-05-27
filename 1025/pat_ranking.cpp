#include <iostream>
#include <cstdio>
#include <cinttypes>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

struct pat_ranking
{
    std::uint64_t number;
    std::uint8_t score;
    std::uint8_t location_number = 0;
    std::uint8_t local_rank = 0;
};

int main(int argc, char const *argv[])
{
    std::int32_t positive_number;
    std::int32_t ranklists;

    std::scanf("%" SCNd32, &positive_number);

    if (positive_number == 0)
    {
        return 0;
    }

    std::vector<pat_ranking> all;
    for (size_t i = 0; i < positive_number; i++)
    {
        std::scanf("%" SCNd32, &ranklists);
        std::vector<pat_ranking> b;
        for (size_t j = 0; j < ranklists; j++)
        {
            pat_ranking a;
            std::scanf("%" SCNu64 " %" SCNu8, &a.number, &a.score);
            a.location_number = i + 1;
            b.push_back(a);
        }
        std::sort(b.begin(), b.end(), [](const pat_ranking &l, const pat_ranking &r) {
            if (l.score == r.score)
            {
                return l.number < r.number;
            }

            return l.score > r.score;
        });

        std::uint8_t score = b.begin()->score - 1;
        std::uint64_t rank = 0;
        std::uint64_t rank1 = 0;
        std::for_each(b.begin(), b.end(), [&score, &rank1, &rank](pat_ranking &l) {
            rank1++;
            if (l.score != score)
            {
                l.local_rank = rank1;
                rank = rank1;
            }
            else
            {
                l.local_rank = rank;
            }

            score = l.score;
        });

        all.insert(all.end(), b.begin(), b.end());
    }

    std::sort(all.begin(), all.end(), [](const pat_ranking &l, const pat_ranking &r) {
        if (l.score == r.score)
        {
            return l.number < r.number;
        }

        return l.score > r.score;
    });

    std::uint8_t score = all.begin()->score - 1;
    std::uint32_t rank = 0;
    std::uint32_t rank1 = 0;
    std::cout << all.size() << std::endl;
    std::for_each(all.begin(), all.end(), [&score, &rank, &rank1](const pat_ranking &l) {
        rank1++;
        if (l.score != score)
        {
            std::printf("%013" PRIu64 " %" SCNu8 " %" SCNu8 " %" SCNu8 "\n", l.number, rank1, l.location_number, l.local_rank);
            rank = rank1;
        }
        else
        {
            std::printf("%013" PRIu64 " %" SCNu8 " %" SCNu8 " %" SCNu8 "\n", l.number, (rank), l.location_number, l.local_rank);
        }
        score = l.score;
    });
    return 0;
}