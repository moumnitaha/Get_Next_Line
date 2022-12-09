/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:12:08 by tmoumni           #+#    #+#             */
/*   Updated: 2022/12/09 12:13:49 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_hasnewline(char *str)
{
	int	index;

	if (!str)
		return (-1);
	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	if (str[index] == '\n')
		return (index);
	return (-1);
}

char	*handle_line(char *buff, int read_val)
{
	char	*line;
	int		nlindex;
	int		count;

	count = 0;
	if (!buff || read_val == -1)
		return (NULL);
	if (ft_hasnewline(buff) == -1)
		return (ft_strdup(buff));
	nlindex = ft_hasnewline(buff);
	line = (char *)malloc(nlindex + 2);
	if (!line)
		return (NULL);
	while (count < nlindex)
	{
		line[count] = buff[count];
		count++;
	}
	line[count] = '\n';
	line[count + 1] = '\0';
	return (line);
}

char	*trim_buff(char *buff)
{
	int		nlindex;
	int		bufflen;
	int		count;
	char	*str;

	if (!buff)
		return (NULL);
	count = 0;
	nlindex = ft_hasnewline(buff);
	bufflen = ft_strlen(buff);
	if (nlindex == -1 || bufflen == nlindex + 1)
		return (free(buff), NULL);
	str = (char *)malloc(bufflen - nlindex + 1);
	while (count < bufflen - nlindex)
	{
		str[count] = buff[nlindex + 1 + count];
		count++;
	}
	str[count] = '\0';
	return (free(buff), str);
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
		str = (char *)malloc(BUFFER_SIZE + 1);
		if (!str)
			return (NULL);
		read_val = read(fd, str, BUFFER_SIZE);
		if (read_val < 1)
		{
			free(str);
			break ;
		}
		str[read_val] = '\0';
		buff = ft_strjoin(buff, str);
		free(str);
	}
	next_line = handle_line(buff, read_val);
	buff = trim_buff(buff);
	return (next_line);
}
