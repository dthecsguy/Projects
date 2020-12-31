#ifndef PARSE_TEST_H
#define PARSE_TEST_H

#include "gtest/gtest.h"
#include "../header/command.hpp"
#include "../header/master.hpp"
#include "../header/parse.hpp"

TEST(ParseTests, ValidParse){
    std::string input = "echo hello";
    Parse parser(input);
    parser.parse();
    parser.build_tree();
    testing::internal::CaptureStdout();
    bool result = parser.execute(0,1);
    std::string out = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(out, "hello\n");
    EXPECT_EQ(result, true);
}

TEST(ParseTests, ParseQuote){
    std::string input = "echo \"hello\"";
    Parse parser(input);
    parser.parse();
    parser.build_tree();
    testing::internal::CaptureStdout();
    bool result = parser.execute(0,1);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "hello\n");
    EXPECT_EQ(result, true);
}

TEST(ParseTests, ParseQuoteWithConnector){
    std::string input = "echo \"hello && goodbye\"";
    Parse parser(input);
    parser.parse();
    parser.build_tree();
    testing::internal::CaptureStdout();
    bool result = parser.execute(0,1);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "hello && goodbye\n");
    EXPECT_EQ(result, true);
}

TEST(ParseTests, ParseQuoteWithPipe){
    std::string input = "echo hello | wc";
    Parse parser(input);
    parser.parse();
    parser.build_tree();
    testing::internal::CaptureStdout();
    bool result = parser.execute(0,1);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "      1       1       6\n");
    EXPECT_EQ(result, true);
}

TEST(ParseTests, ParseQuoteWithOutputRedirect){
    std::string input = "echo hello > out";
    Parse parser(input);
    parser.parse();
    parser.build_tree();
    testing::internal::CaptureStdout();
    bool result = parser.execute(0,1);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(output, "");
    EXPECT_EQ(result, true);
}

#endif
