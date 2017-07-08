/*----------------------------------------------------------------------*/
/* 			Universidade Federal de São João del - Rei 
				Algoritmos e Estrutura de Dados III
				Ciência da Computação - 3º período
					
		Redimensionamento de imagens - Programação Dinâmica e Grafos
		    
					Isabella Vieira Ferreira
					 Mônica Neli de Resende
						Maio / 2012                                     */
/*----------------------------------------------------------------------*/

#include "operacoes_grafos.h"

/*----------------------------------------------------------------------*/
/* Pega os adjacentes e depois os adjacentes de cada adjacente e poe no 
    heap																*/
/*----------------------------------------------------------------------*/

void heap_adjacentes (matriz *imagem, celula **heap) {	

	int i, j, k = 1;
	quant = 0;
	
	//Criando o vetor de pesos
	(*heap) = (celula *) malloc(sizeof(celula)*((imagem->H * imagem->W)+1));
	
	for(i = 1; i<=imagem->H;i++){
		for (j = 1; j<= imagem->W; j++){
			
			if (i == 1 ){
				
				imagem->inicio[i][j].distancia = imagem->inicio[i][j].Grad;
				
			}
			
			(*heap)[k].L = i;
			(*heap)[k].C = j;
			k++;
			quant++;
		}
		
	}
  
}//Função

/*------------------------------------------------------------------------------*/
/* Pega os adjacentes																*/
/*------------------------------------------------------------------------------*/

int adjacentes (matriz imagem, celula raiz, celula *borda_esquerda, celula *borda_direita, celula *meio, int *flag) {
	
	(*flag) = 0;
	
	//Se for borda superior esquerda
	if (raiz.C == 1 && raiz.L != imagem.H) {

		//Adjacente da esquerda
		borda_esquerda->L = raiz.L+1; 		//[i+1]
		borda_esquerda->C = raiz.C;			//[j]
		
		//Adjacente da direita
		borda_direita->L = raiz.L+1;		//[i+1]
		borda_direita->C = raiz.C+1;		//[j+1]
	
		// Flag é 1 se tem 2 adjacentes
		(*flag) = 1;
		
	} else if (raiz.C == imagem.W && raiz.L != imagem.H) {		//se for borda superior direita

		//Adjacente da esquerda
		borda_esquerda->L = raiz.L+1; 		//[i+1]
		borda_esquerda->C = raiz.C-1;		//[j-1]
		
		//Adjacente da direita
		borda_direita->L = raiz.L+1;		//[i+1]
		borda_direita->C = raiz.C;			//[j]
		
		// Flag é 1 se tem 2 adjacentes
		(*flag) = 1;
	
	} else if (raiz.L == imagem.H) {			//se for a última linha da matriz

		return 1;
		
	} else {		// se for meio - (i!=1, i!=h, j!=1, j!=w) 

		//Adjacente da esquerda
		borda_esquerda->L = raiz.L+1; 		//[i+1]
		borda_esquerda->C = raiz.C-1;		//[j-1]
		
		//Adjacente da direita
		borda_direita->L = raiz.L+1;		//[i+1]
		borda_direita->C = raiz.C;			//[j]
		
		//Adjacente do meio
		meio->L = raiz.L+1;			//[i+1]
		meio->C = raiz.C+1;			//[j+1]
		
		//Flag é 0 se tem três adjacentes
		*flag = 0;
		
	}

	return 0;
	
}		

/*----------------------------------------------------------------------*/
/* Algoritmo de Dijkstra - menor caminho								*/
/*----------------------------------------------------------------------*/
void Dijkstra(matriz *imagem, celula *heap){ 
  
  int flag;
  celula v1,adj1,adj2,adj3;  
  int num = 0, num1 = 0, cont = 1;     					// Vertices

  /*enquanto heap nao estiver vazio*/
	while (cont <= quant ) { 

     v1 = heap[cont];
     cont++;
	num++;
	
   //Se a lista de adjacentes nao for vazia
    if (adjacentes(*imagem, v1, &adj1, &adj2, &adj3, &flag)!=1){ 
		
		// menor caminho / borda esquerda
		if ((*imagem).inicio[adj1.L][adj1.C].distancia > (*imagem).inicio[adj1.L][adj1.C].Grad + (*imagem).inicio[v1.L][v1.C].distancia) { 
			
			(*imagem).inicio[adj1.L][adj1.C].distancia = (*imagem).inicio[adj1.L][adj1.C].Grad + (*imagem).inicio[v1.L][v1.C].distancia;
			(*imagem).inicio[adj1.L][adj1.C].coluna = v1.C;
			
		} 
		
		// menor caminho / borda da direita
		if ((*imagem).inicio[adj2.L][adj2.C].distancia > (*imagem).inicio[adj2.L][adj2.C].Grad + (*imagem).inicio[v1.L][v1.C].distancia) { 
	
			(*imagem).inicio[adj2.L][adj2.C].distancia = (*imagem).inicio[adj2.L][adj2.C].Grad + (*imagem).inicio[v1.L][v1.C].distancia;
			(*imagem).inicio[adj2.L][adj2.C].coluna = v1.C;   //Antecessor
			
		} 
		
		//Apenas dois adjcentes
		if (flag == 0){
			
			// menor caminho / meio
			if ((*imagem).inicio[adj3.L][adj3.C].distancia > (*imagem).inicio[adj3.L][adj3.C].Grad + (*imagem).inicio[v1.L][v1.C].distancia) { 
				
				(*imagem).inicio[adj3.L][adj3.C].distancia = (*imagem).inicio[adj3.L][adj3.C].Grad + (*imagem).inicio[v1.L][v1.C].distancia;
				(*imagem).inicio[adj3.L][adj3.C].coluna = v1.C;
				
			} 
		}
		
	} else num1++;  //ifzao

		
 }//while
 
}//funcao
