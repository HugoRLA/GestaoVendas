
#include "stock.h"


void showStock(int codigo){

    int entrieSize = 10;
    char entry[10];
    int readBytes;
    const char s[2] = " ";
   
    int fdStock = open("STOCKS.txt", O_RDONLY, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdStock  < 0){
        printf("ERROR OPENING STOCKS FILE\n");
    }
    int fdArtigos = open("ARTIGOS.txt", O_RDONLY, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdArtigos  < 0){
        printf("ERROR OPENING ARTIGOS FILE\n");
    }
    //buscar a quantidade
    lseek(fdStock, codigo * entrieSize, SEEK_SET);

    readBytes =read(fdStock, entry,entrieSize);
    char* token1;
    char* quantidade;

    token1 = strtok(entry, s);

    quantidade= strtok(NULL, s);
    int quantidade1=atoi(quantidade);

    lseek(fdArtigos, codigo * entrieSize, SEEK_SET);

    read(fdArtigos, entry, entrieSize);
    char* token;
    char* precoaux;

    token = strtok(entry, s);

    precoaux = strtok(NULL, s);

    printf("Stock %d Preço %d",quantidade1,atoi(precoaux));

    close(fdArtigos);
    close(fdStock);


}

void modifyStock(int codigo, int quantidade){


    //abrir ficheiro do stock

    printf("hugo");


}

int main(int argc, char const *argv[]){

    if(argc == 2){
        showStock(atoi(argv[1]));
    }else if (argc == 3){
        modifyStock(atoi(argv[1]), atoi(argv[2]));
    }

}

