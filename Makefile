CC = gcc

CFLAGS  = -Wall -Wextra -g -fsanitize=address,undefined

SRCS = src/minishell.c

TARGET = bin/minishell

# this is generic:
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	$(RM) $(TARGET)
