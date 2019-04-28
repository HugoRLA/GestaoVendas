#include<stdio.h>


typedef struct Artigo{
	long codigo;
	char* nome;
	int preco;
	int quantidade;	
} Artigo;


long insereArt(char* nome, char* preco);
int alteraNome(long codigo, char* nome);
int alteraPreco(long codigo, char* preco);

