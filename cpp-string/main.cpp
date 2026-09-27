#include <iostream>
#include "String.h"
#include <stdexcept>

int main()
{
	try
	{
		std::cout << "-------------------------------------------------\n";

		char testFunction[] = "Hello";
		char testFunctionSecond[100];
		std::cout << "Function: length of string - " << strLength(testFunction) << '\n'
			<< "Function: copy - " << strCopy(testFunctionSecond, testFunction) << '\n';

		std::cout << "-------------------------------------------------\n";

		String str1;
		String str2("Hello");
		String str(nullptr);
		std::cout << "Test << : " << str2 << '\n';
		std::cout << "Default: " << str1 << '\n'
			<< "Parametrs 1: " << str2 << '\n'
			<< "Parametrs 2: " << str << '\n';
		String str3(str2);
		String str4(std::move(str2));
		std::cout << "Copy: " << str3 << '\n'
			<< "Move: " << str4 << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "First string before swap: " << str1 << '\n'
			<< "Second string before swap: " << str4 << '\n';
		str1.swap(str4);
		std::cout << "First string after swap: " << str1 << '\n'
			<< "Second string after swap: " << str4 << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "Length of string: " << str1.length() << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "First string: " << str1 << ", is string empty : " << str1.empty() << '\n'
			<< "Second string: " << str4 << ", is string empty : " << str4.empty() << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "1 String before clear: " << str1 << '\n';
		str1.clear();
		std::cout << "1 String after clear: " << str1 << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "First string: " << str1 << ", second string: " << str3 << '\n';
		str1 = str3;
		std::cout << "First string after copy assignment: " << str1 << '\n';

		std::cout << "-------------------------------------------------\n";

		String str5("yes");
		std::cout << "First string: " << str1 << ", second string: " << str5 << '\n';
		str1 = std::move(str5);
		std::cout << "First string after move assignment: " << str1 << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "First string: " << str1 << ", second string (char*): nonono" << '\n';
		str1 = "nonono";
		std::cout << "First string after assignment with char*: " << str1 << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "String: " << str1 << ", first element of str1: " << str1[0]
			<< ", second element of str1: " << str1[1] << '\n';
		//std::cout << str1[100];
		std::cout << "-------------------------------------------------\n";

		String str6(" world!");
		std::cout << "First string: " << str3 << ", Second string: " << str6 << '\n';
		String testSumFirst = str3 + str6;
		std::cout << "String after summation: " << testSumFirst << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "First string: " << str3 << ", summand:  Good work!" << '\n';
		String testSumSecond = str3 + " Good work!";
		std::cout << "String after summation: " << testSumSecond << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "First string before summation and assignment: " << str3 << ", Second string: " << str6 << '\n';
		str3 += str6;
		std::cout << "First string after summation and assignment: " << str3 << '\n';

		std::cout << "-------------------------------------------------\n";

		std::cout << "First string: " << str3 << ", summand:  Good work!" << '\n';
		str3 += " Good work!";
		std::cout << "String after summation and assignment: " << str3 << '\n';

		std::cout << "-------------------------------------------------\n";

		String strTest1("apple");
		String strTest2("blueberry");
		String strTest3("apple");
		String strTest4;
		String strTest5("appletwo");
		String strTest6("apricot");
		std::cout << "Operator <" << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest2 << ", is str1 < str2: " << (strTest1 < strTest2) << '\n';
		std::cout << "str1: " << strTest4 << ", str2: " << strTest3 << ", is str1 < str2: " << (strTest4 < strTest3) << '\n';
		std::cout << "str1: " << strTest2 << ", str2: " << strTest3 << ", is str1 < str2: " << (strTest2 < strTest3) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest5 << ", is str1 < str2: " << (strTest1 < strTest5) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest6 << ", is str1 < str2: " << (strTest1 < strTest6) << '\n';

		std::cout << "Operator >" << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest2 << ", is str1 > str2: " << (strTest1 > strTest2) << '\n';
		std::cout << "str1: " << strTest4 << ", str2: " << strTest3 << ", is str1 > str2: " << (strTest4 > strTest3) << '\n';
		std::cout << "str1: " << strTest2 << ", str2: " << strTest3 << ", is str1 > str2: " << (strTest2 > strTest3) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest5 << ", is str1 > str2: " << (strTest1 > strTest5) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest6 << ", is str1 > str2: " << (strTest1 > strTest6) << '\n';

		std::cout << "Operator ==" << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest2 << ", is str1 == str2: " << (strTest1 == strTest2) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest3 << ", is str1 == str2: " << (strTest1 == strTest3) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest4 << ", is str1 == str2: " << (strTest1 == strTest4) << '\n';

		std::cout << "Operator !=" << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest2 << ", is str1 != str2: " << (strTest1 != strTest2) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest3 << ", is str1 != str2: " << (strTest1 != strTest3) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest4 << ", is str1 != str2: " << (strTest1 != strTest4) << '\n';

		std::cout << "Operator <=" << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest2 << ", is str1 <= str2: " << (strTest1 <= strTest2) << '\n';
		std::cout << "str1: " << strTest4 << ", str2: " << strTest3 << ", is str1 <= str2: " << (strTest4 <= strTest3) << '\n';
		std::cout << "str1: " << strTest2 << ", str2: " << strTest3 << ", is str1 <= str2: " << (strTest2 <= strTest3) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest5 << ", is str1 <= str2: " << (strTest1 <= strTest5) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest6 << ", is str1 <= str2: " << (strTest1 <= strTest6) << '\n';

		std::cout << "Operator >=" << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest2 << ", is str1 >= str2: " << (strTest1 >= strTest2) << '\n';
		std::cout << "str1: " << strTest4 << ", str2: " << strTest3 << ", is str1 >= str2: " << (strTest4 >= strTest3) << '\n';
		std::cout << "str1: " << strTest2 << ", str2: " << strTest3 << ", is str1 >= str2: " << (strTest2 >= strTest3) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest5 << ", is str1 >= str2: " << (strTest1 >= strTest5) << '\n';
		std::cout << "str1: " << strTest1 << ", str2: " << strTest6 << ", is str1 >= str2: " << (strTest1 >= strTest6) << '\n';

		std::cout << "-------------------------------------------------\n";

		String testFirst("abcdef");
		String testSecond("aabcd");
		String testThird("abcccd");
		String testFourth("abcdd");
		String testFifth("a");
		String test;
		std::cout << "First string: " << testFirst << ", has consecutive duplicates: " << testFirst.hasConsecutiveDuplicates() << '\n'
			<< "Second string: " << testSecond << ", has consecutive duplicates: " << testSecond.hasConsecutiveDuplicates() << '\n'
			<< "Third string: " << testThird << ", has consecutive duplicates: " << testThird.hasConsecutiveDuplicates() << '\n'
			<< "Fourth string: " << testFourth << ", has consecutive duplicates: " << testFourth.hasConsecutiveDuplicates() << '\n'
			<< "Fifth string: " << testFifth << ", has consecutive duplicates: " << testFifth.hasConsecutiveDuplicates() << '\n'
			<< "Empty string: " << test << ", has consecutive duplicates: " << test.hasConsecutiveDuplicates() << '\n';

		std::cout << "-------------------------------------------------\n";

		return 0; 
	}
	catch (const std::out_of_range& err)
	{
		std::cerr << err.what();
	}
	catch (const std::bad_alloc& err)
	{
		std::cerr << "Memory error\n";
	}
	catch (const std::runtime_error& err)
	{
		std::cerr << err.what();
	}
	catch (...)
	{
		std::cerr << "Error\n";
	}
}

