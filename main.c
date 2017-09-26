/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 13:59:43 by ademenet          #+#    #+#             */
/*   Updated: 2017/09/26 17:15:49 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free(void *ptr)
{
	if (ptr == 0)
		return;
}

// Malloc implementation
// Return pointer to the newly allocated size
// Return NULL pointer otherwise
void		*malloc(size_t size)
{
	void	*block;
	int		page_size;

	// Il faut que la taille soit un multiple de page size
	page_size = getpagesize();
	// 
	
	return(block);
}

int		main()
{
	printf("%d", getpagesize());
	return(0);
}
