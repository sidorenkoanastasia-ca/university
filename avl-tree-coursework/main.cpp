#include <iostream>
#include <fstream>
#include <string>
#include "avltree.h"
#include "linenumbers.h"
#include "crossreferences.h"

int main()
{
    AVLtree<std::string, LineNumbers> tree;

    std::cout << "Choose input source:\n1. File\n2. Console\n> ";
    int choice;
    if (!(std::cin >> choice))
    {
        return 0;
    }
    std::cin.ignore();

    if (choice == 1)
    {
        std::string filename;
        std::cout << "Enter filename: ";
        std::getline(std::cin, filename);

        if (filename.empty())
        {
            std::cerr << "Error: filename cannot be empty!\n";
            return 1;
        }

        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error: cannot open file '" << filename << "'\n";
            return 1;
        }
        processText(file, std::cout, tree);
        std::cout << "Tree is balanced: " << ((tree.isAVL()) ? "PASS" : "FAIL") << '\n';
        file.close();
    }
    else if (choice == 2)
    {
        std::cout << "Enter your text:\n";
        processText(std::cin, std::cout, tree);
    }
    else
    {
        std::cerr << "Error: invalid choice\n";
        return 1;
    }
    if (tree.empty())
    {
        std::cout << "No words found to generate cross references.\n";
        return 0;
    }
    if (choice == 2)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cout << "Choose output destination:\n1. Console\n2. File\n> ";
    int outputChoice;
    if (!(std::cin >> outputChoice))
    {
        return 0;
    }
    std::cin.ignore();
    if (outputChoice == 1)
    {
        std::cout << "Unique words in text: " << tree.size() << '\n';
        std::cout << "Height of the AVL-tree: " << tree.getHeight() << '\n';
        printCrossReferences(std::cout, tree);
    }
    else if (outputChoice == 2)
    {
        std::string outFilename;
        std::cout << "Enter output filename: ";
        std::getline(std::cin, outFilename);

        if (outFilename.empty())
        {
            std::cerr << "Error: filename cannot be empty!\n";
            return 1;
        }

        std::ofstream outFile(outFilename);
        if (!outFile.is_open())
        {
            std::cerr << "Error: cannot open file '" << outFilename << "' for writing\n";
            return 1;
        }
        outFile << "Unique words in text: " << tree.size() << '\n';
        outFile << "Height of the AVL-tree: " << tree.getHeight() << '\n';
        printCrossReferences(outFile, tree);
        outFile.close();
        std::cout << "Cross references successfully saved to '" << outFilename << "'\n";
    }
    else
    {
        std::cerr << "Error: invalid output choice\n";
        return 1;
    }
    return 0;
}

