#include "sv.h"



void my_popen (const char *cmd, int privatefifo)
{
    int fd[2];
    int read_fd, write_fd, status,n;
    int pid;
    char ch[PIPE_BUF];
    char argv[PIPE_BUF];



    /* First, create a pipe and a pair of file descriptors for its both ends */
    pipe(fd);
    read_fd = fd[0];
    write_fd = fd[1];

    /* Now fork in order to create process from we'll read from */
    pid = fork();
    if (pid == 0) {
        /* Child process */

        /* Close "read" endpoint - child will only use write end */
        close(read_fd);

        /* Now "bind" fd 1 (standard output) to our "write" end of pipe */
        dup2(write_fd,1);

        memset(argv, 0x0, PIPE_BUF);
        strcat(argv, "./stock ");
        strcat(argv, cmd);
        printf("argv %s\n", argv);

        /* Execute command via shell - this will replace current process */
        execl("/bin/sh", "sh", "-c", argv, NULL);

        exit(1);


    } else {
        /* Parent */

        /* Close "write" end, not needed in this process */
        close(write_fd);

        wait(&status);

        memset(ch, 0x0, PIPE_BUF);

        while ((n = read(read_fd, ch, PIPE_BUF)) > 0){
            write(privatefifo,ch,n);
        };
        

    }
}



void initServer(){

    int fdVendas = open("VENDAS.txt",O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdVendas < 0){
        printf("ERROR OPENING VENDAS FILE\n");
    }
    close(fdVendas);

    int fdStock = open("STOCKS.txt", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdStock  < 0){
        printf("ERROR OPENING STOCKS FILE\n");

    }
    close(fdStock);
}

int main(){

    int privatefifo, dummyfifo, publicfifo, n, done;
    struct message msg;
    FILE *fin;
    static char buffer[PIPE_BUF];

    initServer();

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

        int pid;
        if((pid = fork()) == 0) {

            privatefifo = open(msg.fifo_name, O_WRONLY|O_NDELAY);

            my_popen(msg.cmd_line, privatefifo);

            close(privatefifo);

            exit(EXIT_SUCCESS);

        }else{

            signal(SIGCHLD,SIG_IGN);

        }


    }
    return 0;

}

