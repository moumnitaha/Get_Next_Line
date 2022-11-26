/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 10:12:11 by tmoumni           #+#    #+#             */
/*   Updated: 2022/11/26 12:38:26 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

static char	*stralloc(size_t start, size_t strlen, size_t len)
{
	char	*str;

	if (start <= strlen)
	{
		if (len <= strlen - start)
			str = (char *)malloc((len + 1) * sizeof(char));
		else
			str = (char *)malloc((strlen - start + 1) * sizeof(char));
	}
	else
		str = (char *)malloc(sizeof(char));
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	count;
	size_t	strlen;

	if (!s)
		return (NULL);
	count = 0;
	strlen = ft_strlen(s);
	if (len > strlen)
		len = strlen;
	str = stralloc(start, strlen, len);
	if (!str)
		return (NULL);
	if (start < strlen)
	{
		while (s[count + start] && count < len)
		{
			str[count] = s[start + count];
			count++;
		}
	}
	str[count] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	count;

	count = 0;
	ptr = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (count < ft_strlen((char *)s))
	{
		ptr[count] = s[count];
		count++;
	}
	ptr[count] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	count;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	count = 0;
	if (!str)
		return (NULL);
	while (count < s1len + s2len)
	{
		if (count < s1len)
			str[count] = s1[count];
		else
			str[count] = s2[count - s1len];
		count++;
	}
	str[count] = '\0';
	return (str);
}