#include "sv.h"


int main(){

    int privatefifo, dummyfifo, publicfifo, n, done;
    struct message msg;
    FILE *fin;
    static char buffer[PIPE_BUF];

    /*creating the PUBLIC fifo*/
    mkfifo(PUBLIC, S_IFIFO | 0666);

    /*
    Server process opens the PUBLIC fifo in write mode to make sure that
    the PUBLIC fifo is associated with atleast one WRITER process. As a
    result it never receives EOF on the PUBLIC fifo. The server process
    will block any empty PUBLIC fifo waiting for additional messages to
    be written. This technique saves us from having to close and reopen
    the public FIFO every time a client process finishes its activities.
    */

    if( (publicfifo = open(PUBLIC, O_RDONLY)) < 0 ||
        (dummyfifo = open(PUBLIC, O_WRONLY | O_NDELAY)) < 0) {
        perror(PUBLIC);
        _exit(1);
    }

    /*Read the message from PUBLIC fifo*/
    while(read(publicfifo, &msg, sizeof(msg)) > 0) {

        n=0;
        done=0;

        do {
            if((privatefifo = open(msg.fifo_name, O_WRONLY|O_NDELAY)) == -1) {
                sleep(5);
            }
            else {



                write(privatefifo,"\n",1);
                printf("MSG FROM FIFO : %s\n", msg.fifo_name);
                printf("MSG COMMAND : %s\n", msg.cmd_line);

                write(privatefifo,msg.cmd_line, strlen(msg.cmd_line));
                memset(buffer, 0x0, PIPE_BUF);

                //while((n= read(fileno(fin), buffer, PIPE_BUF)) > 0) {
                //    write(privatefifo, buffer, n);
                //    memset(buffer, 0x0, PIPE_BUF);
                //}


                done = 1;
            }
        }while(n++ < 5 && !done);

        if(!done) {
            perror("Not accessed the private fifo\n");
            _exit(1);
        }

    }
    return 0;

}