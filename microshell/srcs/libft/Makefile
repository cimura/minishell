# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cimy <cimy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 16:27:09 by sshimura          #+#    #+#              #
#    Updated: 2024/08/13 16:11:01 by cimy             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
SRCS		=	ft_atoi.c ft_isalpha.c ft_itoa.c ft_memcpy.c ft_strlcpy.c ft_toupper.c ft_isascii.c ft_memmove.c ft_strlen.c ft_atoi.c ft_isdigit.c ft_memset.c ft_strncmp.c	ft_bzero.c ft_isprint.c ft_strchr.c ft_strnstr.c ft_calloc.c ft_memchr.c ft_strdup.c ft_strrchr.c ft_isalnum.c ft_memcmp.c ft_strlcat.c ft_tolower.c ft_split.c ft_strjoin.c ft_strtrim.c ft_substr.c ft_strmapi.c ft_striteri.c ft_putstr_fd.c ft_putendl_fd.c ft_putchar_fd.c ft_putnbr_fd.c
BONUS_SRCS	=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUS_OBJS	=	$(BONUS_SRCS:%.c= %.o)
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

ifeq ($(BONUS_FLAG),true)
	SOURCES = $(SRCS) $(BONUS_SRCS)
else
	SOURCES = $(SRCS)
endif
OBJS = $(SOURCES:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
		@ar rcs $(NAME) $(OBJS)

clean:
		rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
		rm -f $(NAME)

re: all clean

bonus: 
		$(MAKE) all BONUS_FLAG=true

.PHONY : all clean fclean re bonus
