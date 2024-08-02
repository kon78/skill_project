#include <gtest/gtest.h>

#include "service.h"
#include "convjson.h"
#include "invertindex.h"
#include <memory>

TEST(testService, NumbFiles)
{
    Service TestServ;
    int n = TestServ.numbRespFiles();
    EXPECT_EQ(n, 7);
}

TEST(TestIvertIndex, index){
  int argc = 3; char* argv[] = {"this", "is", "test"};
  shared_ptr<Service>_shrdPtrServ = make_shared<Service>(argc, argv); 
  // service = new Service(argc, argv);
  ConverterJSON* clConvJSON = new ConverterJSON();
  InvertedIndex* clInvInd = new InvertedIndex();
  
  clConvJSON->SetObjServ(_shrdPtrServ);//передача
  clInvInd->SetObjServ(_shrdPtrServ);
  clInvInd->UpdateDocumentBase(clConvJSON->GetTextDocuments());
  int n = clInvInd->GetNumbFiles();
  // cout << "n=" << n << endl;
  EXPECT_EQ(n,7);
  //если убирать в тесте обьекты - ошибка
  // delete clInvInd; delete clInvInd; _shrdPtrServ.reset();
}

TEST(testServiceArgum, arguments)
{
    int argc = 3; char* argv[] = {"this", "is", "test"};
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