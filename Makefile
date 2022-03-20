# Generic makefile for small C-projects
# Run make dirs to setup project

SHELL := /bin/bash

# Compiler stuff
CC = gcc
CFLAGS = -g -Wall

# Directories
SRCDIR = src
OBJDIR = obj
BINDIR = bin

# Add directories for project here:
DIRS = $(SRCDIR) $(OBJDIR) $(BINDIR)

# List of source og object files
SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

# Name of program
PRGNAME = main

.PHONY: all
all: $(BINDIR)/$(PRGNAME)

# Compile to object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c dirs
	@echo "Creating object files"
	$(CC) $(CFLAGS) -c $< -o $@

# Compile to binary file
$(BINDIR)/$(PRGNAME): $(OBJS)
	@echo "Creating binary file"
	$(CC) $(CFLAGS) $(OBJS) -o $(BINDIR)/$(PRGNAME)

# Run binary file
.PHONY: run
run: $(BINDIR)/$(PRGNAME)
	@echo "Executing $(PRGNAME)"
	./$(BINDIR)/$(PRGNAME)

.PHONY: time
time: $(BINDIR)/$(PRGNAME)
	@echo "Timing $(PRGNAME)"
	time $(BINDIR)/$(PRGNAME)

# Create directories if they don't exist
.PHONY: dirs
dirs:
	@echo "Creating directories"
	@for d in $(DIRS) ; do \
		mkdir -p $$d ; \
	done

# Clean workspace
.PHONY: clean
clean:
	@echo "Cleaning workspace"
	$(RM) -r $(BINDIR) $(OBJDIR)

# Show variables for debugging
.PHONY: show
show:
	@echo 'CC          :' $(CC)
	@echo 'CFLAGS      :' $(CFLAGS)
	@echo 'SRCDIR      :' $(SRCDIR)
	@echo 'OBJDIR      :' $(OBJDIR)
	@echo 'BINDIR      :' $(BINDIR)
	@echo 'SRCS        :' $(SRCS)
	@echo 'OBJS        :' $(OBJS)
	@echo 'PRGNAME     :' $(PRGNAME)