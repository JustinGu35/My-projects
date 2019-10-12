CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

OBJS=amazon.o user.o db_parser.o product.o product_parser.o util.o book.o moive.o clothing.o mydatastore.o

all: amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

amazon.o: amazon.cpp db_parser.h datastore.h product_parser.h book.h clothing.h movie.h mydatastore.h util.h review.h msort.h heap.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c amazon.cpp
user.o: user.cpp user.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c user.cpp
db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h util.h review.h msort.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c db_parser.cpp
product.o: product.cpp product.h review.h msort.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product.cpp
product_parser.o: product_parser.cpp product_parser.h product.h book.h movie.h clothing.h util.h review.h msort.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c product_parser.cpp
util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c util.cpp
book.o: book.h book.cpp product.h util.h review.h msort.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c book.cpp
moive.o: movie.h movie.cpp product.h util.h review.h msort.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c movie.cpp
clothing.o: clothing.h clothing.cpp product.h util.h review.h msort.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c clothing.cpp
mydatastore.o: mydatastore.h mydatastore.cpp datastore.h product.h user.h review.h msort.h heap.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c mydatastore.cpp
sortcomp.o: sortcomp.cpp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c sortcomp.cpp


clean:
	rm -f *.o amazon
