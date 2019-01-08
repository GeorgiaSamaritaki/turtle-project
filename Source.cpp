#include "LOGO.h"


START_PROGRAM
try {

	MAKE number = (NUMBER: 21); //define number variable with value 21
	MAKE hello = (WORD: "hello"); //define hello variable with value “hello”
						//define myMoves variable contains list of turtle moves
			
	MAKE myMoves = LIST[
		LIST[(WORD:"FORWARD"), (NUMBER:100)],
			LIST[(WORD:"LEFT"), (NUMBER:90)],
			LIST[(WORD:"FORWARD"), (NUMBER:100)]
	];
			
		
	//define array variable
	MAKE array = ARRAY {
		number,
		hello,
		(NUMBER: 12),
		(BOOLEAN: TRUE),
		myMoves
	};
		printf("ok");
	//define book variable with sentence type
	MAKE book = SENTENCE(hello, (WORD: "hello!"))

	ITEM({ (NUMBER: 4) }, array) // get value of 4th element(i.e. TRUE)
	ITEM({ (NUMBER:5), (NUMBER:2) }, array) // get value of array
											// i.e. {“BACK”, 100})
	SETITEM({ (NUMBER:3) }, array, (NUMBER:1)) // set new value in
												// 3rd element
	SETITEM({ (NUMBER:5) }, array, myMoves) // set new value in
											// 5th element
	/*

			MAKE v = SUM((NUMBER : 12), ITEM({ (NUMBER:1) }, array)) // v = 12 + 21
			SETITEM({ (NUMBER:3) }, array, SUM((NUMBER: 1), var)) // array[3] = 1 + 33
			SSIGN number = DIFFERENCE((NUMBER : 12), number) // number = 12 - number
			MAKE v2 = MINUS(number) // v2 = -12
			MAKE v3 = PRODUCT((NUMBER : 12), number, v2)//v3=12*number*v2
			MAKE v4 = QUOTIENT((NUMBER: 12), number) // v4 = 12 / 21
			MAKE v5 = MODULO((NUMBER: 12), number) // v5 = 12 % 21
			ASSIGN v5 = SUM(v2, PRODUCT(ITEM({ (NUMBER:1) }, array)), v3), v) // v5 = v2 + (array[1]*v3) + v
			number == (NUMBER : 21) // BOOLEAN: TRUE
			(NUMBER : 22) >= number // BOOLEAN: TRUE
			number <= (NUMBER : 22) // BOOLEAN: FALSE
			AND(number == (NUMBER: 5), text2 == text) // BOOLEAN: FALSE
			OR( // BOOLEAN: TRUE
				number == (NUMBER: 5),
				ITEM({ (NUMBER:3) }, array), // this is TRUE…
				text2 == text
			)
			OR( // BOOLEAN: TRUE
				number == SUM((NUMBER:19), (NUMBER: 1), (NUMBER: 1)),
				AND(text2 == text, number)
			)
				IF AND(number == (NUMBER: 5), text2 == text) DO
					SETITEM({ (NUMBER:3) }, array, SUM((NUMBER: 1), newVar))
				END
				IF number == ITEM({ (NUMBER:2), (NUMBER:3) }, list) DO
					SETITEM({ (NUMBER:3) }, array, SUM(newVar, (NUMBER: 1)))
				ELIF number >= 5 DO
					SETITEM({ (NUMBER:3) }, array, DIFFERENCE(newVar, (NUMBER: 1)))
				END

				IF AND(number == (NUMBER: 5), text2 == text) DO
					IF number == ITEM({ (NUMBER:2), (NUMBER:3) }, list) DO
						SETITEM({ (NUMBER:3) }, array, SUM(newVar, (NUMBER: 1)))
					ELSE
						SETITEM({ (NUMBER:3) }, array, DIFFERENCE(newVar, (NUMBER: 1)))
					END
				END
				REPEAT NUMBER : 5 TIMES
					DO
					REPCOUNT // number of the current iteration
					FORWARD(NUMBER : 100) // move turtle 100 steps
					RIGHT(NUMBER : 90) // turtle turns right 90 degrees
				END

				REPEAT WHILE number != (NUMBER : 5)
				DO
					REPCOUNT // number of the current iteration
					FORWARD(NUMBER : 100) // move turtle 100 steps
					RIGHT(NUMBER : 90) // turtle turns right 90 degrees
					ASSIGN number = DIFFERENCE(number, (NUMBER: 1))
				END

				FOREACH myMoves DO
					SHOW : ELEM //ELEM is each element of the list
				END
				*/

	printf("here");
}
catch (exception e) {
	printf("\nNOPE\n");
}

END_PROGRAM