JAVAC = javac
JFLAGS += -Xlint -g

SRCS = 	Edge.java \
		Graph.java \
		GuiGraph.java \
		Vertex.java
OBJS = ${SRCS:.java=.class}

.SUFFIXES:	.java .class

.java.class:
	$(JAVAC) $(JFLAGS) $<

all:	$(OBJS)

clean:
	rm -f *.class
#	vim: set noet:
