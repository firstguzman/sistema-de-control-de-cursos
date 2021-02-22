#include <iostream>
#include <stdio.h>
#include <stdlib.h>


struct alumnos{
    char nombre[50];
	char apellidos[50];
    char direccion[50];
    char correo[50];
    char cedula[50];
	char telefono[50];
    char fNacimiento[50];
    alumnos *proxalumno;
    alumnos *antalumno;

};

struct materias{
	materias *proxMateria;

	char materia[50];
	char area[50];
	unsigned int codigoMat;
	int creditos;
	int semestre;
	};

struct cursos{
	char horario[50];
	unsigned int codigoCurso;
	int ano;
	int lapso;
	materias *deMateria;
	cursos *proxCurso;
	};

struct recordAlumno{
    char nota[2];
    char estatus [20];
	cursos *deCurso;
	recordAlumno *proxNota;
};

struct indiceAlumnos{
    alumnos *alumno;
    recordAlumno *record;
    indiceAlumnos *proxAlum;
};

struct recordCurso{
	char nota[20];
	char estatus [20];
	alumnos *alumno;
	recordCurso *prox;
};

struct cursosY{
	recordCurso * record;
	cursos *deCurso;
	cursosY *proxCursoy;
};

struct indiceCursos{
	int ano;
	cursosY *recordYC;
	indiceCursos *proxInCurso;

};

