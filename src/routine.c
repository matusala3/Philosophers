/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:37:57 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/21 15:53:10 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void philo_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->state_mtx);
    philo->state = PH_SLEEPING;
    pthread_mutex_unlock(&philo->state_mtx);
    log_action(philo, "is sleeping");
    usleep(philo->table->cfg.time_to_sleep_ms * 1000);
}

static int acquire_forks(t_philo *philo)
{
    t_fork *first_fork;
    t_fork *second_fork;

    if(philo->left == philo->right)
    {
        pthread_mutex_lock(&philo->left->mtx);
        log_action(philo, "has taken a fork");
        pthread_mutex_unlock(&philo->left->mtx);
        return (1);
    }
    if(philo->left->id < philo->right->id)
    {
        first_fork = philo->left;
        second_fork = philo->right;
    }
    else
    {
        first_fork = philo->right;
        second_fork = philo->left;
    }
    pthread_mutex_lock(&first_fork->mtx);
    log_action(philo, "has taken a fork");
    pthread_mutex_lock(&second_fork->mtx);
    log_action(philo, "has taken a fork");
    return (0);
}

static void eat(t_philo *philo)
{
    uint64_t meal_time;

    if(acquire_forks(philo))
    {
        while (!should_stop(philo->table))
            usleep(1000);
        return ;
    }
    pthread_mutex_lock(&philo->state_mtx);
    philo->state = PH_EATING;
    meal_time = get_time_us();
    if(meal_time == 0)
        meal_time = philo->last_meal_us;
    philo->last_meal_us = meal_time;
    philo->meals_done++;
    pthread_mutex_unlock(&philo->state_mtx);
    log_action(philo, "is eating");
    usleep(philo->table->cfg.time_to_eat_ms * 1000);
    release_forks(philo);
}

static void think(t_philo *philo)
{
    pthread_mutex_lock(&philo->state_mtx);
    philo->state = PH_THINKING;
    pthread_mutex_unlock(&philo->state_mtx);
    log_action(philo, "is thinking");
    if(philo->table->cfg.philo_num > 1 && philo->table->cfg.philo_num % 2 == 1)
        usleep(1000);
}

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if(philo->table->cfg.philo_num > 1)
    {
        if(philo->table->cfg.philo_num % 2 == 1 && philo->id == philo->table->cfg.philo_num)
            usleep(philo->table->cfg.time_to_eat_ms * 1000);
        else if(philo->id % 2 == 0)
            usleep(philo->table->cfg.time_to_eat_ms * 500);
    }
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
        philo_sleep(philo);
    }
    return (NULL);
}
