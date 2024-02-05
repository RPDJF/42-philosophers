/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_atoitoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rude-jes <rude-jes@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 22:55:42 by rude-jes          #+#    #+#             */
/*   Updated: 2024/02/03 01:39:10 by rude-jes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static unsigned long	inputparser(long n)
{
	unsigned long	output;

	if (n < 0)
		output = -n;
	else
		output = n;
	return (output);
}

char	*ft_itoa(long n)
{
	char			*p;
	unsigned long	temp;
	int				isneg;
	int				len;

	isneg = 0;
	if (n < 0)
		isneg = 1;
	temp = inputparser(n);
	len = 0;
	while (++len, temp >= 10)
		temp /= 10;
	p = (char *)galloc((len + 1 + isneg) * sizeof(char));
	if (!p)
		return (0);
	p[(len + isneg) * sizeof(char)] = 0;
	temp = inputparser(n);
	while (len-- > 0)
	{
		p[len + isneg] = (temp % 10) + '0';
		temp /= 10;
	}
	if (isneg)
		p[0] = '-';
	return (p);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

long	ft_atoi(const char *str)
{
	long	output;
	int		sign;

	output = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign = -sign;
	while (ft_isdigit(*str))
		output = output * 10 + *(str++) - '0';
	return (sign * output);
}
