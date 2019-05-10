
#include "stock.h"


void showStock(int codigo){

    int entrieSize = 30;
    char entry[30];
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

    //verifica se o codido existe, ie, se o numero de bytes do ficheiro for maior que o offset, entao o codigo existe
    int offset = codigo * entrieSize;
    int readBytes = lseek(fdStock, 0, SEEK_END);
    lseek(fdStock, 0, SEEK_SET);

    if (readBytes > offset) {

        //buscar a quantidade
        lseek(fdStock, offset, SEEK_SET);

        read(fdStock, entry, entrieSize);

        token = strtok(entry, s);
        quantidade = strtok(NULL, s);
        int quantidade1 = atoi(quantidade);


        //buscar preco
        lseek(fdArtigos, offset, SEEK_SET);

        read(fdArtigos, entry, entrieSize);

        token = strtok(entry, s);

        precoaux = strtok(NULL, s);
        int preco = atoi(precoaux);
        // printf("Stock %d Preço %d",quantidade1,atoi(precoaux));

        close(fdArtigos);
        close(fdStock);

        memset(entry, 0x0, entrieSize);
        sprintf(entry, "Q: %d P:%d", quantidade1, preco);
        memset(entry + strlen(entry), ' ', entrieSize - strlen(entry));
        entry[entrieSize - 1] = '\n';

        write(1, entry, entrieSize);
    }

}

void modifyStock(int codigo, int quantidade) {

    int entrieSize = 30;
    char entry[30];

    char* quantidadeStock;
    char* precoaux;
    char* token;
    const char s[2] = " ";
     int fdStock;
     int fdVenda;
     int fdArtigos;

    fdStock = open("STOCKS.txt", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fdStock < 0) {
        printf("ERROR OPENING STOCKS FILE\n");
    }
    fdArtigos = open("ARTIGOS.txt", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fdStock < 0) {
        printf("ERROR OPENING ARTIGOS FILE\n");
    }
    fdVenda = open("VENDAS.txt", O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fdVenda < 0) {
        printf("ERROR OPENING VENDA FILE\n");
    }

     int offset = codigo * entrieSize;
    int readBytes = lseek(fdStock, 0, SEEK_END);
    lseek(fdStock, 0, SEEK_SET);

    if (readBytes > offset) {
  

    if(quantidade>0){


        lseek(fdStock, offset, SEEK_SET);

        read(fdStock, entry, entrieSize);

        token = strtok(entry, s);
        quantidadeStock = strtok(NULL, s);
        int quantidadeFinal = atoi(quantidadeStock) + quantidade;


       //escrever para nova quantidade para o Stock
        sprintf(entry, "%d %d", codigo, quantidadeFinal);
        memset(entry + strlen(entry), ' ', entrieSize -strlen(entry) );
        entry[entrieSize - 1] = '\n';

        lseek(fdStock, offset, SEEK_SET);

        write(fdStock, entry, entrieSize);

        //sendo output to client
        memset(entry, 0x0, entrieSize);
        sprintf(entry, "NQ: %d",quantidadeFinal);
        memset(entry + strlen(entry), ' ', entrieSize-strlen(entry) );
        entry[entrieSize - 1] = '\n';
        write(1, entry, entrieSize);

        
    } else {


        //buscar quantidade em stock
        lseek(fdStock, offset, SEEK_SET);
        read(fdStock, entry, entrieSize);

        token = strtok(entry, s);
        char *quantidadeStock = strtok(NULL, s);

        int guardaQuant = atoi(quantidadeStock);


        // Buscar preco
        lseek(fdArtigos, offset, SEEK_SET);
        read(fdArtigos, entry, entrieSize);

        token = strtok(entry, s);
        precoaux = strtok(NULL, s);

        int preco = atoi(precoaux);
        int quantidadenova = guardaQuant + quantidade;

        if(quantidadenova >= 0) {

            //escrever noca quantidade para o Stock
            memset(entry, 0x0, entrieSize);
            lseek(fdStock, offset, SEEK_SET);

            read(fdStock, entry, entrieSize);

            lseek(fdStock, offset, SEEK_SET);
            sprintf(entry, "%d %d", codigo, quantidadenova);
            memset(entry + strlen(entry), ' ', entrieSize -strlen(entry));
            entry[entrieSize-1]='\n';

            write(fdStock, entry, entrieSize);


            //Calcula motance e escrever para o venda
            memset(entry, 0x0, entrieSize);
            int montante = preco*(-quantidade);
            sprintf(entry, "%d %d %d", codigo, -quantidade, montante);
            memset(entry + strlen(entry), ' ', entrieSize - strlen(entry));
            entry[entrieSize-1] = '\n';

            lseek(fdVenda, 0, SEEK_END);
            write(fdVenda, entry, entrieSize);

            //send output to client
            memset(entry, 0x0, entrieSize);
            sprintf(entry, "C: %d P: %d M: %d", codigo, preco, montante);
            memset(entry + strlen(entry), ' ', entrieSize -strlen(entry) );
            entry[entrieSize - 1] = '\n';

            write(1, entry,entrieSize);

            
        }else{
            

            write(1, "Inds\n",5);
           
        }
    }

    close(fdVenda);
    close(fdArtigos);
    close(fdStock);
 }

}

int main(int argc, char const *argv[]){

    if(argc == 2){
        showStock(atoi(argv[1]));
    }else if (argc == 3){
        modifyStock(atoi(argv[1]), atoi(argv[2]));
    }

}

