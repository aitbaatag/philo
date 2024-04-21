#include "philo.h"
void error_exit(char *str)
{
    printf ("%s\n", str);
    exit (1);
}
int check_input(char *str)
{
	int i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}
void ft_print_error(int i)
{
	if (i == 1)
		printf(ARG1);
	if (i == 2)
		printf (ARG2);
	if (i == 3)
		printf(ARG3);
	if (i == 4)
		printf (ARG4);
	if (i == 5)
		printf (ARG5);
}
void parsing(int argc, char *argv[], t_data *p_data)
{
	int i;

	i = 1;
	if (argc == 6 || argc == 5)
	{
		while (argv[i])
		{
			if (check_input(argv[i]) == 0)
				i++;
			else
            {
				ft_print_error(i);
                return (1);
            }
		}
		p_data->num_philo = ft_atoi(argv[1]);
		if (p_data->num_philo > 200)
        {
			ft_print_error(1);
            return (2);
        }
		p_data->time_to_die = ft_atoi(argv[2]);
		p_data->time_to_eat = ft_atoi(argv[3]);
		p_data->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			p_data->num_of_times_eat = ft_atoi(argv[5]);
        return (0);
	}
	else
		printf (HELP);
    return (3);
}
int		ft_atoi(const char *str)
{
	unsigned int	num;
	int				i;
	int				np;

	np = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\f' ||
			str[i] == '\r' || str[i] == '\n' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			np = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(np * num));
}