# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/VijayWorkSpace/Assignments/Assignments/Assignment_3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/build

# Include any dependencies generated for this target.
include CMakeFiles/test_sender.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_sender.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_sender.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_sender.dir/flags.make

CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.o: CMakeFiles/test_sender.dir/flags.make
CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.o: /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/sender/tests/test_sender.cpp
CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.o: CMakeFiles/test_sender.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/VijayWorkSpace/Assignments/Assignments/Assignment_3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.o -MF CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.o.d -o CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.o -c /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/sender/tests/test_sender.cpp

CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/sender/tests/test_sender.cpp > CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.i

CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/sender/tests/test_sender.cpp -o CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.s

CMakeFiles/test_sender.dir/sender/src/sender.cpp.o: CMakeFiles/test_sender.dir/flags.make
CMakeFiles/test_sender.dir/sender/src/sender.cpp.o: /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/sender/src/sender.cpp
CMakeFiles/test_sender.dir/sender/src/sender.cpp.o: CMakeFiles/test_sender.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/VijayWorkSpace/Assignments/Assignments/Assignment_3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_sender.dir/sender/src/sender.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_sender.dir/sender/src/sender.cpp.o -MF CMakeFiles/test_sender.dir/sender/src/sender.cpp.o.d -o CMakeFiles/test_sender.dir/sender/src/sender.cpp.o -c /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/sender/src/sender.cpp

CMakeFiles/test_sender.dir/sender/src/sender.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_sender.dir/sender/src/sender.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/sender/src/sender.cpp > CMakeFiles/test_sender.dir/sender/src/sender.cpp.i

CMakeFiles/test_sender.dir/sender/src/sender.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_sender.dir/sender/src/sender.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/sender/src/sender.cpp -o CMakeFiles/test_sender.dir/sender/src/sender.cpp.s

CMakeFiles/test_sender.dir/common/src/config.cpp.o: CMakeFiles/test_sender.dir/flags.make
CMakeFiles/test_sender.dir/common/src/config.cpp.o: /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/common/src/config.cpp
CMakeFiles/test_sender.dir/common/src/config.cpp.o: CMakeFiles/test_sender.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/root/VijayWorkSpace/Assignments/Assignments/Assignment_3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test_sender.dir/common/src/config.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_sender.dir/common/src/config.cpp.o -MF CMakeFiles/test_sender.dir/common/src/config.cpp.o.d -o CMakeFiles/test_sender.dir/common/src/config.cpp.o -c /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/common/src/config.cpp

CMakeFiles/test_sender.dir/common/src/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_sender.dir/common/src/config.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/common/src/config.cpp > CMakeFiles/test_sender.dir/common/src/config.cpp.i

CMakeFiles/test_sender.dir/common/src/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_sender.dir/common/src/config.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/common/src/config.cpp -o CMakeFiles/test_sender.dir/common/src/config.cpp.s

# Object files for target test_sender
test_sender_OBJECTS = \
"CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.o" \
"CMakeFiles/test_sender.dir/sender/src/sender.cpp.o" \
"CMakeFiles/test_sender.dir/common/src/config.cpp.o"

# External object files for target test_sender
test_sender_EXTERNAL_OBJECTS =

test_sender: CMakeFiles/test_sender.dir/sender/tests/test_sender.cpp.o
test_sender: CMakeFiles/test_sender.dir/sender/src/sender.cpp.o
test_sender: CMakeFiles/test_sender.dir/common/src/config.cpp.o
test_sender: CMakeFiles/test_sender.dir/build.make
test_sender: /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/lib/libgtest.a
test_sender: /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/lib/libgtest_main.a
test_sender: /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/lib/libspdlog.a
test_sender: liblogger.a
test_sender: CMakeFiles/test_sender.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/root/VijayWorkSpace/Assignments/Assignments/Assignment_3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable test_sender"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_sender.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_sender.dir/build: test_sender
.PHONY : CMakeFiles/test_sender.dir/build

CMakeFiles/test_sender.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_sender.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_sender.dir/clean

CMakeFiles/test_sender.dir/depend:
	cd /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/VijayWorkSpace/Assignments/Assignments/Assignment_3 /root/VijayWorkSpace/Assignments/Assignments/Assignment_3 /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/build /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/build /root/VijayWorkSpace/Assignments/Assignments/Assignment_3/build/CMakeFiles/test_sender.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/test_sender.dir/depend

