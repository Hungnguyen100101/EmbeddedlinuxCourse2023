.PHONY: all_shared all_static clean

LIB_SHARED_NAME := test_shared
LIB_STATIC_NAME := test_static
CUR_DIR:= .
BIN_DIR:= $(CUR_DIR)/bin
INC_DIR:= $(CUR_DIR)/inc
SRC_DIR:= $(CUR_DIR)/src
OBJ_DIR:= $(CUR_DIR)/ojbs

LIB_DIR:= $(CUR_DIR)/libs
LIB_SHARED:= $(LIB_DIR)/shared
LIB_STATIC:= $(LIB_DIR)/static

INC_FLAGS:= -I$(INC_DIR)

CC:= gcc

mk_objs:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/calculate.c -o $(OBJ_DIR)/calculate_shared.o $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/mymath.c -o $(OBJ_DIR)/mymath_share.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/calculate.c -o $(OBJ_DIR)/calculate_static.o $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/mymath.c -o $(OBJ_DIR)/mymath_static.o $(INC_FLAGS)
mk_shared:
	$(CC) -shared $(OBJ_DIR)/calculate_shared.o $(OBJ_DIR)/mymath_share.o -o $(LIB_SHARED)/lib$(LIB_SHARED_NAME).so
mk_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_STATIC_NAME).a $(OBJ_DIR)/mymath_static.o $(OBJ_DIR)/calculate_static.o
install:
	cp -f $(LIB_SHARED)/lib$(LIB_SHARED_NAME).so /usr/lib
all_shared: mk_objs mk_shared install
	$(CC)  $(OBJ_DIR)/main.o -L$(LIB_SHARED) -l$(LIB_SHARED_NAME) -o $(BIN_DIR)/use-shared-library	
all_static: mk_objs mk_static 
	$(CC)   $(OBJ_DIR)/main.o  -L$(LIB_STATIC) -l$(LIB_STATIC_NAME) -o $(BIN_DIR)/statically-linked
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED)/*
	rm -rf $(LIB_STATIC)/*
	rm -rf $(BIN_DIR)/*

