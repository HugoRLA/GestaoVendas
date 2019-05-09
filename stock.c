
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
    int preco=atoi(precoaux);
   // printf("Stock %d Preço %d",quantidade1,atoi(precoaux));

    close(fdArtigos);
    close(fdStock);

    memset(entry, 0x0, entrieSize);
    sprintf(entry, "Q: %d P:%d",quantidade1,preco);
    memset(entry + strlen(entry), ' ', entrieSize-strlen(entry));
    entry[entrieSize - 1] = '\n';

    write(1, entry,entrieSize);


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
    if(quantidade>0){
        fdStock = open("STOCKS.txt", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
        if (fdStock < 0) {
            printf("ERROR OPENING STOCKS FILE\n");
        }
        fdArtigos = open("ARTIGOS.txt", O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
        if (fdStock < 0) {
            printf("ERROR OPENING ARTIGOS FILE\n");
        }
        fdVenda = open("VENDAS.txt", O_RDWR | O_CREAT | O_APPEND,0666);
        if (fdVenda < 0) {
            printf("ERROR OPENING VENDA FILE\n");
        }


        lseek(fdStock, codigo * entrieSize, SEEK_SET);

        read(fdStock, entry, entrieSize);

        token = strtok(entry, s);
        quantidadeStock = strtok(NULL, s);
        int quantidadeFinal = atoi(quantidadeStock) + quantidade;
       
        sprintf(entry, "%d %d", codigo, quantidadeFinal);
        memset(entry + strlen(entry), ' ', entrieSize -strlen(entry) );
        entry[entrieSize - 1] = '\n';

        lseek(fdStock, codigo * entrieSize, SEEK_SET);

        write(fdStock, entry, entrieSize);

        //sendo output to client
         memset(entry, 0x0, entrieSize);
        sprintf(entry, "NQ: %d",quantidadeFinal);
        memset(entry + strlen(entry), ' ', entrieSize-strlen(entry) );
        entry[entrieSize - 1] = '\n';
        write(1, entry, entrieSize);

        
    } else {

       
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
            lseek(fdStock, codigo * entrieSize, SEEK_SET);

            read(fdStock, entry, entrieSize);
            
            sprintf(entry, "%d %d", codigo, quantidadenova);
            memset(entry + strlen(entry), ' ', entrieSize -strlen(entry));
            entry[entrieSize-1]='\n';

           
            write(fdStock, entry, entrieSize);

            int montante = preco*(-quantidade);
            printf("%d %d %d\n", codigo,quantidade,montante);
            sprintf(entry, "%d %d %d", codigo, -quantidade, montante);
            memset(entry + strlen(entry), ' ', entrieSize - strlen(entry));
            entry[entrieSize-1]='\n';
            
            
            write(fdVenda,entry,entrieSize);

            //send output to client
            memset(entry, 0x0, entrieSize);
            sprintf(entry, "C: %d P: %d M: %d",codigo,preco,montante);
            memset(entry + strlen(entry), ' ', entrieSize -strlen(entry) );
            entry[entrieSize - 1] = '\n';

            write(1, entry,entrieSize);

            
        }else{
            

            write(1, "Inds\n",5);
           

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

