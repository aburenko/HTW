# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/aburenko/soft/clion-2020.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/aburenko/soft/clion-2020.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pl0Compiler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pl0Compiler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pl0Compiler.dir/flags.make

CMakeFiles/pl0Compiler.dir/codegen.c.o: CMakeFiles/pl0Compiler.dir/flags.make
CMakeFiles/pl0Compiler.dir/codegen.c.o: ../codegen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/pl0Compiler.dir/codegen.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pl0Compiler.dir/codegen.c.o   -c /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/codegen.c

CMakeFiles/pl0Compiler.dir/codegen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pl0Compiler.dir/codegen.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/codegen.c > CMakeFiles/pl0Compiler.dir/codegen.c.i

CMakeFiles/pl0Compiler.dir/codegen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pl0Compiler.dir/codegen.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/codegen.c -o CMakeFiles/pl0Compiler.dir/codegen.c.s

CMakeFiles/pl0Compiler.dir/lex.c.o: CMakeFiles/pl0Compiler.dir/flags.make
CMakeFiles/pl0Compiler.dir/lex.c.o: ../lex.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/pl0Compiler.dir/lex.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pl0Compiler.dir/lex.c.o   -c /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/lex.c

CMakeFiles/pl0Compiler.dir/lex.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pl0Compiler.dir/lex.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/lex.c > CMakeFiles/pl0Compiler.dir/lex.c.i

CMakeFiles/pl0Compiler.dir/lex.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pl0Compiler.dir/lex.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/lex.c -o CMakeFiles/pl0Compiler.dir/lex.c.s

CMakeFiles/pl0Compiler.dir/parser.c.o: CMakeFiles/pl0Compiler.dir/flags.make
CMakeFiles/pl0Compiler.dir/parser.c.o: ../parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/pl0Compiler.dir/parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pl0Compiler.dir/parser.c.o   -c /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/parser.c

CMakeFiles/pl0Compiler.dir/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pl0Compiler.dir/parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/parser.c > CMakeFiles/pl0Compiler.dir/parser.c.i

CMakeFiles/pl0Compiler.dir/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pl0Compiler.dir/parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/parser.c -o CMakeFiles/pl0Compiler.dir/parser.c.s

CMakeFiles/pl0Compiler.dir/namelist.c.o: CMakeFiles/pl0Compiler.dir/flags.make
CMakeFiles/pl0Compiler.dir/namelist.c.o: ../namelist.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/pl0Compiler.dir/namelist.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pl0Compiler.dir/namelist.c.o   -c /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/namelist.c

CMakeFiles/pl0Compiler.dir/namelist.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pl0Compiler.dir/namelist.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/namelist.c > CMakeFiles/pl0Compiler.dir/namelist.c.i

CMakeFiles/pl0Compiler.dir/namelist.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pl0Compiler.dir/namelist.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/namelist.c -o CMakeFiles/pl0Compiler.dir/namelist.c.s

CMakeFiles/pl0Compiler.dir/main.c.o: CMakeFiles/pl0Compiler.dir/flags.make
CMakeFiles/pl0Compiler.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/pl0Compiler.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pl0Compiler.dir/main.c.o   -c /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/main.c

CMakeFiles/pl0Compiler.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pl0Compiler.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/main.c > CMakeFiles/pl0Compiler.dir/main.c.i

CMakeFiles/pl0Compiler.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pl0Compiler.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/main.c -o CMakeFiles/pl0Compiler.dir/main.c.s

# Object files for target pl0Compiler
pl0Compiler_OBJECTS = \
"CMakeFiles/pl0Compiler.dir/codegen.c.o" \
"CMakeFiles/pl0Compiler.dir/lex.c.o" \
"CMakeFiles/pl0Compiler.dir/parser.c.o" \
"CMakeFiles/pl0Compiler.dir/namelist.c.o" \
"CMakeFiles/pl0Compiler.dir/main.c.o"

# External object files for target pl0Compiler
pl0Compiler_EXTERNAL_OBJECTS =

pl0Compiler: CMakeFiles/pl0Compiler.dir/codegen.c.o
pl0Compiler: CMakeFiles/pl0Compiler.dir/lex.c.o
pl0Compiler: CMakeFiles/pl0Compiler.dir/parser.c.o
pl0Compiler: CMakeFiles/pl0Compiler.dir/namelist.c.o
pl0Compiler: CMakeFiles/pl0Compiler.dir/main.c.o
pl0Compiler: CMakeFiles/pl0Compiler.dir/build.make
pl0Compiler: CMakeFiles/pl0Compiler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable pl0Compiler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pl0Compiler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pl0Compiler.dir/build: pl0Compiler

.PHONY : CMakeFiles/pl0Compiler.dir/build

CMakeFiles/pl0Compiler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pl0Compiler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pl0Compiler.dir/clean

CMakeFiles/pl0Compiler.dir/depend:
	cd /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug /home/aburenko/edu/HTW/Compiler_Interpreter/pl0Compiler/cmake-build-debug/CMakeFiles/pl0Compiler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pl0Compiler.dir/depend

