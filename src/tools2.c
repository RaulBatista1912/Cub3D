/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabatist <rabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:11:26 by rabatist          #+#    #+#             */
/*   Updated: 2025/08/13 13:08:32 by rabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	remove_white_space_at_the_end(char *line)
{
	int	i;

	i = ft_strlen(line);
	while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t'
			|| line[i - 1] == '\n'))
	{
		line[i - 1] = '\0';
		i--;
	}
}

int	check_rgb_comma(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}
