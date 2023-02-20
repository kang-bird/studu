#include <gtest/gtest.h>
#include "vector.cpp"
#include "array.cpp"
#include "stack.cpp"
#include "queue.cpp"
#include "set.cpp"
#include "list.cpp"
#include "multiset.cpp"
#include "map.cpp"

#include <map>
#include <set>
#include <array>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <algorithm>


/* --------------------------LIST TESTS --------------------------*/

template <class T>
bool equel_list(study::list<T> list, std::list<T> std_list) {
    bool res = true;
    if ((list.size() != std_list.size()) || (list.empty() != std_list.empty()))
        res = false;
    if (res != false) {
        typename study::list<T>::iterator it = list.begin();
        typename std::list<T>::iterator std_it = std_list.begin();
        while (std_it != std_list.end() && res == true) {
            if (*it != *std_it)
                res = false;
            ++it;
            ++std_it;
        }
    }
    return res;
}

TEST(list, default_constructor) {
    study::list<int> list;
    std::list<int> std_list;
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<double> list1;
    std::list<double> std_list1;
    EXPECT_TRUE(equel_list(list1, std_list1));

    study::list<std::string> list2;
    std::list<std::string> std_list2;
    EXPECT_TRUE(equel_list(list2, std_list2));

    study::list<char> list3;
    std::list<char> std_list3;
    EXPECT_TRUE(equel_list(list3, std_list3));

    study::list<std::pair<int, double>> list4;
    std::list<std::pair<int, double>> std_list4;
    EXPECT_TRUE(equel_list(list4, std_list4));

    study::list<std::set<int>> list5;
    std::list<std::set<int>> std_list5;
    EXPECT_TRUE(equel_list(list5, std_list5));
}

TEST(list, init_constructor) {
    study::list<int> list(2);
    std::list<int> std_list(2);
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<double> list1(0);
    std::list<double> std_list1(0);
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<std::string> list2(1);
    std::list<std::string> std_list2(1);
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<char> list3(8);
    std::list<char> std_list3(8);
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<std::pair<int, double>> list4(16);
    std::list<std::pair<int, double>> std_list4(16);
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<std::set<int>> list5(3);
    std::list<std::set<int>> std_list5(3);
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<int> list6(2);
    std::list<int> std_list6(3);
    EXPECT_FALSE(equel_list(list6, std_list6));
}

TEST(list, initializer_list_constructor) {
    study::list<int> list{1, 2, 3};
    std::list<int> std_list{1, 2, 3};
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<double> list1{1.4, 2.0008, 3.122345, 123345};
    std::list<double> std_list1{1.4, 2.0008, 3.122345, 123345};
    EXPECT_TRUE(equel_list(list1, std_list1));

    study::list<std::string> list2{"Hello", "World!"};
    std::list<std::string> std_list2{"Hello", "World!"};
    EXPECT_TRUE(equel_list(list2, std_list2));

    study::list<char> list3{'I', ' ', 'l', 'o', 'v', 'e', ' ', 'c', 'o', 'd', 'e', '!'};
    std::list<char> std_list3{'I', ' ', 'l', 'o', 'v', 'e', ' ', 'c', 'o', 'd', 'e', '!'};
    EXPECT_TRUE(equel_list(list3, std_list3));

    study::list<std::pair<int, double>> list4{{42, 3.1415}, {89, 21}};
    std::list<std::pair<int, double>> std_list4{{42, 3.1415}, {89, 21}};
    EXPECT_TRUE(equel_list(list4, std_list4));

    study::list<std::string> list6{"Hello", "Me!"};
    std::list<std::string> std_list6{"Hello", "World!"};
    EXPECT_FALSE(equel_list(list6, std_list6));
}

TEST(list, copy_constructor) {
    study::list<char> list{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::list<char> std_list{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    study::list<char> list_copy(list);
    std::list<char> std_list_copy(std_list);
    EXPECT_TRUE(equel_list(list, std_list));
    EXPECT_TRUE(equel_list(list_copy, std_list_copy));

    study::list<int> list1{1, 2, 3};
    std::list<int> std_list1{1, 2, 3};
    study::list<int> list1_copy(list1);
    std::list<int> std_list1_copy(std_list1);
    EXPECT_TRUE(equel_list(list1, std_list1));
    EXPECT_TRUE(equel_list(list1_copy, std_list1_copy));
}

TEST(list, move_constructor) {
    study::list<int> list{1, 2, 3};
    std::list<int> std_list{1, 2, 3};
    study::list<int> list_move(std::move(list));
    std::list<int> std_list_move(std::move(std_list));
    EXPECT_TRUE(equel_list(list_move, std_list_move));
    ASSERT_EQ(list.size(), std_list.size());
    ASSERT_EQ(list.empty(), std_list.empty());

    study::list<char> list1{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::list<char> std_list1{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    study::list<char> list1_move(std::move(list1));
    std::list<char> std_list1_move(std::move(std_list1));
    EXPECT_TRUE(equel_list(list1_move, std_list1_move));
    ASSERT_EQ(list1.size(), std_list1.size());
    ASSERT_EQ(list1.empty(), std_list1.empty());
}

TEST(list, move_to_less_buffer) {
    study::list<int> list{123, 34567, 6789634, 34567986, 0, 1, 56};
    std::list<int> std_list{123, 34567, 6789634, 34567986, 0, 1, 56};
    study::list<int> list_move{1, 2};
    std::list<int> std_list_move{1, 2};
    list_move = std::move(list);
    std_list_move = std::move(std_list);
    EXPECT_TRUE(equel_list(list_move, std_list_move));
    ASSERT_EQ(list.size(), std_list.size());
    ASSERT_EQ(list.empty(), std_list.empty());
}

TEST(list, move_to_more_buffer) {
    study::list<int> list{1, 2};
    std::list<int> std_list{1, 2};
    study::list<int> list_move{123, 34567, 6789634, 34567986, 0, 1, 56};
    std::list<int> std_list_move{123, 34567, 6789634, 34567986, 0, 1, 56};
    list_move = std::move(list);
    std_list_move = std::move(std_list);
    EXPECT_TRUE(equel_list(list_move, std_list_move));
    ASSERT_EQ(list.size(), std_list.size());
    ASSERT_EQ(list.empty(), std_list.empty());
}

TEST(list, front_function) {
    study::list<char> list{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::list<char> std_list{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    EXPECT_TRUE(equel_list(list, std_list));
    ASSERT_EQ(list.front(), std_list.front());

    study::list<std::pair<int, double>> list2{{42, 3.1415}, {89, 21}};
    std::list<std::pair<int, double>> std_list2{{42, 3.1415}, {89, 21}};
    EXPECT_TRUE(equel_list(list2, std_list2));
    ASSERT_EQ(list2.front(), std_list2.front());

    study::list<std::string> list3{"Hello", "World!"};
    std::list<std::string> std_list3{"Hello", "World!"};
    EXPECT_TRUE(equel_list(list3, std_list3));
    ASSERT_EQ(list3.front(), std_list3.front());
}


TEST(list, back_function) {
    study::list<char> list{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::list<char> std_list{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    EXPECT_TRUE(equel_list(list, std_list));
    ASSERT_EQ(list.back(), std_list.back());

    study::list<std::pair<int, double>> list2{{42, 3.1415}, {89, 21}};
    std::list<std::pair<int, double>> std_list2{{42, 3.1415}, {89, 21}};
    EXPECT_TRUE(equel_list(list2, std_list2));
    ASSERT_EQ(list2.back(), std_list2.back());

    study::list<std::string> list3{"Hello", "World!"};
    std::list<std::string> std_list3{"Hello", "World!"};
    EXPECT_TRUE(equel_list(list3, std_list3));
    ASSERT_EQ(list3.back(), std_list3.back());
}

TEST(list, const_iterator_access) {
    study::list<char> list{'S', 'e', 'g', 'm', 'e', 'n', 't', 'a', 't', 'i', 'o', 'n'};
    std::list<char> std_list{'S', 'e', 'g', 'm', 'e', 'n', 't', 'a', 't', 'i', 'o', 'n'};
    study::list<char>::const_iterator it = list.cbegin();
    std::list<char>::const_iterator std_it = std_list.cbegin();
    while (it != list.end()) {
        EXPECT_TRUE(*it == *std_it);
        ++it;
        ++std_it;
    }
    study::list<char> list1{'f', 'a', 'u', 'l', 't'};
    std::list<char> std_list1{'f', 'a', 'u', 'l', 't'};
    study::list<char>::const_iterator it1 = list1.cend();
    std::list<char>::const_iterator std_it1 = std_list1.cend();
    --it1;
    --std_it1;
    while (it1 != list1.begin()) {
        EXPECT_TRUE(*it1 == *std_it1);
        --it1;
        --std_it1;
    }
}

TEST(list, citerator_access) {
    study::list<char> list{'S', 'e', 'g', 'm', 'e', 'n', 't', 'a', 't', 'i', 'o', 'n'};
    std::list<char> std_list{'S', 'e', 'g', 'm', 'e', 'n', 't', 'a', 't', 'i', 'o', 'n'};
    study::list<char>::iterator it = list.begin();
    std::list<char>::iterator std_it = std_list.begin();
    while (it != list.end()) {
        EXPECT_TRUE(*it == *std_it);
        ++it;
        ++std_it;
    }
    list.push_back('!');
    std_list.push_back('!');
    ++it;
    ++std_it;
    EXPECT_TRUE(*it == *std_it);
    study::list<char> list1{'f', 'a', 'u', 'l', 't'};
    std::list<char> std_list1{'f', 'a', 'u', 'l', 't'};
    study::list<char>::iterator it1 = list1.end();
    std::list<char>::iterator std_it1 = std_list1.end();
    --it1;
    --std_it1;
    while (it1 != list1.begin()) {
        EXPECT_TRUE(*it1 == *std_it1);
        --it1;
        --std_it1;
    }
    list1.push_back('!');
    std_list1.push_back('!');
    --it1;
    --std_it1;
    --it1;
    --std_it1;
    EXPECT_TRUE(*it1 == *std_it1);
}


TEST(list, max_sizef_function) {
    study::list<int> list;
    std::list<int> std_list;
    ASSERT_EQ(list.max_size(), std_list.max_size());
    study::list<std::string> list1{"Hello", "World!"};
    std::list<std::string> std_list1{"Hello", "World!"};
    ASSERT_EQ(list1.max_size(), std_list1.max_size());
}

TEST(list, clear_function) {
    study::list<std::string> list{"Hello", "World!"};
    std::list<std::string> std_list{"Hello", "World!"};
    list.clear();
    std_list.clear();
    ASSERT_EQ(list.size(), std_list.size());
    ASSERT_EQ(list.empty(), std_list.empty());
}

TEST(list, insert_function) {
    study::list<std::string> list{"Hello,", "World!"};
    std::list<std::string> std_list{"Hello,", "World!"};
    study::list<std::string>::iterator it = list.begin();
    std::list<std::string>::iterator std_it = std_list.begin();
    it = list.insert(it, "Hi or");
    std_it = std_list.insert(std_it, "Hi or");
    ASSERT_EQ(*it, *std_it);
    EXPECT_TRUE(equel_list(list, std_list));

    it = list.begin();
    std_it = std_list.begin();
    ++it;
    ++std_it;
    ++it;
    ++std_it;
    it = list.insert(it, "my dear");
    std_it = std_list.insert(std_it, "my dear");
    EXPECT_TRUE(equel_list(list, std_list));

    it = list.end();
    std_it = std_list.end();
    it = list.insert(it, "Be happy");
    std_it = std_list.insert(std_it, "Be happy");
    EXPECT_TRUE(equel_list(list, std_list));
}

TEST(list, erase_function) {
    study::list<int> list{1, 2, 3, 4, 5, 6, 7, 9, 8, 10};
    std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 9, 8, 10};
    study::list<int>::iterator it = list.begin();
    std::list<int>::iterator std_it = std_list.begin();
    list.erase(it);
    std_list.erase(std_it);
    EXPECT_TRUE(equel_list(list, std_list));

    it = list.end();
    std_it = std_list.end();
    --it;
    --std_it;
    list.erase(it);
    std_list.erase(std_it);
    EXPECT_TRUE(equel_list(list, std_list));

    it = list.begin();
    std_it = std_list.begin();
    ++it;
    ++std_it;
    ++it;
    ++std_it;
    ++it;
    ++std_it;
    list.erase(it);
    std_list.erase(std_it);
    EXPECT_TRUE(equel_list(list, std_list));
}

TEST(list, pop_back_function) {
    study::list<std::string> list{"I'm", "glad", "to see", "you"};
    std::list<std::string> std_list{"I'm", "glad", "to see", "you"};
    list.pop_back();
    std_list.pop_back();
    EXPECT_TRUE(equel_list(list, std_list));
    list.pop_back();
    std_list.pop_back();
    EXPECT_TRUE(equel_list(list, std_list));
    list.pop_back();
    std_list.pop_back();
    EXPECT_TRUE(equel_list(list, std_list));
    list.pop_back();
    std_list.pop_back();
    EXPECT_TRUE(equel_list(list, std_list));
}

TEST(list, push_back_function) {
    study::list<std::string> list;
    std::list<std::string> std_list;
    list.push_back("I'm");
    std_list.push_back("I'm");
    EXPECT_TRUE(equel_list(list, std_list));
    list.push_back("glad");
    std_list.push_back("glad");
    EXPECT_TRUE(equel_list(list, std_list));
    list.push_back("to see");
    std_list.push_back("to see");
    EXPECT_TRUE(equel_list(list, std_list));
    list.push_back("you");
    std_list.push_back("you");
    EXPECT_TRUE(equel_list(list, std_list));
}

TEST(list, pop_front_function) {
    study::list<std::string> list{"I'm", "glad", "to see", "you"};
    std::list<std::string> std_list{"I'm", "glad", "to see", "you"};
    list.pop_front();
    std_list.pop_front();
    EXPECT_TRUE(equel_list(list, std_list));
    list.pop_front();
    std_list.pop_front();
    EXPECT_TRUE(equel_list(list, std_list));
    list.pop_front();
    std_list.pop_front();
    EXPECT_TRUE(equel_list(list, std_list));
    list.pop_front();
    std_list.pop_front();
    EXPECT_TRUE(equel_list(list, std_list));
}

TEST(list, push_front_function) {
    study::list<std::string> list;
    std::list<std::string> std_list;
    list.push_front("I'm");
    std_list.push_front("I'm");
    EXPECT_TRUE(equel_list(list, std_list));
    list.push_front("glad");
    std_list.push_front("glad");
    EXPECT_TRUE(equel_list(list, std_list));
    list.push_front("to see");
    std_list.push_front("to see");
    EXPECT_TRUE(equel_list(list, std_list));
    list.push_front("you");
    std_list.push_front("you");
    EXPECT_TRUE(equel_list(list, std_list));
}

TEST(list, swap_function) {
    study::list<char> list{'l', 'o', 'v', 'e'};
    std::list<char> std_list{'l', 'o', 'v', 'e'};
    study::list<char> list_swap{'o'};
    std::list<char> std_list_swap{'o'};
    list.swap(list_swap);
    std_list.swap(std_list_swap);
    EXPECT_TRUE(equel_list(list, std_list));
    EXPECT_TRUE(equel_list(list_swap, std_list_swap));

    study::list<char> list1{'o'};
    std::list<char> std_list1{'o'};
    study::list<char> list1_swap{'l', 'o', 'v', 'e'};
    std::list<char> std_list1_swap{'l', 'o', 'v', 'e'};
    list1.swap(list1_swap);
    std_list1.swap(std_list1_swap);
    EXPECT_TRUE(equel_list(list1, std_list1));
    EXPECT_TRUE(equel_list(list1_swap, std_list1_swap));

    study::list<char> list2{'l', 'o', 'v', 'e'};
    std::list<char> std_list2{'l', 'o', 'v', 'e'};
    study::list<char> list2_swap;
    std::list<char> std_list2_swap;
    list2.swap(list2_swap);
    std_list2.swap(std_list2_swap);
    EXPECT_TRUE(equel_list(list2, std_list2));
    EXPECT_TRUE(equel_list(list2_swap, std_list2_swap));

    study::list<char> list3;
    std::list<char> std_list3;
    study::list<char> list3_swap{'l', 'o', 'v', 'e'};
    std::list<char> std_list3_swap{'l', 'o', 'v', 'e'};
    list3.swap(list3_swap);
    std_list3.swap(std_list3_swap);
    EXPECT_TRUE(equel_list(list3, std_list3));
    EXPECT_TRUE(equel_list(list3_swap, std_list3_swap));
}

TEST(list, sort_function) {
    study::list<double> list{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    std::list<double> std_list{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    list.sort();
    std_list.sort();
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<double> list1{8};
    std::list<double> std_list1{8};
    list1.sort();
    std_list1.sort();
    EXPECT_TRUE(equel_list(list1, std_list1));

    study::list<char> list2{'c', 'a', 'd', 'b'};
    std::list<char> std_list2{'c', 'a', 'd', 'b'};
    list2.sort();
    std_list2.sort();
    EXPECT_TRUE(equel_list(list2, std_list2));

    study::list<std::string> list3{"to see", "glad", "you", "I'm"};
    std::list<std::string> std_list3{"to see", "glad", "you", "I'm"};
    list3.sort();
    std_list3.sort();
    EXPECT_TRUE(equel_list(list3, std_list3));
}

TEST(list, merge_function) {
    study::list<double> list{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    std::list<double> std_list{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    study::list<double> list_merge{1, 2, 9};
    std::list<double> std_list_merge{1, 2, 9};
    list.merge(list_merge);
    std_list.merge(std_list_merge);
    EXPECT_TRUE(equel_list(list, std_list));
    EXPECT_TRUE(equel_list(list_merge, std_list_merge));
    study::list<double> list1{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    std::list<double> std_list1{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    study::list<double> list1_merge{1, 2, 9};
    std::list<double> std_list1_merge{1, 2, 9};
    list1.sort();
    std_list1.sort();
    list1.merge(list1_merge);
    std_list1.merge(std_list1_merge);
    EXPECT_TRUE(equel_list(list1, std_list1));
    EXPECT_TRUE(equel_list(list1_merge, std_list1_merge));

    study::list<double> list2{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    std::list<double> std_list2{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    study::list<double> list2_merge;
    std::list<double> std_list2_merge;
    list2.sort();
    std_list2.sort();
    list2.merge(list2_merge);
    std_list2.merge(std_list2_merge);
    EXPECT_TRUE(equel_list(list2, std_list2));
    EXPECT_TRUE(equel_list(list2_merge, std_list2_merge));

    study::list<double> list3;
    std::list<double> std_list3;
    study::list<double> list3_merge{1, 2, 9};
    std::list<double> std_list3_merge{1, 2, 9};
    list3.merge(list3_merge);
    std_list3.merge(std_list3_merge);
    EXPECT_TRUE(equel_list(list3, std_list3));
    EXPECT_TRUE(equel_list(list3_merge, std_list3_merge));

    study::list<double> list4{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    std::list<double> std_list4{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    study::list<double> list4_merge{8, 9, 9};
    std::list<double> std_list4_merge{8, 9, 9};
    list4.merge(list4_merge);
    std_list4.merge(std_list4_merge);
    EXPECT_TRUE(equel_list(list4, std_list4));
    EXPECT_TRUE(equel_list(list4_merge, std_list4_merge));

    study::list<double> list5{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    std::list<double> std_list5{ 8, 4.9, 5, 9, 1.2, 1, 3, 2, 6, 4 };
    study::list<double> list5_merge{1, 1, 1};
    std::list<double> std_list5_merge{1, 1, 1};
    list5.merge(list5_merge);
    std_list5.merge(std_list5_merge);
    EXPECT_TRUE(equel_list(list5, std_list5));
    EXPECT_TRUE(equel_list(list5_merge, std_list5_merge));
}

TEST(list, function_splice) {
    study::list<std::string> list{"Hello,", "World!"};
    std::list<std::string> std_list{"Hello,", "World!"};
    study::list<std::string> list_splice{"I'm", "glad", "to see", "you"};
    std::list<std::string> std_list_splice{"I'm", "glad", "to see", "you"};
    study::list<std::string>::const_iterator it = list.cbegin();
    std::list<std::string>::const_iterator std_it = std_list.cbegin();
    ++it;
    ++std_it;
    list.splice(it, list_splice);
    std_list.splice(std_it, std_list_splice);
    EXPECT_TRUE(equel_list(list, std_list));
    EXPECT_TRUE(equel_list(list_splice, std_list_splice));

    study::list<std::string> list1{"I'm", "glad", "to see", "you"};
    std::list<std::string> std_list1{"I'm", "glad", "to see", "you"};
    study::list<std::string> list1_splice;
    std::list<std::string> std_list1_splice;
    study::list<std::string>::const_iterator it1 = list1_splice.cend();
    std::list<std::string>::const_iterator std_it1 = std_list1_splice.cend();
    list1.splice(it1, list1_splice);
    std_list1.splice(std_it1, std_list1_splice);
    EXPECT_TRUE(equel_list(list1, std_list1));
    EXPECT_TRUE(equel_list(list1_splice, std_list1_splice));
}

TEST(list, reverse_function) {
    study::list<int> list{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8, 9};
    list.reverse();
    std_list.reverse();
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<int> list2{2};
    std::list<int> std_list2{2};
    list2.reverse();
    std_list2.reverse();
    EXPECT_TRUE(equel_list(list2, std_list2));

    study::list<int> list3;
    std::list<int> std_list3;
    list3.reverse();
    std_list3.reverse();
    EXPECT_TRUE(equel_list(list3, std_list3));
}

TEST(list, unique_function) {
    study::list<double> list{11, 1.1, 1, 3, 4, 3, 3, 5, 21};
    std::list<double> std_list{11, 1.1, 1, 3, 4, 3, 3, 5, 21};
    list.unique();
    std_list.unique();
    EXPECT_TRUE(equel_list(list, std_list));

    study::list<int> list1{1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::list<int> std_list1{1, 1, 1, 1, 1, 1, 1, 1, 1};
    list1.unique();
    std_list1.unique();
    EXPECT_TRUE(equel_list(list1, std_list1));

    study::list<int> list2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> std_list2{1, 2, 3, 4, 5, 6, 7, 8, 9};
    list2.unique();
    std_list2.unique();
    EXPECT_TRUE(equel_list(list2, std_list2));

    study::list<int> list3;
    std::list<int> std_list3;
    list3.unique();
    std_list3.unique();
    EXPECT_TRUE(equel_list(list3, std_list3));

    study::list<int> list4{2};
    std::list<int> std_list4{2};
    list4.unique();
    std_list4.unique();
    EXPECT_TRUE(equel_list(list4, std_list4));
}

/* --------------------------VECTOR TESTS --------------------------*/
template <class T>
bool equel_vector(study::vector<T> vector, std::vector<T> std_vector) {
    bool res = true;
    if ((vector.size() != std_vector.size()) || (vector.empty() != std_vector.empty()))
        res = false;
    if (res != false) {
        for (size_t i = 0; i < vector.size(); i++)
            if (std_vector[i] != vector[i])
                            res = false;
    }
    return res;
}

template <class T>
bool equel_vector_full(study::vector<T> vector, std::vector<T> std_vector) {
    bool res = true;
    if (!equel_vector(vector, std_vector))
        res = false;
    if (vector.capacity() != std_vector.capacity())
        res = false;
    return res;
}

TEST(vector, default_constructor) {
    study::vector<int> vector;
    std::vector<int> std_vector;
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    study::vector<double> vector1;
    std::vector<double> std_vector1;
    EXPECT_TRUE(equel_vector_full(vector1, std_vector1));

    study::vector<std::string> vector2;
    std::vector<std::string> std_vector2;
    EXPECT_TRUE(equel_vector_full(vector2, std_vector2));

    study::vector<char> vector3;
    std::vector<char> std_vector3;
    EXPECT_TRUE(equel_vector_full(vector3, std_vector3));

    study::vector<std::pair<int, double>> vector4;
    std::vector<std::pair<int, double>> std_vector4;
    EXPECT_TRUE(equel_vector_full(vector4, std_vector4));

    study::vector<std::set<int>> vector5;
    std::vector<std::set<int>> std_vector5;
    EXPECT_TRUE(equel_vector_full(vector5, std_vector5));
}

TEST(vector, init_constructor) {
    study::vector<int> vector(2);
    std::vector<int> std_vector(2);
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    study::vector<double> vector1(0);
    std::vector<double> std_vector1(0);
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    study::vector<std::string> vector2(1);
    std::vector<std::string> std_vector2(1);
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    study::vector<char> vector3(8);
    std::vector<char> std_vector3(8);
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    study::vector<std::pair<int, double>> vector4(16);
    std::vector<std::pair<int, double>> std_vector4(16);
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    study::vector<std::set<int>> vector5(3);
    std::vector<std::set<int>> std_vector5(3);
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    study::vector<int> vector6(2);
    std::vector<int> std_vector6(3);
    EXPECT_FALSE(equel_vector_full(vector6, std_vector6));
}

TEST(vector, initializer_vector_constructor) {
    study::vector<int> vector{1, 2, 3};
    std::vector<int> std_vector{1, 2, 3};
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    study::vector<double> vector1{1.4, 2.0008, 3.122345, 123345};
    std::vector<double> std_vector1{1.4, 2.0008, 3.122345, 123345};
    EXPECT_TRUE(equel_vector_full(vector1, std_vector1));

    study::vector<std::string> vector2{"Hello", "World!"};
    std::vector<std::string> std_vector2{"Hello", "World!"};
    EXPECT_TRUE(equel_vector_full(vector2, std_vector2));

    study::vector<char> vector3{'I', ' ', 'l', 'o', 'v', 'e', ' ', 'c', 'o', 'd', 'e', '!'};
    std::vector<char> std_vector3{'I', ' ', 'l', 'o', 'v', 'e', ' ', 'c', 'o', 'd', 'e', '!'};
    EXPECT_TRUE(equel_vector_full(vector3, std_vector3));

    study::vector<std::pair<int, double>> vector4{{42, 3.1415}, {89, 21}};
    std::vector<std::pair<int, double>> std_vector4{{42, 3.1415}, {89, 21}};
    EXPECT_TRUE(equel_vector_full(vector4, std_vector4));

    study::vector<std::string> vector6{"Hello", "Me!"};
    std::vector<std::string> std_vector6{"Hello", "World!"};
    EXPECT_FALSE(equel_vector_full(vector6, std_vector6));
}

TEST(vector, copy_constructor) {
    study::vector<char> vector{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::vector<char> std_vector{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    study::vector<char> vector_copy(vector);
    std::vector<char> std_vector_copy(std_vector);
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
    EXPECT_TRUE(equel_vector_full(vector_copy, std_vector_copy));

    study::vector<int> vector1{1, 2, 3};
    std::vector<int> std_vector1{1, 2, 3};
    study::vector<int> vector1_copy(vector1);
    std::vector<int> std_vector1_copy(std_vector1);
    EXPECT_TRUE(equel_vector_full(vector1, std_vector1));
    EXPECT_TRUE(equel_vector_full(vector1_copy, std_vector1_copy));
}

TEST(vector, move_constructor) {
    study::vector<int> vector{1, 2, 3};
    std::vector<int> std_vector{1, 2, 3};
    study::vector<int> vector_move(std::move(vector));
    std::vector<int> std_vector_move(std::move(std_vector));
    EXPECT_TRUE(equel_vector_full(vector_move, std_vector_move));
    ASSERT_EQ(vector.size(), std_vector.size());
    ASSERT_EQ(vector.empty(), std_vector.empty());

    study::vector<char> vector1{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::vector<char> std_vector1{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    study::vector<char> vector1_move(std::move(vector1));
    std::vector<char> std_vector1_move(std::move(std_vector1));
    EXPECT_TRUE(equel_vector_full(vector1_move, std_vector1_move));
    ASSERT_EQ(vector1.size(), std_vector1.size());
    ASSERT_EQ(vector1.empty(), std_vector1.empty());
}

TEST(vector, move_to_less_buffer) {
    study::vector<int> vector{123, 34567, 6789634, 34567986, 0, 1, 56};
    std::vector<int> std_vector{123, 34567, 6789634, 34567986, 0, 1, 56};
    study::vector<int> vector_move{1, 2};
    std::vector<int> std_vector_move{1, 2};
    vector_move = std::move(vector);
    std_vector_move = std::move(std_vector);
    EXPECT_TRUE(equel_vector_full(vector_move, std_vector_move));
    ASSERT_EQ(vector.size(), std_vector.size());
    ASSERT_EQ(vector.empty(), std_vector.empty());
}

TEST(vector, move_to_more_buffer) {
    study::vector<int> vector{1, 2};
    std::vector<int> std_vector{1, 2};
    study::vector<int> vector_move{123, 34567, 6789634, 34567986, 0, 1, 56};
    std::vector<int> std_vector_move{123, 34567, 6789634, 34567986, 0, 1, 56};
    vector_move = std::move(vector);
    std_vector_move = std::move(std_vector);
    EXPECT_TRUE(equel_vector_full(vector_move, std_vector_move));
    ASSERT_EQ(vector.size(), std_vector.size());
    ASSERT_EQ(vector.empty(), std_vector.empty());
}


TEST(vector, front_function) {
    study::vector<char> vector{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::vector<char> std_vector{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
    ASSERT_EQ(vector.front(), std_vector.front());

    study::vector<std::pair<int, double>> vector2{{42, 3.1415}, {89, 21}};
    std::vector<std::pair<int, double>> std_vector2{{42, 3.1415}, {89, 21}};
    EXPECT_TRUE(equel_vector_full(vector2, std_vector2));
    ASSERT_EQ(vector2.front(), std_vector2.front());

    study::vector<std::string> vector3{"Hello", "World!"};
    std::vector<std::string> std_vector3{"Hello", "World!"};
    EXPECT_TRUE(equel_vector_full(vector3, std_vector3));
    ASSERT_EQ(vector3.front(), std_vector3.front());
}


TEST(vector, back_function) {
    study::vector<char> vector{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::vector<char> std_vector{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
    ASSERT_EQ(vector.back(), std_vector.back());

    study::vector<std::pair<int, double>> vector2{{42, 3.1415}, {89, 21}};
    std::vector<std::pair<int, double>> std_vector2{{42, 3.1415}, {89, 21}};
    EXPECT_TRUE(equel_vector_full(vector2, std_vector2));
    ASSERT_EQ(vector2.back(), std_vector2.back());

    study::vector<std::string> vector3{"Hello", "World!"};
    std::vector<std::string> std_vector3{"Hello", "World!"};
    EXPECT_TRUE(equel_vector_full(vector3, std_vector3));
    ASSERT_EQ(vector3.back(), std_vector3.back());
}

TEST(vector, const_iterator_access) {
    study::vector<char> vector{'S', 'e', 'g', 'm', 'e', 'n', 't', 'a', 't', 'i', 'o', 'n'};
    std::vector<char> std_vector{'S', 'e', 'g', 'm', 'e', 'n', 't', 'a', 't', 'i', 'o', 'n'};
    study::vector<char>::const_iterator it = vector.begin();
    std::vector<char>::const_iterator std_it = std_vector.begin();
    while (it != vector.end()) {
        EXPECT_TRUE(*it == *std_it);
        ++it;
        ++std_it;
    }
    study::vector<char> vector1{'f', 'a', 'u', 'l', 't'};
    std::vector<char> std_vector1{'f', 'a', 'u', 'l', 't'};
    study::vector<char>::const_iterator it1 = vector1.end();
    std::vector<char>::const_iterator std_it1 = std_vector1.end();
    --it1;
    --std_it1;
    while (it1 != vector1.begin()) {
        EXPECT_TRUE(*it1 == *std_it1);
        --it1;
        --std_it1;
    }
    EXPECT_TRUE(*it1 == *std_it1);
}

TEST(vector, max_sizef_function) {
    study::vector<int> vector;
    std::vector<int> std_vector;
    ASSERT_EQ(vector.max_size(), std_vector.max_size());
    study::vector<std::string> vector1{"Hello", "World!"};
    std::vector<std::string> std_vector1{"Hello", "World!"};
    ASSERT_EQ(vector1.max_size(), std_vector1.max_size());
}

TEST(vector, clear_function) {
    study::vector<std::string> vector{"Hello", "World!"};
    std::vector<std::string> std_vector{"Hello", "World!"};
    vector.clear();
    std_vector.clear();
    ASSERT_EQ(vector.size(), std_vector.size());
    ASSERT_EQ(vector.empty(), std_vector.empty());
}

TEST(vector, insert_function) {
    study::vector<std::string> vector{"Hello,", "World!"};
    std::vector<std::string> std_vector{"Hello,", "World!"};
    study::vector<std::string>::iterator it = vector.begin();
    std::vector<std::string>::iterator std_it = std_vector.begin();
    it = vector.insert(it, "Hi or");
    std_it = std_vector.insert(std_it, "Hi or");
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    it = vector.begin();
    std_it = std_vector.begin();
    ++it;
    ++std_it;
    ++it;
    ++std_it;
    it = vector.insert(it, "my dear");
    std_it = std_vector.insert(std_it, "my dear");
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    it = vector.end();
    std_it = std_vector.end();
    it = vector.insert(it, "Be happy");
    std_it = std_vector.insert(std_it, "Be happy");
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
}

TEST(vector, erase_function) {
    study::vector<int> vector{1, 2, 3, 4, 5, 6, 7, 9, 8, 10};
    std::vector<int> std_vector{1, 2, 3, 4, 5, 6, 7, 9, 8, 10};
    study::vector<int>::iterator it = vector.begin();
    std::vector<int>::iterator std_it = std_vector.begin();
    vector.erase(it);
    std_vector.erase(std_it);
    ASSERT_EQ(vector.capacity(), std_vector.capacity());
    EXPECT_TRUE(equel_vector(vector, std_vector));

    it = vector.end();
    std_it = std_vector.end();
    --it;
    --std_it;
    vector.erase(it);
    std_vector.erase(std_it);
    ASSERT_EQ(vector.capacity(), std_vector.capacity());
    EXPECT_TRUE(equel_vector(vector, std_vector));

    it = vector.begin();
    std_it = std_vector.begin();
    ++it;
    ++std_it;
    ++it;
    ++std_it;
    ++it;
    ++std_it;
    vector.erase(it);
    std_vector.erase(std_it);
    ASSERT_EQ(vector.capacity(), std_vector.capacity());
    EXPECT_TRUE(equel_vector(vector, std_vector));
}

TEST(vector, pop_back_function) {
    study::vector<std::string> vector{"I'm", "glad", "to see", "you"};
    std::vector<std::string> std_vector{"I'm", "glad", "to see", "you"};
    vector.pop_back();
    std_vector.pop_back();
    ASSERT_EQ(vector.capacity(), std_vector.capacity());
    EXPECT_TRUE(equel_vector(vector, std_vector));
    vector.pop_back();
    std_vector.pop_back();
    ASSERT_EQ(vector.capacity(), std_vector.capacity());
    EXPECT_TRUE(equel_vector(vector, std_vector));
    vector.pop_back();
    std_vector.pop_back();
    ASSERT_EQ(vector.capacity(), std_vector.capacity());
    EXPECT_TRUE(equel_vector(vector, std_vector));
    vector.pop_back();
    std_vector.pop_back();
    ASSERT_EQ(vector.capacity(), std_vector.capacity());
    EXPECT_TRUE(equel_vector(vector, std_vector));
}

TEST(vector, push_back_function) {
    study::vector<std::string> vector;
    std::vector<std::string> std_vector;
    vector.push_back("I'm");
    std_vector.push_back("I'm");
    EXPECT_TRUE(equel_vector(vector, std_vector));
    vector.push_back("glad");
    std_vector.push_back("glad");
    EXPECT_TRUE(equel_vector(vector, std_vector));
    vector.push_back("to see");
    std_vector.push_back("to see");
    EXPECT_TRUE(equel_vector(vector, std_vector));
    vector.push_back("you");
    std_vector.push_back("you");
    EXPECT_TRUE(equel_vector(vector, std_vector));
}

TEST(vector, swap_function) {
    study::vector<char> vector{'l', 'o', 'v', 'e'};
    std::vector<char> std_vector{'l', 'o', 'v', 'e'};
    study::vector<char> vector_swap{'o'};
    std::vector<char> std_vector_swap{'o'};
    vector.swap(vector_swap);
    std_vector.swap(std_vector_swap);
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
    EXPECT_TRUE(equel_vector_full(vector_swap, std_vector_swap));

    study::vector<char> vector1{'o'};
    std::vector<char> std_vector1{'o'};
    study::vector<char> vector1_swap{'l', 'o', 'v', 'e'};
    std::vector<char> std_vector1_swap{'l', 'o', 'v', 'e'};
    vector1.swap(vector1_swap);
    std_vector1.swap(std_vector1_swap);
    EXPECT_TRUE(equel_vector_full(vector1, std_vector1));
    EXPECT_TRUE(equel_vector_full(vector1_swap, std_vector1_swap));

    study::vector<char> vector2{'l', 'o', 'v', 'e'};
    std::vector<char> std_vector2{'l', 'o', 'v', 'e'};
    study::vector<char> vector2_swap;
    std::vector<char> std_vector2_swap;
    vector2.swap(vector2_swap);
    std_vector2.swap(std_vector2_swap);
    EXPECT_TRUE(equel_vector_full(vector2, std_vector2));
    EXPECT_TRUE(equel_vector_full(vector2_swap, std_vector2_swap));

    study::vector<char> vector3;
    std::vector<char> std_vector3;
    study::vector<char> vector3_swap{'l', 'o', 'v', 'e'};
    std::vector<char> std_vector3_swap{'l', 'o', 'v', 'e'};
    vector3.swap(vector3_swap);
    std_vector3.swap(std_vector3_swap);
    EXPECT_TRUE(equel_vector_full(vector3, std_vector3));
    EXPECT_TRUE(equel_vector_full(vector3_swap, std_vector3_swap));
}

TEST(vector, reserve_function) {
    study::vector<char> vector_default;
    std::vector<char> std_vector_default;
    vector_default.reserve(130);
    std_vector_default.reserve(130);
    ASSERT_EQ(vector_default.capacity(), std_vector_default.capacity());
    EXPECT_TRUE(equel_vector(vector_default, std_vector_default));

    study::vector<int> vector{'h', 'i', '!'};
    std::vector<int> std_vector{'h', 'i', '!'};
    vector.reserve(50);
    std_vector.reserve(50);
    ASSERT_EQ(vector.capacity(), std_vector.capacity());
    EXPECT_TRUE(equel_vector(vector, std_vector));
}

TEST(vector, shrink_to_fit_function) {
    study::vector<int> vector{1, 2, 3};
    std::vector<int> std_vector{1, 2, 3};
    vector.reserve(50);
    std_vector.reserve(50);
    vector.shrink_to_fit();
    std_vector.shrink_to_fit();
    ASSERT_EQ(vector.capacity(), std_vector.capacity());
    EXPECT_TRUE(equel_vector(vector, std_vector));

    study::vector<int> vector1;
    std::vector<int> std_vector1;
    vector1.resize(100);
    std_vector1.resize(100);
    ASSERT_EQ(vector1.capacity(), std_vector1.capacity());
    EXPECT_TRUE(equel_vector(vector1, std_vector1));
    vector1.resize(50);
    std_vector1.resize(50);
    ASSERT_EQ(vector1.capacity(), std_vector1.capacity());
    EXPECT_TRUE(equel_vector(vector1, std_vector1));
    vector1.shrink_to_fit();
    std_vector1.shrink_to_fit();
    ASSERT_EQ(vector1.capacity(), std_vector1.capacity());
    EXPECT_TRUE(equel_vector(vector1, std_vector1));
    vector1.clear();
    std_vector1.clear();
    ASSERT_EQ(vector1.capacity(), std_vector1.capacity());
    EXPECT_TRUE(equel_vector(vector1, std_vector1));
    vector1.shrink_to_fit();
    std_vector1.shrink_to_fit();
    ASSERT_EQ(vector1.capacity(), std_vector1.capacity());
    EXPECT_TRUE(equel_vector(vector1, std_vector1));
    for (int i = 1000; i < 1300; ++i) {
        vector1.push_back(i);
        std_vector1.push_back(i);
    }
    ASSERT_EQ(vector1.capacity(), std_vector1.capacity());
    EXPECT_TRUE(equel_vector(vector1, std_vector1));
    vector1.shrink_to_fit();
    std_vector1.shrink_to_fit();
    ASSERT_EQ(vector1.capacity(), std_vector1.capacity());
    EXPECT_TRUE(equel_vector(vector1, std_vector1));
}

TEST(vector, iterators) {
    study::vector<int> vector{1, 2, 3};
    std::vector<int> std_vector{1, 2, 3};
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
    study::vector<int>::const_iterator it = vector.begin();
    study::vector<int>::const_iterator it_2 = vector.begin();
    std::vector<int>::const_iterator std_it = std_vector.begin();
    ASSERT_EQ(*it, *std_it);
    EXPECT_TRUE(*it == *std_it);
    EXPECT_TRUE(it == it_2);
    ++it;
    ++std_it;
    ASSERT_EQ(*it, *std_it);
    it = vector.end();
    std_it = std_vector.end();
    ASSERT_EQ(*it, *std_it);
    --it;
    --std_it;
    ASSERT_EQ(*it, *std_it);
    EXPECT_TRUE(it != it_2);
}

TEST(vector, function_at) {
    study::vector<std::string> vector{"access", "specified", "element", "with", "bounds", "checking"};
    std::vector<std::string> std_vector{"access", "specified", "element", "with", "bounds", "checking"};
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
    ASSERT_EQ(vector.at(0), std_vector.at(0));
    ASSERT_EQ(vector.at(1), std_vector.at(1));
    ASSERT_EQ(vector.at(2), std_vector.at(2));
    ASSERT_EQ(vector.at(3), std_vector.at(3));
    ASSERT_EQ(vector.at(4), std_vector.at(4));
    ASSERT_EQ(vector.at(5), std_vector.at(5));
}

TEST(vector, operator_square_brackets) {
    study::vector<std::string> vector{"access", "specified", "element"};
    std::vector<std::string> std_vector{"access", "specified", "element"};
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
    ASSERT_EQ(vector[0], std_vector[0]);
    ASSERT_EQ(vector[1], std_vector[1]);
    ASSERT_EQ(vector[2], std_vector[2]);
}

TEST(vector, function_data) {
    study::vector<int> vector_empty;
    std::vector<int> std_vector_empty;
    ASSERT_EQ(vector_empty.data(), nullptr);
    ASSERT_EQ(std_vector_empty.data(), nullptr);
    EXPECT_TRUE(equel_vector_full(vector_empty, std_vector_empty));
    study::vector<int> vector{1, 2234567, 21, 9874567};
    std::vector<int> std_vector{1, 2234567, 21, 9874567};
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
    ASSERT_NE(vector.data(), nullptr);
    ASSERT_NE(std_vector.data(), nullptr);
}

/* --------------------------ARRAY TESTS --------------------------*/


template <class T, std::size_t N>
bool equel_array(study::array<T, N> array, std::array<T, N> std_array) {
    bool res = true;
    if ((array.size() != std_array.size()) || (array.empty() != std_array.empty()))
        res = false;
    if (res != false) {
        for (size_t i = 0; i < array.size(); i++)
            if (std_array[i] != array[i])
                            res = false;
    }
    return res;
}


TEST(array, default_constructor) {
    study::array<int, 3> array;
    std::array<int, 3> std_array;
    ASSERT_EQ(array.size(), std_array.size());
    ASSERT_EQ(array.empty(), std_array.empty());

    study::array<double, 0> array1;
    std::array<double, 0> std_array1;
    ASSERT_EQ(array1.size(), std_array1.size());
    ASSERT_EQ(array1.empty(), std_array1.empty());

    study::array<std::string, 10> array2;
    std::array<std::string, 10> std_array2;
    ASSERT_EQ(array2.size(), std_array2.size());
    ASSERT_EQ(array2.empty(), std_array2.empty());

    study::array<char, 0> array3;
    std::array<char, 0> std_array3;
    ASSERT_EQ(array3.size(), std_array3.size());
    ASSERT_EQ(array3.empty(), std_array3.empty());

    study::array<std::pair<int, double>, 1> array4;
    std::array<std::pair<int, double>, 1> std_array4;
    ASSERT_EQ(array4.size(), std_array4.size());
    ASSERT_EQ(array4.empty(), std_array4.empty());

    study::array<std::set<int>, 24> array5;
    std::array<std::set<int>, 24> std_array5;
    ASSERT_EQ(array5.size(), std_array5.size());
    ASSERT_EQ(array5.empty(), std_array5.empty());
}

TEST(array, initializer_array_constructor) {
    study::array<int, 3> array{1, 2, 3};
    std::array<int, 3> std_array{1, 2, 3};
    EXPECT_TRUE(equel_array(array, std_array));

    study::array<double, 4> array1{1.4, 2.0008, 3.122345, 123345};
    std::array<double, 4> std_array1{1.4, 2.0008, 3.122345, 123345};
    EXPECT_TRUE(equel_array(array1, std_array1));

    study::array<std::string, 2> array2{"Hello", "World!"};
    std::array<std::string, 2> std_array2{"Hello", "World!"};
    EXPECT_TRUE(equel_array(array2, std_array2));

    study::array<char, 12> array3{'I', ' ', 'l', 'o', 'v', 'e', ' ', 'c', 'o', 'd', 'e', '!'};
    std::array<char, 12> std_array3{'I', ' ', 'l', 'o', 'v', 'e', ' ', 'c', 'o', 'd', 'e', '!'};
    EXPECT_TRUE(equel_array(array3, std_array3));

    study::array<std::string, 2> array6{"Hello", "Me!"};
    std::array<std::string, 2> std_array6{"Hello", "World!"};
    EXPECT_FALSE(equel_array(array6, std_array6));
}

TEST(array, copy_constructor) {
    study::array<char, 14> array{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::array<char, 14> std_array{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    study::array<char, 14> array_copy(array);
    std::array<char, 14> std_array_copy(std_array);
    EXPECT_TRUE(equel_array(array, std_array));
    EXPECT_TRUE(equel_array(array_copy, std_array_copy));

    study::array<int, 3> array1{1, 2, 3};
    std::array<int, 3> std_array1{1, 2, 3};
    study::array<int, 3> array1_copy(array1);
    std::array<int, 3> std_array1_copy(std_array1);
    EXPECT_TRUE(equel_array(array1, std_array1));
    EXPECT_TRUE(equel_array(array1_copy, std_array1_copy));
}

TEST(array, move_constructor) {
    study::array<int, 3> array{1, 2, 3};
    std::array<int, 3> std_array{1, 2, 3};
    EXPECT_TRUE(equel_array(array, std_array));
    study::array<int, 3> array_move(std::move(array));
    std::array<int, 3> std_array_move(std::move(std_array));
    EXPECT_TRUE(equel_array(array_move, std_array_move));
    EXPECT_TRUE(equel_array(array, std_array));

    study::array<char, 14> array1{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::array<char, 14> std_array1{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    study::array<char, 14> array1_move(std::move(array1));
    std::array<char, 14> std_array1_move(std::move(std_array1));
    EXPECT_TRUE(equel_array(array1, std_array1));
    EXPECT_TRUE(equel_array(array1_move, std_array1_move));

    study::array<int, 7> array2{123, 34567, 6789634, 34567986, 0, 1, 56};
    std::array<int, 7> std_array2{123, 34567, 6789634, 34567986, 0, 1, 56};
    study::array<int, 7> array2_move{1, 2};
    std::array<int, 7> std_array2_move{1, 2};
    array2_move = std::move(array2_move);
    array2_move = std::move(array2);
    array2_move = array2_move;
    std_array2_move = std::move(std_array2);
    EXPECT_TRUE(equel_array(array2_move, std_array2_move));
    ASSERT_EQ(array2.size(), std_array2.size());
    ASSERT_EQ(array2.empty(), std_array2.empty());
}

TEST(array, front_function) {
    study::array<char, 14> array{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::array<char, 14> std_array{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    EXPECT_TRUE(equel_array(array, std_array));
    ASSERT_EQ(array.front(), std_array.front());

    study::array<std::string, 2> array3{"Hello", "World!"};
    std::array<std::string, 2> std_array3{"Hello", "World!"};
    EXPECT_TRUE(equel_array(array3, std_array3));
    ASSERT_EQ(array3.front(), std_array3.front());
}


TEST(array, back_function) {
    study::array<char, 14> array{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    std::array<char, 14> std_array{'I', ' ', 'a', 'm', ' ', 'y', 'o', 'u', 'r', ' ', 'h', 'e', 'r', 'o'};
    EXPECT_TRUE(equel_array(array, std_array));
    ASSERT_EQ(array.back(), std_array.back());

    study::array<std::string, 2> array3{"Hello", "World!"};
    std::array<std::string, 2> std_array3{"Hello", "World!"};
    EXPECT_TRUE(equel_array(array3, std_array3));
    ASSERT_EQ(array3.back(), std_array3.back());
}

TEST(array, const_iterator_access) {
    study::array<char, 12> array{'S', 'e', 'g', 'm', 'e', 'n', 't', 'a', 't', 'i', 'o', 'n'};
    std::array<char, 12> std_array{'S', 'e', 'g', 'm', 'e', 'n', 't', 'a', 't', 'i', 'o', 'n'};
    study::array<char, 12>::const_iterator it = array.begin();
    std::array<char, 12>::const_iterator std_it = std_array.begin();
    while (it != array.end()) {
        EXPECT_TRUE(*it == *std_it);
        ++it;
        ++std_it;
    }

    study::array<char, 5> array1{'f', 'a', 'u', 'l', 't'};
    std::array<char, 5> std_array1{'f', 'a', 'u', 'l', 't'};
    study::array<char, 5>::const_iterator it1 = array1.end();
    std::array<char, 5>::const_iterator std_it1 = std_array1.end();
    --it1;
    --std_it1;
    while (it1 != array1.begin()) {
        EXPECT_TRUE(*it1 == *std_it1);
        --it1;
        --std_it1;
    }
    EXPECT_TRUE(*it1 == *std_it1);
}


TEST(array, max_sizef_function) {
    study::array<int, 0> array;
    std::array<int, 0> std_array;
    ASSERT_EQ(array.max_size(), std_array.max_size());

    study::array<std::string, 2> array1{"Hello", "World!"};
    std::array<std::string, 2> std_array1{"Hello", "World!"};
    ASSERT_EQ(array1.max_size(), std_array1.max_size());

    study::array<int, 4> array2;
    std::array<int, 4> std_array2;
    ASSERT_EQ(array2.max_size(), std_array2.max_size());
}

TEST(array, swap_function) {
    study::array<char, 4> array{'l', 'o', 'v', 'e'};
    std::array<char, 4> std_array{'l', 'o', 'v', 'e'};
    study::array<char, 4> array_swap{'o'};
    std::array<char, 4> std_array_swap{'o'};
    array.swap(array_swap);
    std_array.swap(std_array_swap);
    EXPECT_TRUE(equel_array(array, std_array));
    EXPECT_TRUE(equel_array(array_swap, std_array_swap));

    study::array<char, 4> array1{'o'};
    std::array<char, 4> std_array1{'o'};
    study::array<char, 4> array1_swap{'l', 'o', 'v', 'e'};
    std::array<char, 4> std_array1_swap{'l', 'o', 'v', 'e'};
    array1.swap(array1_swap);
    std_array1.swap(std_array1_swap);
    EXPECT_TRUE(equel_array(array1, std_array1));
    EXPECT_TRUE(equel_array(array1_swap, std_array1_swap));

    study::array<char, 4> array2{'l', 'o', 'v', 'e'};
    std::array<char, 4> std_array2{'l', 'o', 'v', 'e'};
    study::array<char, 4> array2_swap;
    std::array<char, 4> std_array2_swap;
    array2.swap(array2_swap);
    std_array2.swap(std_array2_swap);
    EXPECT_TRUE(equel_array(array2, std_array2));
    EXPECT_TRUE(equel_array(array2_swap, std_array2_swap));

    study::array<char, 4> array3;
    std::array<char, 4> std_array3;
    study::array<char, 4> array3_swap{'l', 'o', 'v', 'e'};
    std::array<char, 4> std_array3_swap{'l', 'o', 'v', 'e'};
    array3.swap(array3_swap);
    std_array3.swap(std_array3_swap);
    EXPECT_TRUE(equel_array(array3, std_array3));
    EXPECT_TRUE(equel_array(array3_swap, std_array3_swap));
}


TEST(array, function_at) {
    study::array<std::string, 6> array{"access", "specified", "element", "with", "bounds", "checking"};
    std::array<std::string, 6> std_array{"access", "specified", "element", "with", "bounds", "checking"};
    EXPECT_TRUE(equel_array(array, std_array));
    ASSERT_EQ(array.at(0), std_array.at(0));
    ASSERT_EQ(array.at(1), std_array.at(1));
    ASSERT_EQ(array.at(2), std_array.at(2));
    ASSERT_EQ(array.at(3), std_array.at(3));
    ASSERT_EQ(array.at(4), std_array.at(4));
    ASSERT_EQ(array.at(5), std_array.at(5));
}

TEST(array, operator_square_brackets) {
    study::array<std::string, 3> array{"access", "specified", "element"};
    std::array<std::string, 3> std_array{"access", "specified", "element"};
    EXPECT_TRUE(equel_array(array, std_array));
    ASSERT_EQ(array[0], std_array[0]);
    ASSERT_EQ(array[1], std_array[1]);
    ASSERT_EQ(array[2], std_array[2]);
}

TEST(array, function_data) {
    study::array<int, 0> array_empty;
    std::array<int, 0> std_array_empty;
    ASSERT_EQ(array_empty.data(), nullptr);
    ASSERT_EQ(std_array_empty.data(), nullptr);
    EXPECT_TRUE(equel_array(array_empty, std_array_empty));
    study::array<int, 4> array{1, 2234567, 21, 9874567};
    std::array<int, 4> std_array{1, 2234567, 21, 9874567};
    EXPECT_TRUE(equel_array(array, std_array));
    ASSERT_NE(array.data(), nullptr);
    ASSERT_NE(std_array.data(), nullptr);
}

TEST(array_test_suit, fill_test) {
    std::array<double, 4> std_array;
    study::array<double, 4> array;
    std_array.fill(555);
    array.fill(555);
    for (size_t i = 0; i < std_array.size(); i++)
        ASSERT_EQ(std_array[i], array[i]);
    ASSERT_EQ(std_array.size(), array.size());;
}

/* --------------------------STACK TESTS --------------------------*/

template <class T>
bool equel_stack(study::stack<T> stack, std::stack<T> std_stack) {
    bool res = true;
    if ((stack.size() != std_stack.size()) || (stack.empty() != std_stack.empty()))
        res = false;
    if (res != false) {
        for (size_t i = 0; i < stack.size(); i++) {
            if (std_stack.top() != stack.top() )
                            res = false;
            std_stack.pop();
            stack.pop();
        }
    }
    return res;
}


TEST(stack, default_constructor) {
    study::stack<int> stack;
    std::stack<int> std_stack;
    EXPECT_TRUE(equel_stack(stack, std_stack));

    study::stack<double> stack1;
    std::stack<double> std_stack1;
    EXPECT_TRUE(equel_stack(stack1, std_stack1));

    study::stack<std::string> stack2;
    std::stack<std::string> std_stack2;
    EXPECT_TRUE(equel_stack(stack2, std_stack2));

    study::stack<char> stack3;
    std::stack<char> std_stack3;
    EXPECT_TRUE(equel_stack(stack3, std_stack3));

    study::stack<std::pair<int, double>> stack4;
    std::stack<std::pair<int, double>> std_stack4;
    EXPECT_TRUE(equel_stack(stack4, std_stack4));

    study::stack<std::set<int>> stack5;
    std::stack<std::set<int>> std_stack5;
    EXPECT_TRUE(equel_stack(stack5, std_stack5));
}


TEST(stack, initializer_stack_constructor) {
    study::stack<int> stack{1, 2, 3};
    std::stack<int> std_stack;
    std_stack.push(1);
    std_stack.push(2);
    std_stack.push(3);
    EXPECT_TRUE(equel_stack(stack, std_stack));

    study::stack<char> stack1{'l', 'o', 'v', 'e'};
    std::stack<char> std_stack1;
    std_stack1.push('l');
    std_stack1.push('o');
    std_stack1.push('v');
    std_stack1.push('e');
    EXPECT_TRUE(equel_stack(stack1, std_stack1));

    study::stack<std::pair<int, double>> stack2{{42, 3.1415}, {89, 21}};
    std::stack<std::pair<int, double>> std_stack2;
    std_stack2.push({42, 3.1415});
    std_stack2.push({89, 21});
    EXPECT_TRUE(equel_stack(stack2, std_stack2));

    study::stack<std::string> stack6{"Hello", "Me!"};
    std::stack<std::string> std_stack6;
    EXPECT_FALSE(equel_stack(stack6, std_stack6));
}


TEST(stack, copy_constructor) {
    study::stack<char> stack{'l', 'o', 'v', 'e'};
    std::stack<char> std_stack;
    std_stack.push('l');
    std_stack.push('o');
    std_stack.push('v');
    std_stack.push('e');
    study::stack<char> stack_copy(stack);
    std::stack<char> std_stack_copy(std_stack);
    EXPECT_TRUE(equel_stack(stack, std_stack));
    EXPECT_TRUE(equel_stack(stack_copy, std_stack_copy));

    study::stack<int> stack1{1, 2, 3};
    std::stack<int> std_stack1;
    std_stack1.push(1);
    std_stack1.push(2);
    std_stack1.push(3);
    study::stack<int> stack1_copy(stack1);
    std::stack<int> std_stack1_copy(std_stack1);
    EXPECT_TRUE(equel_stack(stack1, std_stack1));
    EXPECT_TRUE(equel_stack(stack1_copy, std_stack1_copy));
}

TEST(stack, move_constructor) {
    study::stack<char> stack{'l', 'o', 'v', 'e'};
    std::stack<char> std_stack;
    std_stack.push('l');
    std_stack.push('o');
    std_stack.push('v');
    std_stack.push('e');
    study::stack<char> stack_move(std::move(stack));
    std::stack<char> std_stack_move(std::move(std_stack));
    EXPECT_TRUE(equel_stack(stack, std_stack));
    EXPECT_TRUE(equel_stack(stack_move, std_stack_move));

    study::stack<int> stack1{1, 2, 3};
    std::stack<int> std_stack1;
    std_stack1.push(1);
    std_stack1.push(2);
    std_stack1.push(3);
    study::stack<int> stack1_move(std::move(stack1));
    std::stack<int> std_stack1_move(std::move(std_stack1));
    EXPECT_TRUE(equel_stack(stack1, std_stack1));
    EXPECT_TRUE(equel_stack(stack1_move, std_stack1_move));
}

TEST(stack, move_to_less_buffer) {
    study::stack<int> stack{1, 2, 3};
    std::stack<int> std_stack;
    std_stack.push(1);
    std_stack.push(2);
    std_stack.push(3);
    study::stack<int> stack_move{1, 2};
    std::stack<int> std_stack_move;
    std_stack_move.push(1);
    std_stack_move.push(2);
    stack_move = std::move(stack);
    std_stack_move = std::move(std_stack);
    EXPECT_TRUE(equel_stack(stack_move, std_stack_move));
    ASSERT_EQ(stack.size(), std_stack.size());
    ASSERT_EQ(stack.empty(), std_stack.empty());
}

TEST(stack, move_to_more_buffer) {
    study::stack<int> stack{1, 2};
    std::stack<int> std_stack;
    std_stack.push(1);
    std_stack.push(2);
    study::stack<int> stack_move{1, 2, 3, 4};
    std::stack<int> std_stack_move;
    std_stack_move.push(1);
    std_stack_move.push(2);
    std_stack_move.push(3);
    std_stack_move.push(4);
    stack_move = std::move(stack);
    std_stack_move = std::move(std_stack);
    EXPECT_TRUE(equel_stack(stack_move, std_stack_move));
    ASSERT_EQ(stack.size(), std_stack.size());
    ASSERT_EQ(stack.empty(), std_stack.empty());
}

TEST(stack, pop_function) {
    study::stack<char> stack{'l', 'o', 'v', 'e'};
    std::stack<char> std_stack;
    std_stack.push('l');
    std_stack.push('o');
    std_stack.push('v');
    std_stack.push('e');
    EXPECT_TRUE(equel_stack(stack, std_stack));
    stack.pop();
    std_stack.pop();
    EXPECT_TRUE(equel_stack(stack, std_stack));
    stack.pop();
    std_stack.pop();
    EXPECT_TRUE(equel_stack(stack, std_stack));
    stack.pop();
    std_stack.pop();
    EXPECT_TRUE(equel_stack(stack, std_stack));
    stack.pop();
    std_stack.pop();
    EXPECT_TRUE(equel_stack(stack, std_stack));
}

TEST(stack, push_function) {
    study::stack<char> stack;
    std::stack<char> std_stack;
    EXPECT_TRUE(equel_stack(stack, std_stack));
    stack.push('l');
    std_stack.push('l');
    EXPECT_TRUE(equel_stack(stack, std_stack));
    stack.push('o');
    std_stack.push('o');
    EXPECT_TRUE(equel_stack(stack, std_stack));
    stack.push('v');
    std_stack.push('v');
    EXPECT_TRUE(equel_stack(stack, std_stack));
    stack.push('e');
    std_stack.push('e');
    EXPECT_TRUE(equel_stack(stack, std_stack));
}

TEST(stack, swap_function) {
    std::stack<char> std_stack1;
    std_stack1.push('b');
    std_stack1.push('e');
    std_stack1.push(' ');
    std_stack1.push('m');
    std_stack1.push('y');
    std_stack1.push(' ');
    std_stack1.push('g');
    std_stack1.push('i');
    std_stack1.push('r');
    std_stack1.push('l');
    std::stack<char> std_stack2;
    std_stack2.push('N');
    std_stack2.push('O');
    std_stack2.push('O');
    study::stack<char> stack1;
    stack1.push('b');
    stack1.push('e');
    stack1.push(' ');
    stack1.push('m');
    stack1.push('y');
    stack1.push(' ');
    stack1.push('g');
    stack1.push('i');
    stack1.push('r');
    stack1.push('l');
    study::stack<char> stack2;
    stack2.push('N');
    stack2.push('O');
    stack2.push('O');
    std_stack1.swap(std_stack2);
    stack1.swap(stack2);
    EXPECT_TRUE(equel_stack(stack1, std_stack1));
    EXPECT_TRUE(equel_stack(stack2, std_stack2));
}

TEST(stack, top_function) {
    study::stack<char> stack1{'B', 'a', 'g'};
    std::stack<char> std_stack1;
    std_stack1.push('B');
    std_stack1.push('a');
    std_stack1.push('g');
    ASSERT_EQ(stack1.top(), 'g');
    ASSERT_EQ(std_stack1.top(), stack1.top());
    stack1.pop();
    std_stack1.pop();
    ASSERT_EQ(stack1.top(), 'a');
    ASSERT_EQ(std_stack1.top(), stack1.top());
    stack1.pop();
    std_stack1.pop();
    ASSERT_EQ(stack1.top(), 'B');
    ASSERT_EQ(std_stack1.top(), stack1.top());
}

/* --------------------------QUEUE TESTS --------------------------*/


template <class T>
bool equel_queue(study::queue<T> queue, std::queue<T> std_queue) {
    bool res = true;
    if ((queue.size() != std_queue.size()) || (queue.empty() != std_queue.empty()))
        res = false;
    if (res != false) {
        for (size_t i = 0; i < queue.size(); i++) {
            if (std_queue.front() != queue.front() )
                            res = false;
            std_queue.pop();
            queue.pop();
        }
    }
    return res;
}

TEST(queue, default_constructor) {
    study::queue<int> queue;
    std::queue<int> std_queue;
    EXPECT_TRUE(equel_queue(queue, std_queue));

    study::queue<double> queue1;
    std::queue<double> std_queue1;
    EXPECT_TRUE(equel_queue(queue1, std_queue1));

    study::queue<std::string> queue2;
    std::queue<std::string> std_queue2;
    EXPECT_TRUE(equel_queue(queue2, std_queue2));

    study::queue<char> queue3;
    std::queue<char> std_queue3;
    EXPECT_TRUE(equel_queue(queue3, std_queue3));

    study::queue<std::pair<int, double>> queue4;
    std::queue<std::pair<int, double>> std_queue4;
    EXPECT_TRUE(equel_queue(queue4, std_queue4));

    study::queue<std::set<int>> queue5;
    std::queue<std::set<int>> std_queue5;
    EXPECT_TRUE(equel_queue(queue5, std_queue5));
}


TEST(queue, initializer_queue_constructor) {
    study::queue<int> queue{1, 2, 3};
    std::queue<int> std_queue;
    std_queue.push(1);
    std_queue.push(2);
    std_queue.push(3);
    EXPECT_TRUE(equel_queue(queue, std_queue));

    study::queue<char> queue1{'l', 'o', 'v', 'e'};
    std::queue<char> std_queue1;
    std_queue1.push('l');
    std_queue1.push('o');
    std_queue1.push('v');
    std_queue1.push('e');
    EXPECT_TRUE(equel_queue(queue1, std_queue1));

    study::queue<std::pair<int, double>> queue2{{42, 3.1415}, {89, 21}};
    std::queue<std::pair<int, double>> std_queue2;
    std_queue2.push({42, 3.1415});
    std_queue2.push({89, 21});
    EXPECT_TRUE(equel_queue(queue2, std_queue2));

    study::queue<std::string> queue6{"Hello", "Me!"};
    std::queue<std::string> std_queue6;
    EXPECT_FALSE(equel_queue(queue6, std_queue6));
}


TEST(queue, copy_constructor) {
    study::queue<char> queue{'l', 'o', 'v', 'e'};
    std::queue<char> std_queue;
    std_queue.push('l');
    std_queue.push('o');
    std_queue.push('v');
    std_queue.push('e');
    study::queue<char> queue_copy(queue);
    std::queue<char> std_queue_copy(std_queue);
    EXPECT_TRUE(equel_queue(queue, std_queue));
    EXPECT_TRUE(equel_queue(queue_copy, std_queue_copy));

    study::queue<int> queue1{1, 2, 3};
    std::queue<int> std_queue1;
    std_queue1.push(1);
    std_queue1.push(2);
    std_queue1.push(3);
    study::queue<int> queue1_copy(queue1);
    std::queue<int> std_queue1_copy(std_queue1);
    EXPECT_TRUE(equel_queue(queue1, std_queue1));
    EXPECT_TRUE(equel_queue(queue1_copy, std_queue1_copy));
}

TEST(queue, move_constructor) {
    study::queue<char> queue{'l', 'o', 'v', 'e'};
    std::queue<char> std_queue;
    std_queue.push('l');
    std_queue.push('o');
    std_queue.push('v');
    std_queue.push('e');
    study::queue<char> queue_move(std::move(queue));
    std::queue<char> std_queue_move(std::move(std_queue));
    EXPECT_TRUE(equel_queue(queue, std_queue));
    EXPECT_TRUE(equel_queue(queue_move, std_queue_move));

    study::queue<int> queue1{1, 2, 3};
    std::queue<int> std_queue1;
    std_queue1.push(1);
    std_queue1.push(2);
    std_queue1.push(3);
    study::queue<int> queue1_move(std::move(queue1));
    std::queue<int> std_queue1_move(std::move(std_queue1));
    EXPECT_TRUE(equel_queue(queue1, std_queue1));
    EXPECT_TRUE(equel_queue(queue1_move, std_queue1_move));
}

TEST(queue, move_to_less_buffer) {
    study::queue<int> queue{1, 2, 3};
    std::queue<int> std_queue;
    std_queue.push(1);
    std_queue.push(2);
    std_queue.push(3);
    study::queue<int> queue_move{1, 2};
    std::queue<int> std_queue_move;
    std_queue_move.push(1);
    std_queue_move.push(2);
    queue_move = std::move(queue);
    std_queue_move = std::move(std_queue);
    EXPECT_TRUE(equel_queue(queue_move, std_queue_move));
    ASSERT_EQ(queue.size(), std_queue.size());
    ASSERT_EQ(queue.empty(), std_queue.empty());
}

TEST(queue, move_to_more_buffer) {
    study::queue<int> queue{1, 2};
    std::queue<int> std_queue;
    std_queue.push(1);
    std_queue.push(2);
    study::queue<int> queue_move{1, 2, 3, 4};
    std::queue<int> std_queue_move;
    std_queue_move.push(1);
    std_queue_move.push(2);
    std_queue_move.push(3);
    std_queue_move.push(4);
    queue_move = std::move(queue);
    std_queue_move = std::move(std_queue);
    EXPECT_TRUE(equel_queue(queue_move, std_queue_move));
    ASSERT_EQ(queue.size(), std_queue.size());
    ASSERT_EQ(queue.empty(), std_queue.empty());
}

TEST(queue, pop_function) {
    study::queue<char> queue{'l', 'o', 'v', 'e'};
    std::queue<char> std_queue;
    std_queue.push('l');
    std_queue.push('o');
    std_queue.push('v');
    std_queue.push('e');
    EXPECT_TRUE(equel_queue(queue, std_queue));
    queue.pop();
    std_queue.pop();
    EXPECT_TRUE(equel_queue(queue, std_queue));
    queue.pop();
    std_queue.pop();
    EXPECT_TRUE(equel_queue(queue, std_queue));
    queue.pop();
    std_queue.pop();
    EXPECT_TRUE(equel_queue(queue, std_queue));
    queue.pop();
    std_queue.pop();
    EXPECT_TRUE(equel_queue(queue, std_queue));
}

TEST(queue, push_function) {
    study::queue<char> queue;
    std::queue<char> std_queue;
    EXPECT_TRUE(equel_queue(queue, std_queue));
    queue.push('l');
    std_queue.push('l');
    EXPECT_TRUE(equel_queue(queue, std_queue));
    queue.push('o');
    std_queue.push('o');
    EXPECT_TRUE(equel_queue(queue, std_queue));
    queue.push('v');
    std_queue.push('v');
    EXPECT_TRUE(equel_queue(queue, std_queue));
    queue.push('e');
    std_queue.push('e');
    EXPECT_TRUE(equel_queue(queue, std_queue));
}

TEST(queue, swap_function) {
    std::queue<char> std_queue1;
    std_queue1.push('b');
    std_queue1.push('e');
    std_queue1.push(' ');
    std_queue1.push('m');
    std_queue1.push('y');
    std_queue1.push(' ');
    std_queue1.push('g');
    std_queue1.push('i');
    std_queue1.push('r');
    std_queue1.push('l');
    std::queue<char> std_queue2;
    std_queue2.push('N');
    std_queue2.push('O');
    std_queue2.push('O');
    study::queue<char> queue1;
    queue1.push('b');
    queue1.push('e');
    queue1.push(' ');
    queue1.push('m');
    queue1.push('y');
    queue1.push(' ');
    queue1.push('g');
    queue1.push('i');
    queue1.push('r');
    queue1.push('l');
    study::queue<char> queue2;
    queue2.push('N');
    queue2.push('O');
    queue2.push('O');
    std_queue1.swap(std_queue2);
    queue1.swap(queue2);
    EXPECT_TRUE(equel_queue(queue1, std_queue1));
    EXPECT_TRUE(equel_queue(queue2, std_queue2));
}

TEST(queue, back_function) {
    study::queue<char> queue1;
    queue1.push('B');
    queue1.push('a');
    queue1.push('g');
    std::queue<char> std_queue1;
    std_queue1.push('B');
    std_queue1.push('a');
    std_queue1.push('g');
    ASSERT_EQ(queue1.front(), 'B');
    ASSERT_EQ(std_queue1.front(), queue1.front());
    queue1.pop();
    std_queue1.pop();
    ASSERT_EQ(queue1.front(), 'a');
    ASSERT_EQ(std_queue1.front(), queue1.front());
    queue1.pop();
    std_queue1.pop();
    ASSERT_EQ(queue1.front(), 'g');
    ASSERT_EQ(std_queue1.front(), queue1.front());
}

TEST(queue, front_function) {
    study::queue<char> queue1{'B', 'a', 'g'};
    std::queue<char> std_queue1;
    std_queue1.push('B');
    std_queue1.push('a');
    std_queue1.push('g');
    ASSERT_EQ(queue1.back(), 'g');
    ASSERT_EQ(std_queue1.back(), queue1.back());
    queue1.pop();
    std_queue1.pop();
    ASSERT_EQ(std_queue1.back(), queue1.back());
    queue1.pop();
    std_queue1.pop();
    ASSERT_EQ(std_queue1.back(), queue1.back());
}

std::pair<const int, const char*> q0(0, "q0");
std::pair<const int, const char*> q1(1, "q1");
std::pair<const int, const char*> q2(2, "q2");
std::pair<const int, const char*> q3(3, "q3");
std::pair<const int, const char*> q4(4, "q4");
std::pair<const int, const char*> q01(0, "q01");
std::pair<const int, const char*> q111(1, "q111");
std::pair<const int, const char*> q21(2, "q21");
std::pair<const int, const char*> q31(3, "q31");
std::pair<const int, const char*> q41(4, "q41");

std::pair<const int, const char*> q5(5, "q5");
std::pair<const int, const char*> q555(5, "q555");

std::initializer_list<std::pair<const int, const char*>> list = {
    q2, q2, q2, q2, q0, q3, q1, q4, q21, q01, q31, q111, q41 };
std::initializer_list<std::pair<const int, const char*>> list2 = {
    q4, q3, q1, q0, q2, q2, q2, q2, q41, q31, q111, q01, q21 };

/* --ТЕСТЫ MAP И SET-- */
TEST(map_and_set, constructors) {
    study::map<const int, const char*> map1_s21;
    study::map<const int, const char*> map2_s21(list);
    study::map<const int, const char*> map3_s21(map2_s21);
    study::map<const int, const char*> map4_s21(std::move(map3_s21));

    std::map<const int, const char*> map1_std;
    std::map<const int, const char*> map2_std(list2);
    std::map<const int, const char*> map3_std(map2_std);
    std::map<const int, const char*> map4_std(std::move(map3_std));

    map2_s21.print("Test print");
    EXPECT_EQ(map1_s21.size(), map1_std.size());
    EXPECT_EQ(map2_s21.size(), map2_std.size());
    EXPECT_EQ(map3_s21.size(), map3_std.size());
    EXPECT_EQ(map4_s21.size(), map4_std.size());

    map1_s21 = std::move(map4_s21);
    map1_std = std::move(map4_std);

    EXPECT_EQ(map1_s21.size(), map1_std.size());
}

TEST(map_and_set, iterators) {
    study::map<const int, const char*> map_s21(list);
    std::map<const int, const char*> map_std(list2);

    // общее тестирвоание
    auto iter_s21 = map_s21.begin();
    auto iter_std = map_std.begin();

    EXPECT_FALSE(iter_s21 != iter_s21);

    size_t x = 0;
    while (x < map_s21.size() && x < map_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }

    iter_s21 = map_s21.end();
    iter_std = map_std.end();
    x = 0;
    while (x < map_s21.size() && x < map_std.size()) {
        --iter_s21;
        --iter_std;
        EXPECT_EQ(*iter_s21, *iter_std);
        x += 1;
    }
}

TEST(map_and_set, filling) {
    study::map<const int, const char*> map1_s21;
    std::map<const int, const char*> map1_std;
    study::map<const int, const char*> map2_s21(list);
    std::map<const int, const char*> map2_std(list);

    EXPECT_EQ(map1_s21.empty(), map1_std.empty());
    EXPECT_EQ(map2_s21.empty(), map2_std.empty());

    EXPECT_EQ(map1_s21.size(), map1_std.size());
    EXPECT_EQ(map2_s21.size(), map2_std.size());

    EXPECT_EQ(map1_s21.max_size(), 461168601842738790);
    EXPECT_EQ(map2_s21.max_size(), 461168601842738790);
}

TEST(map_and_set, editing) {
    std::pair<const int, const char*> q6(6, "q6");
    std::pair<const int, const char*> q7(7, "q7");
    std::pair<const int, const char*> q8(8, "q8");
    std::pair<const int, const char*> q9(9, "q9");
    std::pair<const int, const char*> q10(10, "q10");
    std::pair<const int, const char*> q11(11, "q11");

    study::map<const int, const char*> map1_s21(list);
    std::map<const int, const char*> map1_std(list2);
    study::map<const int, const char*> map2_s21(list);
    std::map<const int, const char*> map2_std(list2);
    study::map<const int, const char*> map3_s21;
    std::map<const int, const char*> map3_std;

    // проверка функции clear()
    map1_s21.clear();
    map1_std.clear();
    EXPECT_EQ(map1_s21.size(), map1_std.size());

    // првоерка функции insert() с учётом возравта пары <итератор, bool вставки>
    auto result_i5_s21 = map1_s21.insert(q5);
    auto result_i10_s21 = map1_s21.insert(q10);
    auto result_i6_s21 = map1_s21.insert(q6);
    auto result_i9_s21 = map1_s21.insert(q9);
    auto result_i7_s21 = map1_s21.insert(q7);
    auto result_i8_s21 = map1_s21.insert(q8);
    auto result_i11_s21 = map1_s21.insert(q11);

    auto result_i11_std = map1_std.insert(q11);
    auto result_i10_std = map1_std.insert(q10);
    auto result_i9_std = map1_std.insert(q9);
    auto result_i8_std = map1_std.insert(q8);
    auto result_i7_std = map1_std.insert(q7);
    auto result_i6_std = map1_std.insert(q6);
    auto result_i5_std = map1_std.insert(q5);

    // проверка неудачной вставки
    auto result_i55_s21 = map1_s21.insert(q5);
    auto result_i55_std = map1_std.insert(q5);
    EXPECT_EQ(*(result_i55_std.first), *(result_i55_s21.first));
    EXPECT_EQ(result_i55_std.second, result_i55_s21.second);

    EXPECT_EQ(*(result_i5_std.first), *(result_i5_s21.first));
    EXPECT_EQ(result_i5_std.second, result_i5_s21.second);
    EXPECT_EQ(*(result_i6_std.first), *(result_i6_s21.first));
    EXPECT_EQ(result_i6_std.second, result_i6_s21.second);
    EXPECT_EQ(*(result_i7_std.first), *(result_i7_s21.first));
    EXPECT_EQ(result_i7_std.second, result_i7_s21.second);
    EXPECT_EQ(*(result_i8_std.first), *(result_i8_s21.first));
    EXPECT_EQ(result_i8_std.second, result_i8_s21.second);
    EXPECT_EQ(*(result_i9_std.first), *(result_i9_s21.first));
    EXPECT_EQ(result_i9_std.second, result_i9_s21.second);
    EXPECT_EQ(*(result_i10_std.first), *(result_i10_s21.first));
    EXPECT_EQ(result_i10_std.second, result_i10_s21.second);
    EXPECT_EQ(*(result_i11_std.first), *(result_i11_s21.first));
    EXPECT_EQ(result_i11_std.second, result_i11_s21.second);

    auto iter_s21 = map1_s21.begin();
    auto iter_std = map1_std.begin();
    size_t x = 0;
    while (x < map1_s21.size() || x < map1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(map1_s21.size(), map1_std.size());

    // проверка функции erase()
    // покрытие ветвлений erase()  и emplace()
    map3_s21.emplace(q3, q4, q5);

    map3_std.insert(q5);
    map3_std.insert(q4);
    map3_std.insert(q3);
    map3_s21.erase(--map3_s21.end());
    map3_std.erase(--map3_std.end());
    EXPECT_EQ(map3_s21.size(), map3_std.size());
    map3_s21.erase(map3_s21.begin());
    map3_std.erase(map3_std.begin());
    EXPECT_EQ(map3_s21.size(), map3_std.size());
    map3_s21.erase(map3_s21.begin());
    map3_std.erase(map3_std.begin());
    EXPECT_EQ(map3_s21.size(), map3_std.size());

    // общее тестирование
    map1_s21.erase(--(--(--iter_s21)));
    map1_std.erase(--(--(--iter_std)));

    iter_s21 = map1_s21.begin();
    iter_std = map1_std.begin();
    x = 0;
    while (x < map1_s21.size() || x < map1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(map1_s21.size(), map1_std.size());

    // проверка функции swap
    map1_s21.swap(map2_s21);

    iter_s21 = map2_s21.begin();
    iter_std = map1_std.begin();
    x = 0;
    while (x < map2_s21.size() || x < map1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(map2_s21.size(), map1_std.size());

    iter_s21 = map1_s21.begin();
    iter_std = map2_std.begin();
    x = 0;
    while (x < map1_s21.size() || x < map2_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(map1_s21.size(), map2_std.size());

    // проверка функции merge()
    map1_s21.merge(map2_s21);
    map1_std.merge(map2_std);

    iter_s21 = map1_s21.begin();
    iter_std = map1_std.begin();
    x = 0;
    while (x < map1_s21.size() || x < map1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(map1_s21.size(), map1_std.size());
    EXPECT_EQ(map2_s21.size(), map2_std.size());
}

TEST(map_and_set, view) {
    study::map<const int, const char*> map1_s21(list);
    std::map<const int, const char*> map1_std(list);

    // проверка функции contains()
    int x = -100;
    while (x < 100) {
        EXPECT_EQ(map1_s21.contains(x), map1_std.contains(x));
        x += 1;
    }
}
/* ----------------------------------------------- */

/* --ТЕСТЫ SET-- */
TEST(set, editing) {
    // проверка возврата функции insert() и emplace()
    std::initializer_list<int> set_list = { -1, 0, 2, -100, 700, 300, -30, -29 };
    study::set<int> set_s21;
    set_s21.emplace(-1, 0, 2, -100, 700, 300, -30, -29);
    std::set<int> set_std(set_list);

    EXPECT_EQ(*(set_s21.insert(0).first), *(set_std.insert(0).first));
    EXPECT_EQ((set_s21.insert(0).second), (set_std.insert(0).second));

    // проверка возврата функции merge()
    std::initializer_list<int> set_list2 = { -10, 0, 2, -1050, 7050, 300, -3000, -29 };
    study::set<int> set2_s21(set_list2);
    std::set<int> set2_std(set_list2);
    set_s21.merge(set2_s21);
    set_std.merge(set2_std);

    EXPECT_EQ(set_s21.size(), set_std.size());
    EXPECT_EQ(set2_s21.size(), set2_std.size());
}

TEST(set, view) {
    // проверка функции find()
    std::initializer_list<int> set_list = { -1, 0, 2, -100, 700, 300, -30, -29 };
    study::set<int> set_s21(set_list);
    std::set<int> set_std(set_list);

    auto x = set_list.begin();
    while (x < set_list.end()) {
        EXPECT_EQ(*set_s21.find(*x), *set_std.find(*x));
        x += 1;
    }
    // проверка поиска несуществующего элемента
    EXPECT_EQ(*(--set_s21.find(5)), *(--set_std.find(5)));
}
/* ----------------------------------------------- */

/* --ТЕСТЫ MAP-- */
TEST(map, view) {
    study::map<const int, const char*> map1_s21(list);
    std::map<const int, const char*> map1_std(list);

    // проверка функции at
    map1_s21.at(1) = "qqaz";
    map1_std.at(1) = "qqaz";
    auto x = list.begin();
    while (x < list.end()) {
        EXPECT_EQ(map1_s21.at((*x).first), map1_std.at((*x).first));
        x += 1;
    }
    // проверка оператора []
    x = list.begin();
    while (x < list.end()) {
        EXPECT_EQ(map1_s21[(*x).first], map1_std[(*x).first]);
        x += 1;
    }

    map1_s21[0] = "q00111";
    map1_std[0] = "q00111";
    x = list.begin();
    while (x < list.end()) {
        EXPECT_EQ(map1_s21[(*x).first], map1_std[(*x).first]);
        x += 1;
    }
//    EXPECT_ANY_THROW(map1_s21[600]);
}

TEST(map, editing) {
    // проверка функции insert(const K& key, const M& obj)
    study::map<int, const char*> map1_s21;
    std::map<int, const char*> map1_std;
    map1_s21.insert(0, "q0");
    map1_s21.insert(1, "q1");
    map1_s21.insert(2, "q2");
    map1_s21.insert(3, "q3");
    map1_s21.insert(4, "q4");
    map1_s21.insert(5, "q5");

    map1_std.insert_or_assign(5, "q5");
    map1_std.insert_or_assign(4, "q4");
    map1_std.insert_or_assign(3, "q3");
    map1_std.insert_or_assign(2, "q2");
    map1_std.insert_or_assign(1, "q1");
    map1_std.insert_or_assign(0, "q0");

    size_t x = 0;
    auto iter_s21 = map1_s21.begin();
    auto iter_std = map1_std.begin();
    while (x < map1_s21.size() && x < map1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(map1_s21.size(), map1_std.size());

    // проверка функции insert_or_assign(const K& key, const M& obj)

    map1_s21.insert_or_assign(6, "q6");
    map1_s21.insert_or_assign(7, "q7");
    map1_s21.insert_or_assign(8, "q8");
    map1_s21.insert_or_assign(1, "q11");

    map1_std.insert_or_assign(6, "q6");
    map1_std.insert_or_assign(7, "q7");
    map1_std.insert_or_assign(8, "q8");
    map1_std.insert_or_assign(1, "q11");

    x = 0;
    iter_s21 = map1_s21.begin();
    iter_std = map1_std.begin();
    while (x < map1_s21.size() && x < map1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(map1_s21.size(), map1_std.size());
}
/* ----------------------------------------------- */

/* --ТЕСТЫ MULTISET-- */
TEST(multiset, constructors) {
    study::multiset<std::pair<const int, const char*>> mset1_s21;
    study::multiset<std::pair<const int, const char*>> mset2_s21(list);
    study::multiset<std::pair<const int, const char*>> mset3_s21(mset2_s21);
    study::multiset<std::pair<const int, const char*>> mset4_s21(std::move(mset3_s21));

    std::multiset<std::pair<const int, const char*>> mset1_std;
    std::multiset<std::pair<const int, const char*>> mset2_std(list2);
    std::multiset<std::pair<const int, const char*>> mset3_std(mset2_std);
    std::multiset<std::pair<const int, const char*>> mset4_std(std::move(mset3_std));

    EXPECT_EQ(mset1_s21.size(), mset1_std.size());
    EXPECT_EQ(mset2_s21.size(), mset2_std.size());
    EXPECT_EQ(mset3_s21.size(), mset3_std.size());
    EXPECT_EQ(mset4_s21.size(), mset4_std.size());

    mset1_s21 = std::move(mset4_s21);
    mset1_std = std::move(mset4_std);

    EXPECT_EQ(mset1_s21.size(), mset1_std.size());
}

TEST(multiset, iterators) {
    study::multiset<std::pair<const int, const char*>> mset_s21(list);
    std::multiset<std::pair<const int, const char*>> mset_std(list2);

    // общее тестирвоание
    auto iter_s21 = mset_s21.begin();
    auto iter_std = mset_std.begin();

    EXPECT_FALSE(iter_s21 != iter_s21);

    size_t x = 0;
    while (x < mset_s21.size() && x < mset_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }

    iter_s21 = mset_s21.end();
    iter_std = mset_std.end();
    x = 0;
    while (x < mset_s21.size() && x < mset_std.size()) {
        --iter_s21;
        --iter_std;
        EXPECT_EQ(*iter_s21, *iter_std);
        x += 1;
    }
}

TEST(multiset, filling) {
    study::multiset<std::pair<const int, const char*>> mset1_s21;
    std::multiset<std::pair<const int, const char*>> mset1_std;
    study::multiset<std::pair<const int, const char*>> mset2_s21(list);
    std::multiset<std::pair<const int, const char*>> mset2_std(list);

    EXPECT_EQ(mset1_s21.empty(), mset1_std.empty());
    EXPECT_EQ(mset2_s21.empty(), mset2_std.empty());

    EXPECT_EQ(mset1_s21.size(), mset1_std.size());
    EXPECT_EQ(mset2_s21.size(), mset2_std.size());

    EXPECT_EQ(mset1_s21.max_size(), 461168601842738790);
    EXPECT_EQ(mset2_s21.max_size(), 461168601842738790);
}

TEST(multiset, editing) {
    std::pair<const int, const char*> q6(6, "q6");
    std::pair<const int, const char*> q7(7, "q7");
    std::pair<const int, const char*> q8(8, "q8");
    std::pair<const int, const char*> q9(9, "q9");
    std::pair<const int, const char*> q10(10, "q10");
    std::pair<const int, const char*> q11(11, "q11");

    study::multiset<std::pair<const int, const char*>> mset1_s21(list);
    std::multiset<std::pair<const int, const char*>> mset1_std(list2);
    study::multiset<std::pair<const int, const char*>> mset2_s21(list);
    std::multiset<std::pair<const int, const char*>> mset2_std(list2);
    study::multiset<std::pair<const int, const char*>> mset3_s21;
    std::multiset<std::pair<const int, const char*>> mset3_std;

    // проверка функции clear()
    mset1_s21.clear();
    mset1_std.clear();
    EXPECT_EQ(mset1_s21.size(), mset1_std.size());

    // првоерка функции insert() с учётом возравта пары <итератор, bool вставки>
    auto result_i5_s21 = mset1_s21.insert(q5);
    auto result_i10_s21 = mset1_s21.insert(q10);
    auto result_i6_s21 = mset1_s21.insert(q6);
    auto result_i9_s21 = mset1_s21.insert(q9);
    auto result_i7_s21 = mset1_s21.insert(q7);
    auto result_i8_s21 = mset1_s21.insert(q8);
    auto result_i11_s21 = mset1_s21.insert(q11);

    auto result_i11_std = mset1_std.insert(q11);
    auto result_i10_std = mset1_std.insert(q10);
    auto result_i9_std = mset1_std.insert(q9);
    auto result_i8_std = mset1_std.insert(q8);
    auto result_i7_std = mset1_std.insert(q7);
    auto result_i6_std = mset1_std.insert(q6);
    auto result_i5_std = mset1_std.insert(q5);

    EXPECT_EQ(*result_i5_std, *result_i5_s21);
    EXPECT_EQ(*result_i6_std, *result_i6_s21);
    EXPECT_EQ(*result_i7_std, *result_i7_s21);
    EXPECT_EQ(*result_i8_std, *result_i8_s21);
    EXPECT_EQ(*result_i9_std, *result_i9_s21);
    EXPECT_EQ(*result_i10_std, *result_i10_s21);
    EXPECT_EQ(*result_i11_std, *result_i11_s21);

    auto iter_s21 = mset1_s21.begin();
    auto iter_std = mset1_std.begin();

    size_t x = 0;
    while (x < mset1_s21.size() && x < mset1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(mset1_s21.size(), mset1_std.size());

    // проверка функции erase()
    // покрытие ветвлений erase() + emplace()
    mset3_s21.emplace(q3, q4, q5);
    mset3_std.insert(q5);
    mset3_std.insert(q4);
    mset3_std.insert(q3);
    mset3_s21.erase(--mset3_s21.end());
    mset3_std.erase(--mset3_std.end());
    EXPECT_EQ(mset3_s21.size(), mset3_std.size());
    mset3_s21.erase(mset3_s21.begin());
    mset3_std.erase(mset3_std.begin());
    EXPECT_EQ(mset3_s21.size(), mset3_std.size());
    mset3_s21.erase(mset3_s21.begin());
    mset3_std.erase(mset3_std.begin());
    EXPECT_EQ(mset3_s21.size(), mset3_std.size());

    // общее тестирование
    mset1_s21.erase(--(--(--iter_s21)));
    mset1_std.erase(--(--(--iter_std)));
    iter_s21 = mset1_s21.begin();
    iter_std = mset1_std.begin();

    x = 0;
    while (x < mset1_s21.size() && x < mset1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(mset1_s21.size(), mset1_std.size());

    // проверка функции swap
    mset1_s21.swap(mset2_s21);

    iter_s21 = mset2_s21.begin();
    iter_std = mset1_std.begin();
    x = 0;
    while (x < mset2_s21.size() && x < mset1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(mset2_s21.size(), mset1_std.size());

    iter_s21 = mset1_s21.begin();
    iter_std = mset2_std.begin();
    x = 0;
    while (x < mset1_s21.size() && x < mset2_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(mset1_s21.size(), mset2_std.size());

    // проверка функции merge()
    mset2_s21.insert(q555);
    mset2_std.insert(q555);

    mset1_s21.merge(mset2_s21);
    mset1_std.merge(mset2_std);

    mset2_s21.insert(q555);
    mset2_std.insert(q555);

    mset1_s21.merge(mset2_s21);
    mset1_std.merge(mset2_std);

    iter_s21 = mset1_s21.begin();
    iter_std = mset1_std.begin();
    while (x < mset1_s21.size() && x < mset1_std.size()) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
        x += 1;
    }
    EXPECT_EQ(mset1_s21.size(), mset1_std.size());
    EXPECT_EQ(mset2_s21.size(), mset2_std.size());
}

TEST(multiset, view) {
    study::multiset<std::pair<const int, const char*>> mset1_s21(list);
    std::multiset<std::pair<const int, const char*>> mset1_std(list);

    // проверка функции count()
    auto x = list.begin();
    while (x < list.end()) {
        EXPECT_EQ(mset1_s21.count(*x), mset1_std.count(*x));
        x += 1;
    }
    EXPECT_EQ(mset1_s21.count(q5), mset1_std.count(q5));

    // проверка функции find()
    x = list.begin();
    while (x < list.end()) {
        EXPECT_EQ(*mset1_s21.find(*x), *mset1_s21.find(*x));
        x += 1;
    }
    EXPECT_EQ(*(--mset1_s21.find(q5)), *(--mset1_std.find(q5)));

    // проверка функции contains()
    x = list.begin();
    while (x < list.end()) {
        EXPECT_EQ(mset1_s21.contains(*x), mset1_s21.contains(*x));
        x += 1;
    }
    EXPECT_EQ(mset1_s21.contains(q5), mset1_std.contains(q5));

    // проверка функции lower_bound()
    // в середине диапазон
    auto iter_std = mset1_std.lower_bound(q2);
    auto iter_s21 = mset1_s21.lower_bound(q2);

    EXPECT_EQ(*iter_s21, *iter_std);
    EXPECT_EQ(*(--iter_s21), *(--iter_std));
    EXPECT_EQ(*(++(++iter_s21)), *(++(++iter_std)));

    // несуществующее значение
    iter_std = mset1_std.lower_bound(q5);
    iter_s21 = mset1_s21.lower_bound(q5);

    EXPECT_EQ(*(--iter_s21), *(--iter_std));

    // крайнее правое значение
    iter_std = mset1_std.lower_bound(q41);
    iter_s21 = mset1_s21.lower_bound(q41);

    EXPECT_EQ(*iter_s21, *iter_std);
    EXPECT_EQ(*(--iter_s21), *(--iter_std));
//    EXPECT_ANY_THROW((*(++(++iter_s21))));

    // проверка функции upper_bound()
    // в середине диапазон
    iter_std = mset1_std.upper_bound(q2);
    iter_s21 = mset1_s21.upper_bound(q2);

    EXPECT_EQ(*iter_s21, *iter_std);
    EXPECT_EQ(*(--iter_s21), *(--iter_std));
    EXPECT_EQ(*(++(++iter_s21)), *(++(++iter_std)));

    // несуществующее значение
    iter_std = mset1_std.upper_bound(q5);
    iter_s21 = mset1_s21.upper_bound(q5);

//    EXPECT_ANY_THROW(*iter_s21);
    EXPECT_EQ(*(--iter_s21), *(--iter_std));

    // крайнее правое значение
    iter_std = mset1_std.upper_bound(q4);
    iter_s21 = mset1_s21.upper_bound(q4);

    EXPECT_EQ(*iter_s21, *iter_std);
    EXPECT_EQ(*(--iter_s21), *(--iter_std));
//    EXPECT_ANY_THROW((*(++(++iter_s21))));

    // проверка функции equal_range()
    // в середине диапазон
    auto y_s21 = mset1_s21.equal_range(q2);
    auto y_std = mset1_std.equal_range(q2);
    iter_s21 = y_s21.first;
    iter_std = y_std.first;
    while (iter_std != y_std.second) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
    }
    EXPECT_EQ(*(++iter_s21), *(++iter_std));

    // крайнее правое значение
    y_s21 = mset1_s21.equal_range(q41);
    y_std = mset1_std.equal_range(q41);
    iter_s21 = y_s21.first;
    iter_std = y_std.first;
    while (iter_std != y_std.second) {
        EXPECT_EQ(*iter_s21, *iter_std);
        ++iter_s21;
        ++iter_std;
    }
//    EXPECT_ANY_THROW(*iter_s21);
}

TEST(stack, emplace) {
    std::stack<int> std_stack;
    std_stack.push(1);
    std_stack.push(2);
    std_stack.push(3);
    std_stack.push(4);
    std_stack.emplace(567);
    std_stack.emplace(111);
    std_stack.emplace(98765);
    study::stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.emplace_front(567, 111, 98765);

    EXPECT_TRUE(equel_stack(stack, std_stack));
}

TEST(queue, emplace) {
    std::queue<double> std_queue;
    std_queue.push(1.3);
    std_queue.push(2.008);
    std_queue.push(3);
    std_queue.push(4);
    std_queue.emplace(567.0);
    std_queue.emplace(111.12345);
    std_queue.emplace(98765.90987);
    study::queue<double> queue;
    queue.push(1.3);
    queue.push(2.008);
    queue.push(3);
    queue.push(4);
    queue.emplace_back(567.0, 111.12345, 98765.90987);
    EXPECT_TRUE(equel_queue(queue, std_queue));

    std::queue<const char*> std_queue1;
    std_queue1.push("gg");
    std_queue1.emplace("hello");
    study::queue<const char*> queue1;
    queue1.push("gg");
    queue1.emplace_back("hello");
    EXPECT_TRUE(equel_queue(queue1, std_queue1));
}

TEST(list, emplace_back) {
    std::list<double> std_list;
    std_list.push_back(1.3);
    std_list.push_back(2.008);
    std_list.push_back(3);
    std_list.push_back(4);
    std_list.emplace_back(567.0);
    std_list.emplace_back(111.12345);
    std_list.emplace_back(98765.90987);
    study::list<double> list;
    list.push_back(1.3);
    list.push_back(2.008);
    list.push_back(3);
    list.push_back(4);
    list.emplace_back(567.0, 111.12345, 98765.90987);
    EXPECT_TRUE(equel_list(list, std_list));

    std::list<const char*> std_list1;
    std_list1.push_back("gg");
    std_list1.emplace_back("hello");
    study::list<const char*> list1;
    list1.push_back("gg");
    list1.emplace_back("hello");
    EXPECT_TRUE(equel_list(list1, std_list1));
}

TEST(list, emplace_front) {
    std::list<double> std_list;
    std_list.push_back(1.3);
    std_list.push_back(2.008);
    std_list.push_back(3);
    std_list.push_back(4);
    std_list.emplace_front(567.0);
    std_list.emplace_front(111.12345);
    std_list.emplace_front(98765.90987);
    study::list<double> list;
    list.push_back(1.3);
    list.push_back(2.008);
    list.push_back(3);
    list.push_back(4);
    list.emplace_front(567.0, 111.12345, 98765.90987);
    EXPECT_TRUE(equel_list(list, std_list));

    std::list<const char*> std_list1;
    std_list1.push_back("gg");
    std_list1.emplace_front("hello");
    study::list<const char*> list1;
    list1.push_back("gg");
    list1.emplace_front("hello");
    EXPECT_TRUE(equel_list(list1, std_list1));
}

TEST(list, emplace_function) {
    study::list<std::string> list{"Hello,", "World!"};
    std::list<std::string> std_list{"Hello,", "World!"};
    study::list<std::string>::const_iterator it = list.cbegin();
    std::list<std::string>::const_iterator std_it = std_list.cbegin();
    it = list.emplace(it, "Hi or");
    std_it = std_list.emplace(std_it, "Hi or");
    ASSERT_EQ(*it, *std_it);
    EXPECT_TRUE(equel_list(list, std_list));

    it = list.begin();
    std_it = std_list.begin();
    ++it;
    ++std_it;
    ++it;
    ++std_it;
    it = list.emplace(it, "my dear");
    std_it = std_list.emplace(std_it, "my dear");
    EXPECT_TRUE(equel_list(list, std_list));

    it = list.end();
    std_it = std_list.end();
    it = list.emplace(it, "Be happy");
    std_it = std_list.emplace(std_it, "Be happy");
    EXPECT_TRUE(equel_list(list, std_list));
}

TEST(vector, emplace_function) {
    study::vector<std::string> vector{"Hello,", "World!"};
    std::vector<std::string> std_vector{"Hello,", "World!"};
    study::vector<std::string>::iterator it = vector.begin();
    std::vector<std::string>::iterator std_it = std_vector.begin();
    it = vector.emplace(it, "Hi or");
    std_it = std_vector.emplace(std_it, "Hi or");
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    it = vector.begin();
    std_it = std_vector.begin();
    ++it;
    ++std_it;
    ++it;
    ++std_it;
    it = vector.emplace(it, "my dear");
    std_it = std_vector.emplace(std_it, "my dear");
    EXPECT_TRUE(equel_vector_full(vector, std_vector));

    it = vector.end();
    std_it = std_vector.end();
    it = vector.emplace(it, "Be happy");
    std_it = std_vector.emplace(std_it, "Be happy");
    EXPECT_TRUE(equel_vector_full(vector, std_vector));
}

TEST(vector, emplace_back) {
    std::vector<double> std_vector;
    std_vector.push_back(1.3);
    std_vector.push_back(2.008);
    std_vector.push_back(3);
    std_vector.push_back(4);
    std_vector.emplace_back(567.0);
    std_vector.emplace_back(111.12345);
    std_vector.emplace_back(98765.90987);
    study::vector<double> vector;
    vector.push_back(1.3);
    vector.push_back(2.008);
    vector.push_back(3);
    vector.push_back(4);
    vector.emplace_back(567.0, 111.12345, 98765.90987);
    EXPECT_TRUE(equel_vector(vector, std_vector));

    std::vector<const char*> std_vector1;
    std_vector1.push_back("gg");
    std_vector1.emplace_back("hello");
    study::vector<const char*> vector1;
    vector1.push_back("gg");
    vector1.emplace_back("hello");
    EXPECT_TRUE(equel_vector(vector1, std_vector1));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
