CC = mpicc
CFLAGS ?= -std=c2x -Wall -Wextra -g -O2
CPPFLAGS ?= -Iinclude
LDFLAGS ?=
LDLIBS ?=

TARGET := main
SRC := main.c \
       src/wrapped_mpi.c \
       src/coordinator.c \
       src/client.c \
	   src/runner.c \
	   src/protocol.c \
       src/message.c

BUILD_DIR := build
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

MPIEXEC ?= mpiexec
NP ?= 5
ARGS ?=

MPIEXEC ?= mpiexec
NP ?= 5
ARGS ?=

.PHONY: all run clean rebuild

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)


$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

run: $(TARGET)
	$(MPIEXEC) --oversubscribe -n $(NP) ./$(TARGET) $(ARGS)

clean:
	$(RM) -r $(BUILD_DIR) $(TARGET)

rebuild: clean all

-include $(DEP)
