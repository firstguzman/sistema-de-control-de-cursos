#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#include "auxFuncs.h"
#include "inscripFuncs.h"

void output(indiceAlumnos *indiceA, materias *materia, cursos *curso) {

	materias *materiasp = materia;
	cursos *cursop = curso;
	indiceAlumnos *indiceAp = indiceA;
	recordAlumno *recordA = (indiceA)->record;

	FILE* outputF = fopen("C:\\output.txt", "w");
	//MATERIAS
	fprintf(outputF,"\t\tMATERIAS\n");
	while (materiasp)
	{
		fprintf(outputF,"%s\n",materiasp->materia);
		fprintf(outputF,"%s\n",materiasp->area);
		fprintf(outputF,"%i\n",materiasp->codigoMat);
		fprintf(outputF,"%i\n",materiasp->creditos);
		fprintf(outputF,"%i\n",materiasp->semestre);
		fprintf(outputF,"//\n");
		materiasp = materiasp->proxMateria;
	}

	//CURSOS
	while (cursop)
	{
		fprintf(outputF,"\t\CURSOS\n");
		fprintf(outputF,"%s\n",cursop->codigoCurso);
		fprintf(outputF,"%i\n",cursop->ano);
		fprintf(outputF,"%i\n",cursop->lapso);
		fprintf(outputF,"%s\n",cursop->horario);
		fprintf(outputF,"//\n");
		cursop = cursop->proxCurso;
	}

	//ALUMNOS

	while (indiceAp)
	{
		fprintf(outputF,"\t\ALUMNOS\n");
		fprintf(outputF,"%s\n",indiceAp->alumno->nombre);
		fprintf(outputF,"%s\n",indiceAp->alumno->apellidos);
		fprintf(outputF,"%s\n",indiceAp->alumno->cedula);
		fprintf(outputF,"%s\n",indiceAp->alumno->telefono);
		fprintf(outputF,"%s\n",indiceAp->alumno->correo);
		fprintf(outputF,"%s\n",indiceAp->alumno->direccion);
		fprintf(outputF,"%s\n",indiceAp->alumno->fNacimiento);
		fprintf(outputF,"Notas y cursos cursados:\n");
		recordA = indiceAp->record;
		while (recordA)
		{
			fprintf(outputF,"%s\n",indiceAp->record->nota);
			fprintf(outputF,"%s\n",indiceAp->record->estatus);
			fprintf(outputF,"%i\n",indiceAp->record->deCurso->codigoCurso);
			fprintf(outputF,"%s\n",indiceAp->record->deCurso->deMateria->materia);
			fprintf(outputF,"::\n");
			recordA = recordA->proxNota;
		}
		fprintf(outputF,"//\n");
		indiceAp = indiceAp->proxAlum;
	}

	fclose(outputF);




}
