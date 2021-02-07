/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchani <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:21:49 by dchani            #+#    #+#             */
/*   Updated: 2020/11/24 20:45:39 by dchani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char		*q_pop(char **queue)
{
	int		i;
	char	*ptr;

	ptr = 0;
	i = 0;
	while (queue && (*queue)[i] != '\n')
		i++;
	if ((*queue)[i + 1] && (!(ptr = ft_strdup(&((*queue)[i + 1])))))
		return (0);
	else if (!(*queue)[i + 1] && (!(ptr = ft_strdup(""))))
		return (0);
	free(*queue);
	return (ptr);
}

static	int			line_assign(char **queue, char **line)
{
	int i;

	i = 0;
	while ((*queue)[i] != '\n')
		if ((*queue)[i++] == '\0')
			return (0);
	(*queue)[i] = '\0';
	if (!(*line = ft_strdup(*queue)))
		return (-1);
	(*queue)[i] = '\n';
	if (!(*queue = q_pop(queue)))
		return (-1);
	return (1);
}

static	int			q_push(char **buffer, char **queue, int fd, char **line)
{
	int		cnt;
	char	*tmp;
	int		correct;

	while ((cnt = read(fd, *buffer, BUFFER_SIZE)))
	{
		(*buffer)[cnt] = '\0';
		tmp = *queue;
		if (!(*queue = ft_strjoin(*queue, *buffer)))
		{
			cnt = -1;
			break ;
		}
		free(tmp);
		correct = line_assign(queue, line);
		if (correct == 1)
			break ;
		else if (correct == -1)
		{
			cnt = -1;
			break ;
		}
	}
	free(*buffer);
	return (cnt);
}

static int			eof_case(char **queue_arr, char **line)
{
	if (!(*line = ft_strdup(*queue_arr)))
		return (-1);
	free(*queue_arr);
	*queue_arr = 0;
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*queue_arr[FD_MAX];
	char			*buffer;
	int				correct;

	if (BUFFER_SIZE <= 0 || !line || read(fd, 0, 0) == -1
	|| (!(buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1))))
		return (-1);
	if (queue_arr[fd] && (correct = line_assign(&queue_arr[fd], line)))
	{
		free(buffer);
		return (correct);
	}
	correct = q_push(&buffer, &queue_arr[fd], fd, line);
	if (!correct)
	{
		if (queue_arr[fd])
			return (eof_case(&queue_arr[fd], line));
		else if (!(*line = ft_strdup("")))
			return (-1);
		return (0);
	}
	return (correct > 0 ? 1 : -1);
}
