#include "pch.h"
#include "CppUnitTest.h"
#include "../pkr_laba_5.2(b)/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pkrUnitTest52b
{
	TEST_CLASS(pkrUnitTest52b)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ifstream stream("t.txt");
			int pers = 0;
			char* FileName = 0;
			if (stream.is_open())
			{
				pers = Percent(FileName);
				stream.close();
			}
			Assert::AreEqual(pers, 0);
		}
	};
}
