CXX = g++
CXXFLAGS = -Wall -ggdb
RM = rm -f

main: main.o morse_to_text.o text_to_morse.o dictionnary.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

main.o: main.cpp text_to_morse.h morse_to_text.h dictionnary.h

dictionnary.o: dictionnary.h

morse_to_text.o: morse_to_text.cpp morse_to_text.h dictionnary.h

text_to_morse.o: text_to_morse.cpp text_to_morse.h dictionnary.h

clean:
	$(RM) main.o morse_to_text.o text_to_morse.o dictionnary.o all