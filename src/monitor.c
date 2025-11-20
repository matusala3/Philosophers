/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:48:33 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/20 20:01:32 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void log_death(t_data *table, int philo_id)
{
    uint64_t current_time;
    uint64_t elapsed_ms;

    current_time = get_time_us();
    if(current_time == 0)
        return;
    pthread_mutex_lock(&table->log_mtx);
    elapsed_ms = (current_time - table->start_us) / 1000;
    printf("%llu %d died\n", (unsigned long long)elapsed_ms, philo_id);
    pthread_mutex_unlock(&table->log_mtx);
}

static void handle_death(t_data *table, int i)
{
    log_death(table, i + 1);
    pthread_mutex_lock(&table->stop_mtx);
    table->stop = 1;
    pthread_mutex_unlock(&table->stop_mtx);
}

static int is_philo_dead(t_data *table, int i)
{
    uint64_t last_meal;
    uint64_t current_time;
    uint64_t death_threshold;
    uint64_t time_since_last_meal;

    pthread_mutex_lock(&table->philos[i].state_mtx);
    last_meal = table->philos[i].last_meal_us;
    pthread_mutex_unlock(&table->philos[i].state_mtx);    
    current_time = get_time_us();
    if(current_time == 0)
        return (0);
    if(last_meal == 0)
        last_meal = table->start_us;
    time_since_last_meal = current_time - last_meal;
    death_threshold = table->cfg.time_to_die_ms * 1000;
    return(time_since_last_meal > death_threshold);
}

static int check_all_philos(t_data *table)
{
    int i;

    i = 0;
    while (i < table->cfg.philo_num)
    {
        if(is_philo_dead(table, i))
        {
            handle_death(table, i);
            return (1);
        }
        i++;
    }
    return (0);
}

void *monitor_routine(void *arg)
{
    t_data *table;
    
    table = (t_data *)arg;
    while (!should_stop(table))
    {
        if(check_all_philos(table))
            break;
        usleep(1000);
    }
    return (NULL);
}