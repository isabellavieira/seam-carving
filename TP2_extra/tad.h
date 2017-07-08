/*----------------------------------------------------------------------*/
/* 			Universidade Federal de São João del - Rei 
				Algoritmos e Estrutura de Dados III
				Ciência da Computação - 3º período
					
		Redimensionamento de imagens - Programação Dinâmica e Grafos
		    
					Isabella Vieira Ferreira
					 Mônica Neli de Resende
						Maio / 2012                                     */
/*----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#ifndef TAD_H
#define TAD_H

int quant;

/*----------------------------------------------------------------------*/
/* Estrutura de dados 								                    */
/*----------------------------------------------------------------------*/

typedef struct pixel **Apontador;

typedef struct pixel{
	
	int R, G, B;
	float IL;
	float Grad;
	int coluna;
	float distancia;

}pixel;

typedef struct matriz{
	
	Apontador inicio;
	int H, W;
	
}matriz;

typedef struct celula{

	int L,C;
		
}celula;


/*----------------------------------------------------------------------*/
/* Cabeçalho das funções contidas no arquivo "tad.c"                    */
/*----------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
matriz cria_matriz (int h, int w);
/*----------------------------------------------------------------------*/
float **criar_3x3();
/*----------------------------------------------------------------------*/
void destruir_matriz (matriz *Matriz);
/*----------------------------------------------------------------------*/
void destruir_float (float **Matriz);
/*----------------------------------------------------------------------*/


#endif
