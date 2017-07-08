/*----------------------------------------------------------------------*/
/* 			Universidade Federal de São João del - Rei 
				Algoritmos e Estrutura de Dados III
				Ciência da Computação - 3º período
					
		Redimensionamento de imagens - Programação Dinâmica e Grafos
		    
					Isabella Vieira Ferreira
					 Mônica Neli de Resende
						Maio / 2012                                     */
/*----------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>

#include "tad.h"

#ifndef OPERACOES_GRAFOS_H
#define OPERACOES_GRAFOS_H

/*----------------------------------------------------------------------------------------------------------------*/
/* Cabeçalho das funções contidas no arquivo "operacoes_grafos.c"											      */
/*----------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------*/
void heap_adjacentes (matriz *imagem, celula **heap);
/*----------------------------------------------------------------------------------------------------------------*/
void Constroi(matriz *imagem, celula *heap);
/*----------------------------------------------------------------------------------------------------------------*/
int adjacentes (matriz original, celula raiz, celula *borda_esquerda, celula *borda_direita, celula *meio, int *flag);
/*----------------------------------------------------------------------------------------------------------------*/
void Dijkstra(matriz *imagem, celula *heap);
/*----------------------------------------------------------------------------------------------------------------*/

#endif
