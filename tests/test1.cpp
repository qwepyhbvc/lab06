#include <print.hpp>
#include <gtest/gtest.h>
#include <fstream>

TEST(Print, InFileStream)
{
    std::string filepath = "test_output.txt";
    std::string text = "hello world";
    
    // Записываем в файл
    std::ofstream out(filepath);
    print(text, out);
    out.close();
    
    // Читаем из файла
    std::string result;
    std::ifstream in(filepath);
    std::getline(in, result);
    
    EXPECT_EQ(result, text);
}

TEST(Print, CoutStream)
{
    testing::internal::CaptureStdout();
    print("test message");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "test message");
}
