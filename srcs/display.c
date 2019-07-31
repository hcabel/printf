/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:57:27 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/31 12:36:56 by hcabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_options(t_flags *flags, char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+' || str[i] == '#'
		|| str[i] == '0' || str[i] == ' '))
	{
		if (str[i] == '-')
			flags->options[0] = '-';
		else if (str[i] == '+')
			flags->options[1] = '+';
		else if (str[i] == '#')
			flags->options[2] = '#';
		else if (str[i] == '0')
			flags->options[3] = '0';
		else if (str[i] == ' ')
			flags->options[4] = ' ';
		i++;
	}
	return (i);
}

static int	check_length(t_flags *flags, char *str)
{
	int	i;

	i = 0;
	flags->length = (str[i] >= '0' && str[i] <= '9' ? 0 : -1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		flags->length = flags->length * 10 + str[i] - '0';
		i++;
	}
	return (i);
}

static int	check_precis(t_flags *flags, char *str)
{
	int	i;

	i = 0;
	flags->precis = (str[i] == '.' ? 0 : -1);
	i += (str[i] == '.' ? 1 : 0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		flags->precis = flags->precis * 10 + str[i] - '0';
		i++;
	}
	return (i);
}

static int	check_scale(t_flags *flags, char *str)
{
	if (str[0] == 'h')
	{
		flags->scale[0] = 'h';
		if (str[1] == 'h')
		{
			flags->scale[1] = 'h';
			return (2);
		}
		return (1);
	}
	else if (str[0] == 'l')
	{
		flags->scale[0] = 'l';
		if (str[1] == 'l')
		{
			flags->scale[1] = 'l';
			return (2);
		}
		return (1);
	}
	return (0);
}

int			pf_display(va_list args, char *str, int *ret)
{
	t_flags	flags;
	int 	i;

	if (str[0] == '%' && str[1] == '%')
		return (1);
	ft_bzero(flags.options, 5);
	ft_bzero(flags.scale, 2);
	i = 1;
	i += check_options(&flags, str + i);
	i += check_length(&flags, str + i);
	i += check_precis(&flags, str + i);
	i += check_scale(&flags, str + i);
	flags.type = str[i++];
	if (flags.type == 'd' || flags.type == 'i')
		flags.options[2] = '\0';
	if (flags.type == 'u' || flags.type == 'x' || flags.type == 'X'
		|| flags.type == 'o')
	{
		flags.options[1] = '\0';
		flags.options[4] = '\0';
	}
	if (flags.type == 'c' || flags.type == 's')
		ft_bzero(flags.options + 1, sizeof(char) * 5);
	*ret += pf_dispatch(flags, va_arg(args, double*));
	return (i);
}
