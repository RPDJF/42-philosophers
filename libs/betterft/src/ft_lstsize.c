/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:51:44 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 02:31:01 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../betterft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = -1;
	while (i++, lst)
		lst = (*lst).next;
	return (i);
}
