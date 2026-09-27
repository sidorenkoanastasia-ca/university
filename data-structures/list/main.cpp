#include <iostream>
#include <string>
#include "list.h"

void testConstructors()
{
    std::cout << "==========TEST CONSTRUCTORS===========\n";
    {
        std::cout << "Default constructor: ";
        DoubleOrderedDuplicateList<int> test;
        if (test.isEmpty() && test.size() == 0)
        {
            std::cout << "List is empty, size = 0 - PASSED\n";
        }
        else
        {
            std::cout << "- FAILED\n";
        }
        try
        {
            test.head();
            std::cout << "FAILED: List is empty, but head() didn't throw\n";
        }
        catch (const std::runtime_error& e)
        {
            std::cout << "head() throws - PASSED\n";
        }
        try
        {
            test.tail();
            std::cout << "FAILED: List is empty, but tail() didn't throw\n";
        }
        catch (const std::runtime_error& e)
        {
            std::cout << "tail() throws - PASSED\n";
        }
    }

    {
        std::cout << "Constructor with const T&: ";
        int value = 42;
        DoubleOrderedDuplicateList<int> test(value);
        if (test.size() == 1 && test.head() == 42 && test.tail() == 42)
        {
            std::cout << "size = 1, data = 42 - PASSED\n";
        }
        else
        {
            std::cout << "- FAILED\n";
        }
    }

    {
        std::cout << "Constructor with T&&: ";
        std::string str = "hello";
        DoubleOrderedDuplicateList<std::string> list(std::move(str));
        if (list.size() == 1 && list.head() == "hello")
        {
            std::cout << "size = 1, data = hello - PASSED\n";
        }
        else
        {
            std::cout << "- FAILED\n";
        }
    }

    {
        std::cout << "Copy constructor: ";
        DoubleOrderedDuplicateList<int> original;
        original.insert(10);
        original.insert(20);
        original.insert(30);

        DoubleOrderedDuplicateList<int> copy(original);

        if (copy.size() == 3 && copy.head() == 10 && copy.tail() == 30)
        {
            std::cout << "copy matches original - PASSED\n";

            copy.removeHead();
            if (copy.size() == 2 && original.size() == 3)
            {
                std::cout << "  Independent copy - PASSED\n";
            }
            else
            {
                std::cout << "  Independent copy - FAILED\n";
            }
        }
        else
        {
            std::cout << "- FAILED\n";
        }
    }

    {
        std::cout << "Move constructor: ";
        DoubleOrderedDuplicateList<int> original;
        original.insert(10);
        original.insert(20);
        original.insert(30);
        size_t oldSize = original.size();
        int oldHead = original.head();

        DoubleOrderedDuplicateList<int> moved(std::move(original));

        if (moved.size() == oldSize && moved.head() == oldHead)
        {
            std::cout << "moved contains data - PASSED\n";

            if (original.isEmpty() && original.size() == 0)
            {
                std::cout << "  original is empty - PASSED\n";
            }
            else
            {
                std::cout << "  original is empty - FAILED\n";
            }
        }
        else
        {
            std::cout << "- FAILED\n";
        }
    }
    std::cout << "=======================================\n\n";
}

void testInsert()
{
    std::cout << "============TEST INSERT==============\n";

    {
        std::cout << "Insert into empty list: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(5);
        if (list.size() == 1 && list.head() == 5 && list.tail() == 5)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Insert at beginning: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(5);
        if (list.size() == 2 && list.head() == 5 && list.tail() == 10)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Insert at end: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        if (list.size() == 2 && list.head() == 10 && list.tail() == 20)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Insert in middle: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(30);
        list.insert(20);
        if (list.size() == 3 && list.head() == 10 && list.tail() == 30)
        {
            list.printForward();
            std::cout << " - PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Insert duplicate: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        list.insert(10);
        if (list.size() == 2)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Insert with move: ";
        DoubleOrderedDuplicateList<std::string> list;
        std::string s = "test";
        list.insert(std::move(s));
        if (list.size() == 1 && list.head() == "test")
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }
    std::cout << "======================================\n\n";
}

void testSearch()
{
    std::cout << "=============TEST SEARCH=============\n";

    {
        std::cout << "Search in empty list: ";
        DoubleOrderedDuplicateList<int> list;
        if (!list.search(5))
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Search existing element: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        list.insert(30);
        if (list.search(20))
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Search non-existing element: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        list.insert(30);
        if (!list.search(25))
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Search element smaller than first: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        if (!list.search(5))
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Search element larger than last: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        if (!list.search(25))
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }
    std::cout << "======================================\n\n";
}

void testRemoveHead()
{
    std::cout << "===========TEST REMOVE HEAD==========\n";

    {
        std::cout << "Remove head from empty list: ";
        DoubleOrderedDuplicateList<int> list;
        try
        {
            list.removeHead();
            std::cout << "FAILED - no exception\n";
        }
        catch (const std::out_of_range& e)
        {
            std::cout << "PASSED\n";
        }
    }

    {
        std::cout << "Remove head from single element: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(42);
        list.removeHead();
        if (list.isEmpty())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Remove head from multiple elements: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        list.insert(30);
        list.removeHead();
        if (list.size() == 2 && list.head() == 20 && list.tail() == 30)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }
    std::cout << "======================================\n\n";
}

void testRemoveKey()
{
    std::cout << "============TEST REMOVE KEY==========\n";

    {
        std::cout << "Remove key from empty list: ";
        DoubleOrderedDuplicateList<int> list;
        try
        {
            list.removeKey(5, 10);
            std::cout << "FAILED - no exception\n";
        }
        catch (const std::out_of_range& e)
        {
            std::cout << "PASSED\n";
        }
    }

    {
        std::cout << "Remove single element: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        list.insert(30);
        list.removeKey(20, 20);
        if (list.size() == 2 && list.head() == 10 && list.tail() == 30)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Remove range at beginning: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(5);
        list.insert(10);
        list.insert(15);
        list.insert(20);
        list.insert(25);
        list.removeKey(5, 15);
        if (list.size() == 2 && list.head() == 20 && list.tail() == 25)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Remove range in middle: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(5);
        list.insert(10);
        list.insert(15);
        list.insert(20);
        list.insert(25);
        list.removeKey(10, 20);
        if (list.size() == 2 && list.head() == 5 && list.tail() == 25)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Remove range at end: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(5);
        list.insert(10);
        list.insert(15);
        list.insert(20);
        list.insert(25);
        list.removeKey(15, 25);
        if (list.size() == 2 && list.head() == 5 && list.tail() == 10)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Remove entire list: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(5);
        list.insert(10);
        list.insert(15);
        list.removeKey(5, 15);
        if (list.isEmpty())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Remove range with no matches: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(5);
        list.insert(10);
        list.insert(15);
        list.removeKey(20, 30);
        if (list.size() == 3)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }
    std::cout << "======================================\n\n";
}

void testEquality()
{
    std::cout << "============TEST EQUALITY============\n";

    {
        std::cout << "Empty lists equal: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        if (list1 == list2)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Same elements equal: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(20);
        list1.insert(30);
        list2.insert(10);
        list2.insert(20);
        list2.insert(30);
        if (list1 == list2)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Different sizes not equal: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(20);
        list2.insert(10);
        if (!(list1 == list2))
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Different elements not equal: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(20);
        list1.insert(30);
        list2.insert(10);
        list2.insert(25);
        list2.insert(30);
        if (!(list1 == list2))
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }
    std::cout << "======================================\n\n";
}

void testGetIntersection()
{
    std::cout << "==========TEST INTERSECTION==========\n";

    {
        std::cout << "Intersection of empty lists: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        auto result = getIntersection(list1, list2);
        if (result.isEmpty())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Intersection with common elements: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(20);
        list1.insert(30);
        list1.insert(40);
        list2.insert(20);
        list2.insert(30);
        list2.insert(50);

        auto result = getIntersection(list1, list2);
        if (result.size() == 2)
        {
            result.printForward();
            std::cout << " - PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Intersection with no common elements: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(20);
        list1.insert(30);
        list2.insert(40);
        list2.insert(50);
        list2.insert(60);

        auto result = getIntersection(list1, list2);
        if (result.isEmpty())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Intersection with duplicates: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(10);
        list1.insert(20);
        list2.insert(10);
        list2.insert(20);
        list2.insert(20);

        auto result = getIntersection(list1, list2);
        if (result.size() == 2)
        {
            result.printForward();
            std::cout << " - PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }
    std::cout << "======================================\n\n";
}

void testRemove()
{
    std::cout << "=============TEST REMOVE=============\n";

    {
        std::cout << "Remove from empty list: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list2.insert(10);
        list1.remove(list2);
        if (list1.isEmpty())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Remove with empty second list: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(20);
        list1.remove(list2);
        if (list1.size() == 2)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Remove common elements: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(20);
        list1.insert(30);
        list1.insert(40);
        list2.insert(20);
        list2.insert(40);

        list1.remove(list2);
        if (list1.size() == 2)
        {
            list1.printForward();
            std::cout << " - PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Remove all elements: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(20);
        list1.insert(30);
        list2.insert(10);
        list2.insert(20);
        list2.insert(30);

        list1.remove(list2);
        if (list1.isEmpty())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Second list unchanged after remove: ";
        DoubleOrderedDuplicateList<int> list1;
        DoubleOrderedDuplicateList<int> list2;
        list1.insert(10);
        list1.insert(20);
        list2.insert(10);
        size_t oldSize = list2.size();

        list1.remove(list2);
        if (list2.size() == oldSize)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }
    std::cout << "=====================================\n\n";
}

void testClear()
{
    std::cout << "==============TEST CLEAR=============\n";

    {
        std::cout << "Clear empty list: ";
        DoubleOrderedDuplicateList<int> list;
        list.clear();
        if (list.isEmpty())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Clear non-empty list: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        list.insert(30);
        list.clear();
        if (list.isEmpty())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }

        try
        {
            list.head();
            std::cout << "  FAILED - head() after clear\n";
        }
        catch (const std::runtime_error& e)
        {
            std::cout << "  head() after clear - PASSED\n";
        }
    }
    std::cout << "=====================================\n\n";
}

void testPrintFunctions()
{
    std::cout << "==========TEST PRINT FUNCTIONS========\n";

    {
        std::cout << "Print forward: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        list.insert(30);
        std::cout << "\n  Expected: 10 20 30 \n  Got:      ";
        list.printForward();
        std::cout << " - PASSED\n";
    }

    {
        std::cout << "Print backward: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(10);
        list.insert(20);
        list.insert(30);
        std::cout << "\n  Expected: 30 20 10 \n  Got:      ";
        list.printBackward();
        std::cout << " - PASSED\n";
    }

    {
        std::cout << "Print empty list forward: ";
        DoubleOrderedDuplicateList<int> list;
        std::cout << "\n  Got: ";
        list.printForward();
        std::cout << " - PASSED\n";
    }

    {
        std::cout << "Print empty list backward: ";
        DoubleOrderedDuplicateList<int> list;
        std::cout << "\n  Got: ";
        list.printBackward();
        std::cout << " - PASSED\n";
    }
    std::cout << "======================================\n\n";
}

void testAssignmentOperators()
{
    std::cout << "========TEST ASSIGNMENT OPERATORS=====\n";

    {
        std::cout << "Copy assignment: ";
        DoubleOrderedDuplicateList<int> list1;
        list1.insert(10);
        list1.insert(20);

        DoubleOrderedDuplicateList<int> list2;
        list2 = list1;

        if (list2.size() == 2 && list2.head() == 10 && list2.tail() == 20)
        {
            std::cout << "PASSED\n";

            list2.removeHead();
            if (list1.size() == 2)
            {
                std::cout << "  Independent copy - PASSED\n";
            }
            else
            {
                std::cout << "  Independent copy - FAILED\n";
            }
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Move assignment: ";
        DoubleOrderedDuplicateList<int> list1;
        list1.insert(10);
        list1.insert(20);
        size_t oldSize = list1.size();

        DoubleOrderedDuplicateList<int> list2;
        list2 = std::move(list1);

        if (list2.size() == oldSize && list2.head() == 10)
        {
            std::cout << "PASSED\n";

            if (list1.isEmpty())
            {
                std::cout << "  Original is empty - PASSED\n";
            }
            else
            {
                std::cout << "  Original is empty - FAILED\n";
            }
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }

    {
        std::cout << "Self assignment: ";
        DoubleOrderedDuplicateList<int> list;
        list.insert(42);
        list = list;
        if (list.size() == 1 && list.head() == 42)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
        }
    }
    std::cout << "======================================\n\n";
}

int main()
{
    std::cout << "START TESTING DoubleOrderedDuplicateList\n\n";

    testConstructors();
    testAssignmentOperators();
    testInsert();
    testSearch();
    testRemoveHead();
    testRemoveKey();
    testEquality();
    testGetIntersection();
    testRemove();
    testClear();
    testPrintFunctions();

    std::cout << "\nALL TESTS COMPLETED\n";
    return 0;
}