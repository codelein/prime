##########################################################################
#                                                                        #
# Prime, a program to calculate primes using the Sieve of Eratosthenes.  #
# Copyright (C) 2018 Philip Bowman.                                      #
#                                                                        #
# This program is free software: you can redistribute it and/or modify   #
# it under the terms of the GNU General Public License as published by   #
# the Free Software Foundation, either version 3 of the License, or      #
# (at your option) any later version.                                    #
#                                                                        #
# This program is distributed in the hope that it will be useful,        #
# but WITHOUT ANY WARRANTY; without even the implied warranty of         #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          #
# GNU General Public License for more details.                           #
#                                                                        #
# You should have received a copy of the GNU General Public License      #
# along with this program.  If not, see <https://www.gnu.org/licenses/>. #
#                                                                        #
##########################################################################

#!/usr/bin/make -f

ifneq (,)
This makefile requires GNU Make.
endif

SHELL=/bin/sh

PROGRAM=prime
CXX_FILES := $(wildcard *.cc)
OBJS := $(patsubst %.cc,%.o,$(CXX_FILES))
CXX=c++
CXXFLAGS=-g
LDFLAGS=
LDLIBS=-lm

all:$(PROGRAM)

$(PROGRAM):.depend $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM) $(LDLIBS)

depend:.depend

.depend:cmd=gcc -MM -MF depend $(var); cat depend >> .depend;
.depend:
	@echo "Generating dependencies..."
	@$(foreach var,$(CXX_FILES),$(cmd))
	@rm -f depend

-include .depend

%.o:%.c
	$(CXX) -c $(CXXFLAGS) $< -o $@

%:%.c
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(OBJS) .depend

distclean:
	rm -f $(PROGRAM) $(OBJS) .depend

.PHONY:depend clean distclean
