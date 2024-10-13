# Output binary
BIN = genpasswd

# Put all auto generated stuff to this build dir.
BUILD_DIR = ./build

SOURCE_DIR = src

# List of all the source files.
SOURCE = \
	main.c \

INCLUDES = \
	src \

CC = clang

CC_FLAGS = -march=native -Wall -Werror -Wextra -Wfloat-equal -Wswitch-default \
	   -Wswitch-enum -Wno-unused-parameter -Wno-implicit-fallthrough -g \
	   -pthread -O3 -fsigned-char -flto=thin -pipe -fsanitize=scudo
LNK_FLAGS = -fuse-ld=lld -lsodium -ltcl -Wl,-z,nodlopen -Wl,-z,noexecstack \
	    -Wl,-z,relro -Wl,-z,now \
	    -Wl,--as-needed -Wl,--no-copy-dt-needed-entries

# All .o files go to build dir.
C_OBJ = $(SOURCE:%.c=$(BUILD_DIR)/%.o)
OBJ = $(C_OBJ)


# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)
# Include paths with a -I in front of them
INCLUDEPATHS = $(INCLUDES:%= -I %)

# Actual target of the binary - depends on all .o files.
$(BIN) : PreBuild $(OBJ)
	echo Linking...
	# Create build directories - same structure as sources.
	-mkdir -p $(@D) 2>/dev/null
	# Just link all the object files.
	$(CC) $(OBJ) $(LNK_FLAGS) -o $(BIN)

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	echo Compiling $(notdir $<)
	-mkdir -p $(@D) 2>/dev/null
	# The -MMD flags additionaly creates a .d file with
	# the same name as the .o file.
	$(CC) $(CC_FLAGS) $(INCLUDEPATHS) -MMD -c $< -o $@


.PHONY : clean
clean:
	# This should remove all generated files.
	-rm -r $(BUILD_DIR)
	-rm $(BIN)

.PHONY: PreBuild
PreBuild:
	# This is run at the start of the build
