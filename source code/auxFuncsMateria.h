#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "consultasFuncs.h"


//**************AGREGAR*
void leerArchivoMaterias(materias **materia){

	
	char path[50], dato[20];
	FILE *archive;
	printf("arrastre archivo que desea leer");
	scanf("%s",path);
	if ((archive = fopen(path, "r")) == NULL){
		printf("error opening the file");
		exit(1);
	}

	
	materias *materiap = *materia;
	while (!feof(archive)){
		materias *nuevaM = new materias;
		//nombre
		fgets(dato, 50, archive);
		strcpy(nuevaM->materia,dato);
		printf("%s",nuevaM->materia);
		//area
		fgets(dato, 50, archive);
		strcpy(nuevaM->area,dato);
		//codigo
		fgets(dato, 50, archive);
		//TODO: Ver si hace falta if
		while (materiap){
			if (materiap->codigoMat == atoi(dato))
				printf("ya hay una materia con este codigo");
			   //TODO

			materiap = materiap->proxMateria;
		}
		nuevaM->codigoMat = atoi(dato);
		//creditos
		fgets(dato, 50, archive);
		nuevaM->creditos = atoi(dato);
		//semestre
		fgets(dato, 50, archive);
		nuevaM->semestre = atoi(dato);

		nuevaM->proxMateria = *materia;
		*materia = nuevaM;

		fgets(dato, 50, archive);
		
		
	}
	materiap = *materia;
	while(materiap){
		printf("%s",materiap->area);
	materiap = materiap->proxMateria;
	}

	fclose(archive);
	
}

void leerDatosMateria(materias **materia){
	char resp[3]="si";
	int numero,n;
	while (!(strcmp(resp,"si"))){
		materias *nuevaM = new materias;
		materias *materiap = *materia;
		//nombre
		printf("\tIntroduzca el nombre: \n ");
		scanf("%i",&numero);
		getchar();
		gets((nuevaM)->materia);
		//area
		printf("\tIntroduzca el area: \n ");
		gets((nuevaM)->area);
		//codigo
		printf("\tIntroduzca el codigo: \n ");
		scanf("%i",nuevaM->codigoMat);
		if (nuevaM->codigoMat<0){
			printf("ERROR!!");
			n=1;
			while (n){
				printf("\tIntroduzca el codigo: \n ");
				scanf("%i",nuevaM->codigoMat);
				if (nuevaM->codigoMat>=0)
					n--;
			}
		}
		//TODO: Ver si hace falta if
		while (materiap){
			if (materiap->codigoMat == nuevaM->codigoMat)
				printf("ya hay una materia con este codigo");
			   //TODO
			materiap = materiap->proxMateria;
		}
		//creditos
		printf("\tIntroduzca los creditos: (1-6)\n ");
		scanf("%i",nuevaM->creditos);
		if ((nuevaM->creditos>6) || (nuevaM->creditos<1)){
			printf("cantidad de creditos no permitidos");
			n=1;
			while(n){
				printf("\tIntroduzca los creditos: (1-6)\n ");
				scanf("%i",nuevaM->creditos);
				if ((nuevaM->creditos<=10) || (nuevaM->creditos>=1))
					n--;
			}
		}
		//semestre
		printf("\tIntroduzca el semestre : (1-10)\n ");
		scanf("%i",nuevaM->semestre);
		if ((nuevaM->semestre>10) || (nuevaM->semestre<1)){
			printf("Semestre no valido");
			n=1;
			while(n){
				printf("\tIntroduzca el semestre : (1-10)\n ");
				scanf("%i",nuevaM->semestre);
				if ((nuevaM->semestre<=10) || (nuevaM->semestre>=1))
					n--;
			}
		}	

		nuevaM->proxMateria = *materia;
		*materia = nuevaM;

		printf("Desea agregar otra materia?(si|no)");
		scanf("%s",resp);
	}
}


//********************MODIFICAR***************

void modificarM(materias **materia){
	int codigo = 0, vali = 0, op2 = -2, x=0;
	char dato[20];
	materias *materiap = *materia;
	printf("Escriba el codigo de la materia\n");
	scanf("%i",&codigo);
	while (materiap){
		if (materiap->codigoMat == codigo){
			vali = 1;
			break;
		};
		materiap = materiap->proxMateria;
	};
	printf("here3");
	//TODO: properly exit and menu
	 if (vali == 0)
		 exit(1);
	 while( op2 ){
		 printf ("\n\n\t\tQue desea modifica\n");
        system("cls");
        printf("1.Nombre de la materia\n");
        printf("2. area\n");
		printf("3. creditos\n");
		printf("4. semstre\n");
		printf ("\n\n5. Regresar\n");
        scanf( "%i", &op2);

        switch(op2){
            case 1:
				printf("Escriba el nuevo nombre de la materia\n");
				scanf("%s",dato);
				strcpy(materiap->materia,dato);
		        break;
            case 2:
				printf("Escriba el nuevo nombre de la area\n");
				scanf("%s",dato);
				strcpy(materiap->area,dato);
                break;
			case 3: 
				printf("Escriba el numero de creditos nuevo\n");
				scanf("%s",dato);
				materiap->creditos = atoi(dato);
				break;
			case 4:
				printf("Escriba el numero del nuevo semestre\n");
				scanf("%s",dato);
				materiap->semestre = atoi(dato);
				break;
			case 5: 
				x= 1;
        };
    system("pause");
	if (x == 1)
		break;
    };
}


//**************+ELIMINAR*******************

void eliminarM(materias **materia, cursos **curso, cursosY **cursoY){
	int codigo = 0;
	materias *materiap = *materia;
	cursosY *cursoYp = *cursoY;
	printf ("escriba el codigo de la materia que desea eliminar\n");
	scanf("%i",&codigo);
	printf("here1");
	
	
	if (materiap->codigoMat == codigo){
			printf("here3");
			//eliminando materia
			printf("eliminando %s...\n",materiap->materia);
			*materia = materiap->proxMateria;
	}
	while (materiap && materiap->proxMateria){
		printf("here4");
		//eliminando materia
		printf("eliminando %s...\n",materiap->materia);
		if (materiap->proxMateria->codigoMat == codigo){
			printf("here5");
			materias *aux = materiap->proxMateria;
			materiap->proxMateria=materiap->proxMateria->proxMateria;
			delete aux;
		}
		materiap = materiap->proxMateria;
	}
	
	if (cursoYp && cursoYp->deCurso->deMateria == NULL){
			*cursoY = cursoYp->proxCursoy;
			delete cursoYp->deCurso;
			recordCurso *auxr = cursoYp->proxCursoy->record;
			while(cursoYp->proxCursoy->record){
				auxr = cursoYp->proxCursoy->record;
				cursoYp->proxCursoy->record = cursoYp->proxCursoy->record->prox;
				delete auxr;
			}
			delete cursoYp;
		}
	while (cursoYp  && cursoYp->proxCursoy){
		if (cursoYp->deCurso->proxCurso->deMateria == NULL){
			
			//eliminando cursos
			cursos *auxc = cursoYp->deCurso->proxCurso;
			cursoYp->deCurso->proxCurso = cursoYp->deCurso->proxCurso->proxCurso;
			delete auxc;
			//eliminando record
			recordCurso *auxr = cursoYp->proxCursoy->record;
			while(cursoYp->proxCursoy->record){
				auxr = cursoYp->proxCursoy->record;
				cursoYp->proxCursoy->record = cursoYp->proxCursoy->record->prox;
				delete auxr;
			}
			//eliminando cursoy
			cursosY *aux = cursoYp->proxCursoy;
			cursoYp->proxCursoy = cursoYp->proxCursoy->proxCursoy;
			delete aux;
			}
		materiap = materiap->proxMateria;
		if (materiap == NULL)
		   printf("el codigo no existe\n");
	}

	
}


//****************CONSULTAR********************

void consultarM(materias *materia, cursos *curso){
    int next = 1;
	materias *materiap = materia;
	cursos *cursop = curso;
    printf("Consultando...\n");
	while (materiap){
		
        printf("para pasar a la siguiente materia presione 2\n");
        printf("si quiere los cursos que dan esta materia presione 3\n");
		printf("\t%s %i\n",materiap->materia, materiap->codigoMat);
        scanf("%i",&next);

        if (next == 3){
			cursos *cursop = curso;
			while (cursop){
				if (strstr(cursop->deMateria->materia,materiap->materia))
					printf("\tcodigo: %i \tano: %i \tlapso: %i \thorario: %s\n",cursop->codigoCurso, cursop->ano, cursop->lapso, cursop);
				cursop=cursop->proxCurso;
			}
		}
		else if (next == 2){

			materiap = materiap->proxMateria;
			
		}
    }
}


