NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude

SRC_DIR = src
OBJ_DIR = obj

RM = rm -f

SRC = ${SRC_DIR}/main.c ${SRC_DIR}/utils.c ${SRC_DIR}/helper.c

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW) compiling: $<$(RESET)"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(YELLOW)✅ Object files cleaned."

fclean: clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)✅ All files cleaned."

re: fclean all

.PHONY: all clean fclean re bonus