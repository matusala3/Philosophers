/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:00:41 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/12 20:09:09 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int parse_int(const char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	if(str[*i] == '-' || str[*i] == '+')
    	return (-1);
	return (1);
}

long ft_atol_safe(const char *str, int *err)
{
	int	i;
	int sign;
	long res;

	i = 0;
	res = 0;
	*err = 0;
	if(!str)
		return(*err = 1, 0);
	sign = parse_int(str, &i);
	if (sign == -1)
        return (*err = 1, 0);
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (*err = 1, 0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if(res > 2147483647)
			return (*err = 1, 0);
		i++;
	}
	if (str[i] != '\0' && str[i] != '\n')
		return (*err = 1, 0);
	return (res);
}

int ft_atol(const char *str, int *res)
{
	int err;
	long	val;
	
	val = ft_atol_safe(str, &err);
	if(err || val <= 0)
		return (-1);
	*res = (int) val;
	return (0);
}

int parse_arg(t_config *cfg, int argc, char **argv)
{
	if(ft_atol(argv[1], &cfg->philo_num) != 0)
		return(1);
	if(ft_atol(argv[2], &cfg->time_to_die_ms) != 0)
		return (1);
	if(ft_atol(argv[3], &cfg->time_to_eat_ms) != 0)
		return(1);
	if(ft_atol(argv[4], &cfg->time_to_sleep_ms) != 0)
		return (1);
	if(argc == 6)
	{
		if(ft_atol(argv[5], &cfg->meal_limit) != 0)
			return(1);
	}
	else
		cfg->meal_limit = -1;
}
