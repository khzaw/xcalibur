SOURCE=SimpleGenerator.java

all: $(SOURCE)
	javac $(SOURCE) && java SimpleGenerator > source.txt
