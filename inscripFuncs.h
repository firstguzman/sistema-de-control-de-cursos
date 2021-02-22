#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#include "auxFuncs.h"
#include "auxFuncsCurso.h"


void inscribirA(indiceCursos **indiceCurso, indiceAlumnos **indiceAlumno, alumnos *alumnos, cursos *cursos){
	
	indiceAlumnos *indiceAlumnop = *indiceAlumno;
	indiceCursos *indiceCursop = *indiceCurso;
	cursosY *rcy = (*indiceCurso)->recordYC;
	recordCurso *recordC = (*indiceCurso)->recordYC->record;

	int flag = 0;
	char dato[10];
	int codigo;
	printf("escriba la cedula del alumno\n");
	scanf("%s",dato);
	while (alumnos){
		if (strcmp(alumnos->cedula,dato) == 0){
			printf ("el alumno es %s %s\n", alumnos->nombre, alumnos->apellidos);
			flag = 1;
			break;
			}
		alumnos = alumnos->proxalumno;
		if (!alumnos){
			printf("la cedula no se encuentra registrada en el sistema\n");
		}
	}
	if (flag){
		flag = 0;
		printf("Escriba el codigo del curso en el que quiere inscribir al alumno\n");
		scanf("%i",codigo);
		while (cursos){
			if (cursos->codigoCurso == codigo){
				flag = 1;
				printf("anadiendo a este curso...\n");
				printf("%s, %i", cursos->deMateria->materia, cursos->codigoCurso);
				break;
			}
			cursos = cursos->proxCurso;
			if (!cursos){
				printf("el codigo del curso no se encuentra registrado\n");
				break;
			}
		}
	}
	recordAlumno *nuevoR = new recordAlumno;
	if (flag){
		while (indiceAlumnop){
			if (indiceAlumnop->alumno->cedula == dato){
				printf("indique la nota\n");
				scanf("%s", dato);
				strcpy(nuevoR->nota,dato);
				printf("indique el estatus de inscripcion (PASADO, REPROBADO, CURSANDO, RETIRADO)\n");
				//TODO
				scanf("%s", dato);
				while ((strcmp(dato,"PASADO") != 0)&&(strcmp(dato,"REPROBADO") != 0)&&(strcmp(dato,"CURSANDO") != 0)&&(strcmp(dato,"RETIRADO") != 0)){
					printf("Por favor indique el estatus correctamente (PASADO, REPROBADO, CURSANDO, RETIRADO)");
					scanf("%s", dato);
				}
				strcpy(nuevoR->estatus,dato);
				nuevoR->deCurso = cursos;
				nuevoR->proxNota = indiceAlumnop->record;
				indiceAlumnop->record = nuevoR;
				break;
			}
			indiceAlumnop = indiceAlumnop->proxAlum;
		}
	}

	if (flag){
		flag = 0;
		while (indiceCursop){
			if (indiceCursop->ano == nuevoR->deCurso->ano)
				while (rcy)
					if (rcy->deCurso->codigoCurso == nuevoR->deCurso->codigoCurso){
						recordCurso *nuevoRC  = new recordCurso;
						strcpy(nuevoRC->nota, nuevoR->nota);
						strcpy(nuevoRC->estatus, nuevoR->estatus);
						nuevoRC->alumno = alumnos;
						nuevoRC->prox = recordC;
						recordC = nuevoRC;
						flag = 1;
						break;
					}
					rcy = rcy->proxCursoy;
			if (flag)
				break;
			indiceCursop = indiceCursop->proxInCurso;
		}
	}
	
}

void cambiarN(indiceCursos **indiceCurso, indiceAlumnos **indiceAlumno){
	indiceCursos *indiceCursop = *indiceCurso;
	indiceAlumnos *indiceAlumnop = *indiceAlumno;
	int codigoC = 0;
	char nota[5];
	char cedula[10];
	int flag = 0;
	printf("escriba la cedula del alumno al que le quiere modificar la nota\n");
	scanf("%s",cedula);
	printf("escriba el codigo del curso\n");
	scanf("%i", &codigoC);
	printf("escriba la nueva nota\n");
	scanf("%s",nota);
	while (indiceAlumnop){
		if (strstr(indiceAlumnop->alumno->cedula,cedula)){
			while(indiceAlumnop->record){
				if (indiceAlumnop->record->deCurso->codigoCurso == codigoC){
					strcpy(indiceAlumnop->record->nota, nota);
					while (indiceCursop){
						while (indiceCursop->recordYC){
							if (indiceCursop->recordYC->deCurso->codigoCurso == codigoC){
								while(indiceCursop->recordYC->record){
									if (indiceCursop->recordYC->record->alumno->cedula == cedula)
										strcpy(indiceCursop->recordYC->record->nota,nota);
									indiceCursop->recordYC->record = indiceCursop->recordYC->record->prox;
								}
							}
						indiceCursop->recordYC = indiceCursop->recordYC->proxCursoy;
						}
					indiceCursop = indiceCursop->proxInCurso;
					}
					break;
				}
			indiceAlumnop->record = indiceAlumnop->record->proxNota;
			}
		}
		if (flag)
			break;
		indiceAlumnop = indiceAlumnop->proxAlum;	
		if (!indiceAlumnop)
			printf("no se pudo modificar la nota, revise los datos y vuelva a intentarlo\n");
	}
}

void elimiarDeCurso(indiceAlumnos **indiceAlumno, indiceCursos **indiceCurso, alumnos *alumno, materias *materia, cursos *curso){
	int flag = 0, codigo = 0;
	char cedula[10];
	indiceAlumnos *indiceAp = *indiceAlumno;
	recordAlumno *rca = indiceAp->record;
	indiceCursos *indiceCp = *indiceCurso;
	cursosY *rcy = indiceCp->recordYC;
	recordCurso *rcc = indiceCp->recordYC->record;
	printf("Indique la cedula del alumno\n");
	scanf("%s",cedula);
	flag = buscar(1,atoi(cedula),&alumno,&curso,&materia);
	if (!flag)
		printf("Cedula no encontrada\n");
	printf("Indiqueel codigo del curso de donde lo quiere eliminar\n");
	scanf("%i",&codigo);
	flag +=  buscar(2,codigo,&alumno,&curso,&materia);
	if (flag!=2)
	{
		printf("Curso no encontrado\n");
	}
	if (flag == 2)
	{
		while (indiceAp)
		{
			if (strstr(indiceAp->alumno->cedula,cedula))
			{
				rca = indiceAp->record;
				if (rca->deCurso->codigoCurso == codigo)
				{
					recordAlumno *aux = rca;
					rca = rca->proxNota;
					delete aux;
					break;
				}
				else
				{
					while (rca && rca->proxNota)
					{
						if (rca->proxNota->deCurso->codigoCurso == codigo)
						{
							recordAlumno *aux = rca->proxNota;
							rca->proxNota = rca->proxNota->proxNota;
							delete aux;
							break;
						}
						rca = rca->proxNota;
					}
				}
			}
			indiceAp = indiceAp->proxAlum;
		}
	}
	
	if (flag == 2)
	{
		while (indiceCp)
		{
			rcy = indiceCp->recordYC;
			while (rcy)
			{
				if (rcy->deCurso->codigoCurso == codigo)
				{
					rcc = rcy->record;
					if (strstr(rcc->alumno->cedula, cedula))
						{
							recordCurso *aux = rcc;
							rcc = rcc->prox;
							delete aux;
						}
					else
						while (rcc && rcc->prox)
						{
							if (strstr(rcc->prox->alumno->cedula, cedula))
							{
								recordCurso *aux = rcc->prox;
								rcc->prox = rcc->prox->prox;
								delete aux;
							}
							rcc = rcc->prox;
						}
				}
				rcy = rcy->proxCursoy;
			}
			indiceCp = indiceCp->proxInCurso;
		}
	}
}

void cambiarDeCurso(indiceAlumnos **indiceAlumno, indiceCursos **indiceCurso, alumnos *alumno, materias *materia, cursos *curso){
	int ret = 0, nuevo = 0, flag = 0 ,anoret = 0, anonuevo;
	char cedula[10];
	cursos *cursop = curso;
	indiceAlumnos *indiceAp = *indiceAlumno;
	recordAlumno *rca = indiceAp->record;
	indiceCursos  *indiceCp = *indiceCurso;
	cursosY *rcy = indiceCp->recordYC;
	recordCurso *rcc = indiceCp->recordYC->record;
	printf("Indique la cedula del alumno\n");
	scanf("%s",cedula);
	flag = buscar(1,atoi(cedula),&alumno,&curso,&materia);
	if (!flag) printf("Cedula no encontrada\n");
	printf("Inserte el codigo del curso que quiere retirarse\n");
	scanf("%i",&ret);
	flag += buscar(2,ret,&alumno,&curso,&materia);
	if (flag!=2) printf("Codigo de curso no encontrado\n");
	printf("Inserte el codigo del curso al que quiere ser cambiado\n");
	scanf("%i",&nuevo);
	flag += buscar(2,nuevo,&alumno,&curso,&materia);
	if (flag!=3) printf("Codigo de curso no encontrado\n");
	else{
		while (indiceAp)
		{
			if (strstr(indiceAp->alumno->cedula,cedula))
			{
				rca = indiceAp->record;
				while (rca)
				{
					if (rca->deCurso->codigoCurso == ret)
					{
						anoret= rca->deCurso->codigoCurso;
						while (cursop)
						{
							if (cursop->codigoCurso == nuevo)
							{
								anonuevo = cursop->codigoCurso;
								rca->deCurso = cursop;
								
							}
							cursop = cursop->proxCurso;
						}
					}
					rca = rca->proxNota;
				}
			}
			indiceAp = indiceAp->proxAlum;
		}
		recordCurso *nuevoRC = new recordCurso;
		while (indiceCp)
		{
			if (indiceCp->ano == anoret)
			{
				rcy = indiceCp->recordYC;
				while (rcy)
				{
					rcc = rcy->record;
					if (rcy->deCurso->codigoCurso == ret)
					{	
						if (strstr(rcc->alumno->cedula, cedula))
						{
							strcpy(nuevoRC->nota, rcc->estatus);
							strcpy(nuevoRC->estatus, rcc->estatus);
							recordCurso *aux = rcc;
							rcc = rcc->prox;
							delete aux;
						}
						else
						{
							while (rcc &&rcc->prox)
							{
								if (strstr(rcc->prox->alumno->cedula, cedula))
								{
									strcpy(nuevoRC->nota, rcc->prox->estatus);
									strcpy(nuevoRC->estatus, rcc->prox->estatus);
									recordCurso *aux = rcc->prox;
									rcc->prox = rcc->prox->prox;
									delete aux;
								}
								rcc = rcc->prox;
							}
						}
						
					}
					rcy = rcy->proxCursoy;
				}
			}
			indiceCp = indiceCp->proxInCurso;
		}
		indiceCp = *indiceCurso;
		while (indiceCp)
		{
			if (indiceCp->ano == anonuevo)
			{
				rcy = indiceCp->recordYC;
				while (rcy)
				{
					rcc = rcy->record;
					if (rcy->deCurso->codigoCurso == nuevo)
					{
						nuevoRC->prox = rcc;
						rcc = nuevoRC;
					}
					rcy = rcy->proxCursoy;
				}
			}
			indiceCp = indiceCp->proxInCurso;
		}
		printf("Cursos cambiado");

	}
}