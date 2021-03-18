
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
        bool humanWordSearch(string word);
        Grid<char> gameboard;
        int getScoreHuman();
        int getScoreComputer();
        Lexicon _dictionary;
        string _boardText;

        bool ComputerFindWord(Point start, string &word,set<string> &result);
        void printgameboard(Grid<char> gboard);
        void ClearBoard(Grid<char> &gboard);
        Vector<Point> points;
        std::set<string> computerWordSearch();

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    Point adjacentPoint(Point start, int direct);
    bool FindWord(string word, string &shortword, Point start, char ch);
    bool wordExists(string word);
    bool ContainsPrefix(string word);
    void UnmarkSquare(Point point);
    bool isMarked(Point point);
    Grid<char> markedSquares;
    void MarkSquare(Point point);
    bool findword(int i, int j, string word);
    char getLetter(int row, int col);
    bool checkWord(string word);
    std::vector<Point> FindFirstLetter(string word);
    bool wallexists(Grid<char> MarkedSquares, Point start);


};

#endif // _boggle_h
