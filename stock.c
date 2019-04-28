
#include "stock.h"


void showStock(int codigo){

    int entrieSize = 10;
    char entry[10];
    int readBytes;

    int fdStock = open("STOCKS.txt", O_RDONLY, S_IRWXU | S_IRWXG | S_IRWXO);
    if(fdStock  < 0){
        printf("ERROR OPENING STOCKS FILE\n");
    }

    lseek(fdStock, codigo * entrieSize, SEEK_SET);

    if( (readBytes = read(fdStock, entry, entrieSize)) == 0 ){

        //quantidade 0

    }else{

        //parse da linha para obter quantidade, mesma coisa que fizemos no artigo ppara modificar o preco
    }

    //abrir ficheiros dos artigos para saber o preco

    //posicinar com o lseek

    //ler a linha e basicamente fazer o mesmo que em cima no if


    //write da quantidade e do preco


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

