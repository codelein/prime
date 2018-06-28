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
