NAME		=	microshell

CMD_SRCS	=	ls.c
CMD_OBJS	=	$(CMD_SRCS:%.c=$(OBJ_DIR)%.o)
CMD_DIR		=	command/

MAIN_SRCS	=	main.c
MAIN_OBJS	=	$(MAIN_SRCS:%.c=$(OBJ_DIR)%.o)
MAIN_DIR	=	./

OBJ_DIR		=	objs/

HEADER		=	include/

OBJS		=	$(SRCS:%.c=$(OBJ_DIR)%.o)

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I $(HEADER)
LDFLAGS		=	-lreadline

OBJS		+=	$(CMD_OBJS) $(MAIN_OBJS)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	@echo "$(CYAN)$(BOLD)\nBuilding libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(CMD_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(MAIN_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

all:	$(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re