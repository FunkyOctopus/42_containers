CC = c++
FTNAME = ft_containers
STDNAME = std_containers
FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = intramain.cpp
HEADERS = ./containers/*.hpp ./iterators/*.hpp ./utils/*.hpp

all: $(FTNAME) $(STDNAME)

$(FTNAME): $(SRC) $(HEADERS)
	@$(CC) $(FLAGS) $(SRC) -o $(FTNAME)

$(STDNAME): $(SRC) $(HEADERS)
	@$(CC) $(FLAGS) $(SRC) -o $(STDNAME) -DSTD

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(FTNAME)
	@rm -f $(STDNAME)

re: fclean all