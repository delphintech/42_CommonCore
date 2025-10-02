/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabouab <dabouab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:58:25 by dabouab           #+#    #+#             */
/*   Updated: 2024/05/30 11:49:22 by dabouab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct t_rest
{
	char			rest[BUFFER_SIZE + 1];
	int				fd;
	struct t_rest	*next;
}	t_rest;

char	*get_next_line(int fd);
int		find_end_line(char *str);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t siz);
char	*ft_strljoin(char *s1, char *s2, size_t l);
t_rest	*ft_lstnew(int content);
t_rest	*ft_lstlast(t_rest *lst);
void	ft_lstadd_back(t_rest **lst, t_rest *new);

#endif