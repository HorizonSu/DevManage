CC := gcc
CFLAGS := -Wall -O2
RM := @-rm -f
SRC := $(wildcard *.c)
OBJ := DevManage
 
$(OBJ):$(SRC)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY:clean
clean:
	$(RM) $(OBJ)
