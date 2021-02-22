#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "proyectStructs.h"


//*********CONSULTA****************

void mostrarDatosA(alumnos **alumno){
	alumnos *aux = *alumno;

	printf("nombre: %s %s \tcedula: %s \tcorreo: %s \tdireccion: %s \tnacimiento: %s", aux->nombre, aux->apellidos, aux->cedula, aux->correo, aux->direccion, aux->fNacimiento);
		aux= aux->proxalumno;

    //printf("\t%s\n",alumno->nombre);
    //printf("\t%i\n",alumno->cedula);
    //printf("\t%s\n",alumno->correo);
    //printf("\t%s\n",alumno->direccion);
    //printf("\t%s\i",alumno->fNacimiento);
}

void mostrarNotasA(recordAlumno **record){
	recordAlumno *aux = *record;
	printf("Las notas de las materias que ha cursado el alumno son \n");
	while (aux)
	{
		printf("\tmateria: %s\n",aux->deCurso->deMateria->materia);
		printf("\testatus: %s\n",aux->estatus);
		printf("\tnota: %2s\n\n",aux->nota);
		aux = aux->proxNota;
	}
	
	   
}

void consultarA(indiceAlumnos **ialumno, alumnos **alumno){
    int next = 1;
	indiceAlumnos *ialumnop = *ialumno;
	recordAlumno *rca = (*ialumno)->record;
	alumnos *alumnosp = *alumno;
    printf("Consultando...\n");
	while (ialumnop){
        printf("para pasar al siguiente alumno presione 2\n");
        printf("si quiere los datos del alumno presione 3\n");
        printf("para ver el record del alumno presione 4\n");

		printf("\t%s %s\n",ialumnop->alumno->nombre, ialumnop->alumno->apellidos);
        scanf("%i",&next);
		
		
        if (next == 3){
			mostrarDatosA(&ialumnop->alumno);
			}
        else if (next == 4)
			mostrarNotasA(&ialumnop->record);
		else if ((next == 2))
			ialumnop = ialumnop->proxAlum;
    }
}


//****************************MODIFICAR*****************************

void modificarDato(alumnos **alumno, char cedula[50] ){
	char dato[20];
	char nuevo[20];
	alumnos *alumnop = *alumno;
	while (alumnop){
		if (strstr(alumnop->cedula, cedula))
		{
			break;
		}
		alumnop = alumnop->proxalumno;
	}
	
	printf("\nQue dato quiere modificar: nombre, apellidos, correo, direccion, fecha\n");
	scanf("%s",dato);
	if (strcmp("nombre", dato) == 0){
		printf("escriba el nombre del estudiante\n");
		scanf("%s",nuevo);
		strcpy(alumnop->nombre,nuevo);
	}
	else if (strcmp("apellido", dato) == 0){
		printf("escriba los nuevos apellidos\n");
		scanf("%s",nuevo);
		strcpy(alumnop->apellidos,nuevo);
	}
	else if (strcmp("correo", dato) == 0){
		printf("escriba el correo\n");
		scanf("%s",nuevo);
		strcpy(alumnop->correo,nuevo);
	}
	else if (strcmp("direccion", dato) == 0){
		printf("escriba la direccion\n");
		scanf("%s",nuevo);
		strcpy(alumnop->direccion,nuevo);
	}
	else if (strcmp("fecha", dato) == 0){
		printf("escriba la fecha de nacimiento\n");
		scanf("%s",nuevo);
		strcpy(alumnop->fNacimiento,nuevo);
	};
	//TODO: Edge case
}

void modificarNota(indiceAlumnos **indiceAlumno, indiceCursos **indiceCurso, char cedula[50], alumnos **alumno){
	indiceAlumnos *indiceAlumnop = *indiceAlumno;
	indiceCursos *indiceCursop = *indiceCurso;
	alumnos *alumnop = *alumno;
	char dato[10];
	char notaM[4];
	int codigo = 0, ano = 0, flag = 0;
	//mostrar lista de todas las notas

	while (indiceAlumnop){
		if (strstr(indiceAlumnop->alumno->cedula, cedula))
		{
			break;
		}
		indiceAlumnop = indiceAlumnop->proxAlum;
	}

	printf("Esta es la lista de las notas actualmente\n");
	mostrarNotasA(&indiceAlumnop->record);
	printf("ingrese la materia a la cual quiere cambiarle la nota\n");
	scanf("%s",dato);
	indiceAlumnop = *indiceAlumno;
	recordAlumno *rca = indiceAlumnop->record;
	while(indiceAlumnop){
		rca = indiceAlumnop->record;
		while (rca)
		{
			if (strstr(rca->deCurso->deMateria->materia,dato)){
				flag = 1;
				break;
			}
			rca = rca->proxNota;
		}
		if (flag)
		{
			break;
		}
		indiceAlumnop = indiceAlumnop->proxAlum;
		if (!indiceAlumnop)
			printf("no se encontro\n");
	}

	if (flag)
	{

	codigo = rca->deCurso->codigoCurso;
	ano = rca->deCurso->ano;
	printf("ingrese la nueva nota\n");
	scanf("%s",notaM);
	strcpy(rca->nota,notaM);

	cursosY *rcy = indiceCursop->recordYC;
	recordCurso *rcc = rcy->record;
	while (indiceCursop){
		if (indiceCursop->ano == ano){
			rcy = indiceCursop->recordYC;
				while (rcy){
					if (rcy->deCurso){
						if (rcy->deCurso->codigoCurso == codigo){
							rcc = rcy->record;
							while(rcc){
								if (rcc->alumno->cedula == indiceAlumnop->alumno->cedula)
									strcpy(rcc->nota,notaM);
								rcc = rcc->prox;
							}
						}
					}
				rcy = rcy->proxCursoy;
			}
		
		}
		indiceCursop = indiceCursop->proxInCurso;
	}

	}
	

}

void modificarA(indiceAlumnos **ialumno, alumnos **alumno, recordAlumno **recordAlumno, materias **materia, indiceCursos **indiceCursos){
	char cedula[50];
	char *val;
	int vali = 0, x = 0;
	int op2 = -2;
	
	indiceAlumnos *ialumnop = *ialumno;
	alumnos *alumnop = *alumno;
	printf("Escriba unicamente el numero de la cedula del alumno\n");
	scanf("%s",cedula);
	while (alumnop){
		if (strcmp(alumnop->cedula, cedula) == 0){
			vali = 1;
			break;
		}
		val = strstr(alumnop->cedula,cedula);
		if (val)
			vali = 1;
		alumnop = alumnop->proxalumno;
	};
	
	//TODO: properly exit and menu
	
	 if (!vali){
		 printf("No se encontro la cedula indicada");

		}
	
	 while( op2 && vali){
		printf ("\n\n\t\tQue desea modifica\n");
        system("cls");
        printf("1.\tDato del alumno\n");
        printf("2.\tNota del alumno\n\n");
		printf("3.\tRegresa\n");
        scanf( "%i", &op2);

        switch(op2){
            case 1:
				modificarDato(&*alumno, cedula);
		        break;
            case 2:
				modificarNota(&ialumnop, &*indiceCursos, cedula, &*alumno);
                break;
			case 3:
				x = 1;

        };
    system("pause");
	if (x)
		break;
    };
	
}


//**********************************ELIMINAR*********************

int encontrarA(indiceAlumnos *indiceAlumnos, char cedula[10]){
	if (indiceAlumnos && indiceAlumnos->alumno->cedula == cedula)
			return 2;
	while (indiceAlumnos && indiceAlumnos->proxAlum){
		if (indiceAlumnos->proxAlum->alumno->cedula == cedula)
			return 1;
		indiceAlumnos = indiceAlumnos->proxAlum;
	}
	return 0;
}

void eliminarA(indiceAlumnos **indiceAlumno, indiceCursos **indiceCurso, alumnos ** alumno){
	char dato[20];
	int i = 0;
	int flag = 0;
	indiceAlumnos *indiceAlumnosp = *indiceAlumno;
	alumnos *alumnop = *alumno;
	printf("inserte el numero de la cedula del alumno que desea eliminar\n");
	scanf("%s", dato);
	while (alumnop){
		if (strstr(alumnop->cedula, dato)){
			i = 1;
			break;
		}
		alumnop = alumnop->proxalumno;
	}
	if (!i){
		printf("No se encontro la cedula indicada\n");

	}
	if (strstr(indiceAlumnosp->alumno->cedula, dato) && i){
		indiceAlumnos * aux = indiceAlumnosp;
		recordAlumno *rA = indiceAlumnosp->record;
		recordAlumno *xA = indiceAlumnosp->record;
		indiceAlumnosp = indiceAlumnosp->proxAlum;
		delete rA;
		delete aux;
	}
	else
	while (indiceAlumnosp && indiceAlumnosp->proxAlum && i ){
		if (strstr(indiceAlumnosp->proxAlum->alumno->cedula,dato)){
			indiceAlumnos *aux = indiceAlumnosp->proxAlum;
			recordAlumno *rA = indiceAlumnosp->proxAlum->record;
		
			indiceAlumnosp->proxAlum = indiceAlumnosp->proxAlum->proxAlum;
			delete rA;
			delete aux;
			break;
		}	
		indiceAlumnosp = indiceAlumnosp->proxAlum;
	}

	alumnop = *alumno;

	if (strstr(alumnop->cedula,dato) && i )
	{
		alumnos *aux = alumnop;
			alumnop = alumnop->proxalumno;
			delete aux;
			
	}

	else
	while (alumnop && alumnop->proxalumno)
	{
		if (strstr(alumnop->proxalumno->cedula,dato))
		{
			alumnos *aux = alumnop->proxalumno;
			alumnop->proxalumno = alumnop->proxalumno->proxalumno;
			delete aux;
		}
	}
	indiceCursos *indiceCursop = *indiceCurso;
	cursosY *rcY = indiceCursop->recordYC;
	recordCurso *rcC = indiceCursop->recordYC->record;
	if (i){
		while (indiceCursop){
			rcY = indiceCursop->recordYC;
			while (rcY){
				rcC = indiceCursop->recordYC->record;
				if (rcC){
					if (rcC->alumno == NULL){
						recordCurso *aux = rcC;
						rcC = rcC->prox;
						delete aux;
					}		
					while (rcC && rcC->prox){
						if (rcC->prox->alumno == NULL){
							recordCurso *aux =  rcC->prox;
							rcC->prox = rcC->prox->prox;
							delete(aux);
						}
					rcC = rcC->prox;
					}		
				}
				rcY = rcY->proxCursoy;
			}
			indiceCursop = indiceCursop->proxInCurso;
		}
	}
}


//********************************AGREGAR**********************++++*****

void swap(alumnos *A, alumnos *B){
	alumnos C=*A;
	*A=*B;
	*B=C;
}
void ordenar(alumnos *alumno){
//ordenar a los alumnos por intercambio
		alumnos *t,*ax;
		t=alumno;
		while ((t)&&(t->proxalumno)){
			ax=t;
			while(ax->proxalumno){
				if ((strcmp(ax->proxalumno->apellidos,t->apellidos))<0)
					swap(t,ax);
				else
					ax=ax->proxalumno;
			}
			t=t->proxalumno;
		}
}
int valFech(char cadena[50]){
		printf("entre en funcion \n");
		int end=strlen(cadena),cont=0;
		for (int i=0;i<end;i++){
			printf("entre en for\n");
			if (strcmp(&cadena[i]," ")==0)
				cont--;
			else if ((strcmp(&cadena[i],"0")>=0) || (strcmp(&cadena[i],"9")<=0))
				cont++;
			else if ((strcmp(&cadena[4],"-")==0) || (strcmp(&cadena[7],"-")==0) || (strcmp(&cadena[6],"-")==0)) 
				cont++;
		}
		if ((cont==10) || (cont==9) || (cont==8))
				return 1;
		else
			return 0;
	}
int verificar (char cadena[50]){
	int n=strlen(cadena);
	for (int i=0;i<=n;i++){
		if (strcmp(&cadena[i],"A") >= 0)
			return(0);
		else if (strcmp(&cadena[i]," ") == 0)
			return(0);
	}
	return(1);
}


void leerArchivoAlumno(alumnos **alumno, indiceAlumnos **indiceAlumno, recordAlumno **recordAlumnos, cursos **curso, indiceCursos **indiceCurso){

	//en esta funcion se tiene que crear un nodo en el indice, un nodo en la lista de alumnos y una nueva lista del alumno


	alumnos *aux = *alumno;
	char path[50], dato[50];
	int flag = 0;
	FILE *archive;
	printf("arrastre archivo que desea leer");
	scanf("%s",path);
	if ((archive = fopen(path, "r")) == NULL){
		printf("error opening the file");
		exit(1);
	}

	while (!feof(archive)){
		printf("leyendo alumno...");
		//creacion del nodo alumno
		alumnos *nuevoA = new alumnos;
		//va a leer linea por linea el nombre, cedula, telefono, correo, direccion fnacimiento

		//nombre
		fgets(dato, 50, archive);
		if (strcmp(dato, "") == 0)
			break;
		strcpy(nuevoA->nombre,dato);
		printf("nombre %s\n", nuevoA->nombre);

		//apellido
		fgets(dato, 50, archive);
		strcpy(nuevoA->apellidos,dato);
		printf("apellidos %s\n", nuevoA->apellidos);

		//verificar que el alumno no se encuentre registrado por la cedula
		fgets(dato, 50, archive);
		while (aux){
			
			if (strcmp(aux->cedula, dato) == 0){
				printf("Este alumno ya se encuentra en la base de datos");
				//TODO: llevar a menu
				exit(1);
				
			}
			aux = aux->proxalumno;
		}
		//el alumno es nuevo
		//cedula
		strcpy(nuevoA->cedula,dato);
		printf("cedula %s\n", nuevoA->cedula);

		//telefono
		fgets(dato, 50, archive);
		strcpy(nuevoA->telefono,dato);
		printf("telefono %s\n", nuevoA->telefono);
		//correo
		fgets(dato, 50, archive);
		strcpy(nuevoA->correo,dato);
		printf("correo %s\n", nuevoA->correo);
		//direccion
		fgets(dato, 50, archive);
		strcpy(nuevoA->direccion,dato);
		printf("direccion %s\n", nuevoA->direccion);
		//fnacimiento
		fgets(dato, 50, archive);
		strcpy(nuevoA->fNacimiento,dato);
		printf("nacimiento %s\n", nuevoA->fNacimiento);

		nuevoA->proxalumno = *alumno;
		*alumno = nuevoA;

		indiceAlumnos *nuevoI = new indiceAlumnos;
		nuevoI->alumno = nuevoA;
		nuevoI->record = NULL;
		nuevoI->proxAlum = *indiceAlumno;
		*indiceAlumno = nuevoI;

		//creacion de la lista de notas perteneciente al alumno
		//lee en el siguiente orden, codigo de curso, nota, estatus

		int ano = 0;
		fgets(dato, 50, archive);




		while (!feof(archive)  && strstr(dato, "::")){
			int verificador = 0;
			recordAlumno *nuevoR = new recordAlumno;
			strcpy(nuevoR->nota,"");
			strcpy(nuevoR->estatus,"");
			flag = 0;
			//codigo de curso
			fgets(dato, 50, archive);
			cursos *auxC = *curso;
			if (auxC)
				printf("si");
			while (auxC){
				printf("codigo: %i\n", auxC->codigoCurso);
				if (auxC->codigoCurso == atoi(dato)){	
						printf("Curso se encuentra registrado");
						ano = auxC->ano;
						nuevoR->deCurso = auxC;	
						flag = 1;
						break;
						//uso de brak para tener posicion a donde se va a enlazar el puntero proximamente, se debe refactorizar
				}
				auxC = auxC->proxCurso;
				if (!auxC){
					printf("el curso no se encuentra registrado");
				}
					
			}
			if (!flag)
				break;
			//nota
			fgets(dato, 50, archive);
			strcpy(nuevoR->nota,dato);
			printf("nota: %s\n", nuevoR->nota);
			if (!nuevoR->nota)
				break;
			//estatus
			fgets(dato, 50, archive);
			strcpy(nuevoR->estatus,dato);
			printf("estatus: %s\n", nuevoR->estatus);

			recordAlumno *recordA = (*indiceAlumno)->record;
			*recordAlumnos = (*indiceAlumno)->record;
			

			nuevoR->proxNota = (*recordAlumnos);
			*recordAlumnos = nuevoR;

			//se tiene que anadir el estatus y nota al record de curso

			indiceCursos *indiceCursop = *indiceCurso;

			recordCurso *nuevoRC = new recordCurso;
							strcpy(nuevoRC->nota,nuevoR->nota);
							strcpy(nuevoRC->estatus,nuevoR->estatus);
							nuevoRC->alumno = nuevoA;
							
			
			while(indiceCursop){
				printf("%i", ano);
				if (indiceCursop->ano == ano){
					while (indiceCursop->recordYC){
						printf("paso 1");
						if (indiceCursop->recordYC->deCurso->codigoCurso == nuevoR->deCurso->codigoCurso){
							printf("paso 2");
							nuevoRC->prox = indiceCursop->recordYC->record;
							indiceCursop->recordYC->record = nuevoRC;
							break;
						}
						indiceCursop->recordYC = indiceCursop->recordYC->proxCursoy;
					   }
					break;
					}
				indiceCursop = indiceCursop->proxInCurso;
			}

			
			printf("aqui");

		
		(*indiceAlumno)->record = nuevoR;
		
		fgets(dato, 50, archive);
		}
		//creacion del nodo en el indice
		
		
	}
    fclose(archive);
	
	
}

void agregarNew(alumnos **nuevoA){
	int numero;
	alumnos *aux=*nuevoA;
	printf("\tIntroduzca los nombres: \n ");
	scanf("%i",&numero);
	getchar();
	gets((*nuevoA)->nombre);
	printf("\tIntroduzca los apellidos: \n ");
	gets((*nuevoA)->apellidos);
	printf("\tIntroduzca la cedula: \n ");
	gets((*nuevoA)->cedula);
	if (!(verificar((*nuevoA)->cedula))){
		printf("UPS!...Debio escribir una letra o algun espacio en blanco");
		int attemp=1;
		while (attemp){
			printf("\tIntroduzca la cedula: (solo numeros)\n ");
			gets((*nuevoA)->cedula);
			if (verificar((*nuevoA)->cedula))
				attemp=0;
		}
	}
	if(aux->proxalumno!=NULL)
	while (aux){
			if (strcmp(aux->cedula,(*nuevoA)->cedula) == 0){
				printf("Este alumno ya se encuentra en la base de datos");
				//TODO: llevar a menu
				exit(1);
			system("pause");
				
			}
			aux = aux->proxalumno;
		}
	printf("\tIntroduzca el numero telefonico: \n ");
	gets((*nuevoA)->telefono);
	printf("\tIntroduzca el correo: \n ");
	gets((*nuevoA)->correo);
	printf("\tIntroduzca la direccion: \n ");
	gets((*nuevoA)->direccion);
	printf("\tIntroduzca la fecha de nacimiento: (AAAA-MM-DD)\n ");
	gets((*nuevoA)->fNacimiento);
	if (!valFech((*nuevoA)->fNacimiento)){
		printf("UPS!...Hay un error en la fecha, siga el formato");
		int attemp=1;
		while (attemp){
			printf("\tIntroduzca la fecha de nacimiento: (AAAA-MM-DD)\n ");
			gets((*nuevoA)->fNacimiento);
			if (verificar((*nuevoA)->fNacimiento))
				attemp=0;
		}
	}
}
void agregarNewEsNo(recordAlumno **nuevoR){
	int numero,n;
	printf("\tIntroduzca el estatus: (Normal o Retirado) \n ");
		scanf("%i",&numero);
		getchar();
		gets((*nuevoR)->estatus);
		if (strcmp((*nuevoR)->estatus,"Normal") == 0){
			printf("\tIntroduzca la nota del curso: (en numero 0-20)\n ");
			scanf("%s",&(*nuevoR)->nota);
			n=atoi((*nuevoR)->nota);
			if (n<10)
				printf("Alumno Reprobado");
			else if (n>=10)
				printf("Alumno Aprobado!");
			else  {
				printf("NOTA NO PERMITIDA");
				agregarNewEsNo(nuevoR);
			}
				
		}
		else if (strcmp((*nuevoR)->estatus,"Retirado") == 0){
			printf("Alumno retirado!!");
			strcpy((*nuevoR)->nota,"RE");
		}
		else {
			printf("Estatus no valido, intente de nuevo");
			agregarNewEsNo(nuevoR);
		}
}		
void agregarNewCurso(recordAlumno **recordAlumnos, cursos **curso,indiceCursos **indiceCurso){
	//creacion del record del alumno 
	//suponiendo que al momento de inscribir un alumno se debe inscribir minimo una materia
	int op=1,numero,code=0,verificador=0,ano=0;
	while (op){
		printf("\tIntroduzca el codigo del curso: \n ");
		scanf("%i",&code);
		cursos *auxC = *curso;
		while (auxC && (verificador != 0)){
				if (auxC->codigoCurso == code){
						printf("Curso se encuentro registrado");
						ano = auxC->ano;
						verificador = 1;
						break;
						//uso de brak para tener posicion a donde se va a enlazar el puntero proximamente, se debe refactorizar
					}
				auxC = auxC->proxCurso;
			}

			if (verificador == 0){
					printf("el curso no se encuentra registrado");
					//exit(1);
			}
		recordAlumno *nuevoR = new recordAlumno;
		printf("\tIntroduzca la nota del curso: \n ");
		scanf("%i",&(nuevoR)->nota);
		printf("\tIntroduzca el estatus: \n ");
		scanf("%i",&numero);
		getchar();
		gets(nuevoR->estatus);
		nuevoR->deCurso = auxC;
		nuevoR->proxNota = *recordAlumnos;
		*recordAlumnos = nuevoR;
		
		//se tiene que anadir el estatus y nota al record de curso
		
		indiceCursos *indiceCursop = *indiceCurso;
		while(indiceCursop){
			if (indiceCursop->ano == ano){
				while (indiceCursop->recordYC){
					if (indiceCursop->recordYC->deCurso == nuevoR->deCurso){
						recordCurso *nuevoRC = new recordCurso;
						strcpy(nuevoRC->nota,nuevoR->nota);
						strcpy(nuevoRC->estatus,nuevoR->estatus);
						break;
					}
					indiceCursop->recordYC = indiceCursop->recordYC->proxCursoy;
				}
				break;
			}
			indiceCursop = indiceCursop->proxInCurso;
		}

		system("cls");
		printf("\tDesea agregar otro curso?(si/no): \n ");
		char resp[2];
		scanf("%s", resp);
		if (resp[2]=='no')
			op--;
	}	
}
void leerDatosAlumno(alumnos **alumno, indiceAlumnos **indiceAlumno, recordAlumno **recordAlumnos, cursos **curso,indiceCursos **indiceCurso){
	//ESTA FUNCIîN PERMITE AGREGAR A LOS ALUMNOS MANUALMENTE EN EL SISTEMA 
	char resp[3],val[3];
	int op=1;

	while (op){
		//Creacion del nodo alumno
		alumnos *nuevoA= new alumnos;
		//funcion que agrega a los alumnos manuelamente
		agregarNew(&nuevoA);
		nuevoA->proxalumno=*alumno;
		*alumno=nuevoA;
		ordenar(*alumno);
		
		printf("Desea añadir el alumno a un curso existente? (si/no)");
		scanf("%s", val);
		if (!(strcmp(val,"si"))){
			//Crea el curso y el record del alumno
			agregarNewCurso(recordAlumnos,curso,indiceCurso);
		}

		//creacion del indice
		indiceAlumnos *nuevoI = new indiceAlumnos;
		nuevoI->alumno = *alumno;
		nuevoI->record = NULL;
		nuevoI->proxAlum = *indiceAlumno;
		*indiceAlumno = nuevoI;

		printf("Desea agregar otro alumno?(si|no)");
		scanf("%s",resp);
		if (strcmp(resp,"no") == 0)
			op--;
	}
	//esto es para probar si crea el archivo con los datos nuevos 
	
	//FILE* fichero;
	//fichero = fopen("prueba.txt", "wt");
	//fputs((*alumno)->nombre, fichero);
	//fclose(fichero);
}