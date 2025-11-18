/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:49:04 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/18 17:56:23 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cleanup_philo_mutexes(t_data *table, int count)
{
    int i;
    
    i = 0;
    while (i < count)
    {
        pthread_mutex_destroy(&table->philos[i].state_mtx);
        i++;
    }
    return ;
}

void cleanup_fork_mutexes(t_data *table, int count)
{
    int i;
    
    i = 0;
    while (i < count)
    {
        pthread_mutex_destroy(&table->forks[i].mtx);
        i++;
    }
    return ;
}

void cleanup_all_array_mutexes(t_data *table)
{
    cleanup_philo_mutexes(table, table->cfg.philo_num);
    cleanup_fork_mutexes(table, table->cfg.philo_num);
    return ;
}