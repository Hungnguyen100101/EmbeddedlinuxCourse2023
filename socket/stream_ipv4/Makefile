.PHONY: all clean

CC := gcc
CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin

all:
	$(CC) $(CUR_DIR)/server.c -o $(BIN_DIR)/server
	$(CC) $(CUR_DIR)/client.c -o $(BIN_DIR)/client
clean:
	rm -rf $(BIN_DIR)/*