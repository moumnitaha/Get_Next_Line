/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:12:08 by tmoumni           #+#    #+#             */
/*   Updated: 2022/11/26 12:57:22 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int ft_hasnewline(char *str)
{
	static int	count;

	count = 0;
	while (str[count] != '\0' && str[count] != '\n')
		count++;
	if (str[count] == '\n')
		return (count);
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*str;
	int			read_val;
	
	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	read_val = 0;
	str = (char *)malloc(BUFFER_SIZE + 2);
	read_val = read(fd, str, BUFFER_SIZE);
	str[read_val] = '\n';
	str[read_val + 1] = '\0';
	buff = ft_strdup(str);
	return (buff);
}

int main()
{
	int fd = open("text.txt", O_RDWR, 777);
	printf("1: %s\n", get_next_line(fd));
	printf("2: %s\n", get_next_line(fd));
}