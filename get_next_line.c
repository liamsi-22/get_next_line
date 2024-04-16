/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-fagh <iel-fagh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 09:59:16 by iel-fagh          #+#    #+#             */
/*   Updated: 2023/12/25 22:18:37 by iel-fagh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = ft_read(fd, buff);
	if (!buff)
		return (NULL);
	line = theline(buff);
	buff = newbuff(buff);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
/*
 int main()
 {
	 int fd2 = open("get_next_line.h", O_RDONLY);
 	int fd = open("LOL.txt", O_RDONLY | O_CREAT);
 	char *p;
	char *q;
	while ((q = get_next_line(fd2)))
	{
		printf("%s",q);
		free(q);
	}
	while ((p = get_next_line(fd)))
	{
		printf("%s", p);
		free(p);
	}
 }
 */
