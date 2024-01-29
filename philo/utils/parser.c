/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:54:46 by rude-jes          #+#    #+#             */
/*   Updated: 2024/01/30 00:38:20 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	parse_pint(char *input)
{
	int		output;
	char	*tmp;

	input = ft_strtrim(input, " \t\n\v\f\r");
	if (!input)
		return (-1);
	output = ft_atoi(input);
	if (output < 0)
		return (-1);
	tmp = ft_itoa(output);
	if (!tmp)
		free(input);
	if (!tmp)
		return (-1);
	if (ft_strcmp(input, tmp))
		output = -1;
	free(input);
	free(tmp);
	return (output);
}
