#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int flag=0;
void labescrita (int num1, int num2, char matriz[num1][num2]){
	FILE *escrita;	
		int i,j;
		char str2[100];
		printf ("labirinto de saida: \n");
		scanf("%s",str2);	
		escrita=(fopen(str2,"w+"));	
		fscanf(escrita,"%s", str2);
	
		for(i=1; i<=num1 ; i++){
			for(j=1 ; j<=num2 ; j++ ) {
				fprintf(escrita,"%c ", matriz[i][j]);

			}
					fprintf(escrita,"\n");

		}		
	fclose(escrita);
	system("clear");
	puts("Seu arquivo foi salvo");
	puts("\n\nDesenvolvido por: Gabriel Menezes, Raduchiu Amaral e Raul Andrade.\n\n");
	return ;
	}
int nivel(){ //nivel dos inimigos
	return rand()%10+1;
}
int inimigo(){ // quando ele morre acumula %10
	srand(time(NULL));
	int enemy,skill;
	skill=5;
	enemy=nivel();	
		if (skill<enemy)
		return 0;
			
		if(skill>=enemy)
			skill++;
		return 1;	
		  
}		
int aleatorio (int x){ //aleatorio para ele se movimentar
	return rand()%x+1;
	}
void sleep (time_t delay){ //Função sleep
	
	time_t timer0, timer1;
	time(&timer0);
	do{
		time(&timer1);
	}while((timer1-timer0)< delay);
}
void jogo(){
		char str[100];
			int i, j, num1, num2, inicioX, inicioY, k, cont = 0, lol, finalX, finalY, antesX, antesY;
			char ch;
				FILE * teste ;
				printf ("Digite o nome do labirinto: \n"); // Lê o Labirinto Digitado pelo Usuário
				scanf("%s",str);	
				teste=(fopen(str,"r"));	
					if ((teste == NULL)){
						puts( "Erro na abertura do arquivo .");
						 return; 
					}
				printf("abrindo arquivo\n"); // Abrindo Labirinto	
				system("clear");						
		fscanf(teste,"%d %d", &num1,&num2);
		char matriz[num1][num2];		
	
		for (i=1;i<=num1;i++) { // Lendo o Labirinto
			for(j=1; j<=num2; j++){
				fscanf(teste, " %c%*c", &ch);
				matriz[i][j] = ch;
				printf("%c ", matriz[i][j]);
				if(matriz[i][j] == '@'){ // Salvando posicão inicial
					inicioX = i;
					inicioY = j;
				}
				if(matriz[i][j]== '$'){ // Salvando posição final
					finalX = i;
					finalY = j;
				}
			}
			printf("\n");
		} // Fim da Leitura do Labirinto
		sleep(1);
		struct tPossibilidades{ 
			int x;
			int y;
		};
		struct tPossibilidades talvez[5]; //Struct para saber as possibilidades de movimentação do Personagem.
			for(k = 0 ; k<5 ; k++) {	//Preenchimento do struct com 0.
				talvez[k].x = 0;
				talvez[k].y = 0;
			}
			do{ // DO WHILE pra ele chegar no V (vitora) 
				antesX = inicioX;
				antesY = inicioY;
				
					cont = 0;
					if(matriz[antesX][antesY] == '!'){ // Personagem Ganhou a Batalha
						printf(">>>O personagem ganhou a batalha...\n");
					}
					if(matriz[antesX][antesY] == '?'){ // Personagem Se Perdeu
						printf(">>>O personagem se perdeu...\n");
						labescrita(num1,num2,matriz);
						return;
					}
					if(matriz[antesX][antesY] == '+'){ // Personagem Morreu em Combate
						printf(">>>O personagem morreu em combate...\n");
						
						labescrita(num1,num2,matriz);
						return;
					}
					
					//COMPARAÇÃO DE POSSÍVEIS LOCAIS PARA O PERSONAGEM SE MOVIMENTAR!!!!!	
					if(matriz[inicioX+1][inicioY] != '#' && matriz[inicioX+1][inicioY] !='*' && inicioX+1<=num1 && matriz[inicioX+1][inicioY] != '!'){
						cont++;		
						talvez[cont].x= inicioX+1;
						talvez[cont].y= inicioY;
					}
					if(matriz[inicioX-1][inicioY] != '#' && matriz[inicioX-1][inicioY] !='*' && inicioX-1>=1 && matriz[inicioX-1][inicioY] != '!'){
						cont++;
						talvez[cont].x= inicioX-1;
						talvez[cont].y= inicioY;
					}
					if(matriz[inicioX][inicioY+1] != '#' && matriz[inicioX][inicioY+1] !='*' && inicioY+1<=num2 && matriz[inicioX][inicioY+1] != '!'){
						cont++;
						talvez[cont].x= inicioX;
						talvez[cont].y= inicioY+1;
					}
					if(matriz[inicioX][inicioY-1] != '#' && matriz[inicioX][inicioY-1] !='*' && inicioY-1>=1 && matriz[inicioX][inicioY-1] != '!'){
						cont++;
						talvez[cont].x= inicioX;
						talvez[cont].y= inicioY-1;
					}// FIM DAS COMPARAÇÕES	
				
					if(cont == 0){ // CASO NAO HAJA LUGAR PARA SE MOVIMENTAR
						matriz[antesX][antesY] = '?';
					}
					else{
						lol = aleatorio(cont);
						inicioX = talvez[lol].x;
						inicioY = talvez[lol].y;
						if(matriz[inicioX][inicioY] == '$') {
							if(matriz[antesX][antesY] != '!'){
								matriz[antesX][antesY] = '*';
							}
							matriz[inicioX][inicioY] = 'V';
						}
						else if(matriz[inicioX][inicioY] == '%'){
							if(inimigo() == 1){
								if(matriz[antesX][antesY] != '!'){
									matriz[antesX][antesY] = '*';
								}
								matriz[inicioX][inicioY] = '!';								
							}
							if(inimigo() == 0){
								if(matriz[antesX][antesY] != '!'){
									matriz[antesX][antesY] = '*';
								}
								matriz[inicioX][inicioY] = '+';
							}
						}	
						else{
							if(matriz[antesX][antesY] != '!'){
								matriz[antesX][antesY] = '*';
							}
							matriz [inicioX][inicioY] = '@';
						}
					}
			
			sleep(1);
			system("clear");
			for (i=1 ; i<=num1 ; i++){
				for(j=1 ; j<=num2 ; j++) {
					printf("%c ", matriz[i][j]);
				}	
			printf("\n");
			} // impressao do labirinto com @ andando.
		}while((matriz[finalX][finalY] != 'V')) ; // final do DO WHILE
		printf(">>> personagem conseguiu!\n");	
		labescrita(num1,num2,matriz);	
		return;								
		}
int jogo2(int tentativa){
	char str[100];
	int i, j, num1, num2, inicioX, inicioY, k, cont = 0, lol, finalX, finalY, antesX, antesY;
	char ch;
		FILE * teste ;
		if(flag==0)
		{printf ("Digite o nome do labirinto: \n"); // Lê o Labirinto Digitado pelo Usuário
		scanf("%s",str);
		flag=1;
		}	
		teste=(fopen(str,"r"));	
			if ((teste == NULL)){
				puts( "Erro na abertura do arquivo .");
				 return 1; 
			}
			printf("Abrindo arquivo...\n"); // Abrindo Labirinto	
			system("clear");						
		fscanf(teste,"%d%*c%d\n", &num1,&num2);
		char matriz[num1][num2];		
		for (i=1;i<=num1;i++) { // Lendo o Labirinto
			for(j=1; j<=num2; j++){
				fscanf(teste, " %c%*c", &ch);
				matriz[i][j] = ch;
				if(matriz[i][j] == '@'){ // Salvando posicão inicial
					inicioX = i;
					inicioY = j;
				}
				if(matriz[i][j]== '$'){ // Salvando posição final
					finalX = i;
					finalY = j;
				}
			}

		} // Fim da Leitura do Labirinto
		sleep(0.1);
		struct tPossibilidades{ 
			int x;
			int y;
		};
		struct tPossibilidades talvez[5]; //Struct para saber as possibilidades de movimentação do Personagem.
			for(k = 0 ; k<5 ; k++) {	//Preenchimento do struct com 0.
				talvez[k].x = 0;
				talvez[k].y = 0;
			}

			do{ // DO WHILE pra ele chegar no V (vitora) 
				antesX = inicioX;
				antesY = inicioY;
//				printf("%d %d\n", inicioX, inicioY);
					cont = 0;
					if(matriz[antesX][antesY] == '!'){ // Personagem Ganhou a Batalha
						printf(">>>O personagem ganhou a batalha...\n");
					}
					if(matriz[antesX][antesY] == '?'){ // Personagem Se Perdeu
						
						printf(">>>O personagem se perdeu...\n");					
						return 0;
					}
					if(matriz[antesX][antesY] == '+'){ // Personagem Morreu em Combate
						
						printf(">>>O personagem morreu em combate...\n");					
						return 0;
					}
					if(matriz[antesX][antesY] == 'V'){ 
						printf(">>>O personagem conseguiu...\n");
						return 1;
					}	
					if(tentativa > 1000){
						return 1;
					}
					
					//COMPARAÇÃO DE POSSÍVEIS LOCAIS PARA O PERSONAGEM SE MOVIMENTAR!!!!!	
					if(matriz[inicioX+1][inicioY] != '#' && matriz[inicioX+1][inicioY] !='*' && inicioX+1<=num1 && matriz[inicioX+1][inicioY] != '!'){
						cont++;		
						talvez[cont].x= inicioX+1;
						talvez[cont].y= inicioY;
					}
					if(matriz[inicioX-1][inicioY] != '#' && matriz[inicioX-1][inicioY] !='*' && inicioX-1>=1 && matriz[inicioX-1][inicioY] != '!'){
						cont++;
						talvez[cont].x= inicioX-1;
						talvez[cont].y= inicioY;
					}
					if(matriz[inicioX][inicioY+1] != '#' && matriz[inicioX][inicioY+1] !='*' && inicioY+1<=num2 && matriz[inicioX][inicioY+1] != '!'){
						cont++;
						talvez[cont].x= inicioX;
						talvez[cont].y= inicioY+1;
					}
					if(matriz[inicioX][inicioY-1] != '#' && matriz[inicioX][inicioY-1] !='*' && inicioY-1>=1 && matriz[inicioX][inicioY-1] != '!'){
						cont++;
						talvez[cont].x= inicioX;
						talvez[cont].y= inicioY-1;
					}// FIM DAS COMPARAÇÕES	
				
					if(cont == 0){ // CASO NAO HAJA LUGAR PARA SE MOVIMENTAR
						matriz[antesX][antesY] = '?';
					}
					else{
						lol = aleatorio(cont);
						inicioX = talvez[lol].x;
						inicioY = talvez[lol].y;
						if(matriz[inicioX][inicioY] == '$') {
							if(matriz[antesX][antesY] != '!'){
								matriz[antesX][antesY] = '*';
								matriz[inicioX][inicioY] = 'V';
							}
							else if (matriz[antesX][antesY] == '!'){
								matriz[inicioX][inicioY] = 'V';
					
							}
							printf(">>>O personagem conseguiu...\n");
							labescrita(num1, num2, matriz);
						}
						else if(matriz[inicioX][inicioY] == '%'){
							if(inimigo() == 1){
								if(matriz[antesX][antesY] != '!'){
									matriz[antesX][antesY] = '*';
								}
								matriz[inicioX][inicioY] = '!';								
							}
							if(inimigo() == 0){
								if(matriz[antesX][antesY] != '!'){
									matriz[antesX][antesY] = '*';
								}
								matriz[inicioX][inicioY] = '+';
							}
						}	
						else{
							if(matriz[antesX][antesY] != '!'){
								matriz[antesX][antesY] = '*';
							}
							matriz [inicioX][inicioY] = '@';
						}
					}
			
			sleep(0.1);
			system("clear");
			printf("Tentativas: %d\n", tentativa);
			for (i=1 ; i<=num1 ; i++){
				for(j=1 ; j<=num2 ; j++) {
					printf("%c ", matriz[i][j]);
				}	
			printf("\n");
			} // impressao do labirinto com @ andando.
		//
		}while((matriz[finalX][finalY] != 'V')) ; // final do DO WHILE
		return 1;  								
	}
void teladeinicio(){
	printf("\n");	
	puts("\n\n\n\n\n\n\n\n\n                                MAZE WALKER\n");
	printf("                              Pressione Enter");	
    getchar();    
    system ("clear");
	}
void menu(){
	printf("\n");
	printf("                                MODO DE JOGO:                 \n");
	printf("\n");
    printf("                   1 - Resolver labirinto com uma tentativa.\n");
    printf("                   2 - Resolver labirinto até obter sucesso.\n");
    printf("                   3 - Sair do programa. \n");
    printf("                   ");
	}
int main (){	
	srand((unsigned)time(NULL)*time(NULL));
	int escolha; 
	int tentativas = -1;	
    teladeinicio();
    menu();
    scanf("%d%*c",&escolha); //Escolha do Modo de Jogo
    system ("clear");
     
    if (escolha==1){	// Modo de Jogo 1
			printf("                                Modo 1\n");
			jogo();
	return 0;
	}	
	 if (escolha==2){ //modo 2		
		printf("                                Modo 2\n");		
		do {
			tentativas++;
			}while (!jogo2(tentativas));
			flag=0;			
	return 0;	
	}
	if (escolha==3){ //sair   
		printf("Saindo\n"); 
	return 0;
	}
		 
return 0; 
}
