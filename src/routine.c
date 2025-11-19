/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:37:57 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/19 16:37:26 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    while (1)
    {
        if(should_stop(philo->table))
            break;
        think(philo);
        if(should_stop(philo->table))
            break;
        eat(philo);
        if(should_stop(philo->table))
            break;
        sleep(philo);
    }
    return;
}

static int should_stop(t_data *table)
{
    int stop;

    pthread_mutex_lock(&table->stop_mtx);
    stop = table->stop;
    pthread_mutex_unlock(&table->stop_mtx);
    return (stop);    
}

static void think(t_philo *philo)
{
    pthread_mutex_lock(&philo->state_mtx);
    philo->state = PH_THINKING;
    pthread_mutex_unlock(&philo->state_mtx);
    log_action(philo, "is thinking");
}