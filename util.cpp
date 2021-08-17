#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nextWord(char* word)
{
	char c;
	int i, r_value;

	//printf("BGN nextWord\n");

	r_value = 0;
	c = getchar();
	while (c == ' ' || c == '\t' || c == '\n')
	{
		c = getchar();
	}

	i = 0;

	while (c!= EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n')
		{
			break;
		}
		r_value = 1;
		word[i] = c;
		i++;
		c = getchar();
	}
	word[i] = '\0';

	return r_value;



}
