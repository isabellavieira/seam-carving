/*----------------------------------------------------------------------*/
/* 			Universidade Federal de São João del - Rei 
				Algoritmos e Estrutura de Dados III
				Ciência da Computação - 3º período
					
		Redimensionamento de imagens - Programação Dinâmica e Grafos
		    
					Isabella Vieira Ferreira
					 Mônica Neli de Resende
						 Maio 2012                                      */
/*----------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "tad.h"
#include "funcoes_auxiliares.h"
#include "operacoes_imagem.h"
#include "operacoes_grafos.h"

#define INFINITO       INT_MAX


/*----------------------------------------------------------------------*/
/* Função principal													    */
/*----------------------------------------------------------------------*/

int main (int argc, char *argv[]){

	FILE *entrada;
	matriz imagem, mat_transposta;
	int i,j;
	int k;
	celula *heap;

	char *arquivo_entrada;
	char *estrategia  ;
	char *parametro_h;
	int num_remocao;
	
	quant = 0;
	arquivo_entrada = argv[1];
	estrategia = argv[2];
	parametro_h = argv[3];
	num_remocao = atoi(argv[4]);

	entrada = fopen(arquivo_entrada, "r");
	
	if (entrada == NULL){
		
		printf("\nParametro incorreto!\n\n");
		
		return 1;
		
	}
	
	if (estrategia[0] == 'D' || estrategia[0] == 'd') {
		
		//retirando linhas - coluna na transposta
		if (parametro_h[1] == 'H' || (parametro_h[1] == 'h')) {  
			
			leitura_arquivo (entrada, &imagem);
						
			if (num_remocao > imagem.H) {
				
				printf("\nNão é possível retirar essa quantidade de linhas!\n\n");
				
				return 1;
				
			} else {
				
				mat_transposta = transposta(&imagem);
				
				intensidade_luminosa (&mat_transposta);
		
				for (i = 0; i < num_remocao; i++) {
				
					
					replica(&mat_transposta);
					
					auxiliar_gradiente(&mat_transposta);
						
					melhor_caminho(&mat_transposta);
					
					corta_imagem (&mat_transposta); 
					
				}
				
				imagem = transposta(&mat_transposta);
			
			}
						
		} else {       //retirar colunas - sem transposta
		
			leitura_arquivo (entrada, &imagem);

			if (num_remocao > imagem.W) {
				
				printf("\nNão é possível retirar essa quantidade de colunas!\n\n");
				
				return 1;
				
			} else {

				intensidade_luminosa (&imagem);
				
				for (i = 0; i < num_remocao; i++) {
					
					replica(&imagem);
				
					auxiliar_gradiente(&imagem);
						
					melhor_caminho(&imagem);
					
					corta_imagem (&imagem); 
				}
			}
		}
			
		
	} else if (estrategia[0] == 'G' || estrategia[0] == 'g') {
	
		//removendo colunas - sem transposta
		if (parametro_h[1] == 'W' || (parametro_h[1] == 'w')) {
	 
		  leitura_arquivo(entrada, &imagem);
				
		  if (num_remocao > imagem.W) {
				
				printf("\nNão é possível retirar essa quantidade de colunas!\n\n");
				
				return 1;
				
			} else {
		
				intensidade_luminosa (&imagem);
								
				for (i = 0; i < num_remocao; i++) {
					
					replica(&imagem);	
					
					auxiliar_gradiente(&imagem);
					
					//Inicialização do grafo
					for (k = 1; k <= imagem.H; k++){ 
						
					   for (j = 1; j <= imagem.W; j++){ 
						   
						imagem.inicio[k][j].coluna = -1 ;  
						imagem.inicio[k][j].distancia = INFINITO;
						
					  }
					}

					heap_adjacentes(&imagem, &heap);
					
					Dijkstra(&imagem, &(*heap));	
					
					free(heap);
					quant = 0;			
					corta_caminho_grafos(&imagem);
										
				}
			}

		
		} else {		// se for para remover linhas - coluna na transposta
					
			leitura_arquivo (entrada, &imagem);
					
				if (num_remocao > imagem.H) {
					
					printf("\nNão é possível retirar essa quantidade de linhas!\n\n");
					
					return 1;
					
				} else {
					
					mat_transposta = transposta(&imagem);
			
					intensidade_luminosa (&mat_transposta);
			
					for (i = 0; i < num_remocao; i++) {
											
						replica(&mat_transposta);	
			
						auxiliar_gradiente(&mat_transposta);
					
							//Inicialização do grafo
							for (k = 1; k <= imagem.W; k++){ 
								
							   for (j = 1; j <= imagem.H; j++){ 
								   
								mat_transposta.inicio[k][j].coluna = -1 ;  
								mat_transposta.inicio[k][j].distancia = INFINITO;
								
							  }
							}							
							
							heap_adjacentes(&mat_transposta, &heap);
							Dijkstra(&mat_transposta, &(*heap));
							free(heap);
							quant = 0;
							corta_caminho_grafos(&mat_transposta);
					
					}
					
					imagem = transposta(&mat_transposta);
				
				}
			}		
		}
	
		imprimir(imagem);
		
		destruir_matriz(&imagem);
	
		return 1;
		
}//funcao
