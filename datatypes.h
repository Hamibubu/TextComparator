#ifndef DATATYPES_H_
#define DATATYPES_H_

typedef void * TYPE;
typedef int * INT;
typedef float * FLOAT;
typedef char * STRING;
typedef char * CHAR;
typedef int BOOL;

#define FALSE 0
#define TRUE 1

typedef int (*COMPAREFUNC)(TYPE,TYPE);
typedef void (*PRINTFUNC)(TYPE);
typedef unsigned long long (*HASHFUNC)(TYPE);

INT int_create(int i);
FLOAT float_create(float f);
STRING str_create(char * s);
CHAR char_create(char c);

void data_destroy(TYPE data);

#define int_val(n) 	(*((int *) n))
#define float_val(n) 	(*((float *) n))
#define str_val(n)	((char *) n)
#define char_val(n) (*((char *) n))

#endif /* DATATYPES_H_ */
