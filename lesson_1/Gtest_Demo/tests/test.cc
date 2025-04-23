#include <gtest/gtest.h>
#include "../include/example.h"  // 包含头文件


TEST(TestName, exampletest_1) {
    MSG_t *msg = (MSG_t*)malloc(sizeof(MSG_t));
    strcpy(msg->name, "num1");  
    char* name = Get_Msg_name(msg);
    EXPECT_STREQ(name, "num1");  // 使用 EXPECT_STREQ 比较字符串
    free(msg);
}