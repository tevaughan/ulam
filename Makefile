
# See <http://mad-scientist.net/make/autodep.html>.
ALL_SRC   = $(wildcard *.cpp)
CPPFLAGS += -MD
DEPDIR    = .dep

CC = g++
CXXFLAGS = -std=c++11 -Wall $(shell pkg-config --cflags hdf5)

# The pkg-config program emits the name of the underlying HDF5 C library, but I
# don't know how to get pkg-config to emit the library needed for C++.  So I
# have explicitly written it in at the beginning of LDLIBS.
LDLIBS = -lhdf5_cpp $(shell pkg-config --libs hdf5)

PROGRAM = ulam

# See <http://mad-scientist.net/make/autodep.html>.
%.o : %.cpp
	g++ -ggdb $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
	@mkdir -p $(DEPDIR)
	@cp $*.d $(DEPDIR)/$*.P
	@sed                   \
	    -e 's/#.*//'       \
	    -e 's/^[^:]*: *//' \
	    -e 's/ *\\$$//'    \
	    -e '/^$$/ d'       \
	    -e 's/$$/ :/'      \
	    < $*.d >> $(DEPDIR)/$*.P
	@rm -f $*.d

.PHONY : all clean dox

all: tags

tags : $(PROGRAM)
	ctags -R

$(PROGRAM) : $(ALL_SRC:.cpp=.o)

clean:
	@rm -fv $(PROGRAM)
	@rm -fv *.o
	@rm -fv tags

# See <http://mad-scientist.net/make/autodep.html>.
# The following must be the last line.
-include $(ALL_SRC:%.cpp=$(DEPDIR)/%.P)
