# =============================================
# This makefile is used for MyApp
# =============================================
#
# =============================================
#1. Instructions to build final MyApp
#application – call the compiler, but
#instead of compiling, use it as a linker
# =============================================
./bin/encodeInput : ./obj/encodeInput.o
	gcc ./obj/encodeInput.o -o ./bin/encodeInput
#
# =========================================
#2. Instructions for compiling the
#dependencies that the final MyApp
#binary depends on
# =========================================
./obj/encodeInput.o : ./src/encodeInput.c
	gcc -c ./src/encodeInput.c -c -o ./obj/encodeInput.o

# =========================================
#3. Example of a useful “extra” command
#that you can place in your makefile
#to help you recompile your entire
#project from scratch – the “clean”
#command. You run it by typing
#make clean
#at the command line.
# =========================================
clean:
	rm -f ./obj/*.o
	rm -f ./bin/*

