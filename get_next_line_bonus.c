/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 17:16:10 by iel-fagh          #+#    #+#             */
/*   Updated: 2024/04/16 08:54:40 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*theline(char *buff)
{
	int		i;
	int		j;
	char	*cleanbuff;

	if (!buff)
		return (0);
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	cleanbuff = (char *)malloc(sizeof(char) * (i + 1));
	if (!cleanbuff)
		return (0);
	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		cleanbuff[i++] = buff[j++];
	if (buff[i] == '\n')
		cleanbuff[i++] = buff[j];
	cleanbuff[i] = '\0';
	return (cleanbuff);
}

char	*newbuff(char *buff)
{
	int		i;
	int		j;
	char	*newbuff;

	if (!buff)
		return (0);
	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\0')
		return (free(buff), NULL);
	newbuff = (char *)malloc(sizeof(char) * (ft_strlen(buff) - i));
	if (!newbuff)
		return (NULL);
	i++;
	while (buff[i] != '\0')
		newbuff[j++] = buff[i++];
	newbuff[j] = '\0';
	free(buff);
	return (newbuff);
}

char	*ft_read(int fd, char *buff)
{
	char	*stash;
	ssize_t	numbyte;

	numbyte = 1;
	stash = malloc((size_t)BUFFER_SIZE + 1);
	if (!stash)
		return (NULL);
	while (!ft_strchr(buff, '\n') && numbyte != 0)
	{
		numbyte = read(fd, stash, BUFFER_SIZE);
		if (numbyte == -1)
			return (free(stash), free(buff), NULL);
		stash[numbyte] = '\0';
		buff = ft_strjoin(buff, stash);
		if (!buff)
			return (NULL);
	}
	free(stash);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[256];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = ft_read(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	line = theline(buff[fd]);
	buff[fd] = newbuff(buff[fd]);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
