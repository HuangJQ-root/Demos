# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /snap/cmake/1463/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1463/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cheeco/Demos/vbslite_trans/lesson2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cheeco/Demos/vbslite_trans/lesson2/build

# Include any dependencies generated for this target.
include CMakeFiles/app1_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/app1_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/app1_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/app1_test.dir/flags.make

generated/HelloWorldPlugin.h: /home/cheeco/Demos/vbslite_trans/lesson2/idl/HelloWorld.idl
generated/HelloWorldPlugin.h: /home/cheeco/Demos/vbslite_trans/lesson2/tools/mvbs-idl/mvbs-idl.py
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/cheeco/Demos/vbslite_trans/lesson2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating IDL code"
	/snap/cmake/1463/bin/cmake -E make_directory /home/cheeco/Demos/vbslite_trans/lesson2/build/generated
	python -B /home/cheeco/Demos/vbslite_trans/lesson2/tools/mvbs-idl/mvbs-idl.py -i /home/cheeco/Demos/vbslite_trans/lesson2/idl/HelloWorld.idl -d /home/cheeco/Demos/vbslite_trans/lesson2/build/generated -t TEST

generated/HelloWorldPlugin.c: generated/HelloWorldPlugin.h
	@$(CMAKE_COMMAND) -E touch_nocreate generated/HelloWorldPlugin.c

generated/app1_config.c: /home/cheeco/Demos/vbslite_trans/lesson2/tools/mvbs-cfg/mvbs-config.py
generated/app1_config.c: /home/cheeco/Demos/vbslite_trans/lesson2/multi_topic_test/app1/app1_config.xml
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/cheeco/Demos/vbslite_trans/lesson2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating app_config.c from app1_config.xml"
	/snap/cmake/1463/bin/cmake -E make_directory /home/cheeco/Demos/vbslite_trans/lesson2/build/generated
	python -B /home/cheeco/Demos/vbslite_trans/lesson2/tools/mvbs-cfg/mvbs-config.py -s /home/cheeco/Demos/vbslite_trans/lesson2/multi_topic_test/app1/app1_config.xml -t /home/cheeco/Demos/vbslite_trans/lesson2/build/generated/app1_config.c

CMakeFiles/app1_test.dir/codegen:
.PHONY : CMakeFiles/app1_test.dir/codegen

CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.o: CMakeFiles/app1_test.dir/flags.make
CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.o: /home/cheeco/Demos/vbslite_trans/lesson2/multi_topic_test/app1/app1_test.c
CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.o: CMakeFiles/app1_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/cheeco/Demos/vbslite_trans/lesson2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.o"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.o -MF CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.o.d -o CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.o -c /home/cheeco/Demos/vbslite_trans/lesson2/multi_topic_test/app1/app1_test.c

CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.i"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheeco/Demos/vbslite_trans/lesson2/multi_topic_test/app1/app1_test.c > CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.i

CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.s"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheeco/Demos/vbslite_trans/lesson2/multi_topic_test/app1/app1_test.c -o CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.s

CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.o: CMakeFiles/app1_test.dir/flags.make
CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.o: generated/HelloWorldPlugin.c
CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.o: CMakeFiles/app1_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/cheeco/Demos/vbslite_trans/lesson2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.o"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.o -MF CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.o.d -o CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.o -c /home/cheeco/Demos/vbslite_trans/lesson2/build/generated/HelloWorldPlugin.c

CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.i"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheeco/Demos/vbslite_trans/lesson2/build/generated/HelloWorldPlugin.c > CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.i

CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.s"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheeco/Demos/vbslite_trans/lesson2/build/generated/HelloWorldPlugin.c -o CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.s

CMakeFiles/app1_test.dir/generated/app1_config.c.o: CMakeFiles/app1_test.dir/flags.make
CMakeFiles/app1_test.dir/generated/app1_config.c.o: generated/app1_config.c
CMakeFiles/app1_test.dir/generated/app1_config.c.o: CMakeFiles/app1_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/cheeco/Demos/vbslite_trans/lesson2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/app1_test.dir/generated/app1_config.c.o"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/app1_test.dir/generated/app1_config.c.o -MF CMakeFiles/app1_test.dir/generated/app1_config.c.o.d -o CMakeFiles/app1_test.dir/generated/app1_config.c.o -c /home/cheeco/Demos/vbslite_trans/lesson2/build/generated/app1_config.c

CMakeFiles/app1_test.dir/generated/app1_config.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/app1_test.dir/generated/app1_config.c.i"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cheeco/Demos/vbslite_trans/lesson2/build/generated/app1_config.c > CMakeFiles/app1_test.dir/generated/app1_config.c.i

CMakeFiles/app1_test.dir/generated/app1_config.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/app1_test.dir/generated/app1_config.c.s"
	/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cheeco/Demos/vbslite_trans/lesson2/build/generated/app1_config.c -o CMakeFiles/app1_test.dir/generated/app1_config.c.s

# Object files for target app1_test
app1_test_OBJECTS = \
"CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.o" \
"CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.o" \
"CMakeFiles/app1_test.dir/generated/app1_config.c.o"

# External object files for target app1_test
app1_test_EXTERNAL_OBJECTS =

app1_test: CMakeFiles/app1_test.dir/multi_topic_test/app1/app1_test.c.o
app1_test: CMakeFiles/app1_test.dir/generated/HelloWorldPlugin.c.o
app1_test: CMakeFiles/app1_test.dir/generated/app1_config.c.o
app1_test: CMakeFiles/app1_test.dir/build.make
app1_test: mvbs/libmvbs.a
app1_test: mvbs/libmvbs_aux.a
app1_test: CMakeFiles/app1_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/cheeco/Demos/vbslite_trans/lesson2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable app1_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app1_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/app1_test.dir/build: app1_test
.PHONY : CMakeFiles/app1_test.dir/build

CMakeFiles/app1_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/app1_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/app1_test.dir/clean

CMakeFiles/app1_test.dir/depend: generated/HelloWorldPlugin.c
CMakeFiles/app1_test.dir/depend: generated/HelloWorldPlugin.h
CMakeFiles/app1_test.dir/depend: generated/app1_config.c
	cd /home/cheeco/Demos/vbslite_trans/lesson2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cheeco/Demos/vbslite_trans/lesson2 /home/cheeco/Demos/vbslite_trans/lesson2 /home/cheeco/Demos/vbslite_trans/lesson2/build /home/cheeco/Demos/vbslite_trans/lesson2/build /home/cheeco/Demos/vbslite_trans/lesson2/build/CMakeFiles/app1_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/app1_test.dir/depend

