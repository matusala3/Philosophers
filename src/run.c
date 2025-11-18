/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:25:08 by magebreh          #+#    #+#             */
/*   Updated: 2025/11/18 19:43:32 by magebreh         ###   ########.fr       */
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
    // Robust thread creation with error handling
    // Track created_count for cleanup
    // Return 0 on success, 1 on failure
}