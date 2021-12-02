# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/18 12:03:55 by mdaillet          #+#    #+#              #
#    Updated: 2021/10/18 12:05:26 by mdaillet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME	= libft.a

SRCS  = srcs/ft_memset.c \
		srcs/ft_bzero.c	\
		srcs/ft_memcpy.c	\
		srcs/ft_realloc.c	\
		srcs/ft_strnew.c    \
		srcs/ft_memccpy.c	\
		srcs/ft_memmove.c	\
		srcs/ft_memchr.c	\
		srcs/ft_memcmp.c	\
		srcs/ft_strlen.c	\
		srcs/ft_isalpha.c	\
		srcs/ft_isdigit.c	\
		srcs/ft_isalnum.c	\
		srcs/ft_isascii.c	\
		srcs/ft_isprint.c	\
		srcs/ft_toupper.c	\
		srcs/ft_tolower.c	\
		srcs/ft_strchr.c	\
		srcs/ft_strrchr.c	\
		srcs/ft_strncmp.c	\
		srcs/ft_strlcpy.c	\
		srcs/ft_strlcat.c	\
		srcs/ft_strnstr.c	\
		srcs/ft_atoi.c	\
		srcs/ft_calloc.c	\
		srcs/ft_strdup.c	\
		srcs/ft_substr.c	\
		srcs/ft_strjoin.c	\
		srcs/ft_strtrim.c	\
		srcs/ft_split.c	\
		srcs/ft_itoa.c	\
		srcs/ft_strmapi.c	\
		srcs/ft_putchar_fd.c	\
		srcs/ft_putstr_fd.c	\
		srcs/ft_putendl_fd.c	\
		srcs/ft_putnbr_fd.c	\
		srcs/ft_lstnew.c	\
		srcs/ft_lstadd_front.c	\
		srcs/ft_lstsize.c	\
		srcs/ft_lstlast.c	\
		srcs/ft_lstadd_back.c	\
		srcs/ft_lstclear.c	\
		srcs/ft_lstdelone.c	\
		srcs/ft_lstiter.c	\
		srcs/ft_lstmap.c \
		ft_printf/ft_putchar.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_process.c \
		ft_printf/ft_ft.c \
		ft_printf/ft_hexadecimal.c \
		ft_printf/ft_put_base.c \
		ft_printf/ft_uitoa.c \
		ft_printf/ft_width.c \
		ft_printf/ft_pff.c \
		ft_printf/ft_int.c \
		ft_printf/ft_uint.c \
		ft_printf/ft_str.c \
		ft_printf/ft_ptr.c \
		ft_printf/ft_pourcent.c \
		gnl/get_next_line.c \

OBJS = $(SRCS:.c=.o)
HEADER = includes/
CC = gcc
CC_FLAGS = -Wall -Wextra -Werror
RM = rm -f

$(NAME): $(OBJS)
			@echo "\n\n\033[0;32mCompiling libft..."
			@ar -rcs $(NAME) $(OBJS)
			@echo "\033[0m"

%.o: %.c
			@printf "\033[0;32mCreating libft objects... %-33.33s\r" $@
			@${CC} -c ${CC_FLAGS} -o $@ $< -I ${HEADER}

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
norme :
	norminette $(SRCS) $(HEADER)

re: fclean all

.PHONY: all fclean clean norme re
