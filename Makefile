# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdaillet <mdaillet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 18:46:20 by mdaillet          #+#    #+#              #
#    Updated: 2021/11/06 16:49:19 by mdaillet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS		= srcs/minishell.c \
				  srcs/ft_terminal.c \
				  srcs/ft_arrow_keys.c \
				  srcs/utils/ft_adddel.c \
				  srcs/utils/ft_alloc.c \
				  srcs/utils/ft_builtutils.c \
				  srcs/utils/ft_error.c \
				  srcs/utils/ft_free.c \
				  srcs/utils/ft_list2.c \
				  srcs/utils/ft_list3.c \
				  srcs/utils/ft_list.c \
				  srcs/utils/ft_str.c \
				  srcs/parse/ft_builtin_split.c \
				  srcs/parse/ft_check_input.c \
				  srcs/parse/ft_read.c \
				  srcs/parse/ft_remove_q.c \
				  srcs/parse/ft_tokenize.c \
				  srcs/parse/ft_venv_checker.c \
				  srcs/execute/ft_end.c \
				  srcs/execute/ft_execve.c \
				  srcs/execute/ft_parent.c \
				  srcs/execute/ft_pipe_utils.c \
				  srcs/execute/ft_redirection.c \
				  srcs/execute/ft_execute.c \
				  srcs/execute/ft_manager.c \
				  srcs/execute/ft_pipe_close.c \
				  srcs/execute/ft_pipexe.c \
				  srcs/execute/ft_signal.c \
				  srcs/builtin/ft_builtin.c \
				  srcs/builtin/ft_cmd_cd.c \
				  srcs/builtin/ft_cmd_echo.c \
				  srcs/builtin/ft_cmd_env.c \
				  srcs/builtin/ft_cmd_export.c \
				  srcs/builtin/ft_cmd_pwd.c \
				  srcs/builtin/ft_cmd_unset.c \
				  srcs/builtin/ft_env.c \

HEADER		=	includes/

LIBFT		=	libft/libft.a

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) #-fsanitize=address

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(LIBFT) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lncurses

$(LIBFT)	:
				make -C ./libft

clean		:
				rm -rf $(OBJS)
				make clean -C ./libft

fclean		:	clean
				rm $(NAME)
				make fclean -C ./libft

re			:	fclean all
