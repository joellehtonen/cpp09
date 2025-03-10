NAME	=	PmergeMe
CC		=	c++
FLAGS	=	-Wall -Wextra -Werror -std=c++20
SRCS	=	sources/main.cpp \
			sources/PmergeMe.cpp \
			sources/utils.cpp \
			sources/sort.cpp
HEADER  =	includes/PmergeMe.hpp \
			includes/utils.hpp
OBJS	=	$(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re