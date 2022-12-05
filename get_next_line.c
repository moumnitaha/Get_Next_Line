/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:12:08 by tmoumni           #+#    #+#             */
/*   Updated: 2022/12/05 18:32:05 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_hasnewline(char *str)
{
	int	index;

	if (!str)
		return (-1);
	index = 0;
	while (str[index] != '\0' && str[index] != '\n')
		index++;
	if (str[index] == '\n')
		return (index);
	return (-1);
}

char	*fix_line(char *buff)
{
	char	*line;
	int		nlindex;

	if (!buff)
		return (NULL);
	if (ft_hasnewline(buff) == -1)
		return (buff);
	nlindex = ft_hasnewline(buff);
	line = (char *)malloc(nlindex + 2);
	if (!line)
		return (NULL);
	ft_memmove(line, buff, nlindex);
	line[nlindex] = '\n';
	line[nlindex + 1] = '\0';
	return (line);
}

char	*fix_buff(char *buff)
{
	int		nlindex;
	int		bufflen;
	char	*str;

	if (!buff)
		return (NULL);
	nlindex = ft_hasnewline(buff);
	bufflen = ft_strlen(buff);
	if (nlindex == -1 || bufflen == nlindex + 1)
	{
		free(buff);
		return (NULL);
	}
	str = ft_substr(buff, nlindex + 1, bufflen - (nlindex + 1));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*str;
	char		*next_line;
	int			read_val;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	while (ft_hasnewline(buff) == -1)
	{
		str = (char *)malloc(BUFFER_SIZE * sizeof(char));
		if (!str)
			return (NULL);
		read_val = read(fd, str, BUFFER_SIZE);
		if (read_val < 1)
			break ;
		str[read_val] = '\0';
		buff = ft_strjoin(buff, str);
	}
	free(str);
	next_line = fix_line(buff);
	buff = fix_buff(buff);
	return (next_line);
}
