CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

SERVER      = server
CLIENT      = client
SERVER_SRC  = server.c
CLIENT_SRC  = client.c
HEADER      = minitalk.h

BONUS_DIR   = bonus/
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
SERVER_B_SRC = $(BONUS_DIR)server_bonus.c
CLIENT_B_SRC = $(BONUS_DIR)client_bonus.c
HEADER_BONUS = $(BONUS_DIR)minitalk_bonus.h

all: $(SERVER) $(CLIENT)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER): $(SERVER_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $<

$(CLIENT): $(CLIENT_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $<

$(SERVER_BONUS): $(SERVER_B_SRC) $(HEADER_BONUS)
	$(CC) $(CFLAGS) -o $@ $<

$(CLIENT_BONUS): $(CLIENT_B_SRC) $(HEADER_BONUS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re