NAME        := microshell

OBJ_DIR     := obj/
INC_DIR     := inc/

# ソースファイルとオブジェクトファイルの設定
BUILTIN_DIR := src/builtin/
BUILTIN_SRCS := cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUILTIN := $(addprefix $(OBJ_DIR)builtin/, $(BUILTIN_SRCS:.c=.o))

ENV_DIR := src/env/
ENV_SRCS := env_lst.c
ENV := $(addprefix $(OBJ_DIR)env/, $(ENV_SRCS:.c=.o))

EXEC_DIR := src/exec/
EXEC_SRCS := command_executor.c env_lst_to_array.c util.c helper.c
EXEC := $(addprefix $(OBJ_DIR)exec/, $(EXEC_SRCS:.c=.o))

EXPANDER_DIR := src/expander/
EXPANDER_SRCS := expander_helper.c expander_util.c expander.c
EXPANDER := $(addprefix $(OBJ_DIR)expander/, $(EXPANDER_SRCS:.c=.o))

LEXER_DIR := src/lexer/
LEXER_SRCS := lexer_helper.c lexer_util.c lexer.c
LEXER := $(addprefix $(OBJ_DIR)lexer/, $(LEXER_SRCS:.c=.o))

SIGNAL_DIR := src/signal/
SIGNAL_SRC := signal.c
SIGNAL := $(addprefix $(OBJ_DIR)signal/, $(SIGNAL_SRC:.c=.o))

MINISHELL_DIR := src/
MINISHELL_SRC := minishell.c utils.c
MINISHELL := $(addprefix $(OBJ_DIR), $(MINISHELL_SRC:.c=.o))

# オブジェクトファイルをまとめる
OBJS := $(BUILTIN) $(ENV) $(EXEC) $(EXPANDER) $(LEXER) $(SIGNAL) $(MINISHELL)

LIBFT_DIR := src/libft
LIBFT := $(LIBFT_DIR)/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror
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

# ディレクトリ作成
DIRS := $(OBJ_DIR) $(OBJ_DIR)builtin $(OBJ_DIR)env $(OBJ_DIR)exec $(OBJ_DIR)expander $(OBJ_DIR)lexer $(OBJ_DIR)signal

all: Makefile $(DIRS) $(NAME)

# 必要なディレクトリを作成
$(DIRS):
	@mkdir -p $@

# ソースファイルからオブジェクトファイルを生成
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

$(OBJ_DIR)%.o: $(LEXER_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR)%.o: $(SIGNAL_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(OBJ_DIR)%.o: $(MINISHELL_DIR)%.c
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

# バイナリ生成ルール
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(IFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME) $(LFLAGS)
	@printf "$(ERASE)$(GREEN)$@ made\n$(END)"

# libftのビルドルール
$(LIBFT):
	@$(MAKE) bonus -C $(LIBFT_DIR)

# クリーンアップルール
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(PINK)remove obj dir\n$(END)"

# フルクリーンアップルール
fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "$(PINK)remove lib.a\n$(END)"

# リビルドルール
re: fclean all

.PHONY: all clean fclean re
