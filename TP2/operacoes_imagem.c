/*----------------------------------------------------------------------*/
/* 			Universidade Federal de São João del - Rei 
				Algoritmos e Estrutura de Dados III
				Ciência da Computação - 3º período
					
		Redimensionamento de imagens - Programação Dinâmica e Grafos
		    
					Isabella Vieira Ferreira
					 Mônica Neli de Resende
						Maio / 2012                                     */
/*----------------------------------------------------------------------*/

#include "operacoes_imagem.h"

/*----------------------------------------------------------------------*/
/* Função responsável por calcular o Operador de Sobel.                 */
/*----------------------------------------------------------------------*/

void operador_sobel (float **matriz_vizinhos, float *gradiente){

	float mult_gx = 0.0;
	float mult_gy = 0.0;
	int i, j;
	
	// Operador de sobel para x
	int gx[3][3] = {{-1, 0 , 1},{-2, 0, 2},{-1,0,1}};
	
	// Operador de sobel para y
	int gy[3][3] = {{-1, -2 , -1},{0, 0, 0},{1,2,1}};
	
	
	// Fazendo a multiplicacao da matriz de operador de sobel pelos elementos correspodentes na matriz original
	// A intensidade luminosa estará na matriz_vizinhos
	
	for (i=0; i < 3; i++) {
		
		for (j=0; j < 3; j++) {
				
				mult_gx = (matriz_vizinhos[i][j] * gx[i][j]) + mult_gx;
				mult_gy = (matriz_vizinhos[i][j] * gy[i][j]) + mult_gy;
										
		}	
	}

	// Calculo do gradiente G = sqrt (|Gx|² + |Gy|²)
	(*gradiente) = sqrt((pow (mult_gx,2)) + (pow (mult_gy,2)));
	
}


/*----------------------------------------------------------------------*/
/* Função responsável por "cortar na imagem" o caminho que deve ser 
   retirado para redimensionar a imagem. Operacao para programacao 
   dinamica.															*/
/*----------------------------------------------------------------------*/

void corta_imagem (matriz *imagem) {
	
	int i, j, posicao, aux;
	float menor = 0.0;
	
	
	menor = imagem->inicio[imagem->H][1].Grad;
	posicao = 0;
		
	// Indo na ultima linha e vendo qual e o menor elemento
	for (i = 2; i <= imagem->W; i++) {
		
		if (imagem->inicio[imagem->H][i].Grad < menor) {
		
			menor = imagem->inicio[imagem->H][i].Grad;
			posicao = i;       				// posicao guarda de onde e o menor - corresponde a coluna

		}
	}

	for (i = imagem->H; i >= 1; i--) {
		
		aux = posicao;
		posicao = imagem->inicio[i][posicao].coluna;
		
		// Deslocando a matriz original
		for (j = aux; j < imagem->W; j++) {
			
			imagem->inicio[i][j].R = imagem->inicio[i][j+1].R;
			imagem->inicio[i][j].G = imagem->inicio[i][j+1].G;
			imagem->inicio[i][j].B = imagem->inicio[i][j+1].B;
			imagem->inicio[i][j].IL = imagem->inicio[i][j+1].IL;			

		}
		
	}	
	
	imagem->W = imagem->W-1;
	
}

/*----------------------------------------------------------------------*/
/* Função responsável por "cortar na imagem" o caminho que deve ser 
   retirado para redimensionar a imagem - Operacao para grafos.			*/
/*----------------------------------------------------------------------*/

void corta_caminho_grafos (matriz *imagem) {
	
	int i, j, posicao, aux;
	float menor = 0.0;
	
	posicao = 1;
	
	//menor recebe a primeira distância da última linha
	menor = imagem->inicio[imagem->H][1].distancia;
	
	//percorre a ultima linha da imagem vendo qual a menor distancia
	for (i = 2; i<=imagem->W; i++) {
		
		if (imagem->inicio[imagem->H][i].distancia < menor) {
			
			menor = imagem->inicio[imagem->H][i].distancia;
			posicao = i;       // posicao guarda de onde e o menor - corresponde a coluna
			
		}
	}

	for (i = imagem->H; i >= 1; i--) {
		
		aux = posicao;
		posicao = imagem->inicio[i][posicao].coluna;
				
		
		// Deslocando a matriz original
		for (j = aux; j < imagem->W; j++) {
			
			imagem->inicio[i][j].R = imagem->inicio[i][j+1].R;
			imagem->inicio[i][j].G = imagem->inicio[i][j+1].G;
			imagem->inicio[i][j].B = imagem->inicio[i][j+1].B;
			imagem->inicio[i][j].IL = imagem->inicio[i][j+1].IL;			

		}
		
	}
		
	imagem->W = imagem->W-1;
	
}

/*----------------------------------------------------------------------*/
/* Função responsável por verificar qual é o melhor caminho para 
   redimensionar a imagem												*/
/*----------------------------------------------------------------------*/

void melhor_caminho (matriz *mat) {
	
	int i, j;
	float soma1, soma2, soma3, menor;
	
		
	for (i = 2; i <= mat->H; i++) {
			
		for (j = 1; j <= mat->W; j++) {
				
			// Se for a borda da esquerda
			if (j == 1) {
					
				soma1 = mat->inicio[i][j].Grad + mat->inicio[i-1][j].Grad;
				soma2 = mat->inicio[i][j].Grad + mat->inicio[i-1][j+1].Grad;
					
				if (soma1 < soma2) {
			
					mat->inicio[i][j].Grad = soma1;		
					mat->inicio[i][j].coluna = j;
		
				} else if (soma2 < soma1) {
		
					mat->inicio[i][j].Grad = soma2;
					mat->inicio[i][j].coluna = j+1;
	
				} else if (soma1 == soma2)  { // Se for igual, pega o primeiro que olhou.
		
					mat->inicio[i][j].Grad = soma1;
					mat->inicio[i][j].coluna = j;
	
				}
				
			} else if (j == mat->W) {        // Se for a borda da direita
				
				soma1 = mat->inicio[i][mat->W].Grad + mat->inicio[i-1][mat->W-1].Grad;
		
				soma2 = mat->inicio[i][mat->W].Grad + mat->inicio[i-1][mat->W].Grad;
	
				if (soma1 < soma2) {
	
					mat->inicio[i][mat->W].Grad = soma1;
					mat->inicio[i][j].coluna = mat->W-1;
		
				} else if(soma2 < soma1) {
		
					mat->inicio[i][mat->W].Grad = soma2;
					mat->inicio[i][j].coluna = mat->W;
	
				} else if (soma1 == soma2) {
			
					mat->inicio[i][mat->W].Grad = soma1;
					mat->inicio[i][j].coluna = mat->W-1;
				}
			} else {
			
				soma1 = mat->inicio[i][j].Grad + mat->inicio[i-1][j-1].Grad;
				soma2 = mat->inicio[i][j].Grad + mat->inicio[i-1][j].Grad;
				soma3 = mat->inicio[i][j].Grad + mat->inicio[i-1][j+1].Grad;
	
				menor = soma1;
				mat->inicio[i][j].coluna = j-1;

				if (soma2 < menor) {
		
					menor = soma2;
					mat->inicio[i][j].coluna = j;
			
				} 	
	
				if  (soma3 < menor) {
		
					menor = soma3;
					mat->inicio[i][j].coluna = j+1;
	
				} 	
	
				mat->inicio[i][j].Grad = menor;
			}		
		}
	}	
}


/*----------------------------------------------------------------------*/
/* Função responsável por criar a matriz de intensidade luminosa        */
/*----------------------------------------------------------------------*/

void intensidade_luminosa (matriz *imagem) {
	
	int i, j;
		
	
	for (i = 1; i <= imagem->H ; i++){
		
		for (j = 1; j <= imagem->W; j++){
			
			// Criando uma matriz de itensidade luminosa a partir da matriz original
			imagem->inicio[i][j].IL = (0.30 * (imagem->inicio[i][j].R)) + (0.59 * (imagem->inicio[i][j].G)) + (0.11 * (imagem->inicio[i][j].B));
			
		}
		
		
	}

	return;
	
}


/*----------------------------------------------------------------------*/
/* Função responsável por criar uma matriz com todos os gradientes.     */
/*----------------------------------------------------------------------*/

void auxiliar_gradiente (matriz *mat_transposta) {  
	
	float gradiente;
	float **vizinho;
	int i,j;
	
	vizinho = criar_3x3();
		
	for (i = 1; i <= mat_transposta->H; i++) {
		
		for (j = 1; j <= mat_transposta->W; j++) {

			vizinhos(*mat_transposta, vizinho, i,j);
			operador_sobel (vizinho, &gradiente);
			mat_transposta->inicio[i][j].Grad = gradiente;
			
		}
	}	
	
	destruir_float(vizinho);
	
}
