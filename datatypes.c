#include <stdlib.h>
#include <string.h>
#include "datatypes.h"

INT int_create(int i)
{
	INT new = malloc(sizeof(int));
	*new = i;
	return new;
}
FLOAT float_create(float f)
{
	FLOAT new = malloc(sizeof(float));
	*new = f;
	return new;
}

STRING str_create(char * s)
{
	STRING new = calloc(strlen(s),sizeof(char));
	strcpy(new,s);
	return(new);
}
CHAR char_create(char c)
{
	CHAR new = malloc(sizeof(char));
	*new = c;
	return new;
}
void data_destroy(TYPE data)
{
	free(data);
}

