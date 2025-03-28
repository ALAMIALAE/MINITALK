/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 06:35:25 by aben-dri          #+#    #+#             */
/*   Updated: 2025/03/27 20:48:35 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
		return (write(2, "Invalid Number Of Arguments\n", 28), 1);
	if (!valid_pid(av[1]))
		return (write(2, "Invalid PID\n", 12), 1);
	if ((signal(SIGUSR1, flag_handler)) == SIG_ERR)
	{
		write(2, "signal failed\n", 14);
		exit(1);
	}
	pid = ft_atoi(av[1]);
	message = av[2];
	while (*message)
	{
		send_char(pid, *message);
		message++;
	}
	write(1, "\033[35mThe message was succefully received \033[0m\n", 45);
}
