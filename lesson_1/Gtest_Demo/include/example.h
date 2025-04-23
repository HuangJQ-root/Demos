#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#define NEU_MSG_LEN 128

typedef struct {
    char name[NEU_MSG_LEN];
    char msg[NEU_MSG_LEN];
} MSG_t;

#ifdef __cplusplus
extern "C" {
#endif

char* Get_Msg_name(MSG_t* msg);

#ifdef __cplusplus
}
#endif

#endif