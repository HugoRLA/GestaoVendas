#include "ma.h"
#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUFFERSIZE = 256;

typedef struct Command{
  char operation;
  char* option1;
  char* option2;
} Command;


int main(){


    //ler continuadamente do standart input
    char ch[BUFFERSIZE];
    int readByte;
    const char s[2] = " ";
    char *token;
    Command cmd;



    while ((readByte = read(0, ch, 256)) > 0){

        //o newline conta como byte lido
        if(readByte > 1) {

            //para remover o new line
            readByte = readByte -1;
            //aloca tamanho
            char *str = (char *) malloc(readByte  * sizeof(char));

            //copia para o ch os numero de bytes lidos
            memmove(str, ch, readByte);

            //Separa os comando pelo espaço

            token = strtok(str, s);
            cmd.operation = token[0];
            token = strtok(NULL, s);
            cmd.option1 = token;
            token = strtok(NULL, s);
            cmd.option2 = token;

        }
    }
  
    if(strcmp(&cmd.operation,"i")==0) {
        insereArt(cmd.option1, atof(cmd.option2));
    }
    else{
        printf("errado\n");
    }

    if(strcmp(&cmd.operation,"n")==0) {
        alteraNome(atof(cmd.option1), cmd.option2);
    }
    else{
        printf("errado\n");
    }

    if(strcmp(&cmd.operation,"p")==0) {
        alteraPreco(atof(cmd.option1), atof(cmd.option2));
    }
    else{
        printf("errado\n");
    }
  
    return 0;


}

