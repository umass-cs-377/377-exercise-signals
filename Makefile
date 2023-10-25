.PHONY : all
all : signals mysleep immortal

.DEFAULT_GOAL := all

clean:
	rm signals mysleep immortal

signals: signals.cpp
	g++ -o signals signals.cpp

mysleep: mysleep.cpp
	g++ -o mysleep mysleep.cpp

immortal: immortal.cpp
	g++ -o immortal immortal.cpp