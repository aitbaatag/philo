#include "philo.h"

int main(int argc, char *argv[])
{
	t_data	p_data;
	
	if (parsing(argc, argv, &p_data) != 0)
		return (1);
	if (philo_init(&p_data) != 0)
		return (1);
	if (philosopher_thread(&p_data) != 0)
		return (1);
    return 0;
}