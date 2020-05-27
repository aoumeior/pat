#include <string>
#include <vector>
#include <cstdio>
#include <cinttypes>
#include <cstdint>
#include <iostream>

struct book
{
    std::int32_t id;
    std::string book_title;
    std::string author;
    std::vector<std::string> key_word;
    std::string publisher;
    std::string publisher_year;
    std::string key_words;
};

int main(int argc, char const *argv[])
{
    std::int32_t the_total_number_of_books;
    std::scanf("%" SCNi32, &the_total_number_of_books);
    std::vector<book> books(the_total_number_of_books);

    for (auto &b : books)
    {
        scanf("%" SCNi32, &b.id);
        std::cin >> b.book_title;
        std::cin >> b.author;
        std::cin >> b.key_words;
        std::cin >> b.publisher;
        std::cin >> b.publisher_year;
    }

    std::int32_t the_number_of_users_search_queries;
    std::scanf("%" SCNi32, &the_number_of_users_search_queries);

    return 0;
}
