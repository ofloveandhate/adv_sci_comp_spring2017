### some good resources:
# https://www.gnu.org/software/make/manual/make.html
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html

#choose some options.  by default, compiler optimization is turned off
OPT:= -g -std=c++11


###
# machine-specific configuration setup
###
INC:=$(INC) -I./include
CXX:= g++
INSTALLPATH:=$(HOME)/bin



###
# end machine specific configuration
###


# list additional libs here
LIBS:=


#a few last definitions
ARGS:= $(OPT) $(INC)


CPPFILES := $(wildcard src/*.cpp)
OBJFILES := $(addprefix obj/,$(notdir $(CPPFILES:.cpp=.o)))

###
#BEGIN MAKE RULES
###

#all comes first, so is the default rule when you `make'
all : my_program

my_program : $(OBJFILES)
	$(CXX) $(ARGS) -o my_program $(OBJFILES) $(LIBS)

#simply copy the executables to the installpath
install : all
	cp my_program $(INSTALLPATH)

# a general rule for generating object files.
obj/%.o : src/%.cpp
	@mkdir -p obj
	$(CXX) $(CC_FLAGS) $(ARGS) -c -o $@ $<

clean :
	rm -f $(OBJFILES) my_program

CC_FLAGS += -MMD
-include $(OBJFILES:.o=.d)
