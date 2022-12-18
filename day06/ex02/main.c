
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include "get_next_line.h"

/*
Searches the given string for the first area where
a range 14 consecutive characters were all different.
The given string is expected to be at least 14 characters
long.

The function searches the entire string, starting with the
1st 14 characters. If a pair of dupes were found, the searched
area of 14 characters is incremented in such a way that the
same pair of matching characters won't be found again:

...|.....a.....a..|.........  -->  ........a|.....a........|...

. = chars in str
a = matching chars in searched range
| = searched range

If such an area was found in the string, the position of the
last character of the found area is returned. Otherwise -1
is returned.
*/
int	checkStart(char **s)
{
	int		start	= 0;
	int		end		= start + 13;
	int		i		= start;
	int		j		= i + 1;
	bool	dupes	= false;
	char	*str	= *s;

	while (str[start] && str[end])
	{


		i = start;
		while (i < end && str[i])
		{


			j = i + 1;
			while(j <= end && str[j])
			{
				if (str[i] == str[j])
				{
					dupes = true;
					break ;
				}
				else if (i == end -1 && j == end && str[i] != str[j])
				{
					// while (start <= end)		//write the section of str that has no repetition
					// {
					// 	write(STDOUT_FILENO, &str[start], sizeof(char));
					// 	start++;
					// }
					// write(STDOUT_FILENO, "\n", sizeof(char));
					return end;
				}
				j++;
			}
			if (dupes)
				break ;


			i++;
		}
		if (dupes)
		{
			start = i;
			dupes = false;
		}


		start++;
		end = start + 13;
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
	if (len < 14)
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
