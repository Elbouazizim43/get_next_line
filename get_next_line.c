/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-bo <mohel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:04:08 by mohel-bo          #+#    #+#             */
/*   Updated: 2024/12/12 23:32:04 by mohel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_hold(char *str)
{
	char	*res;

	if (!str)
		return (NULL);
	res = ft_strchr (str, '\n');
	if (!res)
		return (NULL);
	res ++;
	if (*res == '\0')
		return (NULL);
	return (ft_strdup (res));
}

static	char	*ft_line(char *str)
{
	char	*line;
	int		i;
	int		size;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i++] == '\n')
			break ;
	}
	size = i;
	line = malloc (size + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < size)
	{
		line[i] = str[i];
		i++;
	}
	line [i] = '\0';
	return (line);
}

static	char	*ft_read(int fd, char *tmp)
{
	char	*buffer;
	int		r;

	buffer = malloc ((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(tmp), NULL);
	while (ft_strchr (tmp, '\n') == 0)
	{
		r = read (fd, buffer, BUFFER_SIZE);
		if (r < 0)
			return (free(buffer), NULL);
		if (r == 0)
			return (free(buffer), tmp);
		buffer[r] = '\0';
		tmp = ft_strjoin(tmp, buffer);
		if (!tmp)
			return (free(buffer), NULL);
	}
	free (buffer);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*hold;
	char		*line;
	char		*buff;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, 0, 0) < 0)
		return (free(hold), hold = NULL, NULL);
	tmp = hold;
	hold = NULL;
	buff = ft_read (fd, tmp);
	if (!buff)
		return (NULL);
	line = ft_line (buff);
	if (!line)
		return (free(buff), NULL);
	hold = ft_hold(buff);
	free (buff);
	return (line);
}
