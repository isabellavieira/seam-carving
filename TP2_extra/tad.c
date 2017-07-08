/*----------------------------------------------------------------------*/
/* 			Universidade Federal de São João del - Rei 
				Algoritmos e Estrutura de Dados III
				Ciência da Computação - 3º período
					
		Redimensionamento de imagens - Programação Dinâmica e Grafos
		    
					Isabella Vieira Ferreira
					 Mônica Neli de Resende
						  Maio/2012                                     */
/*----------------------------------------------------------------------*/

#include "tad.h"

/*----------------------------------------------------------------------*/
/* Função responsável por criar uma matriz do tipo "matriz".            */
/*----------------------------------------------------------------------*/

matriz cria_matriz (int h, int w){

	int i;
	matriz imagem;
	
	imagem.inicio = (pixel **) malloc (sizeof(pixel*)*h);
	
	imagem.H = h-2;
	imagem.W = w-2;
	
	for (i = 0; i < h; i++){
		
		imagem.inicio[i] = (pixel *) malloc (sizeof(pixel)*w);
		
	}
	
	return (imagem);	
	
}


/*----------------------------------------------------------------------*/
/* Função responsável por destruir uma matriz do tipo "float". 		    */
/*----------------------------------------------------------------------*/

void destruir_float (float **Matriz) {
	
	int i;
	
	for(i = 0; i < 3; i++) {
		
		free(Matriz[i]);
		
	}
		free(Matriz);

}

/*----------------------------------------------------------------------*/
/* Função responsável por destruir uma matriz do tipo "matriz".		    */
/*----------------------------------------------------------------------*/

void destruir_matriz (matriz *Matriz) {
	
	int i;
	
	for(i = 0; i < Matriz->H; i++) {
		
		free(Matriz->inicio[i]);
		
	}
		free(Matriz->inicio);

}


/*--------------------------------------------------------------------------------------*/
/* Função responsável por criar uma matriz 3x3 para armazenar os vizinhos do pixel.	    */
/*--------------------------------------------------------------------------------------*/
float **criar_3x3(){
	
	int k;
	float **vizinho;
	
	vizinho = (float **) malloc (sizeof(float*)*3);
	
	for (k = 0; k < 3; k++){
		
		vizinho[k] = (float *) malloc (sizeof(float)*3);
		
	}
	
	return (vizinho);
}
