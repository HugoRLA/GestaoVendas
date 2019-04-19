#include<stdio.h>


typedef struct Artigo{
	long codigo;
	char* nome;
	int preco;
	int quantidade;	
} Artigo;


long insereArt(char* nome, int preco);
int alteraNome(long codigo, char* nome);
int alteraPreco(long codigo, int preco);

