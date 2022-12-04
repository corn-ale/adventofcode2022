/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonyari <kkonyari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:05:04 by kkonyari          #+#    #+#             */
/*   Updated: 2021/10/15 19:03:58 by kkonyari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	index;

	index = 0;
	if (s == NULL)
		return (0);
	while (s[index] != '\0')
		index++;
	return (index);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		j;

	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i] != '\0')
		{
			newstr[i] = s1[i];
			i++;
		}
	}
	while (s2[j] != '\0')
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	if (s1)
		free(s1);
	s1 = NULL;
	return (newstr);
}
