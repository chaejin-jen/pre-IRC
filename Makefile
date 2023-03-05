NAME := ft_irc
CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
SANFLAG := # -g3 -fsanitize=address

INC := -I./include/

SRC := $(addprefix src/, main.cpp Socket.cpp)
OBJ := $(patsubst src%, obj%, $(SRC:.cpp=.o))

obj/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $<

all : obj $(NAME)

obj:
	@mkdir -p obj

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $^


clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
