/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:30:49 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/22 15:41:04 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*buff;

	if (!f || !del)
		return (NULL);
	buff = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!(new))
		{
			while (buff)
			{
				new = buff->next;
				ft_lstdelone(buff, del);
				free (buff);
				buff = new;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&buff, new);
		lst = lst->next;
	}
	return (buff);
}
