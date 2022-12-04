
#include "get_next_line.h"
#include "elven_calories.h"

int	highest_calories(t_data *data)
{
	int		fd;
	int		elfCount;
	int		elfCalories;
	bool	elf;
	char	*line;

	fd = open("../input.txt", O_RDONLY);
	elfCount = 0;
	elfCalories = 0;
	elf = false;
	line = get_next_line(fd);
	if (fd < 0 || !line)
		return (EXIT_FAILURE);
	data->elfWithHighestCalories = 0;
	data->highestCalories = 0;
	while (line)
	{
		if (!elf && strncmp(line, "\n", strlen(line)) != 0)
		{
			elfCount++;
			elf = true;
			elfCalories += atoi(line);
			printf("elf no.%d:\n", elfCount);
		}
		else if(elf && strncmp(line, "\n", strlen(line)) != 0)
		{
			elfCalories += atoi(line);
		}
		else if (elf && strncmp(line, "\n", strlen(line)) == 0)
		{
			elf = false;
			printf("total: %d\n", elfCalories);
			if (elfCalories > data->highestCalories)
			{
				data->highestCalories = elfCalories;
				data->elfWithHighestCalories = elfCount;
			}
			elfCalories = 0;
		}
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
		if (!line)
		{
			elf = false;
			printf("total: %d\n", elfCalories);
			if (elfCalories > data->highestCalories)
			{
				data->highestCalories = elfCalories;
				data->elfWithHighestCalories = elfCount;
			}
			elfCalories = 0;
		}
	}
	if (!data->elfWithHighestCalories || !data->highestCalories)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main()
{
	int 	error;
	t_data	result;

	error = highest_calories(&result);
	if (error == EXIT_FAILURE)
	{
		printf("error\n");
		return (EXIT_FAILURE);
	}
	else
	{
		printf("\nelf with highest calories:\telf no.%d\n", result.elfWithHighestCalories);
		printf("total calories carried by elf with highest calories:\t%d\n", result.highestCalories);
	}
	return (EXIT_SUCCESS);
}

// X-lose Y-draw Z-win