// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include <grid.h>
#include "point.h"
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
        Lexicon dictionary;
        string _boardText;
        bool isMarked(int i, int j);
        void MarkSquare(Point point);
        bool findword(int i, int j, string word);
        Point FindFirstLetter(string word);
        bool FindWord(string word,string shortword, Point start, char ch, int dir);
        void UnmarkSquare(Point point);
        bool ComputerFindWord(Point start, int dir, string &word);

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    // TODO: add any other member functions/variables necessary
};

#endif // _boggle_h
