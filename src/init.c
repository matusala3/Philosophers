/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:56:06 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/12 21:22:29 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init(t_data *table)
{
	table->philos = malloc(sizeof(t_philo) * table->cfg.philo_num);
	if(!table->philos)
		return (1);
	table->forks = malloc(sizeof(t_fork) * table->cfg.philo_num);
	if(!table->forks)
	{
		free(table->philos);
		return(1);
	}
	return (0);
}

int safe_mutex_handle(pthread_mutex_t *mutex, int op)
{
	//if op is lock call the fucntion othread_mutex_lock and 
	//do this for unlock, init and destroy
}