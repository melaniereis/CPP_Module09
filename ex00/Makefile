# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/24 15:02:25 by meferraz          #+#    #+#              #
#    Updated: 2025/05/27 15:17:50 by meferraz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = easyfind

#------------------------------------------------------------------------------#
#                             NAMES AND PATHS                                  #
#------------------------------------------------------------------------------#

BUILD_PATH  = .build
SRC_PATH    = src
INC_PATH    = inc

HEADERS     = $(addprefix $(INC_PATH)/, ansi.h \
										easyfind.hpp\
				)
SRCS        = $(addprefix $(SRC_PATH)/, main.cpp \
				)
OBJS        = $(SRCS:$(SRC_PATH)/%.cpp=$(BUILD_PATH)/%.o)

#------------------------------------------------------------------------------#
#                             FLAGS & COMMANDS                                 #
#------------------------------------------------------------------------------#

CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98 -g
RM          = rm -fr
MKDIR       = mkdir -p
INCLUDES    = -I$(INC_PATH)

# Valgrind options
V_ARGS      = --leak-check=full --show-leak-kinds=all --track-origins=yes

#------------------------------------------------------------------------------#
#                             COLORS & EMOJIS                                  #
#------------------------------------------------------------------------------#

GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

ROCKET = 🚀
LAPTOP = 💻
BROOM = 🧹
DONE = ✅
BUG = 🐞
TARGET = 🎯
REBUILD = 🔄

#------------------------------------------------------------------------------#
#                                   RULES                                      #
#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS) | $(BUILD_PATH)
	@echo "$(BLUE)$(ROCKET) Linking objects to create $(NAME)... $(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $@
	@echo "$(GREEN)$(DONE) Build complete! $(RESET)"

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp $(HEADERS) | $(BUILD_PATH)
	@$(MKDIR) $(@D)
	@echo "$(YELLOW)$(LAPTOP) Compiling $<... $(RESET)"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_PATH):
	@$(MKDIR) $(BUILD_PATH)

val: $(NAME)
	@echo "$(BLUE)$(BUG) Running valgrind on $(NAME)... $(RESET)"
	@valgrind $(V_ARGS) ./$(NAME)

vgdb: $(NAME)
	@echo "$(BLUE)$(BUG) Running valgrind with debug on $(NAME)... $(RESET)"
	@valgrind --vgdb-error=0 $(V_ARGS) ./$(NAME)

gdb: all
	@echo "$(BLUE)$(BUG) Starting GDB for $(NAME)... $(RESET)"
	@gdb -tui -q ./$(NAME) -x .gdbinit

test: all
	@echo "$(BLUE)$(TARGET) Testing $(NAME)... $(RESET)"
	@./$(NAME)

clean:
	@echo "$(RED)$(BROOM) Cleaning object files... $(RESET)"
	@$(RM) $(OBJS) $(BUILD_PATH)

fclean: clean
	@echo "$(RED)$(BROOM) Removing executable and build directory... $(RESET)"
	@$(RM) $(NAME)

re: fclean all
	@echo "$(BLUE)$(REBUILD) Rebuilding $(NAME)... $(RESET)"

.PHONY: all clean fclean re val vgdb gdb test
