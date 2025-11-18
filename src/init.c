/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 20:56:06 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/18 19:44:17 by magebreh         ###   ########.fr       */
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
	init_philos(table);
	if(init_philo_fork(table))
	{
		free(table->philos);
		free(table->forks);
		return (1);
	}
	if(init_table_mutexes(table))
	{
		cleanup_all_array_mutexes(table);
        free(table->philos);
        free(table->forks);
        return (1);
	}
	return (0);
}

static void init_philos(t_data *table)
{
	int i;
	
	i = 0;
	table->stop = 0;
	table->start_us = get_time_us();
	while (i < table->cfg.philo_num)
	{
		table->forks[i].id = i;
		table->philos[i].id = i + 1;
		table->philos[i].meals_done = 0;
		table->philos[i].last_meal_us = 0;
		table->philos[i].state = PH_THINKING;
		table->philos[i].left = &table->forks[i];
		table->philos[i].right = &table->forks[(i + 1) % table->cfg.philo_num];
		table->philos[i].table = table;
		i++;
	}
	return ;
}

static int init_philo_fork(t_data *table)
{
	int i;

	i = 0;
	while (i < table->cfg.philo_num)
	{
		if(pthread_mutex_init(&table->philos[i].state_mtx, NULL))
		{
			cleanup_philo_mutexes(table, i + 1);
			return (1);
		}
		if(pthread_mutex_init(&table->forks[i].mtx, NULL))
		{
			cleanup_philo_mutexes(table, i + 1);
			cleanup_fork_mutexes(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int init_table_mutexes(t_data *table)
{
    if(pthread_mutex_init(&table->stop_mtx, NULL))
        return (1);
        
    if(pthread_mutex_init(&table->log_mtx, NULL))
    {
        pthread_mutex_destroy(&table->stop_mtx);
        return (1);
    }
    return (0);
}
