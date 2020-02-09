#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "spawn-common.h"

int main( int argc, char * argv[] )
{
    int stop = 0;
    int mode = 0666;
    int msgid;
    struct MyMsgStruct msg;
    char const * argv_key = "9001";
    key_t msg_key;

    if ( argc < 2 )
    {
        fprintf( stderr, "Arguments not enough!\nspawn-manager <exit|list|new> sock\n" );
        return 1;
    }
    if ( argc > 2 )
    {
        argv_key = argv[2];
    }
    msg_key = (key_t)atoi(argv_key);
    if ( msg_key == 0 )
        msg_key = (key_t)elf_hash( argv_key, strlen(argv_key) );

    if ( ( msgid = msgget( msg_key, mode /*| IPC_CREAT*/ ) ) == -1 )
    {
        fprintf( stderr, "msgget failed with error: '%s', No spawn-fcgi service is running on sock(%s)\n", strerror(errno), argv_key );
    }
    else
    {
        int rc;

        if ( !stop )
        {
            memset( &msg, 0, sizeof(msg) );
            /* fgets( msg.msg_text, MSG_TEXT_SIZE, stdin ); */
            strcpy( msg.msg_text, argv[1] );

            /* msg.msg_text[ strlen(msg.msg_text) - 1 ] = 0; */
            msg.msg_type = 1;
            if ( ( rc = msgsnd( msgid, (void *)&msg, MSG_TEXT_SIZE, 0 ) ) == -1 )
            {
                stop = 1;
                fprintf( stderr, "msgsnd failed with error: %s\n", strerror(errno) );
            }
            else
            {
                if ( strncmp( msg.msg_text, "end", 3 ) == 0 )
                {
                    stop = 1;
                    printf("End manager process!\n");
                }
                else if ( strncmp( msg.msg_text, "exit", 4 ) == 0 )
                {
                    stop = 1;
                }
            }
        }
    }

    return 0;
}

