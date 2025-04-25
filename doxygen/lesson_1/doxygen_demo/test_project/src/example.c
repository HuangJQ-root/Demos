#include "example.h"

/**
 * @brief 此函数用于获取消息名
 *
 * 该函数接收一个消息指针。
 *
 * @param msg 指向一个消息结构体
 * @return 消息名
 */
char* Get_Msg_name(MSG_t* msg) {
    return msg->name;
}

