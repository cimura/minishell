NAME        :=  microshell

BUILTIN_DIR :=  src/builtin/
ENV_DIR     :=  src/env/
EXEC_DIR    :=  src/exec/
EXPANDER_DIR    :=  src/expander/
LEXER_DIR   :=  src/lexer/

LIST_SRCS   :=  $(wildcard $(BUILTIN_DIR)*.c) \
                $(wildcard $(ENV_DIR)*.c) \
                $(wildcard $(EXEC_DIR)*.c) \
                $(wildcard $(EXPANDER_DIR)*.c) \
                $(wildcard $(LEXER_DIR)*.c) \
				src/minishell.c

SRC_DIRS    :=  src/ src/builtin/ src/env/ src/lexer/ src/exec/ src/expander/ 
OBJ_DIR     :=  obj/
INC_DIR     :=  inc/

SRCS        :=  $(addsuffix $(SRC_DIRS:%), $(LIST_SRCS))
OBJS		:=	$(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))
LIBFT_DIR   :=  src/libft
LIBFT       :=  $(LIBFT_DIR)/libft.a

CC          :=  cc
CFLAGS      :=  -Wall -Wextra -Werror
#DEBUG_FLAGS    :=  -g -fsanitize=address
LDFLAGS     :=  -lreadline
IFLAGS      :=  -I$(LIBFT_DIR)/include -I$(INC_DIR)
LFLAGS		:=	-L$(LIBFT_DIR) -lft

ERASE		:=	\033[2K\r
PINK		:=	\033[35m
BLUE		:=	\033[34m
GREEN		:=	\033[32m
END			:=	\033[0m

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJS): $(LIST_SRCS)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "$(ERASE)$(BLUE) > Compilation :$(END) $<"

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(IFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME) $(LFLAGS)
	@printf "$(ERASE)$(GREEN)$@ made\n$(END)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

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
