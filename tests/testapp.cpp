// #include <multiply/multiply.h>
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
// #include "multiply.h"
#include "service.h"
#include "invertindex.h"
// #include "appparam.h"
// #include "appparam.h"

using namespace nlohmann::json_abi_v3_11_3;

// TEST(MultiplyTests, TestIntegerOne_One)
// {
//     const auto expected = 1;
//     const auto actual = multiply(1, 1);
//     ASSERT_EQ(expected, actual);
// }


// TEST(MultiplyTests, TestIntegerZero_Zero)
// {
//     const auto expected = 0;
//     const auto actual = multiply(0, 0);
//     ASSERT_EQ(expected, actual);
// }

// TEST(MultiplyTests, TestIntegerZero_One)
// {
//     const auto expected = 0;
//     const auto actual = multiply(0, 1);
//     ASSERT_EQ(actual, expected);
// }

TEST(TestApplication, TestSerializaton){
    json jString = "this is a simple test";
    std::string cppString = jString.dump();
    EXPECT_EQ(bool(cppString == std::string(jString.dump())), true);
}

TEST(TestApplication, TestEqualMap){
    Service serv;
    serv.readFile("freq_dictionary.map");
    vector<string> vec1 = serv.GetDataFile();
    serv.clearVec();
    
    serv.readFile("freq_dictionaryTh.map");
    vector<string> vec2 = serv.GetDataFile();
    ASSERT_EQ(vec1, vec2);    
}

// TEST(MultiplyTests, ClearVector){
// Service serv;
// serv.readFile("config.json");
// int sizeVec = serv.SizeVector();
// EXPECT_EQ(sizeVec > 0, true);
// serv.clearVec();
// sizeVec = serv.SizeVector();
// EXPECT_EQ(sizeVec == 0, true);
// }

// TEST(MultiplyTests, ClearVec1){
//   Service serv;
//   vector<string>vec{"one", "two", "three"};
//   serv.clearVec1(vec);
//   vector<string>vec1;
//   ASSERT_EQ(vec, vec1);
// }

// TEST(MultiplyTests, readFileJSON){
//   Service serv;
//   json j = {
//     {"requests",{
//       "milk water","sugar solt","index"
//     }
//     }
//   };
//   /*файл должен наодиться в папке skill_project\build, если его там, значит его там нет или 
//   он находится в папке skill_project, тогда к имени файла надо добавлять ..\\fname.xyz*/
//   //пока выключил этих механизмы в классе Service
//   // serv.readjson("..\\requests.json");
//   // json t = serv.GetJSON();
//   // cout << "TEST " << t << endl;
//   std::ifstream f("..\\requests.json");
//   json data = json::parse(f);
//   ASSERT_EQ(j, data);
// }

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}