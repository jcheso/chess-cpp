all: chess

chess: ChessMain.o ChessPiece.o ChessBoard.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o
	g++ -g ChessMain.o ChessPiece.o ChessBoard.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o -o chess

ChessMain.o: ChessMain.cpp  Helper.h
	g++ -Wall -g -c ChessMain.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h
	g++ -Wall -g -c ChessPiece.cpp ChessPiece.h

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	g++ -Wall -g -c ChessBoard.cpp ChessBoard.h

Bishop.o: Bishop.cpp Bishop.h
	g++ -Wall -g -c Bishop.cpp Bishop.h
	
King.o: King.cpp King.h
	g++ -Wall -g -c King.cpp King.h

Knight.o: Knight.cpp Knight.h
	g++ -Wall -g -c Knight.cpp Knight.h

Pawn.o: Pawn.cpp Pawn.h
	g++ -Wall -g -c Pawn.cpp Pawn.h

Queen.o: Queen.cpp Queen.h
	g++ -Wall -g -c Queen.cpp Queen.h

Rook.o: Rook.cpp Rook.h
	g++ -Wall -g -c Rook.cpp Rook.h

clean:
	rm -f *.o *.h.gch chess