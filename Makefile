# Compiler and flags, set once and used everywhere
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wshadow -g -MMD -MP

# Shared code: every reusable .cpp goes in this list, and only this list
LIB_OBJS = students.o gradebook.o account.o savings.o money.o shapes.o bank.o parse.o
LIB      = libpractice.a

# Programs: every *_test.cpp is found automatically, plus the two named programs
PROGRAMS = grades.exe report.exe $(patsubst %.cpp,%.exe,$(wildcard *_test.cpp))

APPS = bank_app.exe

all: $(PROGRAMS) $(APPS)

# Bundle the shared objects into one static library
$(LIB): $(LIB_OBJS)
	ar rcs $@ $^

# Any program = its own .o + the library; the linker takes only the pieces it needs
%.exe: %.o $(LIB)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each .cpp into a .o; header dependencies come from the generated .d files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run every program, one after another
RUN_TARGETS = $(addprefix run-,$(PROGRAMS))

run: $(RUN_TARGETS)

$(RUN_TARGETS): run-%: %
	./$<

# Delete everything that was built
clean:
	del /Q *.o *.d *.a *.exe

.PHONY: all run clean $(RUN_TARGETS)

# Keep the .o files: make would otherwise delete them as 'intermediate' files
.SECONDARY:

# Pull in the dependency files that g++ generated (if any exist yet)
-include $(wildcard *.d)
