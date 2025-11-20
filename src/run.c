/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:25:08 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/20 19:54:14 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
    printf("✅ Successfully created %d philosopher threads\n", i);
    return (0);    
}

static int create_monitor_thread(t_data *table)
{
    if(pthread_create(&table->monitor, NULL, monitor_routine, table) != 0)
    {
        printf("ErrorL Faild to create monitor thread\n");
        return (1);
    }
    printf("✅ Monitor thread created successfully\n");
    return (0);
}

static void wait_for_sim_end(t_data *table)
{
    int i;
    int failed_joins;

    if(pthread_join(table->monitor, NULL) != 0)
        printf("Error: Failed to join monitor thread\n");
    i = 0;
    failed_joins = 0;
    while (i < table->cfg.philo_num)
    {
        if(pthread_join(table->philos[i].thread, NULL) != 0)
        {
            printf("Error: Failed to join philosophers thread %d\n", i + 1);
            failed_joins++;
        }
        i++;
    }
    if(failed_joins > 0)
        printf("Warning: %d threads may not have joined properly\n", failed_joins);
    else
        printf("✅ All threads joined successfully\n");
}

int run_sim(t_data *table)
{
    if(create_philosopher_threads(table) != 0)
        return (1);
    if(create_monitor_thread(table) != 0)
    {
        cleanup_partial_threads(table, table->cfg.philo_num);
        return (1);
    }
    wait_for_sim_end(table);
    return (0);
}
