/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_mem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 00:07:17 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/03 01:50:29 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*ft_reallocf(void *ptr, size_t size, size_t newsize)
{
	unsigned char	*old_alloc;
	unsigned char	*new_alloc;
	size_t			i;

	i = 0;
	if (ptr == 0)
		return (galloc(newsize));
	old_alloc = (unsigned char *)ptr;
	new_alloc = (unsigned char *)galloc(newsize);
	if (new_alloc == 0)
	{
		gfree(ptr);
		return (0);
	}
	while (i < size && i < newsize)
	{
		new_alloc[i] = old_alloc[i];
		i++;
	}
	gfree(ptr);
	return (new_alloc);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count * size > (size_t)2147483647)
		return (0);
	p = galloc(count * size);
	if (!p)
		return (0);
	memset(p, 0, count * size);
	return (p);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dstwriter;

	if (!dest && !src)
		return (0);
	dstwriter = dest;
	while (src++, dstwriter++, (size_t)dstwriter - 1 - (size_t)dest < n)
		*(dstwriter - 1) = *(unsigned char *)(src - 1);
	return (dest);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*p;

	if (start >= ft_strlen(s))
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	p = (char *)ft_calloc(len + 1, sizeof(char));
	if (!p)
		return (0);
	ft_memcpy(p, s + start, len);
	return (p);
}
