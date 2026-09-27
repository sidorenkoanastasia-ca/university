#include "HashTable.h"
#include <iostream>

void printSeparator()
{
    std::cout << "\n========================================\n" << std::endl;
}

void testInsertAndDuplicates()
{
    std::cout << "=== Test 1: Insert and duplicates ===\n";

    HashTable ht;

    std::cout << "Insert (1.5, Alice): " << (ht.insert(1.5, "Alice") ? "OK" : "FAIL") << '\n';
    std::cout << "Insert (2.7, Bob): " << (ht.insert(2.7, "Bob") ? "OK" : "FAIL") << '\n';
    std::cout << "Insert (3.14, Charlie): " << (ht.insert(3.14, "Charlie") ? "OK" : "FAIL") << '\n';
    std::cout << "Insert (1.5, Duplicate): " << (ht.insert(1.5, "Duplicate") ? "OK" : "FAIL - duplicate blocked") << '\n';

    std::cout << "Number of elements: " << ht.getNumber() << '\n';

    std::cout << "Test 1 COMPLETED\n";
}

void testSearch()
{
    std::cout << "=== Test 2: Search ===\n";

    HashTable ht;
    ht.insert(1.5, "Alice");
    ht.insert(2.7, "Bob");
    ht.insert(3.14, "Charlie");

    std::string value;

    std::cout << "Search 1.5: ";
    if (ht.search(1.5, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Search 2.7: ";
    if (ht.search(2.7, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Search 3.14: ";
    if (ht.search(3.14, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Search 99.9: ";
    if (ht.search(99.9, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Test 2 COMPLETED\n";
}

void testRemove()
{
    std::cout << "=== Test 3: Remove ===\n";

    HashTable ht;
    ht.insert(1.5, "Alice");
    ht.insert(2.7, "Bob");

    std::string value;

    std::cout << "Before remove:\n";
    std::cout << "  Search 1.5: " << (ht.search(1.5, value) ? "FOUND" : "NOT FOUND") << '\n';

    std::cout << "Remove 1.5: " << (ht.remove(1.5) ? "OK" : "FAIL") << '\n';

    std::cout << "After remove:\n";
    std::cout << "  Search 1.5: " << (ht.search(1.5, value) ? "FOUND" : "NOT FOUND") << '\n';

    std::cout << "Remove 1.5 again: " << (ht.remove(1.5) ? "OK" : "FAIL - already removed") << '\n';

    std::cout << "Search 2.7 (still exists): ";
    if (ht.search(2.7, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Number of elements: " << ht.getNumber() << '\n';

    std::cout << "Test 3 COMPLETED\n";
}

void testLongestChain()
{
    std::cout << "=== Test 4: Longest chain ===\n";

    HashTable ht;

    std::cout << "Inserting 50 elements...\n";
    for (int i = 0; i < 50; ++i)
    {
        ht.insert(static_cast<double>(i * 10), "Value" + std::to_string(i));
    }

    std::cout << "Number of elements: " << ht.getNumber() << '\n';
    std::cout << "Longest chain length: " << ht.getLongestChain() << '\n';

    std::cout << "Test 4 COMPLETED\n";
}

void testFloatingPointKeys()
{
    std::cout << "=== TEST 5: Floating point keys ===\n";

    HashTable ht;

    std::cout << "Inserting 10 close numbers (1.0 - 1.9)...\n";
    ht.insert(1.0, "One point zero");
    ht.insert(1.1, "One point one");
    ht.insert(1.2, "One point two");
    ht.insert(1.3, "One point three");
    ht.insert(1.4, "One point four");
    ht.insert(1.5, "One point five");
    ht.insert(1.6, "One point six");
    ht.insert(1.7, "One point seven");
    ht.insert(1.8, "One point eight");
    ht.insert(1.9, "One point nine");

    std::string value;

    std::cout << "Search 1.5: ";
    if (ht.search(1.5, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Search 1.99: ";
    if (ht.search(1.99, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Longest chain: " << ht.getLongestChain() << '\n';

    std::cout << "Test 5 COMPLETED\n";
}

void testRemoveAndReinsert()
{
    std::cout << "=== Test 6: Remove and re-insert ===\n";

    HashTable ht;

    ht.insert(42.0, "Answer");
    std::string value;

    std::cout << "Inserted (42.0, Answer)\n";

    std::cout << "Search 42.0: ";
    if (ht.search(42.0, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Remove 42.0: " << (ht.remove(42.0) ? "OK" : "FAIL") << '\n';

    std::cout << "Search 42.0 after remove: ";
    if (ht.search(42.0, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Re-insert (42.0, The Answer): " << (ht.insert(42.0, "The Answer") ? "OK" : "FAIL") << '\n';

    std::cout << "Search 42.0 after re-insert: ";
    if (ht.search(42.0, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Test 6 COMPLETED\n";
}

void testManyOperations()
{
    std::cout << "=== Test 7: Many operations ===\n";

    HashTable ht;

    std::cout << "Inserting 100 elements (0-99)...\n";
    for (int i = 0; i < 100; ++i)
    {
        ht.insert(static_cast<double>(i), "Number" + std::to_string(i));
    }

    std::cout << "Number of elements: " << ht.getNumber() << '\n';

    std::string value;
    int foundCount = 0;
    for (int i = 0; i < 100; ++i)
    {
        if (ht.search(static_cast<double>(i), value))
        {
            ++foundCount;
        }
    }
    std::cout << "Found " << foundCount << " out of 100 elements\n";

    std::cout << "Removing elements 0-49...\n";
    for (int i = 0; i < 50; ++i)
    {
        ht.remove(static_cast<double>(i));
    }

    std::cout << "Number of elements after removal: " << ht.getNumber() << '\n';

    foundCount = 0;
    for (int i = 0; i < 50; ++i)
    {
        if (ht.search(static_cast<double>(i), value))
        {
            ++foundCount;
        }
    }
    std::cout << "Removed elements still found: " << foundCount << " (should be 0)\n";

    foundCount = 0;
    for (int i = 50; i < 100; ++i)
    {
        if (ht.search(static_cast<double>(i), value))
        {
            ++foundCount;
        }
    }
    std::cout << "Remaining elements found: " << foundCount << " (should be 50)\n";

    std::cout << "Longest chain: " << ht.getLongestChain() << '\n';

    std::cout << "Test 7 COMPLETED\n";
}

void testPrint()
{
    std::cout << "=== Test 8: Print table ===\n";

    HashTable ht;
    ht.insert(10.5, "Ten");
    ht.insert(20.3, "Twenty");
    ht.insert(30.7, "Thirty");
    ht.insert(40.1, "Forty");
    ht.insert(50.9, "Fifty");

    std::cout << "Table contents:\n";
    ht.print(std::cout);

    std::cout << "Test 8 COMPLETED\n";
}

void testMoveConstructor()
{
    std::cout << "=== Test 9: Move constructor ===\n";

    HashTable ht1;
    ht1.insert(1.0, "First");
    ht1.insert(2.0, "Second");
    ht1.insert(3.0, "Third");

    std::cout << "Original table before move:\n";
    ht1.print(std::cout);

    HashTable ht2 = std::move(ht1);

    std::cout << "New table after move:\n";
    ht2.print(std::cout);

    std::string value;
    std::cout << "Search in new table 2.0: ";
    if (ht2.search(2.0, value))
    {
        std::cout << "FOUND -> " << value << '\n';
    }
    else
    {
        std::cout << "NOT FOUND\n";
    }

    std::cout << "Test 9 COMPLETED\n";
}

void testMoveAssignment()
{
    std::cout << "=== Test 10: Move assignment ===\n";

    HashTable ht1;
    ht1.insert(1.0, "First");
    ht1.insert(2.0, "Second");

    HashTable ht2;
    ht2.insert(3.0, "Third");
    ht2.insert(4.0, "Fourth");

    std::cout << "Before move assignment:\n";
    std::cout << "  ht1 size: " << ht1.getNumber() << '\n';
    std::cout << "  ht2 size: " << ht2.getNumber() << '\n';

    ht2 = std::move(ht1);

    std::cout << "After move assignment:\n";
    std::cout << "  ht2 size: " << ht2.getNumber() << '\n';

    std::cout << "ht2 contents:\n";
    ht2.print(std::cout);

    std::cout << "Test 10 COMPLETED\n";
}

void testHashFunctionDistribution()
{
    std::cout << "=== Test 11: Hash function distribution ===\n";

    HashTable ht;

    std::cout << "Inserting 1000 close keys (1.00, 1.01, 1.02, ...)...\n";
    for (int i = 0; i < 1000; ++i)
    {
        double key = 1.0 + static_cast<double>(i) / 100.0;
        ht.insert(key, "Value" + std::to_string(i));
    }

    std::cout << "Number of elements: " << ht.getNumber() << '\n';
    std::cout << "Longest chain: " << ht.getLongestChain() << '\n';

    std::cout << "Test 11 COMPLETED\n";
}

int main()
{
    std::cout << "========== HASH TABLE TESTS ==========\n";

    testInsertAndDuplicates();
    printSeparator();

    testSearch();
    printSeparator();

    testRemove();
    printSeparator();

    testLongestChain();
    printSeparator();

    testFloatingPointKeys();
    printSeparator();

    testRemoveAndReinsert();
    printSeparator();

    testManyOperations();
    printSeparator();

    testPrint();
    printSeparator();

    testMoveConstructor();
    printSeparator();

    testMoveAssignment();
    printSeparator();

    testHashFunctionDistribution();
    printSeparator();

    return 0;
}