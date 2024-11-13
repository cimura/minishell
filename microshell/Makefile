NAME		:=	microshell

# BUILTIN_DIR	:=	src/builtin/
# ENV_DIR		:=	src/env/
# EXEC_DIR	:=	src/exec/
# EXPANDER_DIR	:=	src/expander/
# LEXER_DIR	:=	src/lexer/

LIST_SRCS	:=	main.c \
				$(wildcard $(BUILTIN_DIR)*.c) \
				$(wildcard $(ENV_DIR)*.c) \
				$(wildcard $(EXEC_DIR)*.c) \
				$(wildcard $(EXPANDER_DIR)*.c) \
				$(wildcard $(LEXER_DIR)*.c)

SRC_DIRS	:=	src/builtin/ src/env/ src/lexer/ src/exec/ src/expander/ 
OBJ_DIR	:=	obj/
INC_DIR		:=	inc/

SRCS		:=	$(wildcard $(SRC_DIRS)/*.c)
OBJS		:=	$($(SRC_DIRS)%.c=$(OBJ_DIR)%.o)
# INCS		:=	$(addprefix $(INC_DIR),$(LIST_SRCS:.c=.h))

LIBFT_DIR	:=	src/libft
LIBFT		:=	$(LIBFT_DIR)/libft.a

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
#DEBUG_FLAGS	:=	-g -fsanitize=address
LDFLAGS		:=	-lreadline
IFLAGS		:=	-I$(LIBFT_DIR)/include -I$(INC_DIR)

ERASE		:=	\033[2K\r
PINK		:=	\033[35m
BLUE		:=	\033[34m
GREEN		:=	\033[32m
END			:=	\033[0m

all: $(NAME)

$(OBJ_DIR)%.o: $(SRCS)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(LDFLAGS) $(IFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@printf "$(ERASE)$(GREEN)$@ made\n$(END)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(PINK)remove obj dir\n$(END)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean	
	@printf "$(PINK)remove lib.a\n$(END)"

re: fclean all

.PHONY: all clean fclean re
