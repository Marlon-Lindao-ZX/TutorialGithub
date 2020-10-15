#include <stdbool.h>

#define MAX 150
#define CAP 30

/*Deber realizado por MARLON EDDIE LINDAO VARAS y VIELKA VERONICA VILLAVICENCIO VALLEJO*/

typedef struct Estudiante{
	char nombre[MAX];
	long matricula;
	int nota1;
	int nota2;
	int nota3;
}estudiante_t;

typedef struct Curso{
	estudiante_t student[CAP];
	int elementos;
}curso_t;

int validateI(int option);
long validateL();
bool crearEstudiante(curso_t *s);
bool isEmpty(curso_t *s);
void cleanBuffer();
void mostrarEstudiante(estudiante_t *e);
estudiante_t crear(char name[],long matr,int grade1,int grade2,int grade3);
void iniciar(curso_t *s);
void mostrar_Menu(curso_t *s);
bool buscarE(int matr,curso_t *s);
bool borrarE(int matr,curso_t *s);
bool eliminar(int index,curso_t *s);
void generarA(int index,curso_t *s);
float calcularNota(estudiante_t *e);
float * buscarEstNota(curso_t *s);
void buscarEstudiante(curso_t *s);
void borrarEstudiante(curso_t *s);
void mostrarEstadistica(curso_t *s);
