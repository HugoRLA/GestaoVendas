
#include "stock.h"


void showStock(int codigo){

    int entrieSize = 10;
    char entry[10];

    const char s[2] = " ";
    char *token;
    char *precoaux;
    char *quantidade;
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

    read(fdStock, entry,entrieSize);


    token = strtok(entry, s);

    quantidade= strtok(NULL, s);
    int quantidade1=atoi(quantidade);

    lseek(fdArtigos, codigo * entrieSize, SEEK_SET);

    read(fdArtigos, entry, entrieSize);

    token = strtok(entry, s);

    precoaux = strtok(NULL, s);

    printf("Stock %d Preço %d",quantidade1,atoi(precoaux));

    close(fdArtigos);
    close(fdStock);


}

void modifyStock(int codigo, int quantidade) {

    int entrieSize = 10;
    char entry[10];

    char* quantidadeStock;
    char* precoaux;
    char* token;
    const char s[2] = " ";


    if (quantidade > 0) {
        int fdStock = open("STOCKS.txt", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
        if (fdStock < 0) {
            printf("ERROR OPENING STOCKS FILE\n");
        }

        lseek(fdStock, codigo * entrieSize, SEEK_SET);

        read(fdStock, entry, entrieSize);

        token = strtok(entry, s);
        quantidadeStock = strtok(NULL, s);

        int quantidadeFinal = atoi(quantidadeStock) + quantidade;

        sprintf(entry, "%d %d", codigo, quantidadeFinal);
        memset(entry + strlen(entry), ' ', entrieSize);
        entry[entrieSize - 1] = '\n';

        lseek(fdStock, codigo * entrieSize, SEEK_SET);

        write(fdStock, entry, entrieSize);
        write(1, entry, entrieSize);

        close(fdStock);
    } else {

        int fdStock = open("STOCKS.txt", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
        if (fdStock < 0) {
            printf("ERROR OPENING STOCKS FILE\n");
        }
        int fdArtigos = open("ARTIGOS.txt", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
        if (fdStock < 0) {
            printf("ERROR OPENING ARTIGOS FILE\n");
        }
        int fdVenda = open("VENDAS.txt", O_RDWR | O_CREAT | O_APPEND,0666);
        if (fdVenda < 0) {
            printf("ERROR OPENING VENDA FILE\n");
        }

        lseek(fdStock, codigo * entrieSize, SEEK_SET);

        read(fdStock, entry, entrieSize);

        token = strtok(entry, s);
        char *quantidadeStock = strtok(NULL, s);

        int guardaQuant = atoi(quantidadeStock);

        lseek(fdArtigos, codigo * entrieSize, SEEK_SET);
        read(fdArtigos, entry, entrieSize);


        token = strtok(entry, s);

        precoaux = strtok(NULL, s);

        int preco=atoi(precoaux);

        int quantidadenova = guardaQuant + quantidade;

        if(quantidadenova >= 0) {

            sprintf(entry, "%d %d", codigo, quantidadenova);
            memset(entry + strlen(entry), ' ', entrieSize);
            entry[entrieSize-1]='\n';
            lseek(fdStock, codigo * entrieSize, SEEK_SET);
            write(fdStock, entry, entrieSize);

             int montante = preco*(-quantidade);
             printf("Codigo: %d Preco: %d Montante: %d",codigo,preco,montante);
                sprintf(entry, "%d %d %d", codigo, -quantidade,montante);
                memset(entry + strlen(entry), ' ', entrieSize);
                entry[entrieSize-1]='\n';
                lseek(fdVenda, codigo * entrieSize, SEEK_SET);
                write(fdVenda,entry,entrieSize);

            
        }else{
            printf("Nao é possivel efetuar o seu pedido de venda, quantidade atual é: %d",guardaQuant);

            close(fdVenda);
            close(fdArtigos);
            close(fdStock);

    }
 }
}

int main(int argc, char const *argv[]){

    if(argc == 2){
        showStock(atoi(argv[1]));
    }else if (argc == 3){
        modifyStock(atoi(argv[1]), atoi(argv[2]));
    }

}

