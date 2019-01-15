#include "LOGO.h"

TO draw_square WITH args FSTART
	// args is a list [length, [r,g,b]]
		SETPENCOLOR ARG(NUMBER: 2)
		REPEAT(NUMBER:4) TIMES
		DO
		FORWARD ARG(NUMBER: 1)
		RIGHT(NUMBER: 90)
		END
FEND

START_PROGRAM
try {
		
	MAKE number = (NUMBER: 21); //define number variable with value 21
	MAKE hello = (WORD: "hello"); //define hello variable with value “hello”
						//define myMoves variable contains list of turtle moves
	
	
	MAKE myMoves = LIST[
		LIST[(WORD:"FORWARD"), (NUMBER:100)],
			LIST[(WORD:"LEFT"), (NUMBER:90)],
			LIST[(WORD:"FORWARD"), (NUMBER:100)]
	]
		SHOW : myMoves
			//MAKE newvar = myMoves.get(0);
	//define array variable
	MAKE array = ARRAY {
		number,
		hello,
		(NUMBER: 12),
		(BOOLEAN: TRUE),
		ARRAY {
			myMoves,
			LIST[
				(WORD: "BACK"),
				(NUMBER:100)
			]
		}
	};
	//define book variable with sentence type
	MAKE book = SENTENCE(hello, (WORD: "hello!"))

	
	ITEM({ (NUMBER: 4) }, array);
	// get value of 4th element(i.e. TRUE)
	
	ITEM({ (NUMBER:5), (NUMBER:2) }, array); // get value of array
											// i.e. {“BACK”, 100})

	SETITEM({ (NUMBER:3) }, array, (NUMBER:1)) // set new value in
												// 3rd element

	SETITEM({ (NUMBER:5) }, array, myMoves); // set new value in
											// 5th element

	MAKE v = sum_l( (NUMBER : 12), ITEM({ (NUMBER:1) }, array) ); // v = 12 + 21
	
	SETITEM({ (NUMBER:3) }, array, SUM((NUMBER: 1), v)); // array[3] = 1 + 33
	
	ASSIGN number = DIFFERENCE((NUMBER : 12), number); // number = 12 - number
	MAKE v2 = MINUS(number); // v2 = -12
	ASSIGN number = (NUMBER : 21) // number = 12 - number
	
	
	MAKE v3 = PRODUCT((NUMBER : 12), number, v2)//v3=12*number*v2
	MAKE v4 = QUOTIENT((NUMBER: 12), number) // v4 = 12 / 21
	MAKE v5 = MODULO((NUMBER: 12), number)// v5 = 12 % 21
	ASSIGN v5 = SUM(v2, PRODUCT(ITEM({ (NUMBER:1) }, array), v3), v); // v5 = v2 + (array[1]*v3) + v
	MAKE a = (number == (NUMBER : 21)); // BOOLEAN: TRUE
	MAKE b = ((NUMBER : 22) >= number); // BOOLEAN: TRUE
	MAKE c = (number >= (NUMBER : 22)); // BOOLEAN: FALSE
	

	MAKE d = AND(
		number == (NUMBER: 5), 
		(BOOLEAN: TRUE)
	); // BOOLEAN: FALSE

	MAKE text = (WORD: "text")
	MAKE text2 = (WORD: "text2")


	MAKE e = OR( // BOOLEAN: TRUE
		ITEM({ (NUMBER:4) }, array), 
		text2 == text
	)
	MAKE f = OR( // BOOLEAN: TRUE
		number == SUM((NUMBER:19), (NUMBER: 1), (NUMBER: 1)),
		AND(text2 == text, number)
	);

	MAKE list = LIST[
		number,
		LIST[
			(NUMBER: 2), (NUMBER:3), (NUMBER:2)
		]
	];


	IF AND(number == (NUMBER: 5), text2 == text) DO
		SETITEM({ (NUMBER:3) }, array, SUM((NUMBER: 1), v))

	END
		
	IF number == ITEM({ (NUMBER:2), (NUMBER:3) }, list) DO
		SETITEM({ (NUMBER:3) }, array, SUM(v, (NUMBER: 1)))
	ELIF number >= 5 DO
		SETITEM({ (NUMBER:3) }, array, DIFFERENCE(v, (NUMBER: 1)))
	END

	IF AND(number == (NUMBER: 5), text2 == text) DO
		IF number == ITEM({ (NUMBER:2), (NUMBER:3) }, list) DO
			SETITEM({ (NUMBER:3) }, array, SUM(v, (NUMBER: 1)))
		ELSE
			SETITEM({ (NUMBER:3) }, array, DIFFERENCE(v, (NUMBER: 1)))
		END
	END

	REPEAT NUMBER : 5 TIMES
	DO
		FORWARD(NUMBER : 100); // move turtle 100 steps
		RIGHT(NUMBER : 90); // turtle turns right 90 degrees
	END
		
		MAKE turtleMoves = LIST[
			ARRAY	 { (WORD:"FORWARD"), (NUMBER: 100) },
				ARRAY{ (WORD:"RIGHT"), (NUMBER: 90) },
				ARRAY{ (WORD:"FORWARD"), (NUMBER: 100) },
				ARRAY{ (WORD:"RIGHT"), (NUMBER: 90) },
				ARRAY{ (WORD:"FORWARD"), (NUMBER: 100) },
				ARRAY{ (WORD:"LEFT"), (NUMBER: 90) },
				ARRAY{ (WORD:"FORWARD"), (NUMBER: 100) },
				ARRAY{ (WORD:"LEFT"), (NUMBER: 90) }
		]

		CENTER
		REPEAT 2 TIMES	DO
			FOREACH turtleMoves DO
				IF ITEM({ (NUMBER: 1) }, ELEM) == (WORD: "FORWARD") DO
					FORWARD ITEM({ (NUMBER: 2) }, ELEM)
				ELIF ITEM({ (NUMBER: 1) }, ELEM) == (WORD: "BACK") DO
					BACK ITEM({ (NUMBER: 2) }, ELEM)
				ELIF ITEM({ (NUMBER: 1) }, ELEM) == (WORD: "LEFT") DO
					LEFT ITEM({ (NUMBER: 2) }, ELEM)
				ELSE
					RIGHT ITEM({ (NUMBER: 2) }, ELEM)
				END
			END
		 END
		PENUP
		CENTER
		RIGHT(NUMBER: 90)
		FORWARD(NUMBER: 150)
		PENDOWN
		REPEAT(NUMBER: 360) TIMES DO
		FORWARD(NUMBER: 2)
		RIGHT(NUMBER: 1)
		END
	
	CENTER
	
	CLEAR

	printf("here");
	REPEAT(NUMBER:36) TIMES DO
		CALL draw_square(
			LIST[ 
				PRODUCT((NUMBER:12), REPCOUNT) ,
				LIST[	SUM((NUMBER:12), REPCOUNT), 
						(NUMBER:0), 
						(NUMBER:0)
				]
			]
		)
		RIGHT(NUMBER: 10)
	END

}catch (exception e) {

}

END_PROGRAM

