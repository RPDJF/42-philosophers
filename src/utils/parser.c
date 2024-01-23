/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:54:46 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/23 04:08:21 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	parse_pint(char *input)
{
	int		output;
	char	*tmp;

	input = ft_strtrim(input, " \t\n\v\f\r");
	output = ft_atoi(input);
	if (output < 0)
		return (-1);
	tmp = ft_itoa(output);
	if (!tmp)
		gfree(input);
	if (!tmp)
		return (-1);
	if (ft_strncmp(input, tmp,
			ft_max((int)ft_strlen(input), (int)ft_strlen(tmp))))
		output = -1;
	gfree(input);
	gfree(tmp);
	return (output);
}
