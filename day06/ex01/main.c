
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int	checkStart(char **s)
{
	int		i = 3;
	char	*str = *s;

	while (str[i] && str[i] != '\n')
	{
		if (str[i] == str[i - 1] || str[i] == str[i - 2] || str[i] == str[i - 3]
			|| str[i - 1] == str[i - 2] || str[i - 1] == str[i - 3]
			|| str[i - 2] == str[i - 3])
			i++;
		else
			return i;
	}
	return -1;
}

int	printErr(char *errMsg, char **line)
{
	char	*tmp;

	if (line == NULL)
		tmp = NULL;
	else
		tmp = *line;

	for (int i = 0; errMsg[i]; i++)
		write(STDERR_FILENO, &errMsg[i], sizeof(char));
	if (tmp)
		free(tmp);
	return 1;
}

int main()
{
	int		fd; 
	char	*line;
	int		res;
	int		len;

	fd = open("../input.txt", O_RDONLY);
	if (fd == -1)
		return (printErr("error with file\n", NULL));
	line = get_next_line(fd);
	close(fd);
	if (!line)
		return (printErr("error: empty file\n", NULL));
	len = strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len < 4)
		return (printErr("error: input too short\n", &line));
	res = checkStart(&line);
	if (res == -1)
		return (printErr("error: no marker in stream\n", &line));
	else
		printf("marker appeared after character %d\n", res + 1);
		// index starts at location 1 instead of 0...

	free(line);
	return 0;
}
