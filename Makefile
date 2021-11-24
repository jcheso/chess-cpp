all: chess

chess: chessmain.o helper.o chesspiece.o chessboard.o  bishop.o king.o knight.o pawn.o queen.o rook.o
	g++ -g chessmain.o helper.o chesspiece.o chessboard.o bishop.o king.o knight.o pawn.o queen.o rook.o -o chess

chessmain.o: chessmain.cpp  helper.hpp
	g++ -Wall -g -c chessmain.cpp

helper.o: helper.cpp helper.hpp
	g++ -Wall -g -c helper.cpp helper.hpp
	
chesspiece.o: chesspiece.cpp chesspiece.hpp
	g++ -Wall -g -c chesspiece.cpp chesspiece.hpp

chessboard.o: chessboard.cpp chessboard.hpp
	g++ -Wall -g -c chessboard.cpp chessboard.hpp

bishop.o: bishop.cpp bishop.hpp
	g++ -Wall -g -c bishop.cpp bishop.hpp
	
king.o: king.cpp king.hpp
	g++ -Wall -g -c king.cpp king.hpp

knight.o: knight.cpp knight.hpp
	g++ -Wall -g -c knight.cpp knight.hpp

pawn.o: pawn.cpp pawn.hpp
	g++ -Wall -g -c pawn.cpp pawn.hpp

queen.o: queen.cpp queen.hpp
	g++ -Wall -g -c queen.cpp queen.hpp

rook.o: rook.cpp rook.hpp
	g++ -Wall -g -c rook.cpp rook.hpp

clean:
	rm -f *.o chess