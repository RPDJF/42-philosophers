/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:45:31 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/30 00:16:36 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

size_t	ft_strlen(const char *s)
{
	char	*reader;

	reader = (char *)s;
	while (*reader)
		reader++;
	return (reader - s);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	size;
	size_t	i;

	size = ft_strlen(s);
	dup = malloc((size + 1) * sizeof(char));
	if (!dup)
		return (0);
	i = -1;
	while (i++, i < size)
		dup[i] = s[i];
	dup[i] = 0;
	return (dup);
}

static int	checkcharset(char const c, char const *set)
{
	while (*set)
		if (*(set++) == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (0);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && checkcharset(s1[start], set))
		start++;
	while (end > 0 && s1[end] && checkcharset(s1[end], set))
		end--;
	if (end < start)
		return (ft_strdup(""));
	return (ft_substr(s1, start, end - start + 1));
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (!*s1 && !*s2)
		return (0);
	return (*s1 - *s2);
}
