#include<stdio.h>


typedef struct Artigo{
	long codigo;
	char* nome;
	int preco;
	int quantidade;	
} Artigo;


int insereArt(const char* nome,const char* preco);
int alteraNome(int codigo,const char* nome);
int alteraPreco(int codigo,const char* preco);

