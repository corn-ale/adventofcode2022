
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include "get_next_line.h"

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

/* libft                                            */
/* ************************************************ */

int	main()
{
	char	*line;
	char	*trimmed;
	char	**setup;
	int		i;
	int		size;
	int		fd;
	int		fd2;
	int		numOfStacks;
	int		numOfCrates;


	// malloc 2d array
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


	// read into 2d array
	fd2 = open("../input.txt", O_RDONLY);
	if (fd2 < 0)
	{
		printf("error with file\n");
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd2);
	if (!line)
	{
		printf("error: file is empty\n");
		return (EXIT_FAILURE);
	}
	while (i < size)
	{
		setup[i] = line;
		line = get_next_line(fd2);
		i++;
	}
	close(fd2);


	// count number of stacks
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
	printf("num of crates: %d\n", numOfCrates);


	// init array of stacks


	
	// print 2d array, then free 2d array
	for (int j = 0; j < i; j++)
		printf("%s", setup[j]);
	for (int k = 0; setup[k]; k++)
		free(setup[k]);
	free(setup);


	// trimmed = ft_strtrim(line, "\n");
	// free(line);
	// free(trimmed);
	return (EXIT_SUCCESS);
}
