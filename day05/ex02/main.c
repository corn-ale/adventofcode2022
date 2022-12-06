
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include "get_next_line.h"



/* ************************************************ */
/* libft                                            */
/*   |                                              */
/*   |                                              */
/*   v                                              */
/*                                                  */
/* ************************************************ */

// size_t	ft_strlen(const char *s)
// {
// 	size_t	index;

// 	index = 0;
// 	while (s[index] != '\0')
// 	{
// 		index++;
// 	}
// 	return (index);
// }

char	*ft_strchr(const char *s, int c)
{
	int		index;
	char	d;

	index = 0;
	d = c;
	while (s[index] != '\0' && s[index] != d)
	{
		index++;
	}
	if (s[index] == (char)c)
		return (&((char *)s)[index]);
	else
		return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;
	char	d;

	d = c;
	index = ft_strlen(s);
	while (s[index] != d && index > 0)
		index--;
	if (s[index] == d)
		return (&((char *)s)[index]);
	else
		return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*newstr;
	unsigned int	i;
	size_t			j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	while (i < start)
		i++;
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	newstr = malloc(len + 1);
	if (newstr == NULL)
		return (NULL);
	while (j < len && start < ft_strlen(s))
	{
		newstr[j] = s[i];
		i++;
		j++;
	}
	newstr[j] = '\0';
	return (newstr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	int		i;
	int		j;

	i = 0;
	if (s1 == 0 || set == 0)
		return (0);
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) && s1[i] != 0)
		i++;
	while (ft_strrchr(set, s1[j - 1]) && s1[i] != 0)
		j--;
	newstr = ft_substr(s1, i, j - i);
	if (newstr == 0)
		return (0);
	return (newstr);
}



/* ************************************************ */
/*  main                                            */
/*   |                                       ^      */
/*   |                                       |      */
/*   v                                       |      */
/*                                         libft    */
/* ************************************************ */



int	fakemain()
{
	char	*line;
	char	*trimmed;
	char	**setup;
	char	**arrayOfStacks;
	int		i;
	int		size;
	int		fd;
	int		fd2;
	int		numOfStacks;
	int		numOfCrates;


	// malloc for **setup here
	// later on the input file will be read into **setup until
	// the first empty line is found
	i = 0;
	fd = open("../input.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("error with file\n");
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		printf("error: file is empty\n");
		return (EXIT_FAILURE);
	}
	size = 0;
	while (line[0] != '\n')
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
		size++;
	}
	printf("\n");
	free(line);
	close(fd);
	line = NULL;
	setup = malloc(sizeof(char *) * (size + 1));
	if (!setup)
	{
		printf("error with malloc\n");
		return (EXIT_FAILURE);
	}
	setup[size] = NULL;


	// read into **setup here
	// had to use gnl with BUFFER_SIZE set to 1
	fd2 = open("../input.txt", O_RDONLY);
	if (fd2 < 0)
	{
		printf("error with file\n");
		free(setup);
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd2);
	if (!line)
	{
		printf("error: file is empty\n");
		free(setup);
		return (EXIT_FAILURE);
	}
	while (i < size)
	{
		setup[i] = line;
		line = get_next_line(fd2);
		i++;
	}
	free(line);
	close(fd2);


	// count number of stacks
	// later this number will be used to malloc a 
	// 2d array which will represent the stacks
	numOfStacks = 0;
	int l;
	int m = 0;
	for (l = 0; setup[l + 1] != NULL; l++)
		;
	while (setup[l][m] != '\0')
	{
		while (!isdigit(setup[l][m]) && setup[l][m] != '\0')
			m++;
		if (isdigit(setup[l][m]))
		{
			numOfStacks++;
			while (isdigit(setup[l][m]))
				m++;
		}
	}
	printf("num of stacks: %d\n", numOfStacks);
	

	// count number of crates
	// the approach is to count the total num of crates in
	// the input file, because this is the max number of
	// crates that a single stack can have (in case all of the
	// crates have been stacked into one single stack)
	// this way i wont have to reallocate the stacks every time
	// a crate is moved, just need to rewrite them with '\0'
	numOfCrates = 0;
	int n = 0;
	int o = 0;
	while (setup[n])
	{
		o = 0;
		while (setup[n][o])
		{
			if (isalpha(setup[n][o]))
				numOfCrates++;
			o++;
		}
		n++;
	}
	printf("num of crates: %d\n\n", numOfCrates);


	// init **arrayOfStacks and load the crates into them
	//
	// 1: malloc for **arrayOfStacks and
	// 2: free already allocated stuff if malloc fails midway through
	// 3: find last array before the NULL array in **setup and
	// 4: iterate through it to find the positions of the numbers
	//    which represent the crates
	// 5: using the position of the numbers/crates, iterate throught
	//    **setup UPWARDS, and load the crates into the correct place
	//    in **arrayOfStacks
	//
	// part 1,
	arrayOfStacks = malloc(sizeof(char *) * (numOfStacks + 1));
	if (!arrayOfStacks)
	{
		printf("error with malloc\n");
		for (int k = 0; setup[k]; k++)
			free(setup[k]);
		free(setup);
		return (EXIT_FAILURE);
	}
	arrayOfStacks[numOfStacks] = NULL;
	for (int p = 0; p < numOfStacks; p++)
	{
		arrayOfStacks[p] = calloc(1, sizeof(char) * (numOfCrates + 1));
		if (arrayOfStacks[p] == NULL)
		{									// part 2,
			for (int z = 0; z <= p; z++)
				free(arrayOfStacks[z]);
			free(arrayOfStacks);
			for (int k = 0; setup[k]; k++)
				free(setup[k]);
			free(setup);
			printf("error with malloc\n");
			return (EXIT_FAILURE);
		}
	}
	// part 3,
	l = 0;
	m = 0;
	int q = -1;
	int	r = 0;
	for (l = 0; setup[l + 1] != NULL; l++)
		;
	while (setup[l][m] != '\0')
	{
		while (!isdigit(setup[l][m]) && setup[l][m] != '\0')
			m++;
		if (isdigit(setup[l][m]))
		{							// part 4, found the crate
			q++;
			r = 0;
			for (int tmp = l - 1; tmp >= 0 && isalpha(setup[tmp][m]); tmp--)
			// for (int tmp = l - 1; tmp >= 0; tmp--)
			{						// part 5, loading crates into stacks
				arrayOfStacks[q][r] = setup[tmp][m];
				r++;
			}
			while (isdigit(setup[l][m]))
				m++;
		}
	}
	// printing the starting state of stacks
	printf("initial state of stacks:\n");
	for (int tmp = 0; arrayOfStacks[tmp]; tmp++)
		printf("stack %d: %s\n", tmp+1, arrayOfStacks[tmp]);
	printf("\n");


	// read from input and execute the instructions
	//
	// 1: skip until there is an empty line in file
	// 2: after new line read the instructions
	// 3: get numbers from line
	// 4: execute instructions
	int fd3 = open("../input.txt", O_RDONLY);
	if (fd3 < 0)
	{
		printf("error with file\n");
		for (int k = 0; setup[k]; k++)
			free(setup[k]);
		free(setup);
		for (int k = 0; arrayOfStacks[k]; k++)
			free(arrayOfStacks[k]);
		free(arrayOfStacks);
		return (EXIT_FAILURE);
	}
	// part 1, skipping lines
	char *instr = get_next_line(fd3);
	if (!instr)
	{
		printf("error: empty file\n");
		for (int k = 0; setup[k]; k++)
			free(setup[k]);
		free(setup);
		for (int k = 0; arrayOfStacks[k]; k++)
			free(arrayOfStacks[k]);
		free(arrayOfStacks);
		return (EXIT_FAILURE);
	}
	while (instr[0] != '\n')
	{
		free(instr);
		instr = get_next_line(fd3);
	}
	free(instr);
	// creating getNums used for part 3
	instr = get_next_line(fd3);
	int	tmp = 0;
	int	nCount = 0;
	int	digits = 0;
	char **getNums = malloc(sizeof(char *) * 4);
	int	nums[3];
	if (!getNums)
	{
		printf("error with malloc\n");
		for (int k = 0; setup[k]; k++)
			free(setup[k]);
		free(setup);
		for (int k = 0; arrayOfStacks[k]; k++)
			free(arrayOfStacks[k]);
		free(arrayOfStacks);
		return (EXIT_FAILURE);
	}
	getNums[3] = NULL;
	for (int qq = 0; qq < 3; qq++)
	{
		getNums[qq] = calloc(1, sizeof(char) * 3);
		if (getNums[qq] == NULL)
		{
			printf("error with calloc\n");
			for (int k = 0; getNums[k]; k++)
				free(getNums[k]);
			free(getNums);
			for (int k = 0; setup[k]; k++)
				free(setup[k]);
			free(setup);
			for (int k = 0; arrayOfStacks[k]; k++)
				free(arrayOfStacks[k]);
			free(arrayOfStacks);
			return (EXIT_FAILURE);
		}
	}
	// part 2, read the instructions
	char	*Crates;
	int		ww = 0;
	int		yy = 0;

	Crates = calloc(1, sizeof(char) * (numOfCrates + 1));
	if (!Crates)
	{
		printf("error with calloc\n");
		for (int k = 0; setup[k]; k++)
			free(setup[k]);
		free(setup);
		for (int k = 0; arrayOfStacks[k]; k++)
			free(arrayOfStacks[k]);
		free(arrayOfStacks);
		for (int k = 0; getNums[k]; k++)
			free(getNums[k]);
		free(getNums);
		return (EXIT_FAILURE);
	}

	// for (int tmp = 0; arrayOfStacks[tmp]; tmp++)
	// 	printf("stack %d: |%s|\n", tmp+1, arrayOfStacks[tmp]);
	// printf("\n");
	// for (int i = 0; i < 10; i++)
	while (instr)
	{
		// printf("%s", instr);
		// valid instructions here
		nCount = 0;
		tmp = 0;
		while (instr[tmp])
		{
			if (isdigit(instr[tmp]))
			{							// part 3, get the nums
				digits = 0;
				while (isdigit(instr[tmp]))
				{
					getNums[nCount][digits] = instr[tmp];
					tmp++;
					digits++;
					nums[nCount] = atoi(getNums[nCount]);
				}
				nCount++;
			}
			tmp++;
		}
		// numbers are converted to ints and loaded into nums here
		// printf("%s %s %s\n", getNums[0], getNums[1], getNums[2]);
		// printf("%d %d %d\n", nums[0], nums[1], nums[2]);
		for (int l = 0; l < 3; l++)
			for (int k = 0; k < 2; k++)
				getNums[l][k] = '\0';
		

		// part 4, execute instructions
		for (ww = 0; arrayOfStacks[nums[1] - 1][ww + nums[0]] != '\0'; ww++)
			;
		strlcpy(Crates, &arrayOfStacks[nums[1] - 1][ww], nums[0] + 1);
		for (int t = 0; t < nums[0]; t++)
		{
			arrayOfStacks[nums[1] - 1][ww] = '\0';
			ww++;
		}
		// printf("moving crates: %s\n", Crates);
		for (yy = 0; arrayOfStacks[nums[2] - 1][yy] != '\0'; yy++)
			;
		for (int xx = 0; xx < nums[0]; xx++)
		{
			arrayOfStacks[nums[2] - 1][yy] = Crates[xx];
			yy++;
		}


		// for (int tmp = 0; arrayOfStacks[tmp]; tmp++)
		// 	printf("stack %d: %s\n", tmp+1, arrayOfStacks[tmp]);
		// printf("\n");


		free(instr);
		instr = get_next_line(fd3);
	}

	// printing the final state of stacks
	printf("final state of stacks:\n");
	for (int tmp = 0; arrayOfStacks[tmp]; tmp++)
		printf("stack %d: %s\n", tmp+1, arrayOfStacks[tmp]);
	printf("\n");

	
	int le = 0;
	printf("top crates at the end: ");
	for (int tmp = 0; arrayOfStacks[tmp]; tmp++)
	{
		le = strlen(arrayOfStacks[tmp]);
		printf("%c", arrayOfStacks[tmp][le - 1]);
	}
	printf("\n\n");
	
	close(fd3);


	// print 2d array, then free 2d array
	// for (int j = 0; j < i; j++)
	// 	printf("%s", setup[j]);
	for (int k = 0; setup[k]; k++)
		free(setup[k]);
	free(setup);
	for (int k = 0; arrayOfStacks[k]; k++)
		free(arrayOfStacks[k]);
	free(arrayOfStacks);
	for (int k = 0; getNums[k]; k++)
		free(getNums[k]);
	free(getNums);
	free(Crates);


	// trimmed = ft_strtrim(line, "\n");
	// free(line);
	// free(trimmed);
	return (EXIT_SUCCESS);
}

int main()
{
	fakemain();
	// system("leaks a.out");
	return (EXIT_SUCCESS);
}
