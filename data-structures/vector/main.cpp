#include <iostream>
#include <string>
#include "Vector.h"

void test_constructors() 
{
    std::cout << "\n--- Testing Constructors ---\n";

    Vector<int> v1;
    std::cout << "Default constructor: "
        << "size=" << v1.size()
        << ", capacity=" << v1.capacity()
        << (v1.empty() ? " (empty)" : " (not empty)")
        << " - " << (v1.size() == 0 && v1.capacity() == 0 ? "Pass" : "Fail") << '\n';

    Vector<int> v2(5);
    std::cout << "Size constructor(5): "
        << "size=" << v2.size()
        << ", capacity=" << v2.capacity()
        << " - " << (v2.size() == 5 && v2.capacity() == 5 ? "Pass" : "Fail") << '\n';

    Vector<std::string> v3(3, "hello");
    std::cout << "Size+value constructor(3, \"hello\"): ";
    for (size_t i = 0; i < v3.size(); ++i) 
    {
        std::cout << v3[i] << " ";
    }
    bool ok = (v3.size() == 3 && v3[0] == "hello" && v3[1] == "hello" && v3[2] == "hello");
    std::cout << "- " << (ok ? "Pass" : "Fail") << '\n';

    Vector<int> v4(v2);
    std::cout << "Copy constructor: "
        << "size=" << v4.size()
        << ", capacity=" << v4.capacity()
        << " - " << (v4.size() == 5 && v4.capacity() == 5 ? "Pass" : "Fail") << '\n';

    Vector<int> v5(std::move(v4));
    std::cout << "Move constructor: "
        << "new size=" << v5.size()
        << ", old size=" << v4.size()
        << " - " << (v5.size() == 5 && v4.size() == 0 ? "Pass" : "Fail") << '\n';
}


void test_access_methods()
{
    std::cout << "\n--- Testing Element Access ---\n";

    Vector<int> v(5);
    for (int i = 0; i < 5; ++i)
    {
        v[i] = i;
    }

    std::cout << "operator[]: ";
    for (size_t i = 0; i < v.size(); ++i) 
    {
        std::cout << v[i] << " ";
    }
    std::cout << "- Pass\n";

    try 
    {
        int x = v.at(2);
        std::cout << "at(2) = " << x << " - Pass\n";
    }
    catch (...) 
    {
        std::cout << "at(2) - Fail\n";
    }

    try 
    {
        v.at(10);
        std::cout << "at(10) should throw - Fail\n";
    }
    catch (const std::out_of_range&) 
    {
        std::cout << "at(10) throws exception - Pass\n";
    }

    std::cout << "front() = " << v.front() << " (expected 0)"
        << (v.front() == 0 ? " - Pass" : " - Fail") << '\n';
    std::cout << "back() = " << v.back() << " (expected 4)"
        << (v.back() == 4 ? " - Pass" : " - Fail") << '\n';
}

void test_push_back()
{
    std::cout << "\n--- Testing push_back (copy and move) ---\n";
    {
        std::cout << "Test 1: Copy push_back\n";
        Vector<std::string> v;
        std::string s1 = "Hello";
        std::string s2 = "World";

        std::cout << "Before push: s1 = \"" << s1 << "\", s2 = \"" << s2 << "\"\n";

        v.push_back(s1); 
        v.push_back(s2); 

        std::cout << "After push: v[0] = \"" << v[0] << "\", v[1] = \"" << v[1] << "\"\n";
        std::cout << "After push: s1 = \"" << s1 << "\", s2 = \"" << s2 << "\"\n";

        bool ok = (v.size() == 2 && v[0] == "Hello" && v[1] == "World"
            && s1 == "Hello" && s2 == "World");
        std::cout << "Copy push_back test: " << (ok ? "Pass" : "Fail") << "\n";
    }

    {
        std::cout << "\nTest 2: Move push_back\n";
        Vector<std::string> v;
        std::string s1 = "Hello";
        std::string s2 = "World";

        std::cout << "Before push: s1 = \"" << s1 << "\", s2 = \"" << s2 << "\"\n";

        v.push_back(std::move(s1)); 
        v.push_back(std::move(s2));

        std::cout << "After push: v[0] = \"" << v[0] << "\", v[1] = \"" << v[1] << "\"\n";
        std::cout << "After push: s1 = \"" << s1 << "\", s2 = \"" << s2 << "\"\n";

        bool ok = (v.size() == 2 && v[0] == "Hello" && v[1] == "World");
        std::cout << "Move push_back test: " << (ok ? "Pass" : "Fail") << "\n";
    }

    {
        std::cout << "\nTest 3: Capacity growth\n";
        Vector<int> v;

        for (int i = 0; i < 5; ++i)
        {
            v.push_back(i);
            std::cout << "After push " << i << ": size=" << v.size()
                << ", capacity=" << v.capacity() << '\n';
        }

        bool ok = (v.size() == 5);
        for (int i = 0; i < 5; ++i)
        {
            if (v[i] != i) ok = false;
        }

        std::cout << "Elements: ";
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << "- " << (ok ? "Pass" : "Fail") << '\n';
    }
}

void test_pop_back() 
{
    std::cout << "\n--- Testing pop_back ---\n";

    Vector<int> v;
    for (int i = 0; i < 5; ++i)
    {
        v.push_back(i);
    }
    std::cout << "Before pop: size=" << v.size() << ", elements: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';

    v.pop_back();
    std::cout << "After pop: size=" << v.size() << ", elements: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << (v.size() == 4 && v[3] == 3 ? " - Pass" : " - Fail") << '\n';

    v.pop_back();
    v.pop_back();
    std::cout << "After 2 more pops: size=" << v.size()
        << (v.size() == 2 ? " - Pass" : " - Fail") << '\n';

    Vector<int> empty;
    empty.pop_back();
    std::cout << "Pop on empty: size=" << empty.size()
        << (empty.size() == 0 ? " - Pass" : " - Fail") << '\n';
}

void test_insert()
{
    std::cout << "\n--- Testing insert ---\n";

    Vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    std::cout << "Initial: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';

    v.insert(2, 99);
    std::cout << "After insert(2,99): ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    bool ok1 = (v.size() == 5 && v[2] == 99);
    std::cout << (ok1 ? " - Pass" : " - Fail") << '\n';

    v.insert(0, 88);
    std::cout << "After insert(0,88): ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    bool ok2 = (v.size() == 6 && v[0] == 88);
    std::cout << (ok2 ? " - Pass" : " - Fail") << '\n';

    v.insert(v.size(), 77);
    std::cout << "After insert at end: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    bool ok3 = (v.size() == 7 && v[6] == 77);
    std::cout << (ok3 ? " - Pass" : " - Fail") << '\n';
    {
        std::cout << "\nTest with large size:\n";
        Vector<int> v;

        for (int i = 0; i < 100; ++i) 
        {
            v.push_back(i);
        }
        std::cout << "Before insert: size=" << v.size()
            << ", capacity=" << v.capacity() << '\n';

        v.insert(50, 999);
        std::cout << "After insert(50,999): size=" << v.size()
            << ", capacity=" << v.capacity() << '\n';

        bool ok = (v.size() == 101 && v[50] == 999);
        for (int i = 0; i < 50; ++i) 
        {
            if (v[i] != i)
            {
                ok = false;
            }
        }
        for (int i = 51; i < 101; ++i) 
        {
            if (v[i] != i - 1)
            {
                ok = false;
            }
        }
        std::cout << "Elements correct: " << (ok ? "Pass" : "Fail") << '\n';
    }

    {
        std::cout << "\nTest move insert:\n";
        Vector<std::string> v;
        v.push_back("zero");
        v.push_back("one");
        v.push_back("two");
        v.push_back("three");

        std::cout << "Before: ";
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << '\n';

        std::string s = "MOVED";
        std::cout << "Before move: s = \"" << s << "\"\n";

        v.insert(2, std::move(s));

        std::cout << "After insert(2, move(s)): ";
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << '\n';
        std::cout << "After move: s = \"" << s << "\" (should be empty)\n";

        bool ok = (v.size() == 5 && v[2] == "MOVED");
        std::cout << (ok ? "Pass" : "Fail") << '\n';
    }

    {
        std::cout << "\nTest exception handling:\n";
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);

        try 
        {
            v.insert(10, 99); 
            std::cout << "Should throw - Fail\n";
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Caught out_of_range - Pass\n";
        }

        try 
        {
            v.insert(v.size() + 1, 99);
            std::cout << "Should throw - Fail\n";
        }
        catch (const std::out_of_range&) 
        {
            std::cout << "Caught out_of_range - Pass\n";
        }
    }
}

void test_erase() 
{
    std::cout << "\n--- Testing erase ---\n";

    Vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    std::cout << "Initial: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';

    v.erase(3);
    std::cout << "After erase(3): ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    bool ok1 = (v.size() == 9 && v[3] == 4);
    std::cout << (ok1 ? " - Pass" : " - Fail") << '\n';

    v.erase(1, 3);
    std::cout << "After erase(1,3): ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    bool ok2 = (v.size() == 6);
    std::cout << (ok2 ? " - Pass" : " - Fail") << '\n';
    {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
        {
            v.push_back(i);
        }

        v.erase(0, 4);
        std::cout << "After erase all(0,4): size=" << v.size();
        std::cout << (v.size() == 0 ? " - Pass" : " - Fail") << '\n';
    }

    {
        Vector<int> v;
        for (int i = 0; i < 10; ++i)
        {
            v.push_back(i);
        }
        size_t old_cap = v.capacity();

        v.erase(3);
        std::cout << "Capacity after erase: " << v.capacity()
            << " (should be " << old_cap << ")";
        std::cout << (v.capacity() == old_cap ? " - Pass" : " - Fail") << '\n';
    }

    {
        Vector<int> v;
        v.push_back(1);
        v.push_back(2);

        try 
        {
            v.erase(5);
            std::cout << "Invalid index 5: Should throw - Fail\n";
        }
        catch (const std::out_of_range&) 
        {
            std::cout << "Invalid index 5: Caught exception - Pass\n";
        }
    }
    {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
        {
            v.push_back(i);
        }

        try
        {
            v.erase(2, 6); 
            std::cout << "Invalid range(2,6): Should throw - Fail\n";
        }
        catch (const std::out_of_range&)
        {
            std::cout << "Invalid range(2,6): Caught exception - Pass\n";
        }

        try 
        {
            v.erase(4, 2); 
            std::cout << "Invalid range(4,2): Should throw - Fail\n";
        }
        catch (const std::out_of_range&) 
        {
            std::cout << "Invalid range(4,2): Caught exception - Pass\n";
        }
    }
    {
        Vector<int> empty;

        try 
        {
            empty.erase(0);
            std::cout << "Erase on empty vector: Should throw - ";
        }
        catch (const std::out_of_range&) 
        {
            std::cout << "Caught exception - Pass\n";
        }

    }


}

void test_reserve_resize() 
{
    std::cout << "\n--- Testing reserve and resize ---\n";

    Vector<int> v;
    for (int i = 0; i < 5; ++i)
    {
        v.push_back(i);
    }
    std::cout << "Initial: size=" << v.size() << ", capacity=" << v.capacity() << '\n';

    v.reserve(20);
    std::cout << "After reserve(20): size=" << v.size()
        << ", capacity=" << v.capacity()
        << (v.capacity() == 20 ? " - Pass" : " - Fail") << '\n';

    v.resize(3);
    std::cout << "After resize(3): size=" << v.size()
        << ", elements: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << (v.size() == 3 ? " - Pass" : " - Fail") << '\n';

    v.resize(6, 42);
    std::cout << "After resize(6,42): size=" << v.size()
        << ", elements: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    bool ok = (v.size() == 6 && v[3] == 42 && v[4] == 42 && v[5] == 42);
    std::cout << (ok ? " - Pass" : " - Fail") << '\n';
}

void test_shrink_to_fit() 
{
    std::cout << "\n--- Testing shrink_to_fit ---\n";

    Vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    std::cout << "Before shrink: size=" << v.size()
        << ", capacity=" << v.capacity() << '\n';

    v.shrink_to_fit();
    std::cout << "After shrink: size=" << v.size()
        << ", capacity=" << v.capacity()
        << (v.capacity() == 10 ? " - Pass" : " - Fail") << '\n';
}

void test_comparison_operators() 
{
    std::cout << "\n--- Testing comparison operators ---\n";

    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    Vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);

    Vector<int> v3;
    v3.push_back(1);
    v3.push_back(2);
    v3.push_back(4);

    std::cout << "v1 == v2: " << (v1 == v2) << " (expected 1)"
        << (v1 == v2 ? " - Pass" : " - Fail") << '\n';
    std::cout << "v1 != v3: " << (v1 != v3) << " (expected 1)"
        << (v1 != v3 ? " - Pass" : " - Fail") << '\n';
    std::cout << "v1 < v3: " << (v1 < v3) << " (expected 1)"
        << (v1 < v3 ? " - Pass" : " - Fail") << '\n';
    std::cout << "v3 > v1: " << (v3 > v1) << " (expected 1)"
        << (v3 > v1 ? " - Pass" : " - Fail") << '\n';
    std::cout << "v2 < v1: " << (v2 < v1) << " (expected 0)"
        << (v2 < v1 ? " - Fail" : " - Pass") << '\n';
    std::cout << "v3 >= v1: " << (v3 >= v1) << " (expected 1)"
        << (v3 >= v1 ? " - Pass" : " - Fail") << '\n';
    std::cout << "v2 <= v1: " << (v2 <= v1) << " (expected 1)"
        << (v2 <= v1 ? " - Pass" : " - Fail") << '\n';
}
void test_assignment_operators()
{
    std::cout << "\n--- Testing assignment operators ---\n";

    {
        Vector<int> v1;
        for (int i = 0; i < 5; ++i)
        {
            v1.push_back(i);
        }

        Vector<int> v2;
        v2.push_back(99);
        v2.push_back(100);

        std::cout << "Before copy assignment:\n";
        std::cout << "  v1: ";
        for (size_t i = 0; i < v1.size(); ++i)
        {
            std::cout << v1[i] << " ";
        }
        std::cout << "(size=" << v1.size() << ", cap=" << v1.capacity() << ")\n";
        std::cout << "  v2: ";
        for (size_t i = 0; i < v2.size(); ++i)
        {
            std::cout << v2[i] << " ";
        }
        std::cout << "(size=" << v2.size() << ", cap=" << v2.capacity() << ")\n";

        v2 = v1;

        std::cout << "After v2 = v1:\n";
        std::cout << "  v1: ";
        for (size_t i = 0; i < v1.size(); ++i)
        {
            std::cout << v1[i] << " ";
        }
        std::cout << "(size=" << v1.size() << ", cap=" << v1.capacity() << ")\n";
        std::cout << "  v2: ";
        for (size_t i = 0; i < v2.size(); ++i)
        {
            std::cout << v2[i] << " ";
        }
        std::cout << "(size=" << v2.size() << ", cap=" << v2.capacity() << ")\n";

        bool ok = (v2.size() == 5);
        for (int i = 0; i < 5; ++i) 
        {
            if (v2[i] != i)
            {
                ok = false;
            }
        }
        std::cout << "Copy assignment test: " << (ok ? "Pass" : "Fail") << "\n";
    }

    {
        Vector<std::string> v1;
        v1.push_back("one");
        v1.push_back("two");
        v1.push_back("three");

        Vector<std::string> v2;
        v2.push_back("temp");
        v2.push_back("data");

        std::cout << "\nBefore move assignment:\n";
        std::cout << "  v1: ";
        for (size_t i = 0; i < v1.size(); ++i)
        {
            std::cout << v1[i] << " ";
        }
        std::cout << "(size=" << v1.size() << ", cap=" << v1.capacity() << ")\n";
        std::cout << "  v2: ";
        for (size_t i = 0; i < v2.size(); ++i)
        {
            std::cout << v2[i] << " ";
        }
        std::cout << "(size=" << v2.size() << ", cap=" << v2.capacity() << ")\n";

        v2 = std::move(v1); 

        std::cout << "After v2 = std::move(v1):\n";
        std::cout << "  v1: ";
        for (size_t i = 0; i < v1.size(); ++i)
        {
            std::cout << v1[i] << " ";
        }
        std::cout << "(size=" << v1.size() << ", cap=" << v1.capacity() << ")\n";
        std::cout << "  v2: ";
        for (size_t i = 0; i < v2.size(); ++i)
        {
            std::cout << v2[i] << " ";
        }
        std::cout << "(size=" << v2.size() << ", cap=" << v2.capacity() << ")\n";

        bool ok = (v2.size() == 3 && v1.size() == 0);
        ok = ok && (v2[0] == "one" && v2[1] == "two" && v2[2] == "three");
        std::cout << "Move assignment test: " << (ok ? "Pass" : "Fail") << "\n";
    }

    {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
        {
            v.push_back(i);
        }

        std::cout << "\nSelf-assignment test:\n";
        std::cout << "Before: ";
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << "(size=" << v.size() << ")\n";

        v = v; 

        std::cout << "After v = v: ";
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << "(size=" << v.size() << ")\n";

        bool ok = (v.size() == 5);
        for (int i = 0; i < 5; ++i) 
        {
            if (v[i] != i)
            {
                ok = false;
            }
        }
        std::cout << "Self-assignment test: " << (ok ? "Pass" : "Fail") << "\n";

        v = std::move(v); 

        std::cout << "After v = std::move(v): ";
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << " ";
        }

        std::cout << "(size=" << v.size() << ")\n";

        ok = (v.size() == 5);
        for (int i = 0; i < 5; ++i)
        {
            if (v[i] != i)
            {
                ok = false;
            }
        }
        std::cout << "Self-move assignment test: " << (ok ? "Pass" : "Fail") << "\n";
    }
}

void test_clear()
{
    std::cout << "\n--- Testing clear ---\n";

    {
        Vector<int> v;
        for (int i = 0; i < 10; ++i)
        {
            v.push_back(i);
        }

        std::cout << "Before clear: size=" << v.size()
            << ", capacity=" << v.capacity() << "\n  elements: ";
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << "\n";

        v.clear();

        std::cout << "After clear: size=" << v.size()
            << ", capacity=" << v.capacity() << "\n";

        bool ok = (v.size() == 0);
        std::cout << "Clear test: " << (ok ? "Pass" : "Fail") << "\n";
    }

    {
        Vector<int> empty;
        std::cout << "\nEmpty vector before clear: size=" << empty.size() << "\n";

        empty.clear();

        std::cout << "Empty vector after clear: size=" << empty.size() << "\n";
        std::cout << "Clear on empty test: " << (empty.size() == 0 ? "Pass" : "Fail") << "\n";
    }

    {
        Vector<int> v;
        for (int i = 0; i < 5; ++i)
        {
            v.push_back(i);
        }
        v.clear();
        v.push_back(42);
        v.push_back(43);

        std::cout << "\nAfter clear + push_backs: ";
        for (size_t i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << "(size=" << v.size() << ")\n";

        bool ok = (v.size() == 2 && v[0] == 42 && v[1] == 43);
        std::cout << "Usage after clear test: " << (ok ? "Pass" : "Fail") << "\n";
    }
}

void test_swap()
{
    std::cout << "\n--- Testing swap ---\n";

    Vector<int> v1;
    for (int i = 0; i < 3; ++i)
    {
        v1.push_back(i * 10);
    }

    Vector<int> v2;
    for (int i = 0; i < 5; ++i)
    {
        v2.push_back(i * 100);
    }

    std::cout << "Before swap:\n";
    std::cout << "  v1: ";
    for (size_t i = 0; i < v1.size(); ++i)
    {
        std::cout << v1[i] << " ";
    }
    std::cout << "(size=" << v1.size() << ", cap=" << v1.capacity() << ")\n";
    std::cout << "  v2: ";
    for (size_t i = 0; i < v2.size(); ++i)
    {
        std::cout << v2[i] << " ";
    }
    std::cout << "(size=" << v2.size() << ", cap=" << v2.capacity() << ")\n";

    v1.swap(v2);

    std::cout << "After v1.swap(v2):\n";
    std::cout << "  v1: ";
    for (size_t i = 0; i < v1.size(); ++i)
    {
        std::cout << v1[i] << " ";
    }
    std::cout << "(size=" << v1.size() << ", cap=" << v1.capacity() << ")\n";
    std::cout << "  v2: ";
    for (size_t i = 0; i < v2.size(); ++i)
    {
        std::cout << v2[i] << " ";
    }
    std::cout << "(size=" << v2.size() << ", cap=" << v2.capacity() << ")\n";

    bool ok1 = (v1.size() == 5);
    for (int i = 0; i < 5; ++i) 
    {
        if (v1[i] != i * 100)
        {
            ok1 = false;
        }
    }

    bool ok2 = (v2.size() == 3);
    for (int i = 0; i < 3; ++i) 
    {
        if (v2[i] != i * 10)
        {
            ok2 = false;
        }
    }

    std::cout << "Swap test: " << ((ok1 && ok2) ? "Pass" : "Fail") << "\n";

    Vector<int> empty;
    Vector<int> v3;
    v3.push_back(1);
    v3.push_back(2);

    std::cout << "\nSwap with empty:\n";
    std::cout << "Before: empty size=" << empty.size() << ", v3 size=" << v3.size() << "\n";

    empty.swap(v3);

    std::cout << "After: empty size=" << empty.size() << ", v3 size=" << v3.size() << "\n";

    bool ok3 = (empty.size() == 2 && v3.size() == 0);
    std::cout << "Swap with empty test: " << (ok3 ? "Pass" : "Fail") << "\n";
}

void test_insertion_sort() 
{
    std::cout << "\n--- Testing insertion_sort ---\n";

    Vector<int> v;
    v.push_back(5);
    v.push_back(2);
    v.push_back(8);
    v.push_back(1);
    v.push_back(9);
    v.push_back(3);

    std::cout << "Before sort: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';

    insertion_sort(v);

    std::cout << "After sort: ";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';

    bool sorted = true;
    for (size_t i = 1; i < v.size(); ++i) 
    {
        if (v[i] < v[i - 1])
        {
            sorted = false;
        }
    }
    std::cout << "Vector is sorted: " << (sorted ? "YES - Pass" : "NO - Fail") << '\n';
}

int main() {
    std::cout << "------------------------------------\n";
    std::cout << "     VECTOR CLASS TESTS       \n";
    std::cout << "------------------------------------\n";

    test_constructors();
    test_access_methods();
    test_push_back();
    test_pop_back();
    test_insert();
    test_erase();
    test_reserve_resize();
    test_shrink_to_fit();
    test_comparison_operators();
    test_assignment_operators();
    test_clear();                  
    test_swap();
    test_insertion_sort();

    return 0;
}