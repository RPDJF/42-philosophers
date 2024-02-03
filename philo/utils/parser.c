/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 03:54:46 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/03 01:50:01 by rude-jes         ###   ########.fr       */
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
		gfree(input);
	if (!tmp)
		return (-1);
	if (ft_strcmp(input, tmp))
		output = -1;
	gfree(input);
	gfree(tmp);
	return (output);
}

int	init_simulation_limit(t_data *data, int argc, char **argv)
{
	if (argc == 6)
	{
		data->number_of_times_each_philosopher_must_eat = parse_pint(argv[5]);
		if (data->number_of_times_each_philosopher_must_eat < 0)
			return (-1);
	}
	else
		data->number_of_times_each_philosopher_must_eat = 0;
	return (0);
}
