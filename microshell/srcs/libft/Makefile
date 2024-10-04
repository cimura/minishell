# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 16:27:09 by sshimura          #+#    #+#              #
#    Updated: 2024/10/05 00:04:18 by cimy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a
LIST_SRCS	:=	ft_atoi.c ft_isalpha.c ft_itoa.c ft_memcpy.c ft_strlcpy.c ft_toupper.c \
				ft_isascii.c ft_memmove.c ft_strlen.c ft_isdigit.c ft_memset.c \
				ft_strncmp.c ft_bzero.c ft_isprint.c ft_strchr.c ft_strnstr.c \
				ft_calloc.c ft_memchr.c ft_strdup.c ft_strrchr.c ft_isalnum.c \
				ft_memcmp.c ft_strlcat.c ft_tolower.c ft_split.c ft_strjoin.c \
				ft_strtrim.c ft_substr.c ft_strmapi.c ft_striteri.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_putchar_fd.c ft_putnbr_fd.c
LIST_BONUS	:=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

DIR_SRCS	:=	srcs
DIR_OBJS	:=	objs
DIR_INCS	:=	include

SRCS		:=	$(addprefix $(DIR_SRCS)/,$(LIST_SRCS))
BONUS_SRCS	:=	$(addprefix $(DIR_SRCS)/,$(LIST_BONUS))
OBJS		:=	$(addprefix $(DIR_OBJS)/,$(LIST_SRCS:.c=.o))
BONUS_OBJS	:=	$(addprefix $(DIR_OBJS)/,$(LIST_BONUS:.c=.o))
INCS		:=	$(addprefix $(DIR_INCS)/,$(LIST_SRCS:.c=.h))

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror

ERASE		:=	\033[2K\r
PINK		:=	\033[35m
BLUE		:=	\033[34m
GREEN		:=	\033[32m
END			:=	\033[0m

ifeq ($(BONUS_FLAG),true)
	$(OBJS) += $(BONUS_OBJS)
endif

all: $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@$(CC) $(CFLAGS) -I$(DIR_INCS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(DIR_OBJS):
	@mkdir -p $(DIR_OBJS)

$(NAME): $(DIR_OBJS) $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@printf "$(ERASE)$(GREEN)$@ made\n$(END)"

clean:
	@rm -rf $(DIR_OBJS)
	@printf "$(PINK)[LIBFT]remove obj dir\n$(END)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(PINK)[LIBFT]remove lib.a\n$(END)"

re: fclean all

bonus: $(OBJS) $(BONUS_OBJS)
	@$(MAKE) all BONUS_FLAG=true

.PHONY: all clean fclean re bonus
