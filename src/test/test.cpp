#include <gtest/gtest.h>
#include "lib/alg.h"

TEST(AlgoTest, SameResult)
{
    std::vector<std::string> strings = 
    {
        "One two OreeOle",
        "O?e",
        "aaa???aaa"
        "AAAAAAOneAAAA",
        "AxA"
    };
    std::string pattern = "O?e";
    for (auto& s : strings){
        auto kmp = KMP(pattern, s);
        auto fnd = find(pattern, s);
        ASSERT_EQ(kmp.size(),fnd.size()) << s;
        for (int i = 0; i < kmp.size(); ++i) {
            ASSERT_EQ(kmp[i].first, fnd[i].first) << s;
            ASSERT_EQ(kmp[i].second, fnd[i].second) << s;
        }
       
    }    
}

TEST(AlgoTest, KMPTest1)
{
    std::string s = "abcdef";
    std::string p = "?";
    auto kmp = KMP(p,s);
    ASSERT_EQ(kmp.size(),s.size());
    for (int i = 0; i < kmp.size(); ++i) {
        ASSERT_EQ(kmp[i].first, i+1);
        ASSERT_EQ(kmp[i].second.size(), 1);
        ASSERT_EQ(kmp[i].second[0], s[i]);
    }
}


TEST(AlgoTest, KMPTest2)
{
    std::string s = "abcdef";
    std::string p = "??";
    auto kmp = KMP(p,s);
    ASSERT_EQ(kmp.size(),5);
    for (int i = 1; i < kmp.size(); ++i) {
        ASSERT_EQ(kmp[i-1].first, i);
        ASSERT_EQ(kmp[i-1].second, s.substr(i-1,2));
    }
}



TEST(AlgoTest, KMPTest3)
{
    std::string s = "abcdef";
    std::string p = "??????";
    auto kmp = KMP(p,s);
    ASSERT_EQ(kmp.size(),1);
    for (int i = 1; i < kmp.size(); ++i) {
        ASSERT_EQ(kmp[i-1].first, i);
        ASSERT_EQ(kmp[i-1].second, s.substr(i-1,2));
    }
}

TEST(AlgoTest, KMPTest4) 
{
    std::string s = "abcdef";
    std::string p = "???a??";
    auto kmp = KMP(p,s);
    ASSERT_EQ(kmp.size(),0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}