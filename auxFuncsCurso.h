#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "auxFuncsMateria.h"



//**************AGREGAR***************//

void leerArchivoCursos(cursos **curso, materias **materia, indiceCursos **indiceCurso){

	int flag = 0, i = 0;
	char path[50], dato[20];
	FILE *archive;
	printf("arrastre archivo que desea leer");
	scanf("%s",path);
	if ((archive = fopen(path, "r")) == NULL){
		printf("error opening the file");
		exit(1);
	}
	
	

	while (!feof(archive)){
		cursos *nuevoC = new cursos;
		materias *materiap = *materia;
		cursos *cursop = *curso;

		flag = 0;
		//codigo
		fgets(dato, 50, archive);
		printf("leyendo el codigo");
			//se verifica que el codigo no este repetido
		while(cursop){
			if (cursop->codigoCurso == atoi(dato)){
				printf("el codigo del curso esta repetido\n");
				flag = 1;
				break;
				}
			cursop = cursop->proxCurso;
		}
		if (flag)
			break;

		nuevoC->codigoCurso = atoi(dato);
		
		//ano
		fgets(dato, 50, archive);
		nuevoC->ano = atoi(dato);
		printf("ano: %i\n",nuevoC->ano);
		//lapso
		fgets(dato, 50, archive);
		nuevoC->lapso = atoi(dato);
		printf("lapso: %i\n",nuevoC->lapso);
		//codigo materia
		fgets(dato, 50, archive);
		if (!materiap){
			printf("no se encuentra ninguna materia registrada, por favor registre materias y vuelva a intentarlo\n");
			break;
		}
		while (materiap){
			if (materiap->codigoMat == atoi(dato)){
				printf("la materia se encuentra registrada\n");
				nuevoC->deMateria = materiap;
				printf("codigo materia: %s\n",nuevoC->deMateria->materia);
				flag = 1;
				break;
			}
			materiap = materiap->proxMateria;
			if (!materiap){
				printf("la materia a la que se le esta intentando anadir el curso no existe\n");
			}
		}
		if (!flag)
			break;

		nuevoC->deMateria = materiap;
		//horario
		fgets(dato, 50, archive);
		strcpy(nuevoC->horario, dato);
		printf("horario: %s\n",nuevoC->horario);

		// lee //
		fgets(dato, 50, archive);
		printf("%s\n",dato);

		//se anade el nodo a la lista de cursos
		nuevoC->proxCurso = *curso;
		*curso = nuevoC;
	


		//printf("%i",nuevoC->codigoCurso);
		//printf("%s",nuevoC->deMateria->materia);

		//creacion del nodo tipo cursoY

		cursosY *cursoY = new cursosY;
		cursoY->deCurso = nuevoC;
		cursoY->record = NULL;
		cursoY->proxCursoy = NULL;
		printf("materia: %s\n",cursoY->deCurso->deMateria->materia);
		i++;
		
		if (cursoY->deCurso == NULL)
			break;

		////ubicacion o creacion del nodo en indice curso y union de nodo cursoY
		indiceCursos *indiceCursop = *indiceCurso;
		printf("aqui0\n");
		indiceCursos *nuevoI = new indiceCursos;
		nuevoI->ano = nuevoC->ano;
		printf("ano del nuevo i %i",nuevoI->ano);
		nuevoI->recordYC = cursoY;
		nuevoI->proxInCurso = NULL;

		if (indiceCursop == NULL){
			printf("el inide curso esta vacio\n");
			printf("NULL\n");
			//para unirlo se inserta de primero
			nuevoI->proxInCurso = *indiceCurso;
			*indiceCurso = nuevoI;	
			printf("aqui1\n");
					
		}
		else if (indiceCursop->ano == nuevoC->ano){
			cursoY->proxCursoy = indiceCursop->recordYC;
			indiceCursop->recordYC = cursoY;
			printf("aqui2\n");
			printf("IGUAL\n");
		}	
		else if (nuevoC->ano > indiceCursop->ano ){
			//no hay ningun nodo con el ano y es el primero
			//para unirlo se inserta de primero
			nuevoI->proxInCurso = indiceCursop;	
			indiceCursop = nuevoI;
			printf("aqui3\n");
		}

		else if (indiceCursop && !indiceCursop->proxInCurso){
			if (!nuevoI->ano)
				exit(1);
			indiceCursop->proxInCurso = nuevoI;
			printf("aqui4\n");
			printf("ANADIENDO DE SEGUNDO\n");
		}
		
		
		else if (indiceCursop && indiceCursop->proxInCurso){
			while (indiceCursop->proxInCurso->ano > nuevoC->ano)
				indiceCursop = indiceCursop->proxInCurso;
			if (indiceCursop->proxInCurso->ano == nuevoC->ano){
				cursoY->proxCursoy = indiceCursop->proxInCurso->recordYC;
				indiceCursop->proxInCurso->recordYC = cursoY->proxCursoy;
			}
				//TODO: verificar que no falte ningun otro enlace
			else{
				//no hay ningun nodo con el ano so se crea
				//para unirlo se crea aux y se enlaza ordenadamente
				indiceCursos *aux = indiceCursop->proxInCurso;
				indiceCursop->proxInCurso = nuevoI;
				nuevoI->proxInCurso = aux;
				//if (nuevoI->proxInCurso->proxInCurso)
					//aux->proxInCurso = NULL;

				
			}
			
		}
		printf("i: %i\n",i);
		
	}

	fclose(archive);
	

}

void leerDatosCursos(cursos **curso, materias **materia, indiceCursos **indiceCurso){
	char resp[3]="si";
	int numero,n,flag;
	while (!(strcmp(resp,"si"))){
		cursos *nuevoC = new cursos;
		cursos *cursop = *curso;
		materias *materiap = *materia;
		//codigo
		printf("\tIntroduzca el codigo: \n ");
		scanf("%i",nuevoC->codigoCurso);
		if (nuevoC->codigoCurso<0){
			printf("ERROR!!");
			n=1;
			while (n){
				printf("\tIntroduzca el codigo: \n ");
				scanf("%i",nuevoC->codigoCurso);
				if (nuevoC->codigoCurso>=0)
					n--;
			}
		}
			//se verifica que el codigo no este repetido
		while(cursop){
			if (cursop->codigoCurso == nuevoC->codigoCurso){
				printf("el codigo del curso esta repetido\n");
				flag = 1;
				break;
				}
			cursop = cursop->proxCurso;
		}
		if (flag)
			break;

		//ano
		printf("\tIntroduzca el anho: \n ");
		scanf("%i",nuevoC->ano);

		//lapso
		printf("\tIntroduzca el lapso: (1-4)\n ");
		scanf("%i",nuevoC->lapso);
		if ((nuevoC->lapso>4) || (nuevoC->lapso<1)){
			printf("Lapso no permitido");
			n=1;
			while(n){
				printf("\tIntroduzca el lapso: (1-4)\n ");
				scanf("%i",nuevoC->lapso);
				if ((nuevoC->lapso<=4) || (nuevoC->lapso>=1))
					n--;
			}
		}

		//materia a la que corresponde
		if (!materiap){
			printf("no se encuentra ninguna materia registrada, por favor registre materias y vuelva a intentarlo\n");
			break;
		}
		printf("\tIntroduzca el codigo de la materia a la que corresponde el curso: \n ");
		scanf("%i",numero);
		while(materia){
			if (materiap->codigoMat == numero){
				printf("la materia se encuentra registrada\n");
				nuevoC->deMateria = materiap;
				printf("codigo materia: %s\n",nuevoC->deMateria->materia);
				flag = 1;
				break;
				//materia si se encontro
			}
			materiap = materiap->proxMateria;
			if (!materiap){
				printf("la materia a la que se le esta intentando anadir el curso no existe\n");
				exit(1);
			}
			//TODO: go back
			if (!flag)
				break;
		}
		nuevoC->deMateria = materiap;
		
		//horario
		printf("\tIntroduzca el horario de la materia: (Matutino, Vespertino, Nocturno\n ");
		scanf("%i",&numero);
		getchar();
		gets(nuevoC->horario);
		if ((strcmp(nuevoC->horario,"Matutino")==0) || (strcmp(nuevoC->horario,"Vespertino")==0) || (strcmp(nuevoC->horario,"Nocturno")==0))
			printf("Horario aceptado");
		else {
			n=1;
			while(n){
				printf("\tIntroduzca el horario de la materia: (Matutino, Vespertino, Nocturno\n ");
				gets(nuevoC->horario);
				if ((strcmp(nuevoC->horario,"Matutino")==0) || (strcmp(nuevoC->horario,"Vespertino")==0) || (strcmp(nuevoC->horario,"Nocturno")==0)){
					printf("Horario aceptado");
					n--;
				}
			}
		}

		nuevoC->proxCurso = *curso;
		*curso = nuevoC;

		//creacion del nodo tipo cursoY

		cursosY *cursoY = new cursosY;
		cursoY->deCurso = nuevoC;
		cursoY->record = NULL;

		////ubicacion o creacion del nodo en indice curso y union de nodo cursoY

		indiceCursos *indiceCursop = *indiceCurso;
		
		if (indiceCursop->ano == nuevoC->ano)
			cursoY->proxCursoy = indiceCursop->recordYC;
		else if (nuevoC->ano > indiceCursop->ano ){
			//no hay ningun nodo con el ano y es el primero
			indiceCursos *nuevoI = new indiceCursos;
			nuevoI->ano = nuevoC->ano;
			nuevoI->recordYC = cursoY;
			//para unirlo se inserta de primero
			nuevoI->proxInCurso = indiceCursop;	
		}
		else if (indiceCursop && indiceCursop->proxInCurso){
			while (indiceCursop->proxInCurso->ano > nuevoC->ano)
				indiceCursop = indiceCursop->proxInCurso;
			if (indiceCursop->proxInCurso->ano == nuevoC->ano)
				cursoY->proxCursoy = indiceCursop->proxInCurso->recordYC;
				//TODO: verificar que no falte ningun otro enlace
			else{
				//no hay ningun nodo con el ano so se crea
				indiceCursos *nuevoI = new indiceCursos;
				nuevoI->ano = nuevoC->ano;
				nuevoI->recordYC = cursoY;
				//para unirlo se crea aux y se enlaza ordenadamente
				indiceCursos *aux = indiceCursop->proxInCurso;
				indiceCursop->proxInCurso = nuevoI;
				nuevoI->proxInCurso = aux;	
			}
		}

		printf("Desea agregar otro curso?(si|no)");
		scanf("%s",resp);
	}
}


//********************MODIFICAR***************

//busca y enlaza
void buscarAnteriorCursoY(cursosY **cursoY, cursosY **cursoYbuscado){
	cursosY *cursoYp = *cursoY;
	while (cursoYp)
		if (cursoYp->proxCursoy == *cursoYbuscado){
			cursosY *aux = cursoYp->proxCursoy->proxCursoy;
			cursoYp->proxCursoy = aux;
			break;
		}
		cursoYp = cursoYp->proxCursoy;
}

void buscarNuevoAno(indiceCursos *indiceCursop,cursosY *curso, int anoNuevo){
	while(indiceCursop)
		if (indiceCursop->ano == anoNuevo){
			while (!indiceCursop->recordYC->proxCursoy)
				indiceCursop->recordYC = indiceCursop->recordYC->proxCursoy;
			indiceCursop->recordYC->proxCursoy = curso;
		}
		indiceCursop = indiceCursop->proxInCurso;
	}

void cambiarAno(indiceCursos **indiceCurso, cursos **curso, int anoViejo, int anoNuevo){
	indiceCursos *indicecursop = *indiceCurso;
	cursosY *cursoY;

	while (indicecursop)
		if (indicecursop->ano == anoViejo){
			cursoY = indicecursop->recordYC;
			while(indicecursop->recordYC){
				if (indicecursop->recordYC->deCurso == *curso){
					buscarAnteriorCursoY(&cursoY, &indicecursop->recordYC);
					buscarNuevoAno(*indiceCurso, indicecursop->recordYC, anoNuevo); 
					break;
				}
				indicecursop->recordYC = indicecursop->recordYC->proxCursoy;
			}
		}
		indicecursop = indicecursop->proxInCurso;
	}

void modificarC(cursos **curso, indiceCursos **indiceCurso){
	char dato[20];
	char *val;
	int codigo;
	int vali = 0, x = 0;
	int op2 = -2;
	cursos *cursop = *curso;
	if (indiceCurso)
		printf("el indice de curso si existe");
	printf("Escriba el codigo del curso\n");
	scanf("%i",&codigo);
	//busca el curso
	while (cursop){
		if (cursop->codigoCurso == codigo){
			vali = 1;
			break;
		};
		cursop = cursop->proxCurso;
	};
	//TODO: properly exit and menu
	 if (vali == 0)
		 exit(1);
		//no encontro el curso
	 while( op2 ){
		 printf ("\n\n\t\tQue desea modifica\n");
        system("cls");
        printf("1.\tAno del curso\n");
        printf("2.\Lapso del curso\n");
		printf("3.\Horario del curso\n\n");
		printf("4.\Regresar\n");
        scanf( "%i", &op2);

        switch(op2){
            case 1:
				printf("Escriba el nuevo ano\n");
				scanf("%s",dato);
				cambiarAno(indiceCurso,curso, cursop->ano, atoi(dato));
		        break;
            case 2:
				printf("Escriba el lapso \n");
				scanf("%s",dato);
				cursop->lapso = atoi(dato);
                break;
			case 3: 
				printf("Escriba el horario\n");
				scanf("%s",dato);
				strcpy(cursop->horario, dato);
				break;
			case 4: 
				x=1;
				break;
			
        };
    system("pause");
	if (x)
		break;
    };
}


 //*************+ELIMINAR*******************+

void eliminarC(materias **materia, cursos **curso,  indiceAlumnos **indiceAlumno, indiceCursos **indiceCurso){
	int codigo = 0;
	materias *materiap = *materia;
	cursos *cursop = *curso;
	indiceCursos *indiceCursop = *indiceCurso;
	indiceAlumnos *indiceAlumnop = *indiceAlumno;
	printf ("escriba el codigo del curso que desea eliminar\n");
	scanf("%i",&codigo);
	printf("1");
	if (cursop->codigoCurso == codigo){
		printf("1");
		cursos *aux = cursop;
		cursop = cursop->proxCurso;
		delete aux;
	}
	else {
	while (cursop && cursop->proxCurso){
		printf("2");
		if (cursop->proxCurso->codigoCurso == codigo)
		{
			printf("3");
			cursos *aux = cursop->proxCurso;
			cursop->proxCurso = cursop->proxCurso->proxCurso;
			delete aux;
		}
		cursop = cursop->proxCurso;
	}
	}
	/*if (indiceAlumno){
		printf("4");
		if (!indiceAlumnop->record->deCurso){
			recordAlumno *aux = indiceAlumnop->record;
			indiceAlumnop->record = indiceAlumnop->record->proxNota;
			delete aux;
		}
		while (indiceAlumnop->record  && indiceAlumnop->record->proxNota){
			if (!indiceAlumnop->record->proxNota->deCurso){
				recordAlumno *aux = indiceAlumnop->record->proxNota;
				indiceAlumnop->record->proxNota = indiceAlumnop->record->proxNota->proxNota;
			}
			indiceAlumnop->record = indiceAlumnop->record->proxNota;
		}
	}*/

	

	while (indiceCursop)
	{

		if (!indiceCursop->recordYC->deCurso){
			printf("6");
			delete indiceCursop->recordYC->record;
			cursosY *aux = indiceCursop->recordYC;
			indiceCursop->recordYC = indiceCursop->recordYC->proxCursoy;
			delete aux;
		}

		while (indiceCursop->recordYC && indiceCursop->recordYC->proxCursoy){
			printf("7");
			if (!indiceCursop->recordYC->proxCursoy->deCurso)
			{
				printf("8");
				
				cursosY *aux = indiceCursop->recordYC->proxCursoy;
				indiceCursop->proxInCurso = indiceCursop->proxInCurso->proxInCurso;
				delete aux;
			}
			indiceCursop->recordYC = indiceCursop->recordYC->proxCursoy;
		}
		indiceCursop = indiceCursop->proxInCurso;

	}
	indiceCursop = *indiceCurso;
	if (indiceCursop->recordYC == NULL)
	{
		indiceCursos *aux = indiceCursop;
		indiceCursop = indiceCursop->proxInCurso;
		delete aux;
	}
	else
		while (indiceCursop && indiceCursop->proxInCurso)
		{
			if (indiceAlumnop->proxAlum == NULL)
			{
				indiceCursos *aux = indiceCursop->proxInCurso;
				indiceCursop = indiceCursop->proxInCurso->proxInCurso;
				delete aux;
			}
		}	
	
}


//*******************CONSULTAR**************

void consultarCurso(indiceCursos **indiceC){
	int next = 1;
	indiceCursos *indiceCp = *indiceC;

    printf("Consultando...\n");


	while (indiceCp){


        printf("\npara pasar al siguiente ano presione 2\n");
        printf("si quiere ver los cursos de este ano presione 3\n");
        
		
		printf("\t%i \n",indiceCp->ano);
        scanf("%i",&next);
		
		
        if (next == 3){

			int i = 0;
			if (indiceCp->recordYC)
			
			while (indiceCp->recordYC){

				printf("\n\npara pasar al siguiente curso presione 2\n");
				printf("si quiere ver los alumnos y notas de este curso presione 3\n");
				printf("si quiere ver las especificaciones del curso presione 4\n\n");

				printf("\t%s %i",indiceCp->recordYC->deCurso->deMateria->materia, indiceCp->recordYC->deCurso->codigoCurso);
				scanf("%i\n",&next);

				if (next == 3){
					while (indiceCp->recordYC->record){
					printf("\t%s \tnota: %i\t estatus: %s\n",indiceCp->recordYC->record->alumno, indiceCp->recordYC->record->nota, indiceCp->recordYC->record->estatus);
					indiceCp->recordYC->record = indiceCp->recordYC->record->prox;
					}
				}

				else if (next == 4)
					printf("\tmateria: %s \tcodigo: %i \tano: %i \tlapso: %i \thorario: %s\n",indiceCp->recordYC->deCurso->deMateria->materia, indiceCp->recordYC->deCurso->codigoCurso, indiceCp->recordYC->deCurso->ano, indiceCp->recordYC->deCurso->lapso, indiceCp->recordYC->deCurso->horario);
	
				else if ((next == 2)){
					if (indiceCp->recordYC->proxCursoy == NULL){
						printf("Esos fueron los unicos cursos pertenecientes al ano %i", indiceCp->ano);
						break;
					}
					else indiceCp->recordYC = indiceCp->recordYC->proxCursoy;
			
			
					
				}
			}

		}

	else if ((next == 2))
			indiceCp = indiceCp->proxInCurso;

    }


	
}