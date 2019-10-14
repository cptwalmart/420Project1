#ifndef WORK_H
#def WORK_H

#include <cstdio>
#include <cstdlib>

#define BUFFERSIZE 11
#define BUFFERSIZEFACTORIAL 39916800

typedef struct permuter
{
	char string[BUFFERSIZE];
	int string_length;
	unsigned int all_permutations[BUFFERSIZEFACTORIAL];
	int answers_found = 0;
	
	int storelocation = 0;
	void generatePermuntations(int first)
	{
		if(first == (string_length - 1))
		{
			all_permutations[storelocation] = atoi(string);
			storelocation++;
		}
		else
		{
			int i;
			for(i = first; i < string_length; i++)
			{
				int flag = 1;
				int j;
				for(j = first; j < i; j++)
				{
					if(string[j] == string[i])
					{
						flag = 0;
						break;
					}
				}
				if(flag != 0)
				{
					char temp = string[first];
					string[first] = string[i];
					string[i] = temp;
					generatePermuntations(first + 1);
					temp = string[first];
					string[first] = string[i];
					string[i] = temp;
				}
			}
		}
	}
	
	int checkAllPermutations(unsigned int * answers, int answers_size, unsigned int key)
	{
		int i, j;
		string_length = sprintf(string, "%d", key);
		generatePermuntations(0);
		for(i = 0; i < storelocation; i++)
		{
			for(j = 0; j < answers_size; j++)
			{
				if(all_permutations[i] == answers[j])
				{
					answers_found++;
				}
			}
		}
		storelocation = 0;
		int retval = answers_found;
		answers_found = 0;
		return retval;
	}
};

#endif