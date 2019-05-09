
#include "cv.h"

int main()
{

    int publicfifo, privatefifo, n;
    static char buffer[PIPE_BUF];
    struct message msg;
    int i=0;

    /*Using sprintf to create a unique fifo name
    and save into message structure*/
    sprintf(msg.fifo_name, "/tmp/fifo%d", getpid());

    /*Creating the PRIVATE fifo*/
    if(mkfifo(msg.fifo_name, S_IFIFO | 0666) < 0) {
        //perror(msg.fifo_name); substituir para escrever para o err
        _exit(1);
    }

    /*Opening PUBLIC fifo in WRITE ONLY mode*/
    if((publicfifo = open(PUBLIC,O_WRONLY)) < 0) {
        unlink(msg.fifo_name);
        //perror(PUBLIC); substituir para escrever para o err
        _exit(1);
    }

    while (read(0, &buffer[i], 1) >0) {
       /* end of line */ 
    if (buffer[i] == '\n' || buffer[i] == 0x0) {
       
       strcpy(msg.cmd_line,buffer);
       
        //escreve para o servidor
        write(publicfifo, &msg, sizeof(msg));


        //abre fifo privado para ler do servidor
        if((privatefifo = open(msg.fifo_name, O_RDONLY))< 0) {
          ///  printf("1\n");
            perror(msg.fifo_name);
            goto CLEANUP;
        }

        while((n = read(privatefifo, buffer, PIPE_BUF)) > 0) {
             write(1, buffer, n);
        }

        close(privatefifo);
            
    
     i=0;

    }
    else {i++;}

}
    //fecha e elimana fifo
    CLEANUP:
    close(publicfifo);
    unlink(msg.fifo_name);

    return 0;
}
