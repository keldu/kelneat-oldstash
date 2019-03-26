.PHONY: all clean

CXX = clang++

MKDIR = mkdir -p
RM = rm -rf

BUILDDIR = build
SRCDIR = src
BINDIR = bin
LIBDIR = lib
HDRDIR = headers

GENETICS = genetics
NEURAL = neural
DATABASE = storage

CXXFLAGS ?= -g -Wall
CXXFLAGS += -std=c++14
CXXFLAGS += -I./$(HDRDIR)

LDFLAGS =
LDLIBS = -lsqlite3

SOURCES = $(SRCDIR)/neat.cpp $(SRCDIR)/minesweep.cpp
SOURCES += $(wildcard $(SRCDIR)/$(NEURAL)/*.cpp)
SOURCES += $(wildcard $(SRCDIR)/$(GENETICS)/*.cpp)
SOURCES += $(wildcard $(SRCDIR)/$(DATABASE)/*.cpp)

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

all: target

#lib: $(OBJECTS)
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

run: all
	$(CD) $(BINDIR)
	./NEAT

prep:
	$(MKDIR) $(BUILDDIR)
	$(MKDIR) $(BUILDDIR)/$(GENETICS)
	$(MKDIR) $(BUILDDIR)/$(NEURAL)
	$(MKDIR) $(BUILDDIR)/$(DATABASE)

preplib: prep
	$(MKDIR) $(LIBDIR)

prepbin: prep
	$(MKDIR) $(BINDIR)

targetlib: preplib lib

targetbin: prepbin NEAT

target: targetlib targetbin

NEAT: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $^ $(SRCDIR)/main.cpp -o $(BINDIR)/$@

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -c -o $@

clean:
	$(RM) $(BUILDDIR) $(BINDIR) $(LIBDIR)
