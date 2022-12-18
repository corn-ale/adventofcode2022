/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonyari <kkonyari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:35:45 by kkonyari          #+#    #+#             */
/*   Updated: 2021/10/15 19:03:06 by kkonyari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str, char *buff)
{
	if (*str)
		free(*str);
	*str = NULL;
	if (buff)
		free(buff);
	return (NULL);
}

int	newlinecheck(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (str[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-1);
}

char	*split(char *container, int bytes, char *forfreeing)
{
	int		i;
	int		j;
	char	*newline;

	free(forfreeing);
	i = 0;
	newline = malloc(bytes + 1);
	if (newline == NULL)
		return (NULL);
	while (i != (bytes + 1))
	{
		newline[i] = container[i];
		i++;
	}
	newline[i] = '\0';
	j = 0;
	while (container[i] != '\0')
	{
		container[j] = container[i];
		i++;
		j++;
	}
	container[j] = '\0';
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	*container;
	char		*buff1;
	int			bytes;

	if (fd < 0)
		return (NULL);
	buff1 = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!buff1)
		return (NULL);
	while (newlinecheck(container) == -1)
	{
		bytes = read(fd, buff1, BUFFER_SIZE);
		if (bytes <= 0)
		{
			if (container != NULL && container[0] == '\0')
				return (ft_free(&container, buff1));
			free(buff1);
			buff1 = container;
			container = NULL;
			return (buff1);
		}
		buff1[bytes] = '\0';
		container = ft_strjoin(container, buff1);
	}
	return (split(container, newlinecheck(container), buff1));
}
