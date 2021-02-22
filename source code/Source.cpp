//Sofia y Cesar

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#include "auxFuncs.h"
#include "inscripFuncs.h"


void mainAux(int c, alumnos **alumnos, indiceAlumnos **indiceAlumnos, recordAlumno **recordAlumno, materias **materias, cursos **cursos, indiceCursos **indiceCurso, cursosY **cursosY){
    int op3 = -1, x=0;
	//alumnos *alumnos = alumnos;
	//indiceAlumnos *indiceA = indiceA;
    while( op3 ){
        //system("cls");
        printf("1.\tAgregar\n");
        printf("2.\tModificar\n");
        printf("3.\tEliminar\n");
        printf("4.\tConsultar\n\n");
		printf("5.\tRegresar\n\n");
        scanf("%i", &op3);

        switch(op3){
            case 1:
					if (c == 1){
						printf("\t1.Agregar alumno mediante archivo\n");
						printf("\t2.Agregar alumno manualmente\n");
						scanf("%i", &op3);

						switch(op3){
						case 1: leerArchivoAlumno(&*alumnos, &*indiceAlumnos,&*recordAlumno, &*cursos, &*indiceCurso);
								break;	
						case 2: leerDatosAlumno(&*alumnos, &*indiceAlumnos,&*recordAlumno, &*cursos, &*indiceCurso);
								break;
						}
					}
					else if (c == 2){
						printf("\t1.Agregar materias mediante archivo\n");
						printf("\t2.Agregar materias manualmente\n");
						scanf("%i", &op3);

						switch(op3){
						case 1: leerArchivoMaterias(&*materias);
								break;	
						case 2: leerDatosMateria(&*materias);
							break;
						}
					}
					else if (c == 3){
						printf("\t1.Agregar cursos mediante archivo\n");
						printf("\t2.Agregar cursos manualmente\n");
						scanf("%i", &op3);

						switch(op3){
						case 1: leerArchivoCursos(&*cursos, &*materias, &*indiceCurso);
								break;	
						case 2: leerDatosCursos(&*cursos, &*materias, &*indiceCurso);
								break;
						}	
                    break;
					}
            case 2:
				if (c == 1){
                        printf("\tModificar alumnos...\n");	
						modificarA(&*indiceAlumnos, &*alumnos, &*recordAlumno,&*materias, &*indiceCurso);
						//mostrarDatosA(alumnos);
                    }
					else if (c == 2){
						printf("\tModificar materias...\n");	
						modificarM(&*materias);
					}
					else if (c == 3){
						printf("\tModificar cursos...\n");	
						modificarC(&*cursos, &*indiceCurso);
					}
                    break;
            case 3:
				if (c == 1){
                        printf("\tEliminar alumnos...\n");	
						eliminarA(&*indiceAlumnos, &*indiceCurso,&*alumnos);
                    }
					else if (c == 2){
						printf("\tEliminar materias...\n");	
						eliminarM(&*materias,&*cursos,&*cursosY);
					}
					else if (c == 3){
						printf("\tEliminar cursos...\n");	
						eliminarC(&*materias,&*cursos,&*indiceAlumnos,&*indiceCurso);
					}
                    break;
            case 4:
                    if (c == 1){
                        printf("\tConsulta de alumnos...\n");	
						consultarA(indiceAlumnos,alumnos);
						//mostrarDatosA(alumnos);
                    }
					else if (c == 2){
						printf("\tConsulta de materias...\n");	
						consultarM(*materias,*cursos);
					}
					else if (c == 3){
						printf("\tConsulta de cursos...\n");	
						consultarCurso(indiceCurso);
					}
                    break;
			case 5: x = 1;
					break;
        }
    system("pause");
	if (x == 1)
		break;
	}
};

void mainMantenimiento(alumnos **alumnos, indiceAlumnos **indiceAlumnos, recordAlumno **recordAlumno, materias **materias, cursos **cursos, indiceCursos **indiceCursos, cursosY **cursosY){
    int op2 = -1, x=0;
    while( op2 ){
       // system("cls");
        printf("1.\tAlumno\n");
        printf("2.\tMateria\n");
        printf("3.\tCurso\n\n");
		printf("4.\tRegresar\n\n");
        scanf( "%i", &op2);

        switch(op2){
            case 1: mainAux(1, alumnos, indiceAlumnos,recordAlumno, materias, cursos, indiceCursos, cursosY);
					break;
			case 2: mainAux(2, alumnos, indiceAlumnos,recordAlumno, materias, cursos, indiceCursos, cursosY);
					break;
			case 3: mainAux(3, alumnos, indiceAlumnos,recordAlumno, materias, cursos, indiceCursos, cursosY);
					break;
			case 4: x = 1;
					break;
        };
    system("pause");
	if (x)
		break;
    }
};

void mainInscripciones(indiceAlumnos **indiceAlumnos, indiceCursos **indiceCursos, alumnos **alumnos, cursos **cursos, materias **materias){
	int op2 = -1, x=0;
    while( op2 ){
       // system("cls");
        printf("1.\tConsultas para obtener clave\n");
        printf("2.\tInscribir alumno en curso\n");
		printf("3.\tAgregar alumnos a curso\n");
		printf("4.\tModificar nota\n");
		printf("5.\tEliminar alumno de un curso\n");
		printf("6.\tEliminar curso\n");
		printf("7.\tRegresar\n\n");
        printf("8.\tSalir\n\n");
        scanf( "%i", &op2);

        switch(op2){
            case 1:
				{
                int op = 0;
				while (1){
					printf("1. buscar cedula del alumno\n");
					printf("2. buscar codigo de cursos y materia\n");
					scanf("%i", &op);
					if (op == 1){
						ubicarAlumno(alumnos);
						break;
					}
					else if (op == 2){
						ubicarCurso(cursos, materias);
						break;
					}
					else 
						printf("Opcion no valida");
				}
		        break;
				}
            case 2: inscribirA(*&indiceCursos, *&indiceAlumnos, *alumnos, *cursos);
					break;
            case 3:
                
                break;
			case 4: cambiarN(*&indiceCursos, *&indiceAlumnos);
					break;
			case 5:
                //mainAux(3);
                break;
			case 6:
                //mainAux(3);
                break;
			case 7:
                //mainAux(3);
                break;
			case 8: x = 1;
					break;
        };
    system("pause");
	if (x == 1)
		break;
    }
};

void mainConsultas(indiceCursos *indiceCurso, indiceAlumnos *indiceAlumno, alumnos *alumno, cursos *curso, materias *materia){
	indiceCursos *indiceCursop = indiceCurso;
	indiceAlumnos *indiceAlumnop = indiceAlumno;
	alumnos *alumnop =  alumno;
	cursos *cursop = curso;
	materias *materiap = materia;
    int op2 = -1, x=0;

	while (indiceCursop)
	{
		printf("1\n");
		while (indiceCursop->recordYC)
		{
			printf("2\n");
			while (indiceCursop->recordYC->record)
			{
				printf("3\n");
				printf("alumno: %s nota %s codigo curso %i\n", indiceCursop->recordYC->record->alumno->nombre, indiceCursop->recordYC->record->nota, indiceCursop->recordYC->deCurso->codigoCurso);
				indiceCursop->recordYC->record = indiceCursop->recordYC->record->prox;
			}
			indiceCursop->recordYC = indiceCursop->recordYC->proxCursoy;
		}
		indiceCursop = indiceCursop->proxInCurso;
	}


    while( op2 ){
       // system("cls");
        printf("1.\tUbicar Alumno\n");
        printf("2.\tUbicar Materia\n");
        printf("3.\tOperaciones con cedula\n\n");
		printf("4. \tOperaciones con curso\n\n");
		printf("5. \tOperaciones con materias\n\n");
		printf("6. \tRegresar\n\n");
        scanf( "%i", &op2);

        switch(op2){
            case 1: ubicarAlumno(&alumno);
					break;
            case 2: ubicarCurso(&curso, &materia);
					 break;
            case 3: operacionesCedula(&indiceCurso,&indiceAlumno,&alumno,&curso,&materia);
					break;
			case 4: operacionesC(&indiceCurso,&alumno,&curso,&materia,&indiceAlumno);
					break;
			case 5: operacionesMateria(&indiceCurso,&alumno,&materia,&curso,&indiceAlumno);
				    break;
			case 6: x = 1;
					break;
        };
    system("pause");
	if (x == 1)
		break;
    }
};

int main() {
	int op = -1, x=0;
    alumnos *alumnos = NULL;
	cursos *cursos = NULL;
	materias *materias = NULL;
	indiceAlumnos *indiceAlumnos = NULL;
	indiceCursos *indiceCursos = NULL;
	recordAlumno *recordAlumno = NULL;
	cursosY *cursosY = NULL;
	recordCurso *recordC= NULL;
	
	while ( op ){
		system("cls");
		while (indiceCursos){
			printf("1\n");
			while (indiceCursos->recordYC){
				printf("2\n");
				while (indiceCursos->recordYC->record){
					printf("3\n");
					printf("alumno: %s nota %s codigo curso %i\n", indiceCursos->recordYC->record->alumno->nombre, indiceCursos->recordYC->record->nota, indiceCursos->recordYC->deCurso->codigoCurso);
					indiceCursos->recordYC->record = indiceCursos->recordYC->record->prox;
				}
				indiceCursos->recordYC = indiceCursos->recordYC->proxCursoy;
			}
			indiceCursos = indiceCursos->proxInCurso;
		}
		printf( "\n\n\t\tMENU\n ");
		printf( "1.\tMantenimiento\n ");
		printf( "2.\tInscripciones\n ");
		printf( "3.\tConsultas\n\n");
		printf( "0.\tSALIR del sistema\n\n ");
		scanf("%i", &op);

		switch (op){
			case 1: mainMantenimiento(&alumnos, &indiceAlumnos, &recordAlumno, &materias, &cursos, &indiceCursos, &cursosY);
					break; 
			case 2: mainInscripciones(&indiceAlumnos,&indiceCursos,&alumnos,&cursos, &materias);
					break;
			case 3: mainConsultas(indiceCursos, indiceAlumnos,alumnos,cursos,materias);
					break;
		}
		system("pause");
	}
    return 0;
};

