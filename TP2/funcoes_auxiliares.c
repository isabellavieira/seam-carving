/*----------------------------------------------------------------------*/
/* 			Universidade Federal de São João del - Rei 
				Algoritmos e Estrutura de Dados III
				Ciência da Computação - 3º período
					
		Redimensionamento de imagens - Programação Dinâmica e Grafos
		    
					Isabella Vieira Ferreira
					 Mônica Neli de Resende
						Maio / 2012                                     */
/*----------------------------------------------------------------------*/

#include "funcoes_auxiliares.h"

/*----------------------------------------------------------------------*/
/* Função responsável por ignorar os comentários no arquivo de entrada. */
/*----------------------------------------------------------------------*/

void ignora_comentario (FILE *entrada, char *caractere){

	if ((*caractere) == '#'){
	
		do {
			// Diferente de \n, ou seja, fim de linha
			while ((*caractere) != '\n'){
					
				fscanf(entrada, "%c" , &(*caractere));
				
			}
			
			// Le o proximo caractere, se for # repete os passos acima, senao retorna o caractere
			fscanf(entrada, "%c" , &(*caractere));
			
		} while ((*caractere) == '#');	
		
	} else return;

}


/*----------------------------------------------------------------------*/
/* Função responsável por ler o RGB do arquivo de entrada.             
   A função le o número como char e o converte para inteiro.			*/
/*----------------------------------------------------------------------*/

int le_palavra (FILE *entrada, char *caractere){  

	char palavra[10]; 
	int i = 0;
	
	while ((*caractere) != ' ' && (*caractere) != '\n' ){
		
		palavra[i] = (*caractere);
		i++;
		fscanf(entrada, "%c" , &(*caractere));	
					
	}
	
	palavra[i] = '\0';
	
	return (atoi(palavra));
}


/*----------------------------------------------------------------------*/
/* Função responsável por escrever no arquivo de saída a imagem 
   redimensionada. 														*/
/*----------------------------------------------------------------------*/

void imprimir (matriz imagem) {
	
	FILE *saida;
	char palavra;
	int i, j, cont = 0;

	saida = fopen("saida.ppm", "w");
	
	fprintf (saida, "P3\n");
	
	// Dimensões da matriz - 'h' e 'w'
	fprintf (saida, "%d %d\n", imagem.W,imagem.H);
	
	fprintf (saida, "255\n");
	

	for (i = 1; i <= imagem.H ; i++){
		
		for (j = 1; j <= imagem.W; j++){
			
			if (cont >= 10){
									
					palavra = '\n';
					fprintf(saida, "%c", palavra);	
					cont = 0;
					
			}
			
				cont++;
				fprintf (saida, "%d %d %d ", imagem.inicio[i][j].R, imagem.inicio[i][j].G, imagem.inicio[i][j].B);
				
			
		}
		
		palavra = '\n';
		fprintf(saida, "%c", palavra);
		
	}	
			
	fclose(saida);

}	


/*----------------------------------------------------------------------*/
/* Função responsável por guardar os 8 "vizinhos" do pixel que está sendo
   analisado.															*/
/*----------------------------------------------------------------------*/

void vizinhos (matriz replicada, float **vizinho, int i, int j) {
	
	vizinho[0][0] = replicada.inicio[i-1][j-1].IL;
	vizinho[0][1] = replicada.inicio[i-1][j].IL;
	vizinho[0][2] = replicada.inicio[i-1][j+1].IL;
	vizinho[1][0] = replicada.inicio[i][j-1].IL;
	vizinho[1][1] = replicada.inicio[i][j].IL;
	vizinho[1][2] = replicada.inicio[i][j+1].IL;
	vizinho[2][0] = replicada.inicio[i+1][j-1].IL;
	vizinho[2][1] = replicada.inicio[i+1][j].IL;
	vizinho[2][2] = replicada.inicio[i+1][j+1].IL;
	
	return;
	
}
	

/*----------------------------------------------------------------------*/
/* Função responsável por replicar a matriz de itensidade luminosa.    
	Cada pixel é transformado em uma matriz 3x3                         */
/*----------------------------------------------------------------------*/

void replica (matriz *mat_transposta){

	int i = 0 , j = 0;
	
	for (j = 1; j <= mat_transposta->W; j++){
		
		// Linha de cima
		mat_transposta->inicio[i][j].IL = mat_transposta->inicio[i+1][j].IL;
		
		// Linha de baixo
		mat_transposta->inicio[mat_transposta->H+1][j].IL = mat_transposta->inicio[mat_transposta->H][j].IL;
		
	}

	j = 0;
	
	for (i = 1; i < mat_transposta->H; i++){
		
		// Coluna a esquerda
		mat_transposta->inicio[i][j].IL = mat_transposta->inicio[i][j+1].IL;
		
		// Coluna a direita
		mat_transposta->inicio[i][mat_transposta->W + 1].IL = mat_transposta->inicio[i][mat_transposta->W].IL;
		
	}		

	// Quinas
	mat_transposta->inicio[0][0].IL = mat_transposta->inicio[1][1].IL;
	mat_transposta->inicio[0][mat_transposta->W+1].IL = mat_transposta->inicio[1][mat_transposta->W].IL;
	mat_transposta->inicio[mat_transposta->H+1][0].IL = mat_transposta->inicio[mat_transposta->H][1].IL;	
	mat_transposta->inicio[mat_transposta->H+1][mat_transposta->W+1].IL = mat_transposta->inicio[mat_transposta->H][mat_transposta->W].IL;	
	
}


/*----------------------------------------------------------------------*/
/* Função responsável por criar a transposta da original.
   Para cortar as linhas, cortar as colunas da transposta.             */
/*----------------------------------------------------------------------*/

matriz transposta (matriz *original){

	int i,j;
	matriz matriz_transposta;
	
	matriz_transposta.H = original->W;
	matriz_transposta.W = original->H;
	
	matriz_transposta = cria_matriz (original->W+2, original->H+2); // Ordem trocada
	
	for (i=1; i <= original->W; i++) {
		
		for (j=1; j <= original->H; j++) {
			
			matriz_transposta.inicio[i][j].R = original->inicio[j][i].R;
			matriz_transposta.inicio[i][j].G = original->inicio[j][i].G;
			matriz_transposta.inicio[i][j].B = original->inicio[j][i].B;
			
		}
	}
	
	return(matriz_transposta);	
	
	destruir_matriz(original);
	
}

/*----------------------------------------------------------------------*/
/* Função responsável por fazer a leitura do arquivo de entrada.        */
/*----------------------------------------------------------------------*/

void leitura_arquivo (FILE *entrada, matriz *imagem){

	int h = 0, w = 0, i = 1, j = 1, palavra;
	char caractere;
	char c;
	
	fscanf(entrada, "%c" , &caractere);
	ignora_comentario (entrada, &caractere);
	
	// Ignorando P3
	if (caractere == 'P'){
		
			fscanf(entrada, "%c" , &caractere);
	}
	
	fscanf(entrada, "%c" , &caractere);
	
	// Dimensões da imagem
	do {

		// Se não é fim de linha o caractere é um espaço entao le o proximo	
		if (caractere != '\n'){			
			fscanf(entrada, "%c" , &caractere);
			palavra = le_palavra (entrada, &caractere);
			
		} else{	// Fim de linha le o proximo
			
			fscanf(entrada, "%c" , &caractere);	
			ignora_comentario (entrada, &caractere);
			palavra = le_palavra (entrada, &caractere);
	
		} 
		//Preenchendo as dimensoes
		if (w == 0){
			
			w = palavra;
			
		} else {
			
			h = palavra;

		}
				
	//Enquanto nao preencher totalmente as dimensões (h e w)
	} while (h == 0 && (caractere == ' ' || caractere == '\n'));

	(*imagem) = cria_matriz (h+2, w+2);

	//Ignorando o valor de maior intensidade da imagem retornando o próprio caractere ou o proximo válido
	fscanf(entrada, "%c" , &caractere);	
	ignora_comentario (entrada, &caractere);
	
	while (caractere != ' ' && caractere != '\n' ){
			fscanf(entrada, "%c" , &caractere);				
	}
		
	fscanf(entrada, "%c" , &caractere);
	
	// Preenchimento da Matriz	
	while (!feof(entrada) && (i <= imagem->H+1)) {
		
		ignora_comentario (entrada, &caractere);		
		palavra = le_palavra (entrada, &caractere);
		imagem->inicio[i][j].R = palavra;
		
		// Continuação da linha ou 1º caractere de outra linha
		fscanf(entrada, "%c" , &caractere);
		ignora_comentario (entrada, &caractere);
		palavra = le_palavra (entrada, &caractere);
		imagem->inicio[i][j].G = palavra;
		
		// Continuação da linha ou 1º caractere de outra linha
		fscanf(entrada, "%c" , &caractere);
		ignora_comentario (entrada, &caractere);
		palavra = le_palavra (entrada, &caractere);
		imagem->inicio[i][j].B = palavra;		
					
		//Controlando o preenchimento de linhas e colunas		
		c = getc(entrada);
		if (c != '\n') {
			ungetc(c,entrada);
		}
		
		j++;
		
		if (j == w+1){
			
			j = 1;
			i++;
			
			
		}
			
		fscanf(entrada, "%c" , &caractere);
	}
	
	fclose(entrada);
}
