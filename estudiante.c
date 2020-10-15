#include "estudiante.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*Deber realizado por MARLON EDDIE LINDAO VARAS y VIELKA VERONICA VILLAVICENCIO VALLEJO*/

int main(){
	curso_t curso;
	iniciar(&curso);
	mostrar_Menu(&curso);
}

void mostrar_Menu(curso_t *s){
	bool control = true;
	char opcion;
	while(control){
		printf("------Menú------\n\n");
		printf(" 1) Registrar estudiante \n 2) Buscar estudiante \n 3) Borrar estudiante \n 4) Mostrar estadísticas curso \n 5) Salir \n \n");
		printf("Ingrese opcion: ");
		scanf(" %c", &opcion);
		switch(opcion){
			case '1':
				crearEstudiante(s);
				break;
			case '2':
				buscarEstudiante(s);
				break;
			case '3':
				borrarEstudiante(s);
				break;
			case '4':
				mostrarEstadistica(s);
				break;
			case '5':
				control = false;
				break;
			default:
				fprintf(stderr,"Opcion invalida");
				cleanBuffer();
				break;
	
		}
	}
}

void iniciar(curso_t *s){
	s -> elementos = 0;
}

int validateI(int option){
	int value,status;
	do{
		cleanBuffer();
		switch(option){
			case 1:
				printf("Ingrese la nota del primer parcial del estudiante: ");
                		status = scanf(" %d", &value);
				break;
			case 2:
				printf("Ingrese la nota del segundo parcial del estudiante: ");
                		status = scanf(" %d", &value);
				break;
			case 3:
				printf("Ingrese la nota del mejoramiento del estudiante: ");
                		status = scanf(" %d", &value);
				break;
			default:
				value = -1;
		}
		if(status != 1) fprintf(stderr,"Ingrese un valor numerico\n\n");
	}while(value < 0 || value > 100 || status != 1);
	return value;	
}

long validateL(){
	long val;
	int status;
	do{
		printf("Ingrese la matrícula del estudiante: ");
                status = scanf(" %ld", &val);
		if(status != 1){
			fprintf(stderr,"Ingrese un valor de matricula correcta\n\n");
			cleanBuffer();
		}
	}while(status != 1);
	return val;

}

estudiante_t crear(char name[],long matr,int grade1,int grade2, int grade3){
	estudiante_t temp;
	int i;
	i = 0;
	while ((temp.nombre[i] = name[i]) != '\0') ++i;
	temp.matricula = matr;
	temp.nota1 = grade1;
	temp.nota2 = grade2;
	temp.nota3 = grade3;
	mostrarEstudiante(&temp);
	return temp;
}

bool crearEstudiante(curso_t *s){
	if(s -> elementos < CAP){
		char name[MAX];
		cleanBuffer();
		long matr;
		int grade1,grade2,grade3;
		printf("Ingrese el nombre del estudiante: ");
		fgets(name,MAX,stdin);
		matr = validateL();
		grade1 = validateI(1);
		grade2 = validateI(2);
		grade3 = validateI(3);
		s ->student[s -> elementos++] = crear(name,matr,grade1,grade2,grade3); 
		return true;
	} else{
		fprintf(stderr,"No hay espacio pra ingresar estudiantes\n\n");
		return false;
	}
}

bool isEmpty(curso_t *s){
	if(s -> elementos == 0) 
		return true;
	return false;
}

void cleanBuffer(){
	char c;
        while((c=getchar())!='\n' && c!=EOF){}
}

void mostrarEstudiante(estudiante_t *e){
	printf("\nNombre: %sMatricula: %ld\n",e -> nombre,e -> matricula);
	printf("Nota1: %d\nNota2: %d\nNota3: %d\n",e->nota1,e->nota2,e->nota3);
	printf("\n\n");
}

bool buscarE(int matr,curso_t *s){
      	for(int i=0;i<(s->elementos);i++){
		if(s->student[i].matricula == matr){
			mostrarEstudiante(&(s->student[i]));
			return true;
		}
	}
	return false;
}

void buscarEstudiante(curso_t *s){
	if(!isEmpty(s)){
		long matr;
		matr = validateL();
		if(!buscarE(matr,s))
			fprintf(stderr,"El estudiante no se encuentra en la lista de estudiantes\n\n");
	} else {
		fprintf(stderr,"La lista de estudiantes se encuentra vacía\n\n");
	}
}

void borrarEstudiante(curso_t *s){
        if(!isEmpty(s)){
                long matr;
                matr = validateL();
                if(!borrarE(matr,s))
                        fprintf(stderr,"La operación no pudo ser realizada\n\n");
        } else {
                fprintf(stderr,"La lista de estudiantes se encuentra vacía\n\n");
        }
}

bool borrarE(int matr,curso_t *s){
        for(int i=0;i<(s->elementos);i++){
                if(s->student[i].matricula == matr){
                       mostrarEstudiante(&(s->student[i]));
		       if(eliminar(i,s))
                       		return true;
		       fprintf(stderr,"La matricula del estudiante no se encuentra registrado\n\n");
		       return false;
                }
        }
        return false;
}

bool eliminar(int index,curso_t *s){
	char a[MAX];
	int len;
	cleanBuffer();
	do{
		printf("Desea eliminar al estudiante encontrado (Y/N): ");
		fgets(a,MAX,stdin);
	}while(!(a[0] == 'Y' || a[0] == 'N') || (strlen(a) != 2));
	if(a[0] == 'Y'){
		generarA(index,s);
		return true;
	}
	return false;
	
}

void generarA(int index,curso_t *s){
	if(s->elementos != 1){
		int i;
       		for(i=(s->elementos-1);i>index;i--)
                	s->student[i-1]=s->student[i];
	}
	s->elementos--;
	
}
		
void mostrarEstadistica(curso_t *s){
	if(!isEmpty(s)){
		float *arreglo;
		int mayor,menor;
		arreglo = buscarEstNota(s);
		printf("----Estadísticas del Curso----\n\n");
		printf("Promedio del Curso: %.2f\n\n",*(arreglo +0));
		printf("Datos del mejor estudiante: \n\n");
		mayor = *(arreglo+1);
		printf("Nota Final del mejor Estudiante: %.2f",(calcularNota(&(s->student[mayor]))));
		mostrarEstudiante(&(s->student[mayor]));
		printf("Datos del peor estudiante: \n\n");
		menor = *(arreglo+2);
		printf("Nota Final del peor Estudiante: %.2f",(calcularNota(&(s->student[menor]))));
		mostrarEstudiante(&(s->student[menor]));
	} else {
		fprintf(stderr,"La lista esta vacía,no hay datos que mostrar\n\n");
	}
}

float calcularNota(estudiante_t *e){
	float notaF;
	if((e->nota1)>(e->nota2)){
		if((e->nota2)>(e->nota3)){
			notaF= (e->nota1)+(e->nota2);
		} else {
			notaF= (e->nota1)+(e->nota3);
		}
	} else if((e->nota1)>(e->nota3)){
		notaF=(e->nota1)+(e->nota2);
	} else {
		notaF=(e->nota2)+(e->nota3);
	}
	return notaF/2;
}

float * buscarEstNota(curso_t *s){
	static float array[3];
	float temp,max,min,promedio;
	int i;
	max = promedio = 0;
	min = 100;
	for(i=0;i<(s->elementos);i++){
		temp = calcularNota(&(s->student[i]));
		if(temp > max){
			max = temp;
			array[1] = i;
		} else if (temp < min) {
			min = temp;
			array[2] = i;
		}
		promedio += temp;

	}
	array[0] = promedio/(i);
	return array;
}	
