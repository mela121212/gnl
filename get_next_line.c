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
	int		read_line;
	char	*char_temp;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buff, BUFFER_SIZE);
		if (read_line == -1)
			return (0);
		else if (read_line == 0)
			break ;
		buff[read_line] = '\0';
		if (!stash)
			stash = ft_strdup("");
		char_temp = stash;
		stash = ft_strjoin(char_temp, buff);
		free(char_temp);
		char_temp = NULL;
		if (ft_strchr (buff, '\n'))
			break ;
	}
	return (stash);
}

static char	*extract_line(char *line)
{
	size_t	count;
	char	*stash;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	stash = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*stash == '\0')
	{
		free(stash);
		stash = NULL;
	}
	line[count + 1] = '\0';
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
