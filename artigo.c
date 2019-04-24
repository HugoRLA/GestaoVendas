#include <zconf.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "artigo.h"



long insereArt(char* nome, char* preco){

    int codigo = -1;
    int apontador;
    int fdStrings;
    int fdArtigos;
    //TODO meter como constante
    int entrieSize = 64;
    char entry[64];



    fdStrings = open("STRINGS.txt",O_CREAT | O_RDWR |O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdStrings < 0){
        printf("ERROR OPENING STRIGNS FILE\n");
    }

    fdArtigos = open("ARTIGOS.txt", O_CREAT | O_RDWR | O_APPEND, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdArtigos < 0){
        printf("ERROR OPENING ARTIGOS FILE\n");

    }

    //criar apontador

    apontador = lseek(fdStrings, 0 , SEEK_END);
    printf("Apontador para String : %d\n", apontador);

    //adicionar newline ao nome

    char *newstr = malloc(strlen(nome) + 2);
    strcpy(newstr, nome);
    strcat(newstr, "\n");

    write(fdStrings, newstr, strlen(newstr));


    codigo = lseek(fdArtigos, 0 , SEEK_END) / entrieSize;
    printf("Codigo : %d\n", codigo);



    sprintf(entry, "%d %s %d", codigo, preco, apontador);
    memset(entry + strlen(entry), ' ', entrieSize);
    entry[entrieSize - 1] = '\n';

    write(fdArtigos, entry, entrieSize);

    close(fdArtigos);
    close(fdStrings);

	return codigo;
}

int alteraNome(long codigo, char* nome){



    int apontador;
    int fdStrings;
    int fdArtigos;
    //meter como constane
    int entrieSize = 64;
    char entry[64];

    const char s[2] = " ";
    char *token;



    fdStrings = open("STRINGS.txt",O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdStrings < 0){
        printf("ERROR OPENING STRIGNS FILE\n");
    }

    fdArtigos = open("ARTIGOS.txt", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
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

    printf("Codigo: %s\n", token);

    preco = strtok(NULL, s);

    printf("preço: %s\n", token);

    token = strtok(NULL, s);

    printf("apontador: %s\n", token);

    sprintf(entry, "%ld %s %d", codigo, preco, apontador);
    memset(entry + strlen(entry), ' ', entrieSize);
    entry[entrieSize - 1] = '\n';

    lseek(fdArtigos, codigo * entrieSize, SEEK_SET);

    write(fdArtigos, entry, entrieSize);

    close(fdArtigos);
    close(fdStrings);

}

int alteraPreco(long codigo, int preco){
	//p
	//procura o artigo no ficheiro ARTIGOS
	//se existir, altera o preco
	//se nao existir -1;
	//se erro return -1;

}




