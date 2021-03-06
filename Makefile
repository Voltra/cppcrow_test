#### [Settings]
COMPILER = g++
CPP_VERSION = 11
OPTIMIZATION_LEVEL = 2
TARGET_BITS = 64

LIBS = tcmalloc fmt
ADD_FLAGS = -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free
BOOST_LIBS = system filesystem date_time# program_options
HEADER_FOLDERS = libs src
DEPENDENCIES = main.cpp
OUTPUT_NAME = app



#### [Computed] do not touch
LIB_LINK = $(addprefix -l,${LIBS})
BOOST_LINK = $(addprefix -lboost_,${BOOST_LIBS})
CUSTOMIZED_FLAGS = -std=c++$(CPP_VERSION) -O$(OPTIMIZATION_LEVEL) -m$(TARGET_BITS)
FLAGS = $(CUSTOMIZED_FLAGS) $(ADD_FLAGS)\
#-D_GLIBCXX_USE_CXX11_ABI=0

LINKER = $(BOOST_LINK) $(LIB_LINK) -pthread
RESOLVER = $(addprefix -I,${HEADER_FOLDERS})



#### [Makefile]
all: $(OUTPUT_NAME)

$(OUTPUT_NAME): $(DEPENDENCIES)
	$(COMPILER) $(FLAGS) $^ -o $@ $(RESOLVER) $(LINKER)
	
clean:
	rm $(OUTPUT_NAME)
