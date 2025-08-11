/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magebreh <magebreh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 17:33:02 by magebreh          #+#    #+#             */
/*   Updated: 2025/08/11 20:03:08 by magebreh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fork
{
    int				forkId;
	pthread_mutex_t	forkMtx;
}	t_fork;

typedef struct s_parsedData
{
	long	philoNum;
	long	timeToDieMs;
	long	timeToEatMs;
	long	timeToSleepMs;
	long	limitMeal;
}	t_parsedData;

typedef struct s_philo
{
	long			philoId;
	long			mealsdDone;
	t_fork			*leftFork;
	t_fork			*rightFork;
	pthread_t		thread;
	u_int64_t		lastMealUs;
	pthread_mutex_t	mtxState;
}	t_philo;

typedef struct s_data
{
	t_parsedData 	parsedData;
	t_fork			*forks;
	t_philo			*philos;
	int				stop;
	pthread_mutex_t	stopMtx;
	u_int64_t		start_us;
	pthread_t		monitor;
}	t_data;




