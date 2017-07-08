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
#include <math.h>
#include <limits.h>

#define INFINITO INT_MAX

#include "funcoes_auxiliares.h"
#include "tad.h"

#ifndef OPERACOES_IMAGEM_H
#define OPERACOES_IMAGEM_H

/*----------------------------------------------------------------------------------------------------------------*/
/* Cabeçalho das funções contidas no arquivo "operacoes_imagem.c"       							              */
/*----------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------*/
void operador_scharr (float **matriz_vizinhos, float *gradiente);
/*----------------------------------------------------------------------------------------------------------------*/
void corta_imagem (matriz *imagem);
/*----------------------------------------------------------------------------------------------------------------*/
void melhor_caminho (matriz *mat);
/*----------------------------------------------------------------------------------------------------------------*/
void intensidade_luminosa (matriz *imagem);
/*----------------------------------------------------------------------------------------------------------------*/
void auxiliar_gradiente (matriz *mat_transposta);
/*----------------------------------------------------------------------------------------------------------------*/
void corta_caminho_grafos (matriz *imagem);
/*----------------------------------------------------------------------------------------------------------------*/

#endif
