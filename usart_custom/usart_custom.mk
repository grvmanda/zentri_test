########################################

# The name of the project component
NAME := app_external_usart_custom

# The name of the project
PROJECT_NAME := usart_custom

# The platform of the target device
PLATFORM := AMW136

# Enable/disable automatic generation of static function prototypes in project source code
$(NAME)_AUTO_PROTOTYPE := 1

# Automatically include source files found in the project directory
$(NAME)_AUTO_SOURCES := 1

# List of files to include in the project build. Paths relative to the project's directory
$(NAME)_SOURCES := main.c

# List of regular expressions to use for including source files into the build
$(NAME)_AUTO_INCLUDE := 

# List of regular expressions to use for excluding source files into the build
$(NAME)_AUTO_EXCLUDE := 

# List of referenced libraries. This should contain library directory names relative to either the SDK or $(NAME)_LIBRARAY_PATHS
$(NAME)_COMPONENTS := 

# List of absolute paths to library directories
$(NAME)_LIBRARAY_PATHS := 

# Pre-processor symbols for this project component only (not referenced libraries)
$(NAME)_DEFINES := 

# Pre-processor symbols for the entire build (this project and all referenced libraries)
GLOBAL_DEFINES := 

# Includes file paths for project component only (not referenced libraries)
$(NAME)_INCLUDES := .

# Includes file paths for the entire build (this project and all referenced libraries)
GLOBAL_INCLUDES := 

# C compiler flags for project component only (not referenced libraries)
$(NAME)_CFLAGS := 

# C compiler flags for the entire build (this project and all referenced libraries)
GLOBAL_CFLAGS := 

# Assembler flags for project component only (not referenced libraries)
$(NAME)_ASMFLAGS := 

# Assembler flags for the entire build (this project and all referenced libraries)
GLOBAL_ASMFLAGS := 

# Linker flags for the entire build (this project and all referenced libraries)
GLOBAL_LDFLAGS := 

# Path to resource manifest .json file (path is relative to project directory)
$(NAME)_RESOURCE_MANIFEST := 

# Paths to app settings .ini files  (paths are relative to project directory)
$(NAME)_APP_SETTINGS := 

# Build targets to execute before the app is built.
# The targets should be defined in a file named: 'project_targets.mk' in the root directory of the project
PRE_BUILD_TARGETS := 

