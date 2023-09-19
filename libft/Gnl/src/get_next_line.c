/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanjon- <amanjon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 07:46:43 by amanjon-          #+#    #+#             */
/*   Updated: 2023/07/26 08:21:29 by amanjon-         ###   ########.fr       */
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
	while (!ft_strchr_gnl(static_line, '\n') && bytes != 0)
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
	int		destsize;

	destsize = (ft_strlen_gnl(ft_strchr_gnl(static_line, '\n')) + 1);
	if (!ft_strchr_gnl(static_line, '\n'))
	{
		free(static_line);
		return (NULL);
	}
	stash = malloc(sizeof(char) * destsize);
	if (stash == NULL)
		return (NULL);
	ft_strlcpy(stash, ft_strchr_gnl(static_line, '\n'), destsize);
	free(static_line);
	return (stash);
}

char	*get_next_line(int fd)
{
	char static		*static_line;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_line = read_and_copy_buf(static_line, fd);
	if (static_line == NULL)
		return (NULL);
	line = save_line(static_line);
	static_line = trim_stash(static_line);
	return (line);
}

/* int	main(void)
{
	char	*aux_end;
	int		fd;

	fd = open("miFichero.txt", O_RDONLY);
	if (fd <= 0)
		return (0);
	 while (1)
	{
		aux_end = get_next_line(fd);
		if (aux_end == NULL)
			break;
		printf("%s", aux_end); 
		free(aux_end);
	}
	aux_end = get_next_line(fd);
	printf("%s", aux_end); 
	free (aux_end);

	aux_end = get_next_line(fd); 
	printf("%s", aux_end);
	free (aux_end);

	aux_end = get_next_line(fd);
	printf("%s", aux_end);
	free(aux_end);
	
	close(fd);
	return(0);
} */
