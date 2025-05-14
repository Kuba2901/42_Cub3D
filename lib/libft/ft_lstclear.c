/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 21:47:34 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/22 17:59:20 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buff;

	if (!lst || !del)
		return ;
	while (lst && *lst)
	{
		buff = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = buff;
	}
	lst = NULL;
}
