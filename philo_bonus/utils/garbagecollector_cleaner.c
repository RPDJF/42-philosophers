/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbagecollector_cleaner.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 01:42:12 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/03 01:50:12 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	gfree(void *address)
{
	t_garbcol	**collector;
	t_garbcol	*todel;

	collector = getgarbage();
	todel = *collector;
	while (todel && todel->content != address)
		todel = todel->next;
	if (!todel)
		free(address);
	else
	{
		if (todel->prev)
			todel->prev->next = todel->next;
		else
			*collector = todel->next;
		if (todel->next)
			todel->next->prev = todel->prev;
		free(todel->content);
		free(todel);
	}
	return ;
}

void	cleargarbage(void)
{
	t_garbcol	**collector;
	t_garbcol	*todel;
	t_garbcol	*tmp;

	collector = getgarbage();
	todel = *collector;
	while (todel)
	{
		free(todel->content);
		tmp = todel->next;
		free(todel);
		todel = tmp;
	}
	*collector = 0;
}
