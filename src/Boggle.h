
#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include <grid.h>
#include "point.h"
#include <vector>
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
        char getLetter(int row, int col);
        bool checkWord(string word);
        bool humanWordSearch(string word);
        Grid<char> gameboard;
        std::set<string> computerWordSearch();
        int getScoreHuman();
        int getScoreComputer();
        bool wallexists(Grid<char> MarkedSquares, Point start);

        Lexicon _dictionary;
        string _boardText;
        //bool isMarked(int i, int j);
        void MarkSquare(Point point);
        bool findword(int i, int j, string word);
        std::vector<int> FindFirstLetter(string word);
        bool FindWord(string word, Point start, char ch);
        void UnmarkSquare(Point point);
        bool isMarked(Point point);
        bool ComputerFindWord(Point start, string &word,set<string> &result);
        void printgameboard(Grid<char> gboard);
        void ClearBoard(Grid<char> &gboard);

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    Point adjacentPoint(Point start, int direct);
    bool wordExists(string word);
    bool ContainsPrefix(string word);

    Grid<char> markedSquares;
};

#endif // _boggle_h
