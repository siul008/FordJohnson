NAME = PmergeMe

SRCS = main.cpp PmergeMe.cpp

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g

CXX = c++

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)
	

fclean: clean
	rm -rf $(NAME)

re: fclean all

