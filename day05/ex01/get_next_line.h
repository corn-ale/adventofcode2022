/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkonyari <kkonyari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 19:05:19 by kkonyari          #+#    #+#             */
/*   Updated: 2022/12/06 16:12:27 by kkonyari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define	GET_NEXT_LINE_H
# define	BUFFER_SIZE 1

# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		newlinecheck(char *str);
char	*split(char *container, int bytes, char *forfreeing);
char	*ft_free(char **str, char *buff);
char	*ft_strjoin(char *s1, char const *s2);
int		ft_strlen(const char *s);

#endif