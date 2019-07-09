/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcabel <hcabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 19:57:27 by hcabel            #+#    #+#             */
/*   Updated: 2019/07/09 00:59:05 by hcabel           ###   ########.fr       */
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

int			pf_display(void *arg, char *str)
{
	t_flags	flags;
	int 	i;

	i = 0;
	while (i < 5)
		flags.options[i++] = '\0';
	i = 0;
	while (i < 2)
		flags.scale[i++] = '\0';
	i = 1;
	i += check_options(&flags, str + i);
	i += check_length(&flags, str + i);
	i += check_precis(&flags, str + i);
	i += check_scale(&flags, str + i);
	flags.type = str[i++];
	pf_dispatch(flags, arg);
	return (i);
}