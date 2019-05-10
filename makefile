CC=gcc 

all: ma stock  sv cv artigo

ma: ma.o
	gcc -o ma ma.c ma.h
	
stock: stock.o
	gcc -o stock stock.c stock.h
	
sv: sv.o
	gcc -o sv  sv.c sv.h
	
cv: cv.o
	gcc -o cv cv.c cv.h

artigo: artigo.o
	gcc -o artigo artigo.c artigo.h

apaga:
	rm -f ARTIGOS.txt STOCKS.txt VENDAS.txt STRING.txt
	
clean:
	rm -r ma stock sv cv artigo

