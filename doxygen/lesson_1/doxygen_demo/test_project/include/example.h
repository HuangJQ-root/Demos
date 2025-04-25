#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#define NEU_MSG_LEN 128

/**
 * @brief 表示一个消息结构体
 *
 * 该结构体用于存储限定长度的消息名和消息内容
 */
typedef struct {
    /**
     * @brief 消息名
     *
     * 包含了本条消息的名称
     */
    char name[NEU_MSG_LEN];

    /**
     * @brief 消息主体
     *
     * 包含了本条消息的内容
     */
    char msg[NEU_MSG_LEN];
} MSG_t;

typedef struct rerespon_msg
{
    MSG_t* msg;
    char* sender[NEU_MSG_LEN];
    char* receiver[NEU_MSG_LEN];
}rerespon_msg_t;


#ifdef __cplusplus
extern "C" {
#endif

char* Get_Msg_name(MSG_t* msg);

#ifdef __cplusplus
}
#endif

#endif