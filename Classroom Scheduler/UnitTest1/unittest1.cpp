#include "stdafx.h"
#include "CppUnitTest.h"

#include "Scheduler.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(FullTest)
		{
			vector<vector<int>> i_vectStudentsCourses = {{0,1}, {1,2}, {2,3}, {3,0}};
			bool bReturnValue = SolveScheduling(
				2, 
				2,
				4,
				i_vectStudentsCourses);
			Assert::IsTrue(bReturnValue);
		}
	};
}