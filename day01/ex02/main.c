
#include "get_next_line.h"
#include "elven_calories.h"

void	init_data(t_data *data)
{
	data->firstElf = 0;
	data->secondElf = 0;
	data->thirdElf = 0;
	data->firstCal = 0;
	data->secondCal = 0;
	data->thirdCal = 0;
}

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
			if (elfCalories > data->firstCal)
			{
				data->thirdCal = data->secondCal;
				data->thirdElf = data->secondElf;
				data->secondCal = data->firstCal;
				data->secondElf = data->firstElf;
				data->firstCal = elfCalories;
				data->firstElf = elfCount;
			}
			else if (elfCalories > data->secondCal)
			{
				data->thirdCal = data->secondCal;
				data->thirdElf = data->secondElf;
				data->secondCal = elfCalories;
				data->secondElf = elfCount;
			}
			else if (elfCalories > data->thirdCal)
			{
				data->thirdCal = elfCalories;
				data->thirdElf = elfCount;
			}
			elfCalories = 0;
			data->topThreeCal = data->firstCal + data->secondCal + data->thirdCal;
		}
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
		if (!line)
		{
			elf = false;
			printf("total: %d\n", elfCalories);
			if (elfCalories > data->firstCal)
			{
				data->thirdCal = data->secondCal;
				data->thirdElf = data->secondElf;
				data->secondCal = data->firstCal;
				data->secondElf = data->firstElf;
				data->firstCal = elfCalories;
				data->firstElf = elfCount;
			}
			else if (elfCalories > data->secondCal)
			{
				data->thirdCal = data->secondCal;
				data->thirdElf = data->secondElf;
				data->secondCal = data->firstCal;
				data->secondElf = data->firstElf;
			}
			else if (elfCalories > data->thirdCal)
			{
				data->thirdCal = data->secondCal;
				data->thirdElf = data->secondElf;
			}
			elfCalories = 0;
			data->topThreeCal = data->firstCal + data->secondCal + data->thirdCal;
		}
	}
	if (!data->firstElf || !data->firstCal || !data->secondElf || !data->secondCal || !data->thirdElf || !data->thirdCal || !data->topThreeCal)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main()
{
	int 	error;
	t_data	result;

	init_data(&result);
	error = highest_calories(&result);
	if (error == EXIT_FAILURE)
	{
		printf("error\n");
		return (EXIT_FAILURE);
	}
	else
	{
		printf("\nelf with highest calories:\telf no.%d\n", result.firstElf);
		printf("total calories carried by elf with highest calories:\t%d\n", result.firstCal);
		printf("\nelf with 2nd highest calories:\telf no.%d\n", result.secondElf);
		printf("total calories carried by elf with 2nd highest calories:\t%d\n", result.secondCal);
		printf("\nelf with 3rd highest calories:\telf no.%d\n", result.thirdElf);
		printf("total calories carried by elf with 3rd highest calories:\t%d\n", result.thirdCal);
		printf("\ntotal calories carried by top 3 elves:\t%d\n", result.topThreeCal);
	}
	return (EXIT_SUCCESS);
}
