#include <algorithm>
#include <set>
#include <vector>
#include "catch.hpp"

#include "pipes/insert.hpp"

TEST_CASE("insert")
{
    std::vector<int> v = {1, 3, -4, 2, 7, 10, 8};
    std::set<int> expected = { -4, 1, 2, 3, 7, 8, 10 };
    std::set<int> results;
    std::copy(begin(v), end(v), pipes::insert(results));
    
    REQUIRE((results == expected));
}

TEST_CASE("insert should not insert existing values")
{
    std::vector<int> v = {1, 3, -4, 2, 7, 10, 8};
    std::set<int> expected = { -4, 1, 2, 3, 7, 8, 10 };
    std::set<int> results = { 3 };
    std::copy(begin(v), end(v), pipes::insert(results));
    
    REQUIRE((results == expected));
}

TEST_CASE("insert's iterator category should be std::output_iterator_tag")
{
    std::set<int> results;
    static_assert(std::is_same<decltype(pipes::insert(results))::iterator_category,
                  std::output_iterator_tag>::value,
                  "iterator category should be std::output_iterator_tag");
}

TEST_CASE("insert::operator=")
{
    auto results1 = std::set<int>{};
    auto insert1 = pipes::insert(results1);
    auto results2 = std::set<int>{};
    auto insert2 = pipes::insert(results2);

    insert2 = insert1;
    pipes::send(0, insert2);
    REQUIRE(results1.size() == 1);
    REQUIRE(results2.size() == 0);
}
