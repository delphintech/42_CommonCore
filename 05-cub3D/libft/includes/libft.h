/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magahat <magahat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:39:05 by magahat           #+#    #+#             */
/*   Updated: 2024/11/07 10:33:19 by magahat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* INCLUDES */
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include <limits.h>
# include <stdarg.h>

/* LISTE */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);

/* STR */
size_t	ft_strlen(const char *str);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s, char c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	*ft_striteri(char *s, void (*f)(unsigned int, char*));

/* MEMORY */
void	ft_bzero(void *b, size_t len);
void	*ft_calloc(size_t number, size_t size);
void	*ft_memchr(const void *b, int c, size_t len);
int		ft_memcmp(const void *b1, const void *b2, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *dst, int c, size_t len);

/* CHECK */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_charcmp(int c, char *s);

/* FILE */
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_base_fd(long long n, char *base, int fd);
void	ft_putstr_fd(char *str, int fd);

/* NBR */
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
int		ft_intlen_base(long n, int len_base);

/* FT_PRINTF */
int		ft_printf_fd(int fd, const char *str, ...);
int		print_str(char *str, int fd);
int		print_nb(long long n, int indic, int fd);

/* GNL */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	128
# endif

size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t siz);
char	*ft_strljoin_gnl(char *s1, char *s2, size_t l);
char	*get_next_line(int fd);

#endif
