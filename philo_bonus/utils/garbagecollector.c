/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbagecollector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 01:28:30 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/03 01:44:07 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_garbcol	**getgarbage(void)
{
	static t_garbcol	*collector;

	return (&collector);
}

static t_garbcol	*lastgarbage(t_garbcol *garb)
{
	if (!garb)
		return (0);
	while (garb->next)
		garb = garb->next;
	return (garb);
}

void	*addgarbage(void *address)
{
	t_garbcol	*tmp;
	t_garbcol	*last;

	if (!address)
		return (0);
	tmp = (t_garbcol *)malloc(sizeof(t_garbcol));
	if (!tmp)
	{
		free(address);
		return (0);
	}
	last = 0;
	tmp->next = 0;
	tmp->prev = 0;
	tmp->content = address;
	if (*getgarbage())
	{
		last = lastgarbage(*getgarbage());
		last->next = tmp;
		tmp->prev = last;
	}
	else
		*getgarbage() = tmp;
	return (tmp->content);
}

void	*galloc(size_t size)
{
	return (addgarbage(malloc(size)));
}
