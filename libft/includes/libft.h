/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 12:03:25 by mdaillet          #+#    #+#             */
/*   Updated: 2021/11/08 12:12:12 by mdaillet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# define BUFFER_SIZE 32

typedef struct s_lst
{
	void			*content;
	struct s_lst	*next;
}	t_lst;

void				*ft_realloc(void *ptr, size_t newsize);
char				*ft_strnew(size_t len);
void				ft_bzero(void *s, size_t n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char *str);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, int n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strncmp(const char *s1, const char *s2, int n);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
t_lst				*ft_lstnew(void *content);
t_lst				*ft_lstlast(t_lst *lst);
t_lst				*ft_lstmap(t_lst *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_lstadd_front(t_lst **alst, t_lst *new);
void				ft_lstadd_back(t_lst **alst, t_lst *new);
void				ft_lstdelone(t_lst *lst, void (*del)(void*));
void				ft_lstclear(t_lst **lst, void (*del)(void*));
void				ft_lstiter(t_lst *lst, void (*f)(void *));
int					ft_lstsize(t_lst *lst);

int					get_next_line(int fd, char **line);

typedef struct s_pff
{
	int				printed;
	int				type;
	int				width;
	int				minus;
	int				zero;
	int				dot;
	int				star;
}	t_pff;

int					ft_putchar(int c);
int					ft_printf(const char *input, ...);
int					ft_putstrl(char *str, int n);
char				*ft_strlow(char *str);
int					ft_char(char c, t_pff pff);
int					ft_intypelist(int c);
int					ft_inflaglist(int c);
int					ft_process(int c, t_pff pff, va_list arguments);
int					ft_pffdot(const char *param, int start, t_pff *pff,
						va_list arguments);
t_pff				ft_pffwidth(va_list arguments, t_pff pff);
t_pff				ft_pffdigit(char c, t_pff pff);
t_pff				ft_pffminus(t_pff pff);
int					ft_width(int width, int len, int zero);
int					ft_hexadecimal(unsigned int ui, int lower, t_pff pff);
char				*ft_put_base(unsigned long long n, int base);
char				*ft_uitoa(unsigned int n);
int					ft_pourcent(t_pff pff);
int					ft_ptr(unsigned long long ull, t_pff pff);
int					ft_str(char *str, t_pff pff);
int					ft_int(int n, t_pff pff);
int					ft_uint(unsigned int n, t_pff pff);

#endif
