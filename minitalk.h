/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dri <aben-dri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:16:43 by aben-dri          #+#    #+#             */
/*   Updated: 2025/03/27 06:19:30 by aben-dri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	char	current_char;
	int		g_bit_counter;
}			t_data;

void		flag_handler(int signum);
int			ft_atoi(const char *str);
void		send_char(int pid, char c);

#endif
