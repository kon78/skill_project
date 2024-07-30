#include <gtest/gtest.h>

#include "service.h"
#include"convjson.h"

// TEST(test_Service_case, test_Service_case_NumbFiles__Test)
TEST(testService, NumbFiles)
{
    // int argc = 0; char* argv[] = {"this", " is", " test\n"};
    // Service* TestServ = new Service(argc, argv);
    Service TestServ;
    int n = TestServ.numbRespFiles();
    EXPECT_EQ(n, 7);
    // delete TestServ;
}

TEST(testServiceArgum, arguments)
{
    int argc = 3; char* argv[] = {"this", "is", "test"};
    // string str; int i = 0;

    // for(auto &arg : argv){
    //     ++i; str += arg[i];
    //     if(i > argc)break;
    //     str += " ";
    // }
    string str = "this is test";
    Service* TestServ = new Service(argc, argv);
    string value = TestServ->GetArgumInfo();
  EXPECT_EQ(bool(value == str),true);
  delete TestServ;
}

TEST(sample_test_case, sample_test){
    EXPECT_EQ(1,1);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}