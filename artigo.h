#include<stdio.h>


typedef struct Artigo{
	long codigo;
	char* nome;
	float preco;
	long quantidade;	
} Artigo;


long insereArt(char* nome, float preco);
int alteraNome(long codigo, char* nome);
int alteraPreco(long codigo, float preco);

