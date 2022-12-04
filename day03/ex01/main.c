
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include "get_next_line.h"

int	find_matching_item(char *firstPocket, char *secondPocket, char *result)
{
	int		first;
	int		second;

	first = 0;
	while (firstPocket[first] != '\0')
	{
		second = 0;
		while (secondPocket[second] != '\0')
		{
			if (firstPocket[first] == secondPocket[second])
			{
				*result = firstPocket[first];
				return (EXIT_SUCCESS);
			}
			second++;
		}
		first++;
	}
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

int	update_result(char *line, int *result)
{
	int		half;
	char	matching_item;
	char	*firstPocket;
	char	*secondPocket;

	matching_item = '#';
	char temp = 'a';
	half = strlen(line) / 2;
	firstPocket = calloc(1, sizeof(char) * (half + 1));
	secondPocket = calloc(1, sizeof(char) * (half + 1));
	if (!firstPocket || !secondPocket)
		return (EXIT_FAILURE);

	find_unique_items(line, &firstPocket, 0, half);
	find_unique_items(line, &secondPocket, half, half * 2);
	// printf("%s  %s\n", firstPocket, secondPocket);	// print unique items in compartments

	if (find_matching_item(firstPocket, secondPocket, &matching_item) == EXIT_FAILURE)
	{
		free(firstPocket);
		free(secondPocket);
		return (EXIT_FAILURE);
	}
	if (matching_item >= 'a' && matching_item <= 'z')
		*result += matching_item - 'a' + 1;
	else if (matching_item >= 'A' && matching_item <= 'Z')
		*result += matching_item - 'A' + 27;
	// printf("%c\n", matching_item);			//print matching item

	free(firstPocket);
	free(secondPocket);
	return (EXIT_SUCCESS);
}

int	main()
{
	int		fd;
	int		i;
	int		result;
	char	*line;
	int		error;

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
		error = update_result(line, &result);
		free(line);
		if (error == EXIT_FAILURE)
		{
			printf("error with program\n");
			close(fd);
			return (EXIT_FAILURE);
		}
		line = get_next_line(fd);
		i++;
	}

	close(fd);
	printf("result is: %d\n", result);
	return (EXIT_SUCCESS);
}
