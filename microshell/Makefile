NAME		:=	microshell

LIST_SRCS	:=	main.c cat.c cd.c echo.c \
				env.c ls.c pwd.c

DIR_SRCS	:=	srcs
DIR_OBJS	:=	objs
DIR_INC		:=	include/

SRCS		:=	$(addprefix $(DIR_SRCS)/,$(LIST_SRCS))
OBJS		:=	$(addprefix $(DIR_OBJS)/,$(LIST_SRCS:.c=.o))

INCS		:=	$(addprefix $(DIR_INCS)/,$(LIST_SRCS:.c=.h))

LIBFT_DIR	:=	srcs/libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
DEBUG_FLAGS	:=	-g -fsanitize=address
LDFLAGS		:=	-lreadline

ERASE		:=	\033[2K\r
PINK		:=	\033[35m
BLUE		:=	\033[34m
GREEN		:=	\033[32m
END			:=	\033[0m

all: $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@$(CC) $(CFLAGS) -I $(DIR_INC) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(DIR_OBJS):
	@mkdir -p $(DIR_OBJS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(DIR_OBJS) $(OBJS)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(LDFLAGS) -I $(DIR_INC) -o $(NAME) $(OBJS) $(LIBFT)
	@printf "$(ERASE)$(GREEN)$@ made\n$(END)"

clean:
	@rm -rf $(DIR_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(PINK)remove obj dir\n$(END)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean	
	@printf "$(PINK)remove lib.a\n$(END)"

re: fclean all

.PHONY: all clean fclean re
