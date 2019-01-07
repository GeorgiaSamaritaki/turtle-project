#include "LOGO.h"


START_PROGRAM
try {
	
	
	REPEAT NUMBER : 5 TIMES
		DO
		printf("this is the %d\n", REPCOUNT );// number of the current iteration
		//FORWARD(NUMBER : 100); // move turtle 100 steps


	REPEAT NUMBER : 5 TIMES
		DO
		printf("~~~~%d\n", REPCOUNT);// number of the current iteration
		//FORWARD(NUMBER : 100); // move turtle 100 steps




		//RIGHT(NUMBER : 90); // turtle turns right 90 degrees
	END;

		//RIGHT(NUMBER : 90); // turtle turns right 90 degrees
	END;

		/*
		 Εντολή REPEAT WHILE condition DO Instructions END.Παραδείγματα:
	o REPEAT WHILE number != (NUMBER : 5)
		DO
		REPCOUNT // number of the current iteration
		FORWARD(NUMBER : 100) // move turtle 100 steps
		RIGHT(NUMBER : 90) // turtle turns right 90 degrees
		ASSIGN number = DIFFERENCE(number, (NUMBER: 1))
		END
		 Εντολή FOREACH list DO Instructions END.Παραδείγματα:
	o FOREACH myMoves DO
		SHOW : ELEM //ELEM is each element of the list
		END		*/

}
catch (exception e) {
	printf("\nNOPE\n");
}
END_PROGRAM
