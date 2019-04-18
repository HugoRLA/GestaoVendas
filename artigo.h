#include<stdio.h>


typedef struct Artigo{
	int codigo;
	char* nome;
	int preco;
	int quantidade;	
} Artigo;


long insereArt(char* nome, int preco);
int alteraNome(int codigo, char* nome);
int alteraPreco(int codigo, int preco);

