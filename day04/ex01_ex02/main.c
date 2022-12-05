
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include "get_next_line.h"

void	update_values_for_ex01(int values[], int *ex01)
{
	if ((values[0] >= values[2] && values[1] <= values[3])
		|| (values[2] >= values[0] && values[3] <= values[1]))
	{
		(*ex01)++;
	}
}

void	update_values_for_ex02(int values[], int *ex02)
{
	if ((values[2] >= values[0] && values[2] <= values[1])
		|| (values[3] >= values[0] && values[3] <= values[1])
		|| (values[0] >= values[2] && values[0] <= values[3])
		|| (values[1] >= values[2] && values[1] <= values[3]))
	{
		(*ex02)++;
	}
}

int	count_pairs(char *line, int *ex01, int *ex02)
{
	int		values[4];
	int		iLine = 0;
	int		iTmp = 0;
	int		len = 0;
	int		loopCount = 0;
	char	*tmp;

	while (loopCount < 4)
	{
		len = iLine;
		while (isdigit(line[len]))
			len++;
		tmp = malloc(sizeof(char) * (len - iLine + 1));
		if (!tmp)
			return (EXIT_FAILURE);
		for (int i = 0; i < len - iLine; i++)
			tmp[i] = '0';
		tmp[len - iLine] = '\0';
		while (tmp[iTmp] && isdigit(line[iLine]))
		{
			tmp[iTmp] = line[iLine];
			iTmp++;
			iLine++;
		}
		values[loopCount] = atoi(tmp);
		// printf("%d ", values[loopCount]);
		free(tmp);
		loopCount++;
		iTmp = 0;
		if (loopCount < 4)
		{
			while (!isdigit(line[iLine]))
				iLine++;
		}
	}
	// printf("\n");

	update_values_for_ex01(values, ex01);
	update_values_for_ex02(values, ex02);

	return (EXIT_SUCCESS);
}

int	main()
{
	int		fd;
	int		i;
	int		ex01 = 0;
	int		ex02 = 0;
	char	*line;

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
		return (EXIT_FAILURE);
	}

	i = 1;
	while(line)
	{
		// printf("%d %s", i, line);
		count_pairs(line, &ex01, &ex02);
		free(line);
		line = get_next_line(fd);
		i++;
	}

	close(fd);
	printf("result for ex01: %d\n", ex01);
	printf("result for ex02: %d\n", ex02);
	return (EXIT_SUCCESS);
}
