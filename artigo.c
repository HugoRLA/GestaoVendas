#include <zconf.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "artigo.h"



int main(int argc, char const *argv[]) {

    int i = 0;
    int res;

    if(strcmp("i",argv[1]) == 0 ){

        insereArt(argv[2], argv[3]);

        //write(1,)

    }else if(strcmp("n",argv[1])== 0){

        alteraNome(atol(argv[2]), argv[3]);

    }else if(strcmp("p",argv[1])== 0){

        alteraPreco(atol(argv[2]), argv[3]);

    }



}


int insereArt(const char* nome,const char* preco){

    int codigo = -1;
    int apontador;
    int fdStrings;
    int fdArtigos;
    //TODO meter como constante
    int entrieSize = 64;
    char entry[64];


    fdStrings = open("STRINGS.txt", O_WRONLY);
    if(fdStrings < 0){
        printf("ERROR OPENING STRIGNS FILE\n");
    }

    fdArtigos = open("ARTIGOS.txt", O_WRONLY);
    if(fdArtigos < 0){
        printf("ERROR OPENING ARTIGOS FILE\n");

    }

    //criar apontador

    apontador = lseek(fdStrings, 0 , SEEK_END);

    //adicionar newline ao nome
    char *newstr = malloc(strlen(nome) + 2);
    strcpy(newstr, nome);
    strcat(newstr, "\n");

    write(fdStrings, newstr, strlen(newstr));


    codigo = lseek(fdArtigos, 0 , SEEK_END) / entrieSize;

    sprintf(entry, "%d %s %d", codigo, preco, apontador);
    memset(entry + strlen(entry), ' ', entrieSize);
    entry[entrieSize - 1] = '\n';

    write(fdArtigos, entry, entrieSize);

    close(fdArtigos);
    close(fdStrings);

    memset(entry, 0x0, entrieSize);
    sprintf(entry, "%d", codigo);
    memset(entry + strlen(entry), ' ', entrieSize);
    entry[entrieSize - 1] = '\n';

    write(1, entry,entrieSize);

    return 1;
}

int alteraNome(int codigo,const char* nome){



    int apontador;
    int fdStrings;
    int fdArtigos;
    //meter como constane
    int entrieSize = 64;
    char entry[64];

    const char s[2] = " ";
    char *token;



    fdStrings = open("STRINGS.txt",O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdStrings < 0){
        printf("ERROR OPENING STRIGNS FILE\n");
    }

    fdArtigos = open("ARTIGOS.txt", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdArtigos < 0){
        printf("ERROR OPENING ARTIGOS FILE\n");

    }


    // TODO codigo duplicado meter em funcoes

    //criar apontador

    apontador = lseek(fdStrings, 0 , SEEK_END);
    printf("Apontador para String : %d\n", apontador);

    //adicionar newline ao nome

    char *newstr = malloc(strlen(nome) + 2);
    strcpy(newstr, nome);
    strcat(newstr, "\n");

    write(fdStrings, newstr, strlen(newstr));

    //mete o apontador para a linha no ficheiro

    lseek(fdArtigos, codigo * entrieSize, SEEK_SET);

    read(fdArtigos, entry, entrieSize);


    //Separa os comando pelo espaço

    char* preco;

    token = strtok(entry, s);
    preco = strtok(NULL, s);
    token = strtok(NULL, s);


    sprintf(entry, "%d %s %d", codigo, preco, apontador);
    memset(entry + strlen(entry), ' ', entrieSize);
    entry[entrieSize - 1] = '\n';

    lseek(fdArtigos, codigo * entrieSize, SEEK_SET);

    write(fdArtigos, entry, entrieSize);

    close(fdArtigos);
    close(fdStrings);

    return 1;

}

int alteraPreco(int codigo, const char* preco){
    char* apontador;
    int fdArtigos;
    //meter como constane
    int entrieSize = 64;
    char entry[64];

    const char s[2] = " ";
    char *token;


    fdArtigos = open("ARTIGOS.txt", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdArtigos < 0){
        printf("ERROR OPENING ARTIGOS FILE\n");

    }

    lseek(fdArtigos, codigo * entrieSize, SEEK_SET);

    read(fdArtigos, entry, entrieSize);


    //Separa os comando pelo espaço

    char* precoaux;

    token = strtok(entry, s);
    printf("Codigo: %s\n", token);

    precoaux = strtok(NULL, s);
    printf("preço: %s\n", preco);

    apontador = strtok(NULL, s);
    printf("apontador: %s\n", token);
    int apontador1=atoi(apontador);

    sprintf(entry, "%d %s %d", codigo, preco, apontador1);
    memset(entry + strlen(entry), ' ', entrieSize);
    entry[entrieSize - 1] = '\n';

    lseek(fdArtigos, codigo * entrieSize, SEEK_SET);

    write(fdArtigos, entry, entrieSize);

    close(fdArtigos);

    return 1;

}








