#include <iostream>
#include <string>
#include <sstream>
#include "avltree.h"
#include "linenumbers.h"
#include "crossreferences.h"

int testsPassed = 0;
int testsFailed = 0;

void testResult(const char* testName, bool condition)
{
    if (condition)
    {
        std::cout << "[PASS] " << testName << '\n';
        testsPassed++;
    }
    else
    {
        std::cout << "[FAIL] " << testName << '\n';
        testsFailed++;
    }
}

void printTestSummary()
{
    std::cout << "\n========== TEST SUMMARY ==========\n";
    std::cout << "Passed: " << testsPassed << '\n';
    std::cout << "Failed: " << testsFailed << '\n';
    std::cout << "Total:  " << (testsPassed + testsFailed) << '\n';
}

// ========== TESTS AVL-TREE ==========

void testConstructorAndEmpty()
{
    std::cout << "\n--- Test AVL1: Constructor and empty ---\n";

    AVLtree<int, std::string> tree;
    testResult("Constructor - tree empty", tree.empty());
    testResult("size() = 0", tree.size() == 0);
}

void testInsertAndSize()
{
    std::cout << "\n--- Test AVL2: Insert and size ---\n";
    AVLtree<int, std::string> tree;
    tree.insert(10, "value_10");
    testResult("after insert 10 - isAVL() true", tree.isAVL());
    tree.insert(20, "value_20");
    testResult("after insert 20 - isAVL() true", tree.isAVL());
    tree.insert(30, "value_30");
    testResult("after insert 30 - isAVL() true", tree.isAVL());
    testResult("insert 3 elements - size = 3", tree.size() == 3);
    testResult("empty() returns false", !tree.empty());
    tree.insert(20, "updated_value_20");
    testResult("insert existing key - size unchanged", tree.size() == 3);
    testResult("after update - isAVL() true", tree.isAVL());
}

void testSearch()
{
    std::cout << "\n--- Test AVL3: Search ---\n";

    AVLtree<int, std::string> tree;
    tree.insert(10, "hello");
    tree.insert(20, "world");
    tree.insert(30, "avltree");

    std::string value;
    bool found = tree.search(20, value);
    testResult("search existing key - returns true", found);
    testResult("search existing key - correct value", value == "world");
    testResult("contains() - true for existing key", tree.search(20));

    found = tree.search(999, value);
    testResult("search non-existing - returns false", !found);
    testResult("contains() - false for non-existing", !tree.search(999));
}

void testRemove()
{
    std::cout << "\n--- Test AVL4: Remove ---\n";
    AVLtree<int, std::string> tree;

    for (int i = 1; i <= 10; ++i)
    {
        tree.insert(i, "value_" + std::to_string(i));
    }
    testResult("size before remove = 10", tree.size() == 10);
    testResult("before remove - isAVL() true", tree.isAVL());
    bool removed = tree.remove(10);
    testResult("remove leaf - returns true", removed);
    testResult("size after remove = 9", tree.size() == 9);
    testResult("removed element not found", !tree.search(10));
    testResult("after remove leaf - isAVL() true", tree.isAVL());
    removed = tree.remove(5);
    testResult("remove node with two children - returns true", removed);
    testResult("size after remove = 8", tree.size() == 8);
    testResult("after remove node with two children - isAVL() true", tree.isAVL());
    removed = tree.remove(999);
    testResult("remove non-existing - returns false", !removed);
    testResult("size unchanged", tree.size() == 8);
    testResult("after remove non-existing - isAVL() true", tree.isAVL());
    for (int i = 1; i <= 10; ++i)
    {
        tree.remove(i);
    }
    testResult("remove all - tree empty", tree.empty());
}

void testTraversals()
{
    std::cout << "\n--- Test AVL5: Traversals (visual check) ---\n";

    AVLtree<int, std::string> tree;
    tree.insert(5, "a");
    tree.insert(3, "b");
    tree.insert(7, "c");
    tree.insert(2, "d");
    tree.insert(4, "e");
    tree.insert(6, "f");
    tree.insert(8, "g");

    std::cout << "Tree structure (print): ";
    tree.print(std::cout);
    std::cout << "\n";

    std::cout << "In-order traversal:   ";
    tree.inOrderWalk(std::cout);
    std::cout << "\n";

    std::cout << "Pre-order traversal:  ";
    tree.preOrderWalk(std::cout);
    std::cout << "\n";

    std::cout << "Post-order traversal: ";
    tree.postOrderWalk(std::cout);
    std::cout << "\n";

    std::cout << "Check visually that in-order is sorted (2 3 4 5 6 7 8)\n";
    testResult("in-order traversal executed (visual check)", true);
}

void testUpdateValue()
{
    std::cout << "\n--- Test AVL6: Update value on existing key ---\n";

    AVLtree<int, std::string> tree;
    tree.insert(42, "initial");

    std::string value;
    tree.search(42, value);
    testResult("initial value correct", value == "initial");

    tree.insert(42, "updated");
    tree.search(42, value);
    testResult("value updated after insert", value == "updated");
    testResult("size unchanged after update", tree.size() == 1);
}

void testCopyConstructor()
{
    std::cout << "\n--- Test AVL7: Copy constructor ---\n";

    AVLtree<int, std::string> tree1;
    tree1.insert(1, "one");
    tree1.insert(2, "two");
    tree1.insert(3, "three");

    AVLtree<int, std::string> tree2(tree1);

    testResult("copy - same size", tree2.size() == tree1.size());

    tree1.insert(4, "four");
    testResult("original size changed", tree1.size() == 4);
    testResult("copy size unchanged", tree2.size() == 3);

    std::string val;
    tree2.search(2, val);
    testResult("copied data correct", val == "two");
}

void testCopyEmptyTree()
{
    std::cout << "\n--- Test AVL8: Copy empty tree ---\n";
    AVLtree<int, std::string> tree1;
    AVLtree<int, std::string> tree2(tree1);

    testResult("copy empty tree - size 0", tree2.size() == 0);
    testResult("copy empty tree - empty", tree2.empty());
}

void testAssignmentOperator()
{
    std::cout << "\n--- Test AVL9: Assignment operator ---\n";
    AVLtree<int, std::string> tree1;
    tree1.insert(1, "one");
    tree1.insert(2, "two");
    AVLtree<int, std::string> tree2;
    tree2.insert(99, "ninety nine");
    tree2 = tree1;
    testResult("assignment - same size", tree2.size() == tree1.size());
    std::string val;
    tree2.search(1, val);
    testResult("assigned data correct", val == "one");
}

void testSelfAssignment()
{
    std::cout << "\n--- Test AVL10: Self assignment ---\n";
    AVLtree<int, std::string> tree;
    tree.insert(1, "one");
    tree.insert(2, "two");
    tree = tree;
    testResult("self assignment - size unchanged", tree.size() == 2);
    std::string val;
    tree.search(1, val);
    testResult("self assignment - data intact", val == "one");
}

void testMoveConstructor()
{
    std::cout << "\n--- Test AVL11: Move constructor ---\n";
    AVLtree<int, std::string> tree1;
    tree1.insert(1, "one");
    tree1.insert(2, "two");
    int oldSize = tree1.size();
    AVLtree<int, std::string> tree2(std::move(tree1));
    testResult("move - new tree has data", tree2.size() == oldSize);
    testResult("move - old tree is empty", tree1.empty());
    std::string val;
    tree2.search(1, val);
    testResult("moved data correct", val == "one");
}

void testIsAVL()
{
    std::cout << "\n--- Test AVL13: isAVL() balance check ---\n";
    AVLtree<int, std::string> avlTree;
    for (int i = 1; i <= 50; ++i)
    {
        avlTree.insert(i, "val_" + std::to_string(i));
    }
    testResult("AVL tree - balanced after 50 sorted inserts", avlTree.isAVL());
    for (int i = 1; i <= 25; ++i)
    {
        avlTree.remove(i);
    }
    testResult("AVL tree - balanced after 25 deletions", avlTree.isAVL());
    AVLtree<int, std::string> unbalancedTree;
    for (int i = 1; i <= 50; ++i)
    {
        unbalancedTree.insertWithoutBalance(i, "val_" + std::to_string(i));
    }
    testResult("Unbalanced tree - isAVL() returns false", !unbalancedTree.isAVL());
    int avlHeight = avlTree.getHeight();
    int unbalancedHeight = unbalancedTree.getHeight();
    std::cout << "  AVL tree height: " << avlHeight << "\n";
    std::cout << "  Unbalanced tree height: " << unbalancedHeight << "\n";
}

void testGetHeight()
{
    std::cout << "\n--- Test AVL14: getHeight() ---\n";
    AVLtree<int, std::string> tree;
    testResult("empty tree height = 0", tree.getHeight() == 0);
    tree.insert(1, "a");
    testResult("1 node height = 1", tree.getHeight() == 1);
    tree.insert(2, "b");
    tree.insert(3, "c");
    testResult("height after inserts <= 2", tree.getHeight() <= 2);
}

// ========== TESTS LINENUMBERS ==========

void testLineNumbersConstructor()
{
    std::cout << "\n--- Test LN1: Constructors ---\n";
    LineNumbers ln1;
    testResult("default constructor - size 0", ln1.size() == 0);
    LineNumbers ln2(5);
    testResult("constructor with line - size 1", ln2.size() == 1);
    testResult("constructor with line - value correct", ln2.getLine(0) == 5);
}

void testLineNumbersAdd()
{
    std::cout << "\n--- Test LN2: add() ---\n";
    LineNumbers ln;
    ln.add(1);
    ln.add(2);
    ln.add(3);
    testResult("add 3 numbers - size 3", ln.size() == 3);
    testResult("add - order preserved", ln.getLine(0) == 1 && ln.getLine(1) == 2 && ln.getLine(2) == 3);
    ln.add(3);
    testResult("duplicate ignored - size unchanged", ln.size() == 3);
    ln.add(5);
    testResult("add after duplicate - size 4", ln.size() == 4);
    testResult("new element added at end", ln.getLine(3) == 5);
}

void testLineNumbersCapacityExpansion()
{
    std::cout << "\n--- Test LN3: Capacity expansion ---\n";

    LineNumbers ln;
    for (int i = 1; i <= 100; ++i)
    {
        ln.add(i);
    }
    testResult("100 elements added", ln.size() == 100);
    testResult("first element correct", ln.getLine(0) == 1);
    testResult("last element correct", ln.getLine(99) == 100);
}

void testLineNumbersCopyAndAssignment()
{
    std::cout << "\n--- Test LN4: Copy and assignment ---\n";
    LineNumbers ln1;
    ln1.add(1);
    ln1.add(2);
    ln1.add(3);
    LineNumbers ln2(ln1);
    testResult("copy constructor - same size", ln2.size() == ln1.size());
    testResult("copy constructor - data correct", ln2.getLine(1) == 2);
    LineNumbers ln3;
    ln3 = ln1;
    testResult("assignment operator - same size", ln3.size() == ln1.size());
    testResult("assignment operator - data correct", ln3.getLine(2) == 3);
    ln1.add(4);
    testResult("original modified - copy unchanged", ln2.size() == 3);
}

void testLineNumbersMove()
{
    std::cout << "\n--- Test LN5: Move constructor and assignment ---\n";
    LineNumbers ln1;
    ln1.add(10);
    ln1.add(20);
    int oldSize = ln1.size();
    LineNumbers ln2(std::move(ln1));
    testResult("move constructor - new has data", ln2.size() == oldSize);
    testResult("move constructor - old is empty", ln1.size() == 0);
    LineNumbers ln3;
    ln3.add(99);
    ln3 = std::move(ln2);
    testResult("move assignment - target has data", ln3.size() == oldSize);
    testResult("move assignment - source is empty", ln2.size() == 0);
}

void testLineNumbersGetLine()
{
    std::cout << "\n--- Test LN6: getLine() ---\n";
    LineNumbers ln;
    ln.add(5);
    ln.add(10);
    ln.add(15);
    testResult("getLine valid index 0", ln.getLine(0) == 5);
    testResult("getLine valid index 1", ln.getLine(1) == 10);
    testResult("getLine valid index 2", ln.getLine(2) == 15);
    testResult("getLine invalid negative", ln.getLine(-1) == -1);
    testResult("getLine out of range", ln.getLine(99) == -1);
}

void testLineNumbersPrint()
{
    std::cout << "\n--- Test LN7: print() and operator<< ---\n";

    LineNumbers ln;
    ln.add(1);
    ln.add(2);
    ln.add(3);
    std::stringstream ss;
    ln.print(ss);
    testResult("print() - not empty", !ss.str().empty());
    std::stringstream ss2;
    ss2 << ln;
    testResult("operator<< - works", !ss2.str().empty());
    testResult("operator<< - format correct", ss2.str() == "1, 2, 3");
}

void testLineNumbersEmpty()
{
    std::cout << "\n--- Test LN8: Empty LineNumbers ---\n";
    LineNumbers ln;
    testResult("empty - size 0", ln.size() == 0);
    testResult("empty - getLine returns -1", ln.getLine(0) == -1);
    std::stringstream ss;
    ln.print(ss);
    testResult("empty - print produces empty string", ss.str().empty());
    std::stringstream ss2;
    ss2 << ln;
    testResult("empty - operator<< produces empty", ss2.str().empty());
}

void testLineNumbersAddDuplicateSequence()
{
    std::cout << "\n--- Test LN9: Add duplicate sequence ---\n";
    LineNumbers ln;
    ln.add(1);
    ln.add(1);
    ln.add(1);
    ln.add(2);
    ln.add(2);
    ln.add(3);
    testResult("multiple duplicates - size 3", ln.size() == 3);
    testResult("order preserved", ln.getLine(0) == 1 && ln.getLine(1) == 2 && ln.getLine(2) == 3);
}

// ========== TESTS CROSS REFERENCES ==========

void testIsWordChar()
{
    std::cout << "\n--- Test CR1: isWordChar() ---\n";

    testResult("isWordChar('a') - true", isWordChar('a') == true);
    testResult("isWordChar('Z') - true", isWordChar('Z') == true);
    testResult("isWordChar('0') - true", isWordChar('0') == true);
    testResult("isWordChar('-') - true", isWordChar('-') == true);
    testResult("isWordChar('\\'') - true", isWordChar('\'') == true);
    testResult("isWordChar(' ') - false", isWordChar(' ') == false);
    testResult("isWordChar('.') - false", isWordChar('.') == false);
    testResult("isWordChar(',') - false", isWordChar(',') == false);
    testResult("isWordChar('!') - false", isWordChar('!') == false);
    testResult("isWordChar('?') - false", isWordChar('?') == false);
}

void testSplitIntoWordsNormal()
{
    std::cout << "\n--- Test CR2: splitIntoWords normal cases ---\n";
    std::string line = "Hello world";
    int maxWords = static_cast<int>(line.length() / 2 + 1);
    std::string* words = new std::string[maxWords];
    int wordCount = 0;
    splitIntoWords(line, words, wordCount, maxWords);
    testResult("'Hello world' - wordCount = 2", wordCount == 2);
    if (wordCount >= 2)
    {
        testResult("first word 'hello'", words[0] == "hello");
        testResult("second word 'world'", words[1] == "world");
    }
    delete[] words;
}

void testSplitIntoWordsPunctuation()
{
    std::cout << "\n--- Test CR3: splitIntoWords with punctuation ---\n";
    std::string line = "Hello, world! How are you?";
    int maxWords = static_cast<int>(line.length() / 2 + 1);
    std::string* words = new std::string[maxWords];
    int wordCount = 0;
    splitIntoWords(line, words, wordCount, maxWords);
    testResult("punctuation sentence - wordCount = 5", wordCount == 5);
    if (wordCount >= 5)
    {
        testResult("'Hello,' -> 'hello'", words[0] == "hello");
        testResult("'world!' -> 'world'", words[1] == "world");
        testResult("'How' -> 'how'", words[2] == "how");
        testResult("'are' -> 'are'", words[3] == "are");
        testResult("'you?' -> 'you'", words[4] == "you");
    }
    delete[] words;
}

void testSplitIntoWordsHyphenAndApostrophe()
{
    std::cout << "\n--- Test CR4: splitIntoWords with hyphens and apostrophes ---\n";
    std::string line = "Don't forget about AVL-tree";
    int maxWords = static_cast<int>(line.length() / 2 + 1);
    std::string* words = new std::string[maxWords];
    int wordCount = 0;
    splitIntoWords(line, words, wordCount, maxWords);
    testResult("hyphen/apostrophe - wordCount = 4", wordCount == 4);
    if (wordCount >= 4)
    {
        testResult("'Don't' -> 'don't'", words[0] == "don't");
        testResult("'AVL-tree' -> 'avl-tree'", words[3] == "avl-tree");
    }
    delete[] words;
}

void testSplitIntoWordsCase()
{
    std::cout << "\n--- Test CR5: splitIntoWords case insensitivity ---\n";
    std::string line = "HeLLo WoRlD";
    int maxWords = static_cast<int>(line.length() / 2 + 1);
    std::string* words = new std::string[maxWords];
    int wordCount = 0;
    splitIntoWords(line, words, wordCount, maxWords);
    testResult("mixed case - wordCount = 2", wordCount == 2);
    if (wordCount >= 2)
    {
        testResult("'HeLLo' -> 'hello'", words[0] == "hello");
        testResult("'WoRlD' -> 'world'", words[1] == "world");
    }
    delete[] words;
}

void testSplitIntoWordsEdgeCases()
{
    std::cout << "\n--- Test CR6: splitIntoWords edge cases ---\n";
    std::string line = "";
    int maxWords = static_cast<int>(line.length() / 2 + 1);
    if (maxWords < 1)
    {
        maxWords = 1;
    }
    std::string* words = new std::string[maxWords];
    int wordCount = 0;
    splitIntoWords(line, words, wordCount, maxWords);
    testResult("empty string - wordCount = 0", wordCount == 0);
    delete[] words;
    line = "   \t .,;!?()";
    maxWords = static_cast<int>(line.length() / 2 + 1);
    words = new std::string[maxWords];
    wordCount = 0;
    splitIntoWords(line, words, wordCount, maxWords);
    testResult("only delimiters - wordCount = 0", wordCount == 0);
    delete[] words;
    line = "   hello   world   ";
    maxWords = static_cast<int>(line.length() / 2 + 1);
    words = new std::string[maxWords];
    wordCount = 0;
    splitIntoWords(line, words, wordCount, maxWords);
    testResult("leading/trailing spaces - wordCount = 2", wordCount == 2);
    if (wordCount >= 2)
    {
        testResult("'hello'", words[0] == "hello");
        testResult("'world'", words[1] == "world");
    }

    delete[] words;
}

void testLongWord()
{
    std::cout << "\n--- Test CR7: Very long word ---\n";
    std::string longWord(1000, 'a');
    std::string line = longWord;
    int maxWords = 1;
    std::string* words = new std::string[maxWords];
    int wordCount = 0;
    splitIntoWords(line, words, wordCount, maxWords);
    testResult("long word - wordCount = 1", wordCount == 1);
    if (wordCount >= 1)
    {
        testResult("long word - content preserved", words[0] == longWord);
    }

    delete[] words;
}

void testProcessTextSimple()
{
    std::cout << "\n--- Test CR8: processText simple input ---\n";
    std::string input = "Hello world\nHello again\n";
    std::stringstream in(input);
    std::stringstream out;
    AVLtree<std::string, LineNumbers> tree;
    processText(in, out, tree);
    testResult("processText - tree not empty", !tree.empty());
    testResult("processText - size = 3", tree.size() == 3);
    LineNumbers lines;
    tree.search("hello", lines);
    testResult("'hello' appears on lines 1 and 2", lines.size() == 2);
    testResult("'hello' line numbers", lines.getLine(0) == 1 && lines.getLine(1) == 2);
    tree.search("world", lines);
    testResult("'world' appears on line 1", lines.size() == 1 && lines.getLine(0) == 1);
    tree.search("again", lines);
    testResult("'again' appears on line 2", lines.size() == 1 && lines.getLine(0) == 2);
}

void testProcessTextWithPunctuation()
{
    std::cout << "\n--- Test CR9: processText with punctuation ---\n";
    std::string input = "Hello, world!\nDon't forget about AVL-tree.\n";
    std::stringstream in(input);
    std::stringstream out;
    AVLtree<std::string, LineNumbers> tree;
    processText(in, out, tree);
    testResult("punctuation test - size = 6", tree.size() == 6);
    LineNumbers lines;
    tree.search("hello", lines);
    testResult("'hello' found", lines.size() >= 1);
    tree.search("don't", lines);
    testResult("'don't' with apostrophe preserved", lines.size() >= 1);
    tree.search("avl-tree", lines);
    testResult("'avl-tree' with hyphen preserved", lines.size() >= 1);
}

void testProcessTextEmpty()
{
    std::cout << "\n--- Test CR10: processText empty input ---\n";
    std::string input = "";
    std::stringstream in(input);
    std::stringstream out;
    AVLtree<std::string, LineNumbers> tree;
    processText(in, out, tree);
    testResult("empty input - tree empty", tree.empty());
    testResult("empty input - size 0", tree.size() == 0);
}

void testProcessTextSameWordMultipleLines()
{
    std::cout << "\n--- Test CR11: processText same word on multiple lines ---\n";
    std::string input = "test\nword test\nanother test\n";
    std::stringstream in(input);
    std::stringstream out;
    AVLtree<std::string, LineNumbers> tree;
    processText(in, out, tree);
    LineNumbers lines;
    tree.search("test", lines);
    testResult("'test' appears on lines 1,2,3", lines.size() == 3);
    testResult("'test' line numbers 1,2,3",
        lines.getLine(0) == 1 && lines.getLine(1) == 2 && lines.getLine(2) == 3);
}

void testPrintCrossReferences()
{
    std::cout << "\n--- Test CR12: printCrossReferences ---\n";

    AVLtree<std::string, LineNumbers> tree;
    tree.insert("apple", LineNumbers(1));
    tree.insert("banana", LineNumbers(2));
    tree.insert("apple", LineNumbers(3));
    tree.insert("cherry", LineNumbers(1));
    std::cout << "Expected: apple : 3, banana : 2, cherry : 1\n";
    std::cout << "Actual:\n";
    printCrossReferences(std::cout, tree);
    testResult("printCrossReferences - check output manually", true);
}


int main()
{
    std::cout << "========== AVL TREE TESTS ==========\n";

    testConstructorAndEmpty();
    testInsertAndSize();
    testSearch();
    testRemove();
    testTraversals();
    testUpdateValue();
    testCopyConstructor();
    testCopyEmptyTree();
    testAssignmentOperator();
    testSelfAssignment();
    testMoveConstructor();
    testIsAVL();
    testGetHeight();

    printTestSummary();

    std::cout << "\n========== LINENUMBERS TESTS ==========\n";

    testLineNumbersConstructor();
    testLineNumbersAdd();
    testLineNumbersCapacityExpansion();
    testLineNumbersCopyAndAssignment();
    testLineNumbersMove();
    testLineNumbersGetLine();
    testLineNumbersPrint();
    testLineNumbersEmpty();
    testLineNumbersAddDuplicateSequence();

    printTestSummary();

    std::cout << "\n========== CROSS REFERENCES TESTS ==========\n";

    testIsWordChar();
    testSplitIntoWordsNormal();
    testSplitIntoWordsPunctuation();
    testSplitIntoWordsHyphenAndApostrophe();
    testSplitIntoWordsCase();
    testSplitIntoWordsEdgeCases();
    testLongWord();
    testProcessTextSimple();
    testProcessTextWithPunctuation();
    testProcessTextEmpty();
    testProcessTextSameWordMultipleLines();
    testPrintCrossReferences();

    printTestSummary();

    return 0;
}