NAME        := minishell

OBJ_DIR     := obj/
INC_DIR     := inc/

BUILTIN_DIR := src/builtin/
BUILTIN_SRCS := cd.c echo.c env.c exit.c export.c export_utils.c export_utils2.c pwd.c unset.c
BUILTIN := $(addprefix $(OBJ_DIR)builtin/, $(BUILTIN_SRCS:.c=.o))

ENV_DIR := src/env/
ENV_SRCS := create_env_lst.c env_lst_to_array.c env_lst_util.c
ENV := $(addprefix $(OBJ_DIR)env/, $(ENV_SRCS:.c=.o))

EXEC_DIR := src/exec/
EXEC_SRCS := commands.c command_executor_utils.c command_executor.c register_cmd_data.c redirect.c heredoc.c exec_and_bltin.c
EXEC := $(addprefix $(OBJ_DIR)exec/, $(EXEC_SRCS:.c=.o))

EXPANDER_DIR := src/expander/
EXPANDER_SRCS := expander.c expand_dollar.c expand_dollar_utils.c expand_quotes.c
EXPANDER := $(addprefix $(OBJ_DIR)expander/, $(EXPANDER_SRCS:.c=.o))

PARSER_DIR := src/parser/
PARSER_SRCS := create_command_list.c parser_utils.c parser.c
PARSER := $(addprefix $(OBJ_DIR)parser/, $(PARSER_SRCS:.c=.o))

SIGNAL_DIR := src/signal/
SIGNAL_SRC := signal.c
SIGNAL := $(addprefix $(OBJ_DIR)signal/, $(SIGNAL_SRC:.c=.o))

SYNTAX_DIR := src/syntax/
SYNTAX_SRC := syntax_utils.c check_syntax.c
SYNTAX := $(addprefix $(OBJ_DIR)syntax/, $(SYNTAX_SRC:.c=.o))

MINISHELL_DIR := src/
MINISHELL_SRC := main.c utils.c utils2.c
MINISHELL := $(addprefix $(OBJ_DIR), $(MINISHELL_SRC:.c=.o))

OBJS := $(BUILTIN) $(ENV) $(EXEC) $(EXPANDER) $(PARSER) $(SIGNAL) $(SYNTAX) $(MINISHELL)

LIBFT_DIR := src/libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -g
#DEBUG_FLAGS := -g -fsanitize=address
LDFLAGS := -lreadline
IFLAGS := -I$(LIBFT_DIR)/include/ -I$(INC_DIR)
LFLAGS := -L$(LIBFT_DIR) -lft

ifeq ($(shell uname), Linux)
	LINK_LIB += -lbsd
endif
ifeq ($(shell uname), Darwin)
	# User have to run brew install readline before run make to build minishell
	CFLAGS += -I $(shell brew --prefix readline)/include
	LDFLAGS += -L$(shell brew --prefix readline)/lib
endif

ERASE := \033[2K\r
PINK := \033[35m
BLUE := \033[34m
GREEN := \033[32m
END := \033[0m

DIRS := $(OBJ_DIR) $(OBJ_DIR)builtin $(OBJ_DIR)env $(OBJ_DIR)exec \
		$(OBJ_DIR)expander $(OBJ_DIR)parser $(OBJ_DIR)signal $(OBJ_DIR)syntax

all: Makefile $(DIRS) $(NAME)

$(DIRS):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(BUILTIN_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR)%.o: $(ENV_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR)%.o: $(EXEC_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR)%.o: $(EXPANDER_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR)%.o: $(PARSER_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR)%.o: $(SIGNAL_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR)%.o: $(SYNTAX_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR)%.o: $(MINISHELL_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(IFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME) $(LFLAGS)
	@printf "$(ERASE)$(GREEN)$@ made\n$(END)"

$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(PINK)remove obj dir\n$(END)"

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "$(PINK)remove lib.a\n$(END)"

re: fclean all

.PHONY: all clean fclean re
