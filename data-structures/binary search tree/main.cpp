#include <iostream>
#include "bst.h"

void printToConsole(const int& value)
{
    std::cout << value << " ";
}

void printDouble(const int& value)
{
    std::cout << value * 2 << " ";
}

void testInsertAndSearch()
{
    std::cout << "\n========== testInsertAndSearch ==========\n";
    BinarySearchTree<int> tree;

    std::cout << "Inserting: 5, 3, 7, 1, 4, 6, 9\n";
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);

    std::cout << "Search 5: " << (tree.searchIterative(5) ? "found" : "not found") << "\n";
    std::cout << "Search 3: " << (tree.searchIterative(3) ? "found" : "not found") << "\n";
    std::cout << "Search 9: " << (tree.searchIterative(9) ? "found" : "not found") << "\n";
    std::cout << "Search 10: " << (tree.searchIterative(10) ? "found" : "not found") << "\n";
    std::cout << "Search 0: " << (tree.searchIterative(0) ? "found" : "not found") << "\n";
}

void testOutput()
{
    std::cout << "\n========== testOutput ==========\n";
    BinarySearchTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);

    std::cout << "Tree structure: ";
    tree.output(std::cout);
    std::cout << "\n";
}

void testNumberOfNodes()
{
    std::cout << "\n========== testNumberOfNodes ==========\n";
    BinarySearchTree<int> tree;

    std::cout << "Empty tree nodes: " << tree.getNumberOfNodes() << "\n";

    tree.insert(5);
    std::cout << "After 5: " << tree.getNumberOfNodes() << "\n";

    tree.insert(3);
    tree.insert(7);
    std::cout << "After 5,3,7: " << tree.getNumberOfNodes() << "\n";

    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);
    std::cout << "After 7 nodes: " << tree.getNumberOfNodes() << "\n";
}

void testHeight()
{
    std::cout << "\n========== testHeight ==========\n";
    BinarySearchTree<int> tree;

    std::cout << "Empty tree height: " << tree.getHeight() << "\n";

    tree.insert(5);
    std::cout << "After 5: " << tree.getHeight() << "\n";

    tree.insert(3);
    tree.insert(7);
    std::cout << "After 5,3,7: " << tree.getHeight() << "\n";

    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);
    std::cout << "After 7 nodes: " << tree.getHeight() << "\n";
}

void testInorderWalk()
{
    std::cout << "\n========== testInorderWalk ==========\n";
    BinarySearchTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);

    std::cout << "Inorder (print): ";
    tree.inorderWalk(printToConsole);
    std::cout << "\n";

    std::cout << "Inorder (double): ";
    tree.inorderWalk(printDouble);
    std::cout << "\n";
}

void testInorderWalkIterative()
{
    std::cout << "\n========== testInorderWalkIterative ==========\n";
    BinarySearchTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);

    std::cout << "Inorder iterative (print): ";
    tree.inorderWalkIterative(printToConsole);
    std::cout << "\n";

    std::cout << "Inorder iterative (double): ";
    tree.inorderWalkIterative(printDouble);
    std::cout << "\n";
}

void testWalkByLevels()
{
    std::cout << "\n========== testWalkByLevels ==========\n";
    BinarySearchTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);

    std::cout << "Level order (print): ";
    tree.walkByLevels(printToConsole);
    std::cout << "\n";

    std::cout << "Level order (double): ";
    tree.walkByLevels(printDouble);
    std::cout << "\n";
}

void testRemove()
{
    std::cout << "\n========== testRemove ==========\n";
    BinarySearchTree<int> tree;

    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);

    std::cout << "Original tree: ";
    tree.inorderWalk(printToConsole);
    std::cout << "\n";

    std::cout << "Remove 1 (leaf): ";
    tree.remove(1);
    tree.inorderWalk(printToConsole);
    std::cout << "\n";

    std::cout << "Remove 3 (has child 4): ";
    tree.remove(3);
    tree.inorderWalk(printToConsole);
    std::cout << "\n";

    std::cout << "Remove 5 (has two children): ";
    tree.remove(5);
    tree.inorderWalk(printToConsole);
    std::cout << "\n";

    std::cout << "Remove 100 (not exists): ";
    std::cout << (tree.remove(100) ? "deleted" : "not found") << "\n";
}

void testCountInRange()
{
    std::cout << "\n========== testCountInRange ==========\n";
    BinarySearchTree<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(13);
    tree.insert(18);
    tree.insert(25);

    std::cout << "Tree: ";
    tree.inorderWalk(printToConsole);
    std::cout << "\n";

    std::cout << "Count in [6, 13]: " << tree.countNodeInRange(6, 13) << "\n";
    std::cout << "Count in [1, 25]: " << tree.countNodeInRange(1, 25) << "\n";
    std::cout << "Count in [100, 200]: " << tree.countNodeInRange(100, 200) << "\n";
    std::cout << "Count in [10, 10]: " << tree.countNodeInRange(10, 10) << "\n";
    std::cout << "Count in [-5, 0]: " << tree.countNodeInRange(-5, 0) << "\n";
}

void testMoveSemantics()
{
    std::cout << "\n========== testMoveSemantics ==========\n";
    BinarySearchTree<int> tree1;

    tree1.insert(5);
    tree1.insert(3);
    tree1.insert(7);

    std::cout << "tree1: ";
    tree1.inorderWalk(printToConsole);
    std::cout << "\n";

    BinarySearchTree<int> tree2 = std::move(tree1);
    std::cout << "tree2 (after move from tree1): ";
    tree2.inorderWalk(printToConsole);
    std::cout << "\n";

    std::cout << "tree1 (after move, should be empty): ";
    tree1.inorderWalk(printToConsole);
    std::cout << "(empty)\n";

    BinarySearchTree<int> tree3;
    tree3.insert(100);
    tree3 = std::move(tree2);
    std::cout << "tree3 (after move assignment from tree2): ";
    tree3.inorderWalk(printToConsole);
    std::cout << "\n";

    std::cout << "tree2 (after move assignment, should be empty): ";
    tree2.inorderWalk(printToConsole);
    std::cout << "(empty)\n";
}

void testDegenerateTree()
{
    std::cout << "\n========== testDegenerateTree ==========\n";
    BinarySearchTree<int> tree;

    std::cout << "Inserting in ascending order: 1,2,3,4,5,6,7\n";
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);

    std::cout << "Tree structure: ";
    tree.output(std::cout);
    std::cout << "\n";

    std::cout << "Height (should be 6): " << tree.getHeight() << "\n";
    std::cout << "Number of nodes: " << tree.getNumberOfNodes() << "\n";
    std::cout << "Search 7: " << (tree.searchIterative(7) ? "found" : "not found") << "\n";
    std::cout << "Count in [3,5]: " << tree.countNodeInRange(3, 5) << "\n";
}

int main()
{
    testInsertAndSearch();
    testOutput();
    testNumberOfNodes();
    testHeight();
    testInorderWalk();
    testInorderWalkIterative();
    testWalkByLevels();
    testRemove();
    testCountInRange();
    testMoveSemantics();
    testDegenerateTree();

    std::cout << "\n========== ALL TESTS COMPLETED ==========\n";

    BinarySearchTree<int> tree;
    tree.insert(15);
    tree.insert(10);
    tree.insert(3);
    tree.insert(12);
    tree.insert(8);
    tree.insert(25);
    tree.insert(20);
    tree.output(std::cout);
    std::cout << '\n';
    tree.remove(8);
    tree.output(std::cout);
    std::cout << '\n';
    tree.remove(10);
    tree.output(std::cout);
    std::cout << '\n';
    tree.remove(15);
    tree.output(std::cout);
    std::cout << '\n';
    return 0;
}