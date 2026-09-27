#ifndef CROSS_REFERENCES_H
#define CROSS_REFERENCES_H
#include <iostream>
#include <fstream>
#include <string>
#include "avltree.h"
#include "linenumbers.h"


bool isWordChar(char ch)
{
    unsigned char uch = static_cast<unsigned char>(ch);
    return std::isalnum(uch) || ch == '-' || ch == '\'';
}

void splitIntoWords(const std::string& line, std::string* words, int& wordCount, int maxWords)
{
    wordCount = 0;
    std::string currentWord;
    currentWord.reserve(32);
    bool hasLetterOrDigit = false;

    for (size_t i = 0; i < line.length(); ++i)
    {
        if (wordCount >= maxWords)
        {
            break;
        }
        unsigned char ch = static_cast<unsigned char>(line[i]);
        if (isWordChar(ch))
        {
            currentWord += static_cast<char>(std::tolower(ch));
            if (std::isalnum(ch))
            {
                hasLetterOrDigit = true;
            }
        }
        else
        {
            if (!currentWord.empty() && hasLetterOrDigit)
            {
                words[wordCount++] = std::move(currentWord);
            }
            currentWord.clear();
            hasLetterOrDigit = false;
        }
    }
    if (!currentWord.empty() && hasLetterOrDigit)
    {
        words[wordCount++] = std::move(currentWord);
    }
}

void processText(std::istream& in, std::ostream& out, AVLtree<std::string, LineNumbers>& tree)
{
    AVLtree<std::string, LineNumbers> tempTree(tree);
    std::string line;
    int lineNumber = 1;
    out << "\n--- Text with line numbers ---\n";
    while (std::getline(in, line))
    {
        out << lineNumber << ": " << line << "\n";
        if (line.empty())
        {
            lineNumber++;
            continue;
        }
        int maxWords = static_cast<int>(line.length() / 2 + 1);
        std::string* words = new std::string[maxWords];
        int wordCount = 0;
        try
        {
            splitIntoWords(line, words, wordCount, maxWords);
            for (int i = 0; i < wordCount && i < maxWords; ++i)
            {
                LineNumbers lines;
                if (tempTree.search(words[i], lines))
                {
                    lines.add(lineNumber);
                    tempTree.insert(words[i], lines);
                }
                else
                {
                    tempTree.insert(words[i], LineNumbers(lineNumber));
                }
            }
            delete[] words;
        }
        catch (...)
        {
            delete[] words;
            throw;
        }

        lineNumber++;
    }
    tree.swap(tempTree);
    out << "--- End of processing. Total lines: " << (lineNumber - 1) << " ---\n";
}


void printCrossReferences(std::ostream& out, const AVLtree<std::string, LineNumbers>& tree)
{
    out << "\n--- Cross References ---\n";
    tree.inOrderWalk(out);
}

#endif