#include <gtest/gtest.h>
#include "AVL/self_balancing_binary_search_tree.h"
#include "hash_table/hash_table.h"


static study::DataBaseClass* tree;
static study::HashTable hash_table;
static study::AVL avl;

std::string GetOutLine(const std::string& key, std::function<void(const std::string&)> fun1, std::function<void()> fun2) {
    std::string result;
    std::stringstream out;
    std::streambuf *oldbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
    if (key != "") {
        fun1(key);
    } else {
        fun2();
    }
    std::getline(out, result);
    std::cout.rdbuf(oldbuf);
    return result;
}

TEST(Hash, Upload) {
    tree = &hash_table;
    tree->Upload("datasets/test.dat");
    EXPECT_TRUE(tree->Exist("one"));
    EXPECT_TRUE(tree->Exist("two"));
    EXPECT_FALSE(tree->Exist("eleven"));

    tree->Upload("datasets/10000.dat");
    EXPECT_TRUE(tree->Exist("40024861"));
    EXPECT_FALSE(tree->Exist("wrong"));
    
    EXPECT_FALSE(tree->Upload("datasets/clear.dat"));
    tree->Clear();
}

TEST(Avl, Upload) {
    tree = &avl;
    tree->Upload("datasets/test.dat");
    EXPECT_TRUE(tree->Exist("one"));
    EXPECT_TRUE(tree->Exist("two"));
    EXPECT_FALSE(tree->Exist("eleven"));

    tree->Upload("datasets/10000.dat");
    EXPECT_TRUE(tree->Exist("40024861"));
    EXPECT_FALSE(tree->Exist("wrong"));
    
    EXPECT_FALSE(tree->Upload("datasets/clear.dat"));
    tree->Clear();
}

TEST(Hash, Set) {
    tree = &hash_table;
    EXPECT_FALSE(tree->Exist("Dog"));
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    EXPECT_TRUE(tree->Exist("Dog"));
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    std::string temp = GetOutLine("Dog", f, nullptr);
    EXPECT_TRUE("[0;40;97msurname name 1997 city 5[0m" == temp);

    EXPECT_FALSE(tree->Set({"Dog", {{"n", "s", 56, "c", 5}, time(nullptr), -1}}));
    tree->Clear();
}

TEST(Avl, Set) {
    tree = &avl;
    EXPECT_FALSE(tree->Exist("Dog"));
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    EXPECT_TRUE(tree->Exist("Dog"));
    EXPECT_FALSE(tree->Exist("Dog2"));
    EXPECT_TRUE(tree->Set({"Dog2", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    EXPECT_TRUE(tree->Exist("Dog2"));
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    std::string temp = GetOutLine("Dog", f, nullptr);
    EXPECT_TRUE("[0;40;97msurname name 1997 city 5[0m" == temp);

    EXPECT_FALSE(tree->Set({"Dog", {{"n", "s", 56, "c", 5}, time(nullptr), -1}}));

    tree->Clear();
}

TEST(Hash, Get) {
    tree = &hash_table;
    tree->Upload("datasets/test.dat");
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    EXPECT_EQ("[0;40;97mAldred Damon 1990 Podgorica 1000[0m", GetOutLine("one", f, nullptr));
    EXPECT_EQ("[0;40;97mWu Kirsten 2009 Nassau 50[0m", GetOutLine("five", f, nullptr));
    EXPECT_EQ("[0;40;97m(null)[0m", GetOutLine("7", f, nullptr));
    tree->Clear();
}

TEST(Avl, Get) {
    tree = &avl;
    EXPECT_EQ(tree->Upload("datasets/test.dat"), 5);
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    EXPECT_EQ("[0;40;97mAldred Damon 1990 Podgorica 1000[0m", GetOutLine("one", f, nullptr));
    EXPECT_EQ("[0;40;97mWu Kirsten 2009 Nassau 50[0m", GetOutLine("five", f, nullptr));
    EXPECT_EQ("[0;40;97m(null)[0m", GetOutLine("7", f, nullptr));
    tree->Clear();
}

TEST(Hash, Del) {
    tree = &hash_table;
    EXPECT_EQ(tree->Upload("datasets/test.dat"), 5);
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    EXPECT_EQ("[0;40;97mAldred Damon 1990 Podgorica 1000[0m", GetOutLine("one", f, nullptr));
    EXPECT_TRUE(tree->Exist("one"));
    tree->Del("one");
    EXPECT_FALSE(tree->Exist("one"));
    EXPECT_FALSE(tree->Del("one"));
    EXPECT_EQ("[0;40;97m(null)[0m", GetOutLine("one", f, nullptr));
    tree->Clear();
}

TEST(Avl, Del) {
    tree = &avl;
    tree->Upload("datasets/test.dat");
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    EXPECT_EQ("[0;40;97mAldred Damon 1990 Podgorica 1000[0m", GetOutLine("one", f, nullptr));
    EXPECT_TRUE(tree->Exist("one"));
    tree->Del("one");
    EXPECT_FALSE(tree->Exist("one"));
    EXPECT_FALSE(tree->Del("one"));
    EXPECT_EQ("[0;40;97m(null)[0m", GetOutLine("one", f, nullptr));
    tree->Clear();
}

TEST(Hash, Update) {
    tree = &hash_table;
    tree->Upload("datasets/test.dat");
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    EXPECT_EQ("[0;40;97mAldred Damon 1990 Podgorica 1000[0m", GetOutLine("one", f, nullptr));
    EXPECT_TRUE(tree->Update({"one", {{"", "", 1997, "Novosibirsk", -1}, time(nullptr), -1}}));
    EXPECT_EQ("[0;40;97mAldred Damon 1997 Novosibirsk 1000[0m", GetOutLine("one", f, nullptr));

    EXPECT_FALSE(tree->Update({"eleven", {{"", "", 1997, "Novosibirsk", -1}, time(nullptr), -1}}));

    tree->Clear();
}

TEST(Avl, Update) {
    tree = &avl;
    tree->Upload("datasets/test.dat");
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    EXPECT_EQ("[0;40;97mAldred Damon 1990 Podgorica 1000[0m", GetOutLine("one", f, nullptr));
    EXPECT_TRUE(tree->Update({"one", {{"", "", 1997, "Novosibirsk", -1}, time(nullptr), -1}}));
    EXPECT_EQ("[0;40;97mAldred Damon 1997 Novosibirsk 1000[0m", GetOutLine("one", f, nullptr));

    EXPECT_FALSE(tree->Update({"eleven", {{"", "", 1997, "Novosibirsk", -1}, time(nullptr), -1}}));

    tree->Clear();
}

TEST(Hash, Keys) {
    tree = &hash_table;
    auto f = [&]() {
        tree->Keys();
    };
    EXPECT_EQ("\x1B[0;40;97mEmpty\x1B[0m", GetOutLine("", nullptr, f));
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    EXPECT_EQ("[0;40;97m1) Dog[0m", GetOutLine("", nullptr, f));
    tree->Clear();
}

TEST(Avl, Keys) {
    tree = &avl;
    auto f = [&]() {
        tree->Keys();
    };
    EXPECT_EQ("\x1B[0;40;97mEmpty\x1B[0m", GetOutLine("", nullptr, f));
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    
    EXPECT_EQ("[0;40;97m1) Dog[0m", GetOutLine("", nullptr, f));
    tree->Clear();
}

TEST(Hash, Rename) {
    tree = &hash_table;
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    auto f = [&]() {
        tree->Keys();
    };
    EXPECT_EQ("[0;40;97m1) Dog[0m", GetOutLine("", nullptr, f));
    EXPECT_TRUE(tree->Rename("Dog", "Cat"));
    EXPECT_FALSE(tree->Rename("Dog", "Cat"));
    EXPECT_EQ("[0;40;97m1) Cat[0m", GetOutLine("", nullptr, f));
    tree->Clear();
}

TEST(Avl, Rename) {
    tree = &avl;
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    auto f = [&]() {
        tree->Keys();
    };
    EXPECT_EQ("[0;40;97m1) Dog[0m", GetOutLine("", nullptr, f));
    EXPECT_TRUE(tree->Rename("Dog", "Cat"));
    EXPECT_FALSE(tree->Rename("Dog", "Cat"));
    EXPECT_EQ("[0;40;97m1) Cat[0m", GetOutLine("", nullptr, f));
    tree->Clear();
}

TEST(Hash, TTL) {
    tree = &hash_table;
    auto cur_time = time(nullptr);
    EXPECT_TRUE(tree->Set({"Cat", {{"name", "surname", 1997, "city", 5}, cur_time, 0}}));
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, cur_time, 100}}));
    EXPECT_TRUE(tree->TTL("Dog") <= 100);
    tree->TTL("Cat");
    EXPECT_TRUE(tree->Exist("Cat"));
    tree->Clear();
}

TEST(Avl, TTL) {
    tree = &avl;
    auto cur_time = time(nullptr);
    EXPECT_TRUE(tree->Set({"Cat", {{"name", "surname", 1997, "city", 5}, cur_time, 0}}));
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, cur_time, 100}}));
    EXPECT_TRUE(tree->TTL("Dog") <= 100);
    tree->TTL("Cat");
    EXPECT_TRUE(tree->Exist("Cat"));
    tree->Clear();
}

TEST(Hash, Find) {
    tree = &hash_table;
    tree->Upload("datasets/test.dat");
    std::string result;
    std::stringstream out;
    std::streambuf *oldbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
    tree->Find({"", "", -1, "Kingston", -1});
    std::getline(out, result);
    std::cout.rdbuf(oldbuf);
    EXPECT_EQ("\x1B[0;40;97m1) three\x1B[0m", result);
    tree->Clear();
}

TEST(Avl, Find) {
    tree = &avl;
    tree->Upload("datasets/test.dat");
    std::string result;
    std::stringstream out;
    std::streambuf *oldbuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
    tree->Find({"", "", -1, "Kingston", -1});
    std::getline(out, result);
    std::cout.rdbuf(oldbuf);
    EXPECT_EQ("\x1B[0;40;97m1) three\x1B[0m", result);
    tree->Clear();
}

TEST(Hash, ShowAll) {
    tree = &hash_table;
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    auto f = [&]() {
        tree->ShowAll();
    };
    EXPECT_EQ("[0;40;97m1) surname name 1997 city 5[0m", GetOutLine("", nullptr, f));
    tree->Clear();
}

TEST(Avl, ShowAll) {
    tree = &avl;
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    auto f = [&]() {
        tree->ShowAll();
    };
    EXPECT_EQ("[0;40;97m1) surname name 1997 city 5[0m", GetOutLine("", nullptr, f));
    tree->Clear();
}

TEST(Hash, Export) {
    tree = &hash_table;
    EXPECT_TRUE(tree->Set({"Cat", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    EXPECT_EQ(tree->Export("temp.txt"), 2);
    EXPECT_EQ(tree->Upload("temp.txt"), 2);
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    std::string temp = GetOutLine("Dog", f, nullptr);
    EXPECT_EQ("[0;40;97msurname name 1997 city 5[0m", temp);
    temp = GetOutLine("Cat", f, nullptr);
    EXPECT_EQ("[0;40;97msurname name 1997 city 5[0m", temp);
    remove("temp.txt");
    tree->Clear();
}

TEST(Avl, Export) {
    tree = &avl;
    EXPECT_TRUE(tree->Set({"Cat", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    EXPECT_TRUE(tree->Set({"Dog", {{"name", "surname", 1997, "city", 5}, time(nullptr), -1}}));
    EXPECT_EQ(tree->Export("temp.txt"), 2);
    EXPECT_EQ(tree->Upload("temp.txt"), 2);
    auto f = [&](const std::string& key) {
        tree->Get(key);
    };
    std::string temp = GetOutLine("Dog", f, nullptr);
    EXPECT_EQ("[0;40;97msurname name 1997 city 5[0m", temp);
    temp = GetOutLine("Cat", f, nullptr);
    EXPECT_EQ("[0;40;97msurname name 1997 city 5[0m", temp);
    remove("temp.txt");
    tree->Clear();
}

TEST (Avl, Balancing) {
    tree = &avl;
    tree->Upload("datasets/100.dat");
    avl.ExportToDot("before_del");
    char rec_srting[100];
    long count2 = 0;
    while (count2 < 500) {
        std::sprintf(rec_srting, "%.04ld", count2);
        if (tree->Del(rec_srting)) {
            EXPECT_TRUE(avl.TreeBalanceCheck());
        }
        count2 += 1;
    }
    tree->Del("0570");  // удаление корня
    // удаление левого узла, при отсутствии правого
    tree->Del("5100");
    tree->Del("4100");
    avl.ExportToDot("after_del");

    while (count2 < 9999) {
        std::sprintf(rec_srting, "%.04ld", count2);
        if (tree->Del(rec_srting)) {
            EXPECT_TRUE(avl.TreeBalanceCheck());
        }
        count2 += 1;
    }
    avl.ExportToDot("full_del");
    tree->Clear();
}

TEST (Avl, Operators) {
    tree = &avl;
    study::AVL avl_cpy;
    study::AVL avl_move;
    study::DataBaseClass* tree_cpy = &avl_cpy;
    study::DataBaseClass* tree_move = &avl_move;

    tree->Upload("datasets/test.dat");
    avl_cpy = avl;
    EXPECT_TRUE(tree->Exist("two"));
    EXPECT_TRUE(tree_cpy->Exist("two"));

    avl_move = std::move(avl);
    EXPECT_FALSE(tree->Exist("two"));
    EXPECT_TRUE(tree_move->Exist("two"));

    tree_cpy->Del("two");
    EXPECT_TRUE(tree_cpy->Exist("four"));
    avl_move = std::move(avl_cpy);
    EXPECT_FALSE(tree->Exist("two"));
    EXPECT_FALSE(tree_move->Exist("two"));
    EXPECT_FALSE(tree_cpy->Exist("four"));
    EXPECT_TRUE(tree_move->Exist("four"));

    tree->Clear();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
