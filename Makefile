
# Copyright 2014  Thomas E. Vaughan
#
# This file is part of Ulam.
#
# Ulam is free software: You can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either Version 3 of the License, or (at your option) any later
# version.
#
# Ulam is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# Ulam.  If not, see <http://www.gnu.org/licenses/>.

# --- See <http://mad-scientist.net/make/autodep.html>. ---
ALL_SRC   = $(wildcard *.cpp)
CPPFLAGS += -MD
DEPDIR    = .dep
# ---------------------------------------------------------

CC       = g++
CXXFLAGS = -std=c++11 -Wall -O2
LDLIBS   = -lm
PROGRAM  = ulam

# --- See <http://mad-scientist.net/make/autodep.html>. ---
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
# ---------------------------------------------------------

.PHONY : all clean dox

all: tags example-output.png

tags : $(PROGRAM)
	ctags -R

$(PROGRAM) : $(ALL_SRC:.cpp=.o)

example-output.png: example-output.ppm
	convert $< $@

example-output.ppm: $(PROGRAM)
	./$(PROGRAM) -s 512 > $@

clean:
	@rm -fv $(PROGRAM)
	@rm -fv *.o
	@rm -fv tags
	@rm -fv example-output.ppm

# --- See <http://mad-scientist.net/make/autodep.html>. ---
# The following must be the last line.
-include $(ALL_SRC:%.cpp=$(DEPDIR)/%.P)
