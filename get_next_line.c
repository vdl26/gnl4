/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vde-lang <vde-lang@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 10:36:13 by vde-lang      #+#    #+#                 */
/*   Updated: 2021/06/19 23:31:32 by vde-lang      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*s;
	const unsigned char	*p;

	s = dest;
	p = src;
	if (dest == '\0' && src == '\0')
		return (dest);
	while (n > 0)
	{
		*s = *p;
		p++;
		s++;
		n--;
	}
	return (dest);
}

int	newline(char *line)
{
	int			i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	save_l(char *str, char **line, int i)
{
	int			len;

	*line = ft_substr(str, 0, i);
	if (*line == NULL)
		return (-1);
	++i;
	len = ft_strlen(str + i) + 1;
	ft_memmove(str, str + i, len);
	return (1);
}

int	ft_remainder(char **savedline, char **line, int ret)
{
	*line = ft_strdup(*savedline);
	free(*savedline);
	*savedline = NULL;
	if (*line == NULL)
		return (-1);
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*savedline[1024];
	char		buff[BUFFER_SIZE + 1];
	int			i;
	int			ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1 || fd > 1024)
	{
		*line = NULL;
		return (-1);
	}
	i = newline(savedline[fd]);
	if (i != -1)
		return (save_l(savedline[fd], line, i));
	ret = read(fd, buff, BUFFER_SIZE);
	while (ret > 0)
	{
		buff[ret] = '\0';
		savedline[fd] = ft_strjoin(savedline[fd], buff);
		if (savedline[fd] == NULL)
			return (-1);
		if (newline(savedline[fd]) != -1)
			return (save_l(savedline[fd], line, newline(savedline[fd])));
		ret = read(fd, buff, BUFFER_SIZE);
	}
	if (savedline[fd])
		return (ft_remainder(&savedline[fd], line, ret));
	*line = NULL;
	return (ret);
}
