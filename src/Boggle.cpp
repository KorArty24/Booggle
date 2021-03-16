#include "Boggle.h"
#include "shuffle.h"
#include "error.h"
#include "point.h"
#include "foreach.h"
#include "iostream"
#include "strlib.h"
#include "grid.h"
#include <vector>
#include <bogglegui.h>

enum directions {NORTH, SOUTHEAST,SOUTH, SOUTHWEST, WEST, EAST, NORTHEAST, NORTHWEST, EASTEAST};

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    markedSquares.resize(4,4);
    markedSquares.fill('O');
    gameboard.resize(4,4);
        _dictionary=dictionary;
        _boardText=boardText;
        shuffle(CUBES,16);
        if (boardText.empty()){
            for (int c=0; c<gameboard.width();c++){
                shuffle(CUBES[c]);
                for (int r=0; r<gameboard.height(); r++){
                    gameboard.set(c,r,CUBES[c][r]);
                }
            }
        } else {
            toUpperCase(boardText);
            vector<string> vec;
            for (int i=1;i<16;i=i+4){
                vec.push_back(boardText.substr(i-1,4));
            }
            for (int i=0; i<vec.size();i++) {
                for (int j=0;j<vec[i].size();j++){
                gameboard.set(i,j,vec[i][j]);
                }
            }
        }
}

char Boggle::getLetter(int row, int col) {
    char letter;
    if (gameboard.inBounds(row,col))
        {
            letter=gameboard.get(row,col);
        } else {
            //cout << "Exception occured while trying to access" << row, col <<
            throw -1;
        }
    return letter;
}

bool Boggle::checkWord(string word) {
    Vector<string> wordsfound;
        if ((word.size()<4)||(!_dictionary.contains(word))||
                (wordsfound.contains(word))) {
            return false;
        } else {
            return true;
        }
}

bool Boggle::humanWordSearch(string word) {
    if (!wordExists(word)) return false;
    int x=FindFirstLetter(word)[0];
    int y=FindFirstLetter(word)[1];
    Point startp(x,y);
    points.add(startp);
    string shortWord;
    shortWord.push_back(word[0]);
    for (int i=1; i<word.length(); i++){
        //ClearBoard(markedSquares);
        if (FindWord(word,points.back(),word[i])){
            shortWord.push_back(word[i]);
        //}   else {
//            i=i-1;
//            shortWord.pop_back();
      //  }
    }
    bool checkword = (shortWord==word)? true : false;
    if (checkword){
        for (Point p:points){
            BoggleGUI::setHighlighted(p.getX(),p.getY(),true);
        }
    }
    return checkword;
}

std::set<string> Boggle::computerWordSearch() {
    std::set<string> _result;
    string word ="";
        for(int i=0; i<gameboard.width(); i++){
            for (int j=0; j<gameboard.height(); j++){
                Point start(i,j);
                ClearBoard(markedSquares);
                ComputerFindWord(start,word,_result);
            }
        }
        return _result;
}

int Boggle::getScoreHuman() {
    // TODO: implement
    return 0;   // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}

bool Boggle::FindWord(string word, Point start, char ch){
        if (isMarked(start)) return false;
        MarkSquare(start);
        for (int dir=NORTH; dir!=EASTEAST; dir++){
            char b=toupper(gameboard[start.getX()][start.getY()]);
            if (b==ch) {
                points.add(start);
                return true;
            }
            if ((wallexists(markedSquares,adjacentPoint(start,dir)))
                 &&(FindWord(word, adjacentPoint(start,dir),ch))){
                return true;
            }
        }

        UnmarkSquare(start);
        return false;
}

bool Boggle::ComputerFindWord(Point start, string &word, set<string> &result ){

    if (isMarked(start)) return false;
    MarkSquare(start);
    char ch=gameboard[start.getX()][start.getY()];
    word+=ch;
    if (!ContainsPrefix(word)) {
        word.pop_back();
        UnmarkSquare(start);
        return false;
    }
    else if (wordExists(word)&&(word.length()>3)) {
        result.emplace(word);
    }
    for (int dir=NORTH; dir!=EASTEAST; dir++){
        if ((wallexists(markedSquares,adjacentPoint(start,dir))&&
             (ComputerFindWord(adjacentPoint(start,dir), word, result)))){
            return true;
        }
    }
    word.pop_back();
    UnmarkSquare(start);
    return false;
  }

void Boggle::printgameboard(Grid<char> gboard){
   string board=gboard.toString2D();
   cout<< gboard;
}

bool Boggle::wordExists(string word) {
    if (_dictionary.contains(word)) {
        return true;
    } else {
        return false;
    }
}

bool Boggle::ContainsPrefix(string word) {
    if (_dictionary.containsPrefix(word)) {
        return true;
    } else { return false; }
}
void Boggle::MarkSquare(Point point){
    markedSquares.set(point.getX(),point.getY(),'X');
    }

void Boggle::UnmarkSquare(Point point){
    markedSquares.set(point.getX(),point.getY(),'O');
    }

Point Boggle::adjacentPoint(Point start, int direct){

    switch(direct){
    case NORTH: return Point(start.getX(),start.getY()-1);
    case SOUTHEAST: return Point(start.getX()+1,start.getY()+1);
    case SOUTH: return Point(start.getX(),start.getY()+1);
    case SOUTHWEST: return Point(start.getX()-1,start.getY()+1);
    case WEST:  return Point(start.getX()-1,start.getY());
    case EAST: return Point(start.getX()+1,start.getY());
    case NORTHEAST: return Point(start.getX()+1,start.getY()-1);
    case NORTHWEST: return Point(start.getX()-1,start.getY()-1);
      }
       return start;
   }

std::vector<int> Boggle::FindFirstLetter(string word){
   std::vector<int> point(2,0);
        for (int row=0;row<gameboard.height();row++){
        for (int col=0;col<gameboard.width();col++){
            if (gameboard[row][col]==word.front()){
               point[0]=(row);
               point[1]=(col);
            }
        }
    }
        return point;
}

bool Boggle::isMarked(Point point){

    int t=markedSquares[point.getX()][point.getY()];
    if (t=='X') {return true;
    } else {
        return false;
    }
}
void Boggle::ClearBoard(Grid<char> &gboard){
    gboard.fill('O');
}
bool Boggle::wallexists(Grid<char> MarkedSquares, Point start){
    if (MarkedSquares.inBounds(start.getX(),start.getY())){
        return true;
    } else {
        return false;
    }
}
