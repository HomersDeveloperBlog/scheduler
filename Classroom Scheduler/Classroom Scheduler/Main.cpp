//Use the header

#include "Scheduler.h"

int main()
{
	//Testing suite suppresses the console and I don't want to fix that
	//Just going to paste the test into main to read teh console
	vector<vector<int>> vectStudentsCourses = {{0,1}, {1,2}, {2,3}, {3,0}};
	bool bReturnValue = SolveScheduling(
		2, 
		2,
		4,
		vectStudentsCourses);

	return 0;
}