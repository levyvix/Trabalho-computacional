/***************************************************************************************************
Nome: Levy Marques Nunes
Matricula: 2018103400
Curso: Estatistica

Um grupo de amigos organizou o 'Bolão entre Amigos' para a primeira fase da Copa
do Mundo. Para participar deve-se colocar na caixinha R$ 10,00. Existem 3 regras de
pontuação e os participantes podem marcar de 0 até no máximo de 3 pontos por jogo
As regras estão listadas abaixo:
> Regra 1: acertando o resultado do jogo : 1 ponto (timeA ou timeB ou empate)
> Regra 2: acertando o número de gols feitos pelo timeA: 1 ponto
> Regra 3: acertando o número de gols feitos pelo timeB: 1 ponto
****************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define JOGOS 48
#define PESSOAS 10

//Variaveis Globais, significando que nao precisa passar nada por parametro, ja que todas as funcoes tem acesso
int a[JOGOS],b[JOGOS],ra[JOGOS],rb[JOGOS]; //Em ordem: aposta TimeA,aposta TimeB,resultado TimeA,resultado TimeB de 48 jogos
int i,j,p=0,pos,empate1=0,empate2=0,pts=0; //contadores
char arq[10], c[5],venc[255]; //strings. Em ordem: nome do arquivo (partic1.txt), valor do participante em caractere pra concatenar, nome do vencedor
int l,k; //contadores

int persistir[PESSOAS]; //lista de participantes que empataram em numero de pontos e regra 1
float maior=0; //verificar pontuação
float somaP=0; //soma dos pontos

FILE *f; //aposta do participante
FILE *r; //gabarito

char nome[PESSOAS][255]; // dividi as informações em vetores e atribui uma ordem por indice, cada indice do vetor representa a informacao de uma pessoa especifica
int pontos[PESSOAS];
int r1[PESSOAS];
int id[PESSOAS];

void lerEPontuar(){ //função pra ler os arquivos e pontuar os participantes

	r=fopen("resultados.txt","r"); //abre o resultado, so precisa ser aberto uma vez
	
	for(k=0;k<PESSOAS;k++){ // k seria o contador de participantes
 		strcpy(arq,"partic"); // string arquivo recebe partic, pq todos os arquivos começam com partic
		sprintf(c,"%d",k+1); //transformação da variavel k, em uma string
		strcat(arq,c); //contatenação do caractere c na string arquivo, Exemplo: para k=1, a string 'arq' fica: partic1
		strcat(arq,".txt"); //adicionando a extensao do arquivo
		f=fopen(arq,"r"); //abre o arquivo
		 
		id[k] = k; //o id do participante é usado pra identificar a pessoa no meio dos vetores, serve pra consulta
		r1[k] = 0; // como regra1 é um contador, precisa ser zerado, se nao ele soma com lixo
		fscanf(f,"%[^\n]s",nome[k]);
		for(i=0;i<JOGOS;i++){
 		    
			fscanf(f,"%d%d",&a[i],&b[i]); //pega as apostas e divide entre a e b, sendo a=aposta do time A, e b=aposta do time B
			fscanf(r,"%d%d",&ra[i],&rb[i]); //mesma coisa só que com os resultados
		}

        	for(j=0;j<JOGOS;j++){ // pontuação dos participantes de acordo com as regras pre-estabelecidas

			    if(a[j] == b[j] && ra[j]==rb[j] || a[j] > b[j] && ra[j] > rb[j] || a[j] < b[j] && ra[j] < rb[j]){ //regra 1
			        p++;
			        r1[k]++; //contador de regra 1
			    }
			    if(a[j] == ra[j]){ //regra 2
			        p++;
			    }
			    if(b[j] == rb[j]){ //regra 3
			        p++;
			    }
	
			    pts +=p; 
			    p=0; // variavel zerada para o proximo jogo
		}
        
			pontos[k] = pts; //pessoa recebe a soma dos pontos de todos os 48 jogos
			somaP += pts; //pra tirar a media de pontos
			
			pts = 0; //zera pro proximo participante
    	}
}

void verificarEmpate(){ // ver se tem empate e desempatar, ou se tiver empate duplo, saber quem e
	
	for(l=0;l<PESSOAS;l++){
        if(pontos[l] >= maior){ //pontos do atual e maior que o maior ate agora
            if(pontos[l] == maior){//pontos iguais
                if(r1[l] >= r1[pos]){//regra 1 maior que a regra1 do maior ate agora
                    if(r1[l] == r1[pos]){//mesma regra1
                        empate2++;
                        persistir[l] = id[l]; //a lista recebe o id, pra comparar na lista quem sao os vencedores
                   }else{
                   //r1.l>r1.pos
                   	    maior = pontos[l];
	                    pos = l; //pega a posicao do vencedor pra fazer a comparacao
	                    persistir[l] = id[l];
	                    empate1++;
                   }
                }
            }else{
                
	            maior = pontos[l];
	            pos = l;
	            persistir[l] = id[l];
	            empate1=empate2=0; //zera o empate caso uma pontuacao mais alta seja alcancada, serve pro filtro de mensagens
        	}
        }
    }
}

void vencedores(){
	if(empate1 == 0 && empate2 == 0){
     	
	    printf("\n\nNao houve empate!\n");
		printf("Vencedor pela quantidade de pontos: %s\n",nome[pos]);
		printf("Pontos de %s: %.f\n",nome[pos],maior);
		printf("Premio: %d\n",100);
		
	}else if(empate1!=0 && empate2==0){
		
		printf("\n\nHouve Empate!\n");
	    printf("Valor dos pontos da Regra1 que desempatou: %d\n",r1[pos]);
	    printf("Vencedor(a): %s\n",nome[pos]);
	    printf("Pontos: %.f\n",maior);
	    printf("Premio: R$%d\n",100);
	    
	}
	else{
		
		printf("\n\nPersistiu o Empate!\n");
		printf("Vencedores: \n");
		for(l=0;l<10;l++){
			if(persistir[l] == id[l] && pontos[l] == maior && r1[l] == r1[pos]){ //so imprime o nome das pessoas que a lista recebeu e que possuem a maior pontuacao, e tem a mesma regra1 que o vencedor
				printf("%s\n", nome[l]);
			}
		}
		printf("\nPontuacao dos participantes: %.f\n",maior);
		printf("Valor do premio de cada vencedor: R$%.2f\n",100.0/(empate2+1)); //soma um porque são as pessoas que empararam, mais o primeiro vencedor
		
	}
	
	printf("\nMedia dos pontos dos participantes: %.2f\n", somaP/10);
	printf("\nPorcentagem de Acertos da maior pontuacao: %.2f%%\n\n",(maior/144)*100); //a formula que tava no pdf, só tirei a variavel
}

void fechaArq(){
	fclose(f);
	fclose(r);
}
void main(){

	lerEPontuar();
    
    verificarEmpate();
    
    vencedores(); //imprimir quem venceu
	
	fechaArq();
}
