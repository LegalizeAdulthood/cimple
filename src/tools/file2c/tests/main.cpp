#include "test.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

void test1()
{
	const std::string expected(
		"\a\033\n"
		"\b\t\n"
		"\f\n"
		"\r\n"
		"''\n"
		"\"\"\n"
		"\\\n"
		"\\\\\n"
		"This is some sample text.\n"
		"\n"
		"More text.\n");
	const std::string actual(reinterpret_cast<const char*>(TEST_FILE2C));

	if (expected != actual)
	{
		std::cout << "expected: " << expected.length()
			<< ", actual: " << actual.length() << "\n";
		throw std::runtime_error("String mismatch");
	}
}

int main(int /* argc */, char** argv)
{
    try
    {
        test1();
    }
    catch (...)
    {
        std::cerr << "Unknown exception.\n";
        return 1;
    }

    std::cout << "+++++ passed all tests (" << argv[0] << ")\n";
    return 0;
}
