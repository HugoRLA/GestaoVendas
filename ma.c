
#include "ma.h"

int initMA(){


    int fdStrings;
    int fdArtigos;

    fdStrings = open("STRINGS.txt", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdStrings < 0){
        printf("ERROR OPENING STRIGNS FILE\n");
        exit(1);
    }
    close(fdStrings);

    fdArtigos = open("ARTIGOS.txt", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdArtigos < 0){
        printf("ERROR OPENING ARTIGOS FILE\n");
        exit(1);
    }
    close(fdArtigos);

    int fdStock = open("STOCKS.txt", O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdStock  < 0){
        printf("ERROR OPENING STOCKS FILE\n");

    }
    close(fdStock);

    return 1;
}

int main(){


    char ch[PIPE_BUF];
    char argv[PIPE_BUF];
    int readByte;
    pid_t childpid;
    int fd[2];
    int read_fd, write_fd, n;
    int status;
    int i=0;
    initMA();


while (read(0, &ch[i], 1) > 0) {
   // printf("ch : %c\n",ch[i] );
    /* end of line */
    if (ch[i] == '\n' || ch[i] == 0x0) {

        //printf("cenas : %s\n", ch);

        pipe(fd);
        read_fd = fd[0];
        write_fd = fd[1];



            if((childpid = fork()) == -1){

                exit(1);
            }

            if (childpid == 0) {
                /* Child process */

                /* Close "read" endpoint - child will only use write end */
                close(read_fd);

                /* Now "bind" fd 1 (standard output) to our "write" end of pipe */

                dup2(write_fd,1);

                /* Execute command via shell - this will replace current process */

                //close(write_fd);

                memset(argv, 0x0, PIPE_BUF);
                strcat(argv, "./artigo ");
                strcat(argv, ch);
               

                execl("/bin/sh", "sh", "-c", argv, NULL);
                 
                exit(1);

            } else {
                /* Parent */

                /* Close "write" end, not needed in this process */
                close(write_fd);

                wait(&status);
                //usar argv em vez do ch
                memset(ch, 0x0, PIPE_BUF);
            
                while ((n = read(read_fd, ch, PIPE_BUF)) > 0){
                    write(1,ch,n);
                };

                memset(ch, 0x0, PIPE_BUF);
            }

            i =0;


        }else{
        i++;
    }
    }
  

    return 0;


}


