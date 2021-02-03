
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
        bool wordExists(string word);
        Set<string> computerWordSearch();
        int getScoreHuman();
        int getScoreComputer();
        Grid<char> gameboard;
        Grid<int> markedSquares;
        Lexicon _dictionary;
        string _boardText;
        //bool isMarked(int i, int j);
        void MarkSquare(Point point);
        bool findword(int i, int j, string word);
        std::vector<int> FindFirstLetter(string word);
        bool FindWord(string word, Point start, char ch);
        void UnmarkSquare(Point point);
        bool isMarked(Point point);
        bool ComputerFindWord(Point start, int dir, string &word, Set<string> & result);
       void printgameboard(Grid<char> gboard);
       void ClearBoard(Grid<int> &gboard);

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    Point adjacentPoint(Point start, int direct);
};

#endif // _boggle_h
