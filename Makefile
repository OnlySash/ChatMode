CC = mpicc
CFLAGS ?= -std=c2x -Wall -Wextra -g -O2
CPPFLAGS ?= -Iinclude
LDFLAGS ?=
LDLIBS ?=

TARGET := main
SRC := main.c \
       src/wrapper_mpi.c \
       src/coordinator.c \
       src/lane.c \
       src/vehicle.c

BUILD_DIR := build
OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:.o=.d)

MPIEXEC ?= mpiexec
NP ?= 5
ARGS ?=

.PHONY: all run clean rebuild
