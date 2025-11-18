NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iinclude
THREADS = -pthread

SRC_DIR = src
OBJ_DIR = obj

RM = rm -f

SRC = main.c \
	  parser.c \
	  init.c \
	  helper.c \
	  cleanup.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(THREADS)
	@echo "✅ $(NAME) compiled successfully.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "🧹 Object files cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo "🧹 All files cleaned"

re: fclean all

.PHONY: all clean fclean re
