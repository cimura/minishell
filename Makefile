NAME		:=	microshell

# BUILTIN_DIR	:=	src/builtin/
# ENV_DIR		:=	src/env/
# EXEC_DIR	:=	src/exec/
# EXPANDER_DIR	:=	src/expander/
# LEXER_DIR	:=	src/lexer/

LIST_SRCS	:=	minishell.c \
				$(wildcard $(BUILTIN_DIR)*.c) \
				$(wildcard $(ENV_DIR)*.c) \
				$(wildcard $(EXEC_DIR)*.c) \
				$(wildcard $(EXPANDER_DIR)*.c) \
				$(wildcard $(LEXER_DIR)*.c)

SRC_DIRS	:=	src/ src/builtin/ src/env/ src/lexer/ src/exec/ src/expander/ 
OBJ_DIR		:=	obj/
INC_DIR		:=	inc/

SRCS		:=	minishell.c \
				echo.c cd.c env.c exit.c export.c pwd.c unset.c \
				command_executor.c  env_lst_to_array.c util.c \
				lexer.c  lexer_helper.c  lexer_util.c \
				expander.c  expander_helper.c  expander_util.c \
				env_lst.c\
OBJS		:=	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
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

$(OBJ_DIR)%.o: $(SRC_DIRS)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) $(LDFAGS) -c $< -o $@
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
