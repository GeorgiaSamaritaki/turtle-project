#include "LOGO.h"


START_PROGRAM

try {
	

MAKE myMoves = LIST[
	LIST[(WORD:"FORWARD"), (NUMBER:100)],
		LIST[(WORD:"LEFT"), (NUMBER:90)],
		LIST[(WORD:"FORWARD"), (NUMBER:100)]
];


//define array variable
//auto sec = { new array_l() };

MAKE number = (NUMBER: 5);
auto b = ((*new l_BOOLEAN()) = 0 ? true : true);

MAKE array = ARRAY{
	number,
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
	//MAKE book = SENTENCE(hello, (WORD: “hello!”))
	

	}
	catch (exception e) {
		printf("\nNOPE\n");
	}
cout << "finish";
END_PROGRAM
