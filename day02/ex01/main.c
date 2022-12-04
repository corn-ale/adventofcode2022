
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include "get_next_line.h"

bool	update_score(char *line, int *score)
{
	bool	error;

	error = false;
	if (line[0] == 'A')				//Rock
	{
		if (line[2] == 'X')
			*score += 4;
		else if (line[2] == 'Y')
			*score += 8;
		else if (line[2] == 'Z')
			*score += 3;
		else
			error = true;
	}
	else if (line[0] == 'B')		//Paper
	{
		if (line[2] == 'X')
			*score += 1;
		else if (line[2] == 'Y')
			*score += 5;
		else if (line[2] == 'Z')
			*score += 9;
		else
			error = true;
	}
	else if (line[0] == 'C')		//Scissors
	{
		if (line[2] == 'X')
			*score += 7;
		else if (line[2] == 'Y')
			*score += 2;
		else if (line[2] == 'Z')
			*score += 6;
		else
			error = true;
	}
	else
		error = true;
	return (error);
}

int	main()
{
	int		fd;
	char	*line;
	int		i;
	int		score;
	bool	error;


	i = 1;
	score = 0;
	error = false;
	fd = open("../input.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("error with fd\n");
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	if (!line)
	{
		printf("error: empty file\n");
		return (EXIT_FAILURE);
	}

	while (line)
	{
		// printf("%d %s", i, line);
		error = update_score(line, &score);
		free(line);
		if (error == true)
		{
			printf("error with my or my opponents hand at line %d\n", i);
			return (EXIT_FAILURE);
		}
		line = get_next_line(fd);
		i++;
	}

	close(fd);
	printf("total score: %d\n", score);
	return (EXIT_SUCCESS);
}

//opponent:	A-Rock B-Paper C-Scissors
//me:		X-Rock Y-Paper Z-Scissors
