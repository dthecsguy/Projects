#ifndef COM_TEST_H
#define COM_TEST_H

#include "gtest/gtest.h"
#include "../header/command.hpp"
#include "../header/master.hpp"
#include "../header/parse.hpp"
 
TEST(SingleComTests, ValidCommand){
    char* command[] = {"echo", "hello world", NULL};

    Master* test = new COM(command);
    testing::internal::CaptureStdout();
    bool result = test->execute(0,1);

    EXPECT_EQ(testing::internal::GetCapturedStdout(), "hello world\n");
    EXPECT_EQ(result, true);
}

TEST(SingleComTests, InvalidCommand){
    char* command[] = {"burger_king", "hello world", NULL};

    Master* test = new COM(command);
    testing::internal::CaptureStderr();
    bool result = test->execute(0,1);

    EXPECT_EQ(testing::internal::GetCapturedStderr(), "No such file or directory\n");
    EXPECT_EQ(result, false);
}

TEST(SingleComTests, Quotes){
    char* command[] = {"echo", "\"hello && mate\"", NULL};
    
    Master* test = new COM(command);
    testing::internal::CaptureStdout();
    bool result = test->execute(0,1);
    
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "\"hello && mate\"\n");
    EXPECT_EQ(result, true);
}

#endif
