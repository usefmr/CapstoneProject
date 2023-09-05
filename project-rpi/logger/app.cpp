
#include "simpleLogger.h"
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg {
    long int msg_type;
    char some_text[BUFSIZ];
};

int main() {
     // LOG_FATAL << "this is a fatal error message";
    int running = 1;
    int msgid;
    struct my_msg some_data;
    long int msg_to_rec = 0;

    msgid = msgget((key_t)12345, 0666 | IPC_CREAT);

    while(true){
    msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_rec, 0);
   if (strncmp(some_data.some_text, "exit", 4) == 0) {
        LOG_TRACE << "user exiting app";
        running = 0;
        }
     if (strncmp(some_data.some_text, "error", 5) == 0) {
        LOG_ERROR << some_data.some_text;
        }
    else if (strncmp(some_data.some_text, "trace", 5) == 0){
        LOG_TRACE << some_data.some_text;
        }
    }


    msgctl(msgid, IPC_RMID, 0);
    return 0;
}
