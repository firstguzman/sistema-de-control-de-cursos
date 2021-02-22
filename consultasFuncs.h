#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#include "proyectStructs.h"
#include "auxFuncsAlum.h"


int buscar(int val, int codigo, alumnos **alumno, cursos **curso, materias **materia){
	alumnos *alumnop = *alumno;
	cursos *cursop = *curso;
	materias *materiap = *materia;
	//validar cedula
	if (val == 1){
		while(alumnop){
			if (atoi(alumnop->cedula) == codigo)
				return 1;
			alumnop = alumnop->proxalumno;
			if (!alumnop){
				printf ("cedula no encontrada\n");
				return 0;
			}

		}
	}		
	//validar curso
	else if (val == 2){
		while(cursop){
			if (cursop->codigoCurso == codigo){
				return 1;
				}
			cursop = cursop->proxCurso;
			if (!cursop){
				printf("codigo no encontrado\n");
				return 0;
			}
		}
	}
	//validar materia
	else {
		while (materiap){
			if (materiap->codigoMat == codigo)
				return 1;
			materiap = materiap->proxMateria;
			if (!materiap){
				printf("codigo no encontrado\n");
				return 0;
			}
		}
	}

}


//funciones del punto 3.1 y 3.2

void ubicarAlumno(alumnos **alumno){
	alumnos *alumnop = *alumno;
	char nombre[10];
	char apellido[10];
	int flag = 0;
	printf("Ingrese el nombre del alumno que desea consultar\n");
	scanf("%s",nombre);
	printf("\nIngrese los apellidos del alumno que desea consultar\n");
	scanf("%s",apellido);
	printf("\nlos alumnos con ese nombre son\n");
    while (alumnop){
		
		if ((strstr(alumnop->nombre,nombre)) && (strstr(alumnop->apellidos,apellido))){
			flag = 1;
			printf("\tnombre:%s %s\tcedula: %s\tcorreo: %s\tdireccion: %s\n",alumnop->nombre, alumnop->apellidos, alumnop->cedula, alumnop->correo, alumnop->direccion);
        }
		alumnop = alumnop->proxalumno;
	}
	if (!flag)
		printf("no hay alumnos con este nombre");
}

void ubicarCurso(cursos **curso, materias **materia){
	char materiaS[10];
	int flag = 0;
	cursos *cursop = *curso;
	materias *materiap = *materia;

	printf("Ingrese el nombre de la materia a la que pertenece el curso\n");
	scanf("%s",materiaS);
	 while (materiap){
		 if (strstr(materiap->materia, materiaS))
			 printf("El codigo de la materia es: %i\n", materiap->codigoMat);
		 printf("1");
		 materiap = materiap -> proxMateria;
	}
	 printf("\nlos cursos que pertenecen a esta materia son\n");
	while (cursop){
		if (strstr(cursop->deMateria->materia,materiaS)){
			flag = 1;
			printf("\n\tcodigo: %i \tano: %i\tlapso: %i\thorario: %s\n",cursop->codigoCurso, cursop->ano,cursop->lapso, cursop->horario);
        }
		cursop = cursop->proxCurso;
	}
	if (!flag)
		printf("\nno se encuentran cursos pertenecientes a esta materia");
}


/////////funciones de 3.3

void mostrarCronologico(indiceCursos **indiceCurso, int cedula){
	indiceCursos *indiceCursop = *indiceCurso;
	cursosY *rcy = (*indiceCurso)->recordYC;
	recordCurso *recordC = (*indiceCurso)->recordYC->record;

	if (indiceCursop && indiceCursop->proxInCurso){
		indiceCursop = indiceCursop->proxInCurso;
		mostrarCronologico(&indiceCursop, cedula);
	}

	//while (indiceCursop){

		rcy = indiceCursop->recordYC;
		while (rcy)
		{
			recordC = rcy->record;
			while (recordC)
			{
				if (atoi(recordC->alumno->cedula) == cedula){
					printf("%i\n", indiceCursop->ano);
					printf("materia: %s curso: %i ", rcy->deCurso->deMateria->materia, rcy->deCurso->codigoCurso);
					if (strcmp(recordC->nota, "RE") == 0) printf("%s\n",recordC->estatus);
					else printf("nota: %s\n",recordC->nota);
				}
				recordC = recordC->prox;
			}
			rcy = rcy->proxCursoy;
		}	
	//indiceCursop = indiceCursop->proxInCurso;
	//}
	
}	

void mostarMateriaE(indiceCursos **indiceCurso, int codigo, int cedula){
	indiceCursos *indiceCursop = *indiceCurso;
	cursosY *rcy = (*indiceCurso)->recordYC;
	recordCurso *recordC = (*indiceCurso)->recordYC->record;
		
	if (indiceCursop && indiceCursop->proxInCurso){
		indiceCursop = indiceCursop->proxInCurso;
		mostarMateriaE(&indiceCursop, codigo, cedula);
	}
	while (rcy)
	{
		if (rcy->deCurso->codigoCurso == codigo){
			while(recordC){
				if (atoi(recordC->alumno->cedula) == cedula){
					printf("%i\n", indiceCursop->ano);
					printf("%s %i ",rcy->deCurso->deMateria->materia,rcy->deCurso->codigoCurso);
					if (strcmp(recordC->nota, "RE") == 0) printf("%s\n",recordC->estatus);
					else printf("%s\n",recordC->nota);
				}
				recordC = recordC->prox;
			}	
		}
		rcy = rcy->proxCursoy;
	}

	
}

void promedios(indiceCursos **indiceCurso, int cedula, indiceAlumnos **indiceAlumno){
	indiceAlumnos *idniceAlumnop = *indiceAlumno;
	recordAlumno *rca = (*indiceAlumno)->record;
	int promedio = 0, reprobadas = 0, retiradas = 0;
	int i = 0;
	while (idniceAlumnop){
		if (atoi(idniceAlumnop->alumno->cedula) == cedula)
		{
			rca = idniceAlumnop->record;
			while (rca)
			{
				if (!strstr(rca->nota, "RE")){
					printf("%s",rca->nota);
					promedio += atoi(rca->nota);
					i++;
					if (atoi(rca->nota) < 10){
						reprobadas++;
					}
				}
				else
					retiradas ++;
				rca = rca->proxNota;
			}
		}
		idniceAlumnop = idniceAlumnop->proxAlum;
	}

	printf("\nSu promedio es de %i\n", promedio/i);
	printf("El numero de materias reprobadas es de %i\n", reprobadas);
	printf("El numero de materias retiradas es de  %i\n", retiradas);


}

void operacionesCedula(indiceCursos **indiceCurso, indiceAlumnos**indiceAlumno, alumnos **alumnos,cursos  **cursos, materias **materias){
	 int op2 = -1, x=0 , flag = 0;
	 char cedula[10];
	 printf("ingrese cedula\n");
	 scanf("%s",cedula);
	 flag = buscar(1,atoi(cedula),alumnos,cursos,materias);
    while( op2  && flag){
       // system("cls");
        printf("1.\tMostrar record academico\n");
        printf("2.\tMostrar numero de veces que ha cursado cierta materia\n");
        printf("3.\tCalcular promedio, numero de materias reprobadas y retiradas\n\n");
		printf("4.\tRegresar\n\n");
        scanf( "%i", &op2);

        switch(op2){
            case 1:
				{
				mostrarCronologico(indiceCurso, atoi(cedula));
				indiceCursos *indiceCursop = *indiceCurso;
				cursosY *rcy = (*indiceCurso)->recordYC;
				recordCurso *recordC = (*indiceCurso)->recordYC->record;

				while (rcy)
				{
					recordC = rcy->record;

					while (recordC)
					{

						if (atoi(recordC->alumno->cedula) == atoi(cedula)){	
							printf("%i\n", indiceCursop->ano);
							printf("materia: %s curso: %i ", rcy->deCurso->deMateria->materia, rcy->deCurso->codigoCurso);
							if (strcmp(recordC->nota, "RE") == 0) printf("%s\n",recordC->estatus);
							else printf("nota: %s\n",recordC->nota);
						}
						recordC = recordC->prox;
					}
					rcy = rcy->proxCursoy;
				}	
		        break;
				}
            case 2:{
               int codigo;
				printf("inserte el codigo de un curso\n");
				scanf("%i", &codigo);
				mostarMateriaE(indiceCurso, codigo, atoi(cedula));
				indiceCursos *indiceCursop = *indiceCurso;
				cursosY *rcy = (*indiceCurso)->recordYC;
				recordCurso *recordC = (*indiceCurso)->recordYC->record;
				while (rcy)
				{
					if (rcy->deCurso->codigoCurso == codigo){
						while (recordC)
						{
							if (atoi(recordC->alumno->cedula) == atoi(cedula)){	
								printf("%i\n", indiceCursop->ano);
								printf("materia: %s curso: %i ", rcy->deCurso->deMateria->materia, rcy->deCurso->codigoCurso);
								if (strcmp(recordC->nota, "RE") == 0) printf("%s\n",recordC->estatus);
								else printf("nota: %s\n",recordC->nota);
							}
							recordC = recordC->prox;
						}
					}
					rcy = rcy->proxCursoy;
				}	


                break;
				}
            case 3:
				promedios(indiceCurso, atoi(cedula),indiceAlumno);
                break;
			case 4:
				x = 1;
                break;
        };
    system("pause");
	if (x)
		break;
    }
}


/////////////funciones punto 3.4

void promediosC( int codigo,  cursos **curso, indiceCursos **indiceCurso){

	cursos *cursop = *curso;
	indiceCursos *indiceCursop = *indiceCurso;
	cursosY *rcy = (*indiceCurso)->recordYC;
	recordCurso *recordC = (*indiceCurso)->recordYC->record;
	
	int inscritos = 0, aprobados = 0, retirados = 0, reprobados = 0, flag = 0, ano = 0;

	
	while (indiceCursop)
	{

		rcy = indiceCursop->recordYC;
		recordC = indiceCursop->recordYC->record;

		if (indiceCursop->ano == ano){

			while (rcy)
			{

				if (rcy->deCurso->codigoCurso == codigo){

					while (recordC)
					{
						inscritos++;
						if (!strstr(recordC->nota,"RE"))
						{
							if (atoi(recordC->nota) < 10)
							{
								reprobados++;
							}
							else
								aprobados++;
						}
						else retirados++;
						recordC =recordC->prox;
					}
				rcy = rcy->proxCursoy;
				}
			}
		}
		indiceCursop = indiceCursop->proxInCurso;
	}


	
	

	printf("\nEl numero de inscritos es %i\n", inscritos);
	printf("El numero de aprobados es %i\n", aprobados);
	printf("El numero de reprobados es %i\n", reprobados);

}

void cursosD(int codigo, alumnos **alumno, indiceAlumnos **indiceAlumno, cursos **curso){
	indiceAlumnos *indiceAlumnop =*indiceAlumno;
	cursos *cursop = *curso;
	alumnos *alumnop = *alumno;
	recordAlumno *ralumno = (*indiceAlumno)->record;
	
	
	while (cursop)
	{
		if (cursop->codigoCurso == codigo)
		{
			printf("\tcodigo de curso: %i \tano: %i \tlapso: %i\t codigo de materia: %i \thorario: %s\n",cursop->codigoCurso, cursop->ano, cursop->lapso, cursop->deMateria->codigoMat, cursop->horario);
			break;
		}
		cursop = cursop->proxCurso;
	}

	while (alumnop)
	{
		indiceAlumnop = *indiceAlumno;

		while (indiceAlumnop)
		{

			if (strcmp(indiceAlumnop->alumno->cedula,alumnop->cedula)== 0)
			{

				ralumno = indiceAlumnop->record;
				while (ralumno)
				{

					printf("%i\n",ralumno->deCurso->codigoCurso);
					printf("%i\n", codigo);
					if (ralumno->deCurso->codigoCurso == codigo)
					{
						printf("\tnombre%s %s \tcedula: %s \ttelefono: %s \tcorreo: %s \tdireccion: %s \tfecha nacimiento: %s\n\n", indiceAlumnop->alumno->nombre, indiceAlumnop->alumno->apellidos, indiceAlumnop->alumno->cedula, indiceAlumnop->alumno->telefono, indiceAlumnop->alumno->correo, indiceAlumnop->alumno->direccion, indiceAlumnop->alumno->fNacimiento);
					}
					ralumno = ralumno->proxNota;
				}
			}
			indiceAlumnop = indiceAlumnop->proxAlum;
		}
		alumnop = alumnop->proxalumno;
	}


}

void operacionesC(indiceCursos **indiceCurso, alumnos **alumno, cursos **curso, materias **materia, indiceAlumnos **indiceAlumno){
	indiceCursos *indiceCursop = *indiceCurso;
	indiceAlumnos *indiceAlumnop = *indiceAlumno;
	alumnos *alumnop =  *alumno;
	cursos *cursop = *curso;
	materias *materiap = *materia;
	int op2 = -1, x=0, codigo = 0, flag = 0;
	
	printf("Escriba el codigo del curso\n");
	scanf("%i",&codigo);
	


	flag = buscar(2, codigo,alumno, curso, materia);
    while( op2 ){
	
       // system("cls");
        printf("1.\tMostrar todos los datos del curso con el numero de inscritos, total de aprobados, retirados y reprobados\n");
        printf("2.\tMostrar todos los datos del curso y sus alumnos con nota ordenado alfabéticamente por apellido\n\n");
		printf("3. \tRegresar\n\n");
        scanf( "%i", &op2);

        switch(op2){
            case 1:
				promediosC(codigo, curso, indiceCurso);
		        break;
            case 2:
				cursosD(codigo, &alumnop, &indiceAlumnop, &cursop);
                break;
            case 3:
				x = 1;
                break;
        };
    system("pause");
	if (x)
		break;
    }
}


///////Funciones 3.5

void totalH(int codigo, indiceAlumnos **indiceAlumno){
	indiceAlumnos *indiceAlumnop = *indiceAlumno;
	recordAlumno *recordA = (*indiceAlumno)->record;
	int reprobados = 0, retirados = 0, prom = 0, i = 0;

	while (indiceAlumnop)
	{
		recordA = indiceAlumnop->record;
		while (recordA)
		{
			if (recordA->deCurso->deMateria->codigoMat == codigo)
			{
				i++;
				if (!strstr(recordA->nota,"RE")){
					prom += atoi(recordA->nota);
					if (atoi(recordA->nota) < 10)	
						reprobados++;
	
				}
				else retirados ++;
			}
			recordA = recordA->proxNota;
		}
		indiceAlumnop = indiceAlumnop->proxAlum;
	}

	if (i!=0)
		prom = prom/i;
	
	printf("El numero de reprobados historicamente es: %i\n",reprobados);
	printf("El numero de retirados historicamente es: %i\n",retirados);
	printf("El promedio historico es: %i\n",prom);

}

void totalA(indiceCursos **indiceCurso, int codigo){
	int ano = 0;
	indiceCursos *indiceCursop = *indiceCurso;
	cursosY *rcy = (*indiceCurso)->recordYC;
	recordCurso *recordC = (*indiceCurso)->recordYC->record;

	printf("ingrese el ano en el que quiere ver el total de alumnos de la materia\n");
	scanf("%i",&ano);
	while (indiceCursop){
		if (indiceCursop->ano == ano){
			rcy = indiceCursop->recordYC;
			while (rcy){
				if (rcy->deCurso->deMateria->codigoMat == codigo){
					recordC = rcy->record;
					while (recordC){
						printf("%s %s %s\n", recordC->alumno->nombre, recordC->alumno->apellidos, recordC->alumno->cedula);
						recordC = recordC->prox;
					}
				}
				rcy = rcy->proxCursoy;
			}
		}
		indiceCursop = indiceCursop->proxInCurso;
	}
}

int destacadosBuscar(indiceCursos **indiceCurso){
	indiceCursos *indiceCursop = *indiceCurso;
	cursosY *rcy = (*indiceCurso)->recordYC;
	recordCurso *recordC = (*indiceCurso)->recordYC->record;
	int notaM = 0;
	while(indiceCursop){
		rcy = indiceCursop->recordYC;
		while(rcy){
			recordC = rcy->record;
			while (recordC){
				if (atoi(recordC->nota) > notaM && !strstr(recordC->nota, "RE"))
					notaM = atoi(recordC->nota);
				recordC = recordC->prox;
			}
			rcy = rcy->proxCursoy;
		}
		indiceCursop = indiceCursop->proxInCurso;
	}
	printf("la nota historica mas alta de esta materia es: %i\n", notaM);
	return notaM;
}

void destacadosMostrar(indiceCursos **indiceCurso, int nota){
	indiceCursos *indiceCursop = *indiceCurso;
	cursosY *rcy = (*indiceCurso)->recordYC;
	recordCurso *recordC = (*indiceCurso)->recordYC->record;
	if ( indiceCursop  && indiceCursop->proxInCurso){
		indiceCursop = indiceCursop->proxInCurso;
		destacadosMostrar(&indiceCursop, nota);
		}
		while (rcy){
			while (recordC){
				if (atoi(recordC->nota) == nota)
					printf("alumno: %s %s cedula: %s curso: %i\n", recordC->alumno->nombre, recordC->alumno->apellidos, recordC->alumno->cedula, indiceCursop->recordYC->deCurso->codigoCurso);
				recordC = recordC->prox;
			}
			rcy = rcy->proxCursoy;
		}

}	

void operacionesMateria(indiceCursos **indiceCursos, alumnos **alumnos, materias **materias, cursos **cursos, indiceAlumnos **indiceAlumnos){
	int op2 = -1, x=0, codigo = 0, flag = 0;
	printf("Escriba el codigo de la materia\n");
	scanf("%i",&codigo);
	flag = buscar(3,codigo, alumnos, cursos, materias);
	if (!flag)
	{
		printf("Materia no encontrada\n");
	}

    while(op2 && flag){
       // system("cls");
        printf("1.\tMostrar total historico\n");
        printf("2.\tMostrar ano particular\n");
		printf("3.\tDestacados\n\n");
		printf("4. \tRegresar\n\n");
        scanf( "%i", &op2);

        switch(op2){
            case 1:
				totalH(codigo, indiceAlumnos);
		        break;
            case 2:
				totalA(indiceCursos, codigo);
                break;
			case 3:
				{
				int nota=0;
				nota = destacadosBuscar(indiceCursos);
				destacadosMostrar(indiceCursos,nota);
				break;
				}
            case 4:
				x = 1;
                break;
        };
    system("pause");
	if (x)
		break;
    }
}