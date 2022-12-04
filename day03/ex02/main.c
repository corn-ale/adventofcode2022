
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include "get_next_line.h"

// Takes 3 char arrays and finds the char that is represent in
// all 3 of them. The shared char then updated into <result>.
// Returns EXIT_SUCCESS (0) on succes, returns EXIT_FAILURE (1) otherwise.
int	find_matching_item(char *one, char *two, char *three, char *result)
{
	int		first;
	int		second;
	int		third;
	int		tIndex;
	int		tempLen;
	char	*temp;

	first = 0;
	second = 0;
	tIndex = 0;
	tempLen = strlen(one);
	temp = calloc(1, sizeof(char) * (tempLen + 1));
	if (!temp)
		return (EXIT_FAILURE);

	while (two[second] != '\0')
	{
		third = 0;
		while (three[third] != '\0')
		{
			if (two[second] == three[third])
			{
				temp[tIndex] = two[second];
				tIndex++;
				break;
			}
			third++;
		}
		second++;
	}
	while (one[first] != '\0')
	{
		tIndex = 0;
		while (temp[tIndex] != '\0')
		{
			if (one[first] == temp[tIndex])
			{
				*result = one[first];
				free(temp);
				return (EXIT_SUCCESS);
			}
			tIndex++;
		}
		first++;
	}
	free(temp);
	return (EXIT_FAILURE);
}

// Takes the given section of the line between <start> and <end - 1>
// (line = 1 line in input file, which represents 1 backpack)
// (section of line = each backpack has two compartments that are equal in size)
// and searches for unique items inside it.
// If it found a unique items, it will put it inside the provided pocket.
// The function should be called so that the <start> and <end> positions
// correctly matches the 1st and 2nd compartments of a backpack.
// <pocket> should the the address of the pointer.
void	find_unique_items(char *line, char **pocket, int start, int end)
{
	int		iPocket;
	int		search;
	bool	duplicate_item;

	iPocket = 1;
	(*pocket)[0] = line[start];	// starting item always goes into the pocket
	while (start < end) 		// go throught given half of line/backpack
	{
		search = 0;
		duplicate_item = false;
		while ((*pocket)[search] != '\0')
		{						// compare every item in line against every item in pocket
			if (line[start] == (*pocket)[search])
				duplicate_item = true;
			search++;
		}
		if (duplicate_item == false)
		{						// new unique item found in line, put it into the pocket
			(*pocket)[iPocket] = line[start]; 
			iPocket++;
		}
		start++;
	}
}

int	update_result(char *one, char *two, char *three, int *result)
{
	int		len1;
	int		len2;
	int		len3;
	char	matching_item;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	matching_item = '#';
	char temp = 'a';
	len1 = strlen(one);
	len2 = strlen(two);
	len3 = strlen(three);
	tmp1 = calloc(1, sizeof(char) * (len1 + 1));
	tmp2 = calloc(1, sizeof(char) * (len2 + 1));
	tmp3 = calloc(1, sizeof(char) * (len3 + 1));
	if (!tmp1 || !tmp2 || !tmp3)
		return (EXIT_FAILURE);

	find_unique_items(one, &tmp1, 0, len1 - 1);
	find_unique_items(two, &tmp2, 0, len2 - 1);
	find_unique_items(three, &tmp3, 0, len3 - 1);
	// the - 1 at the end is because I want to ignore the \n from gnl

	// printf("%s\n%s\n%s\n\n", tmp1, tmp2, tmp3);	// print unique items in groups

	if (find_matching_item(tmp1, tmp2, tmp3, &matching_item) == EXIT_FAILURE)
	{
		free(tmp1);
		free(tmp2);
		free(tmp3);
		return (EXIT_FAILURE);
	}
	if (matching_item >= 'a' && matching_item <= 'z')
		*result += matching_item - 'a' + 1;
	else if (matching_item >= 'A' && matching_item <= 'Z')
		*result += matching_item - 'A' + 27;

	// printf("%c\n", matching_item);			//print matching item in groups

	free(tmp1);
	free(tmp2);
	free(tmp3);
	return (EXIT_SUCCESS);
}

int	main()
{
	int		fd;
	int		i;
	int		error;
	int		result;
	char	*line;
	char	*one;
	char	*two;
	char	*three;

	i = 1;
	result = 0;
	error = EXIT_SUCCESS;
	fd = open("../input.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("error with file\n");
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		printf("error: empty file\n");
		close(fd);
		return (EXIT_FAILURE);
	}

	while (line)
	{
		// printf("%d %s", i, line);

		if ((i + 2) % 3 == 0)
			one = line;
		else if ((i + 1) % 3 == 0)
			two = line;
		else if (i % 3 == 0)
		{
			three = line;

			error = update_result(one, two, three, &result);

			free(one);
			free(two);
			free(three);
			if (error == EXIT_FAILURE)
			{
				printf("error with program\n");
				close(fd);
				return (EXIT_FAILURE);
			}
		}
		line = get_next_line(fd);
		i++;
	}

	close(fd);
	printf("result is: %d\n", result);
	// system("leaks a.out");				//test for leaks
	return (EXIT_SUCCESS);
}
