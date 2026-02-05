/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaguiar- <aaguiar-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:19:08 by aaguiar-          #+#    #+#             */
/*   Updated: 2026/01/26 15:21:02 by aaguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* frees allocated memory on error and returns NULL */
static char	*cleanup(char *buffer, char *stash)
{
	free(buffer);
	free(stash);
	return (NULL);
}

/* reads from fd and appends to stash until '\n' or EOF is found */
static char	*fill_stash(int fd, char *stash)
{
	char	*buffer;
	char	*joined;
	ssize_t	read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(stash, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (cleanup(buffer, stash));
		buffer[read_bytes] = '\0';
		joined = ft_strjoin(stash, buffer);
		if (!joined)
			return (cleanup(buffer, stash));
		free(stash);
		stash = joined;
	}
	free(buffer);
	return (stash);
}

/* extracts the next line from stash */
static char	*get_line(char *stash)
{
	ssize_t	pos;
	char	*line;

	if (!stash || !*stash)
		return (NULL);
	pos = 0;
	while (stash[pos] && stash[pos] != '\n')
		pos++;
	if (stash[pos] == '\n')
		pos++;
	line = ft_substr(stash, 0, pos);
	return (line);
}

/* removes the extracted line from stash */
static char	*shrink_stash(char *stash)
{
	ssize_t	pos;
	char	*rest;

	pos = 0;
	while (stash[pos] && stash[pos] != '\n')
		pos++;
	if (!stash[pos])
	{
		free(stash);
		return (NULL);
	}
	pos++;
	rest = ft_substr(stash, pos, ft_strlen(stash) - pos);
	free(stash);
	if (rest && !*rest)
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	stash = fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = shrink_stash(stash);
	return (line);
}
