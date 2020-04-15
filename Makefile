SRCS = 	$(wildcard *.cpp parser/*.cpp terms/*.cpp utils/*.cpp toplevel/*.cpp api/*.cpp parser/*.cc printer/*.cpp)

OBJS = $(patsubst %.cpp, %.o,$(SRCS))
OBJS2 = $(patsubst %.cc, %.o,$(OBJS))
OBJECTS = $(shell find . -name "*.o")
SUBDIRS = . parser terms utils toplevel api
SUBDIRSCLEAN=$(addsuffix clean,$(SUBDIRS))

all: fzn2omt

fzn2omt: lex yacc $(OBJS2)
	g++ -o $@ $(OBJECTS) -L/usr/local/lib -lgmp

%.o: %.cpp %.cc
	g++ -Wall -g -c $< -w

yacc:
	bison -d parser/flatzincbisonparser.yy -o parser/flatzincbisonparser.cc

lex: 
	flex --header-file=parser/flatzincflexlexer.h --outfile=parser/flatzincflexlexer.cc parser/flatzincflexlexer.ll

clean: $(SUBDIRSCLEAN)

clean_curdir:
	rm -rfv *.o fzn2omt

onlyparse:
	g++    -c -o parser/flatzincbisonparser.o parser/flatzincbisonparser.cc 
	g++ -o fzn2omt ./api/environment.o ./api/optenvironment.o ./configuration.o ./main.o ./parser/flatzincannotation.o ./parser/flatzincbisonparser.o ./parser/flatzincflexlexer.o ./parser/optattributes.o ./terms/signature.o ./terms/term.o ./terms/termmanager.o ./terms/typeuniverse.o ./toplevel/cmdline.o ./toplevel/flatzincbank.o ./toplevel/flatzincconstraints.o ./toplevel/flatzincglconstraints.o ./toplevel/flatzincinterface.o ./toplevel/toplevelinterface.o ./utils/exception.o ./utils/flatzincset.o ./utils/numbers.o -L/usr/local/lib -lgmp
%clean: %
	$(MAKE) -C $< -f $(PWD)/Makefile clean_curdir