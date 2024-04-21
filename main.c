#include "philo.h"

int main(int argc, char *argv[])
{
	t_data	p_data;
	t_philo	p_philo;
	
	if (parsing(argc, argv, &p_data) != 0)
		return (1);
	philo_init(&p_data, p_data.fork->forks);
	init_fork(&p_data);
    return 0;
}