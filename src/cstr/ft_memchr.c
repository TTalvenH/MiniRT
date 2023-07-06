/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:52:01 by hseppane          #+#    #+#             */
/*   Updated: 2023/07/05 10:41:40 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft/cstr.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*it;

	it = (const unsigned char *)s;
	while (n--)
	{
		if (*it == (unsigned char)c)
			return ((void *)it);
		it++;
	}
	return (0);
}
