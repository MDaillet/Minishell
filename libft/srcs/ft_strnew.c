/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:30:35 by mdaillet          #+#    #+#             */
/*   Updated: 2021/10/20 16:52:28 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnew(size_t len)
{
	char	*str;

	str = (char *)malloc(len + 1);
	if (str != (char *) NULL)
		ft_bzero((void *)str, len + 1);
	return (str);
}
