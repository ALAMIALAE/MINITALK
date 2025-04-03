/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:11:06 by aben-dri          #+#    #+#             */
/*   Updated: 2025/04/02 23:39:47 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_received = 0;

void	flag_handler(int signum)
{
	(void)signum;
	g_received = 1;
}

static int	valid_pid(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (((c >> (7 - i)) & 1) == 1)
		{
			if ((kill(pid, SIGUSR2)) == -1)
				exit(1);
		}
		else
		{
			if ((kill(pid, SIGUSR1)) == -1)
				exit(1);
		}
		while (!g_received)
			;
		g_received = 0;
		i++;
	}
}

int	ft_atoi(const char *str)
{
	long	nbr;
	int		i;
	int		sign;

	nbr = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		if ((sign == 1 && nbr > 2147483647) || (sign == -1 && nbr > 2147483648))
			return (-1);
		i++;
	}
	return ((int)nbr * sign);
}

int	main(int ac, char **av)
{
	char	*message;
	__pid_t	pid;

	if (ac != 3)
		return (write(2, "Invalid Number Of Arguments\n", 30), 1);
	if (!valid_pid(av[1]))
		return (write(2, "Invalid PID\n", 14), 1);
	if ((signal(SIGUSR1, flag_handler)) == SIG_ERR)
	{
		write(2, "signal failed\n", 15);
		exit(1);
	}
	pid = ft_atoi(av[1]);
	if (pid == -1)
	{
		write(2, "Error\n", 7);
		exit(1);
	}
	message = av[2];
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
}
