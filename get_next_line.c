/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carmelag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 19:01:59 by carmelag          #+#    #+#             */
/*   Updated: 2023/12/27 19:07:43 by carmelag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_stash(int fd, char *buff, char *stash)
{
	int		bytes;
	char	*aux;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		else if (bytes == -1)
		{
			free(stash);
			return (NULL);
		}
		buff[bytes] = '\0';
		if (!stash)
			stash = ft_strdup("");
		aux = stash;
		stash = ft_strjoin(aux, buff);
		free(aux);
		aux = NULL;
		if (ft_strchr (buff, '\n'))
			break ;
	}
	return (stash);
}

static char	*extract_line(char *line)
{
	size_t	i;
	char	*stash;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (0);
	stash = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	line = fill_stash(fd, buff, stash);
	free(buff);
	buff = NULL;
	if (!line)
		return (NULL);
	stash = extract_line(line);
	return (line);
}
