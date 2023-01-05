#include <stdio.h>
#include <string.h>
#include "datatypes.h"
#include "datatypes.c"
#include "priorityqueue.h"
#include "priorityqueue.c"

// Abraham de León Gutiérrez
// Luis Santiago Zamora Vargas

int compare(TYPE d1,TYPE d2);
void lowersentences(char *cad, int leng);

int main()
{
	//Abrimos el archivo de texto
	FILE *texto1, *texto2;
	char *textoN1, *textoN2;
	unsigned long long bytes1, bytes2;
	int counter=0, distinto =0;
	texto1=fopen("texto1.txt", "r");
	texto2=fopen("texto2.txt", "r");
	if(texto1 == NULL || texto2 == NULL){
		return 1;
	}

	//Vemos su contenido
	fseek(texto1, 0, SEEK_END);
	bytes1 = ftell(texto1);
	fseek(texto2, 0, SEEK_END);
	bytes2 = ftell(texto2);
	rewind(texto1);
	rewind(texto2);
	//Reservamos memoria
	textoN1 = calloc(bytes1+1,sizeof(char));
	textoN2 = calloc(bytes2+1,sizeof(char));

	//Escaneamos el texto
	fread(textoN1,sizeof(char),bytes1,texto1);
	fread(textoN2,sizeof(char),bytes2,texto2);
	
	//Damos un mensaje
	printf("BIENVENIDO AL COMPARADOR DE ARCHIVOS DE TEXTO\n");
	printf(" SERA:  %s == %s\n",textoN1,textoN2);
	printf("[*] COMPARANDO AMBOS TEXTOS\n");

	// Las bajamos a minúsculas
	lowersentences(textoN1,(int)bytes1);
	lowersentences(textoN2,(int)bytes2);

	//Creamos los piorytyqueues
	PRIORITYQUEUE pqfile1, pqfile2 ;
	pqfile1 = priorityqueue_create(compare);
	pqfile2 = priorityqueue_create(compare);
	
	char *arrtemp1 = calloc(bytes1+1,sizeof(char));
	char *arrtemp2 = calloc(bytes2+1,sizeof(char));

	int counter1 =0, counter2=0;
	distinto =0;

	if(distinto ==0){
		int i;
		//Se van añadiendo a priority queues
		//Esto con el objetivo de que se acomoden de manera alfabética
		//Además evitamos agregar las comas, puntos y cosas a evitar y con esto 
		//Evitamos hacer una función de remoción de caracteres
		for(i=0;i<(int)bytes1+1;i++){
			if(textoN1[i] != '.' && textoN1[i] != ',' && textoN1[i] != ' '){
				arrtemp1[counter1]= textoN1[i];
				counter1++;
			}
			if(textoN1[i]== ' ' || textoN1[i]== '\0'){
				printf("1 %s\n", arrtemp1);
				priorityqueue_offer(pqfile1, str_create(arrtemp1));
				memset(arrtemp1,'\0',bytes1);
				counter1=0;
			}
			
		}
		for(i=0;i<(int)bytes2+1;i++){
			if(textoN2[i] != '.' && textoN2[i] != ',' && textoN2[i] != ' '){
				arrtemp2[counter2]= textoN2[i];
				counter2++;
			}
			if(textoN2[i]== ' ' || textoN2[i]== '\0'){
				printf("2 %s\n", arrtemp2);
				priorityqueue_offer(pqfile2, str_create(arrtemp2));
				memset(arrtemp2,'\0',bytes2);
				counter2=0;
			}
			
		}
		if(pqfile1->size!=pqfile2->size){
			distinto = 1;
		}else{
			//Se sacan y se comparan
			int comparacion=0;
			int size = pqfile1->size;
			for(i=0;i<size;i++){
				comparacion= compare(priorityqueue_poll(pqfile1),priorityqueue_poll(pqfile2));
				if(comparacion!=0){
					distinto = 1;
				}
			}
		}

	}
	if(distinto ==1){
		printf("Los archivos son distintos");
	}

	if(distinto ==0){
		printf("Los archivos son iguales");
	}
}

int compare(TYPE d1,TYPE d2)
{
	char *s1 = d1;
	char *s2 = d2;
	int retval = strcmp(s1,s2);
	
	return retval;
}

void lowersentences(char *cad, int leng){
	int i;
	for (i=0;i<leng;i++){
		if(cad[i] <= 'Z' && cad[i] >= 'A'){
			cad[i] += 32;
		}
	}
}
