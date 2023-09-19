/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:30:40 by amanjon-          #+#    #+#             */
/*   Updated: 2023/08/01 08:42:35 by amanjon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*read_and_copy_buf(char *static_line, int fd)
{
	char	*buf;
	int		bytes;

	bytes = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	while (!ft_strchr_gnl_bonus(static_line, '\n') && bytes != 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(static_line);
			free(buf);
			return (NULL);
		}
		buf[bytes] = '\0';
		static_line = ft_strjoin_gnl(static_line, buf);
	}
	free (buf);
	return (static_line);
}

char	*save_line(char *static_line)
{
	char	*line;
	int		i;

	i = 0;
	if (!static_line[i])
		return (NULL);
	while (static_line[i] && static_line[i] != '\n')
		i++;
	line = malloc(sizeof (char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (static_line[i] && static_line[i] != '\n')
	{
		line[i] = static_line[i];
		i++;
	}
	if (static_line[i] == '\n')
	{
		line[i] = static_line[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*trim_stash(char *static_line)
{
	char	*stash;
	int		dest;

	dest = (ft_strlen_gnl_bonus(ft_strchr_gnl_bonus(static_line, '\n')) + 1);
	if (!ft_strchr_gnl_bonus(static_line, '\n'))
	{
		free(static_line);
		return (NULL);
	}
	stash = malloc(sizeof(char) * dest);
	if (stash == NULL)
		return (NULL);
	ft_strlcpy(stash, ft_strchr_gnl_bonus(static_line, '\n'), dest);
	free(static_line);
	return (stash);
}

char	*get_next_line(int fd)
{
	char static		*static_line[1024];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_line[fd] = read_and_copy_buf(static_line[fd], fd);
	if (static_line[fd] == NULL)
		return (NULL);
	line = save_line(static_line[fd]);
	static_line[fd] = trim_stash(static_line[fd]);
	return (line);
}

/* int	main(void)
{
	char	*aux_end;
	char	*aux_end1;
	char	*aux_end2;
	int		fd;
	int		fd1;
	int		fd2;

	fd = open("miFichero.txt", O_RDONLY);
	fd1 = open("miFichero1.txt", O_RDONLY);
	fd2 = open("miFichero2.txt", O_RDONLY);
	if (fd <= 0 || fd1 <= 0 || fd2 <= 0)
		return (0);
		
	 while (1)
	{
		aux_end = get_next_line(fd);
		aux_end1 = get_next_line(fd1);
		aux_end2 = get_next_line(fd2);
		if (aux_end == NULL || aux_end1 == NULL || aux_end2 == NULL)
			break;
		printf("%s", aux_end); 
		printf("%s", aux_end1); 
		printf("%s\n", aux_end2); 
		free(aux_end);
		free(aux_end1);
		free(aux_end2);
	}
	close(fd);
	close(fd1);
	close(fd2);
	return(0);
} */
