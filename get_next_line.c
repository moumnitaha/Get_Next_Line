/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:12:08 by tmoumni           #+#    #+#             */
/*   Updated: 2022/11/27 12:38:06 by tmoumni          ###   ########.fr       */
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

char	*fixline(char *buff)
{
	char	*line;
	int		nlindex;

	if (!buff)
		return (NULL);
	if (ft_hasnewline(buff) == -1)
		return (buff);
	nlindex = ft_hasnewline(buff);
	line = (char *)malloc(nlindex + 2);
	ft_memmove(line, buff, nlindex);
	line[nlindex] = '\n';
	line[nlindex + 1] = '\0';
	return (line);
}

char	*fix_buff(char *buff)
{
	int		index;
	size_t	bufflen;

	if (!buff)
		return (NULL);
	index = ft_hasnewline(buff);
	bufflen = ft_strlen(buff);
	if (index == -1 || ((int)bufflen == index + 1))
	{
		return (free(buff), NULL);
	}
	buff = ft_substr(buff, index + 1, bufflen - (index + 1));
	return (buff);
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
		if (read_val <= 0)
			break ;
		str[read_val] = '\0';
		buff = ft_strjoin(buff, str);
		free(str);
	}
	next_line = fixline(buff);
	buff = fix_buff(buff);
	return (next_line);
}

// int	main(void)
// {
// 	int	fd;

// 	fd = open("text.txt", O_RDWR, 777);
// 	printf("1: %s\n", get_next_line(fd));
// 	printf("2: %s\n", get_next_line(fd));
// 	printf("3: %s\n", get_next_line(fd));
// }
