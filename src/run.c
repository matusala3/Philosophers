/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:25:08 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/19 12:56:49 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int run_sim(t_data *table)
{
    if(create_philosopher_threads(table) != 0)
        return (1);
    if(create_monitor_thread(table) != 0)
    {
        cleanup_philos();
        return (1);
    }
    wait_for_sim_end(table);
    return (0);
}

static int create_philosopher_threads(t_data *table)
{
    int i;

    i = 0;
    while (i < table->cfg.philo_num)
    {
        if(pthread_create(&table->philos[i].thread, NULL, philo_routine, &table->philos[i]) != 0)
        {
            printf("Error: Failed to create philosophers thread %d\n", i + 1);
            cleanup_partial_threads(table, i);
            return (1);
        }
        i++;
    }
    return (0);    
}

static int create_monitor_thread(t_data *table)
{
    
}

static void wait_for_sim_end(t_data *table)
{
    
}
