#include "Boggle.h"
#include "shuffle.h"
#include "error.h"
#include "point.h"
#include "foreach.h"
#include "iostream"
#include "strlib.h"
#include "grid.h"
#include <vector>

enum directions {NORTH, SOUTHEAST,SOUTH, SOUTHWEST, WEST, EAST, NORTHEAST, NORTHWEST, EASTEAST};

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

bool isMarked(Grid<char> &board,Point point);

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
    markedSquares.fill(0);
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
        }  // remove this
}

bool Boggle::humanWordSearch(string word) {

    if (!wordExists(word)) return false;
    int x=FindFirstLetter(word)[0];
    int y=FindFirstLetter(word)[1];
    Point startp(x,y);
    string shortWord;
    shortWord.push_back(word[0]);
    for (int i=1; i<word.length(); i++){
        ClearBoard(markedSquares);
        if (FindWord(word,startp,word[i]))
            shortWord.push_back(word[i]);
    }
    if (shortWord==word) {return true;
    } else
    { return false; }

}

int Boggle::getScoreHuman() {
    // TODO: implement
    return 0;   // remove this
}

Set<string> Boggle::computerWordSearch() {
    Set<string> _result;
    string word ="";
        for(int i=0; i<gameboard.height(); i++){
            for (int j=0; j<gameboard.width(); j++){
                for (int dir=NORTH; dir!=EASTEAST; dir++){
                Point start(i,j);
                MarkSquare(start);
                if (ComputerFindWord(start,dir,word,_result))
                    _result.add(word);
                word="";
            }}
        }
        return _result;
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
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

bool Boggle::FindWord(string word, Point start, char ch){

        bool Marked=isMarked(start) ;
        if (Marked) return false;
        MarkSquare(start);
        for (int dir=NORTH; dir!=EASTEAST; dir++){
            char b=toupper(gameboard[start.getX()][start.getY()]);
            if (b==ch) {return true;}
            if (FindWord(word, adjacentPoint(start,dir),ch)){
                return true;
            }
        }
        UnmarkSquare(start);
        return false;
}

bool Boggle::ComputerFindWord(Point start, int dir, string &word, Set<string> & result){
    char ch=gameboard[start.getX()][start.getY()];
    word+=ch;
    if (!wordExists(word)) return false;
    if (wordExists(word)&&(word.length()>3)) return true;
    if (ComputerFindWord(adjacentPoint(start,dir),dir,word,result)) return true;
    MarkSquare(start);
    return false;
        }

void Boggle::printgameboard(Grid<char> gboard){
   string board=gboard.toString2D();
   cout<< gboard;
}
bool Boggle::wordExists(string word) {

    if (_dictionary.containsPrefix(word)) {
        return true;
    } else { return false; }
}
void Boggle::MarkSquare(Point point){
    markedSquares.set(point.getX(),point.getY(),1);
    }
void Boggle::UnmarkSquare(Point point){
    markedSquares.set(point.getX(),point.getY(),0);
    }

Point Boggle::adjacentPoint(Point start, int direct){

    switch(direct){

    case SOUTH: if (start.getY()<gameboard.height()-1){
            return Point(start.getX(),start.getY()+1);
        } else {
         break;
     }

     case NORTH:
           if (start.getY()>0) {
           return Point(start.getX(),start.getY()-1);
           } else {
               break;
           }
    case SOUTHEAST:
           if ((start.getY()<gameboard.height()-1)&&(start.getX()<gameboard.width()-1)){
           return Point(start.getX()+1, start.getY()+1);
           } else {
               break;
           }
    case SOUTHWEST:
           if ((start.getY()<gameboard.height()-1)&&(start.getX()>0)){
           return Point(start.getX()-1, start.getY()+1);
           } else {
               break;
           }
       case NORTHEAST:
           if ((start.getY()>0)&&(start.getX()<gameboard.width()-1)){
           return Point(start.getX()+1, start.getY()-1);
           } else {
               break;
           }
       case NORTHWEST: if ((start.getX()>0)&&(start.getY()>0)){
               return Point(start.getX()-1, start.getY()-1);
           } else {
               break;
           }
       case WEST: if (start.getX()>0){
               return Point(start.getX()-1,start.getY());
           } else {
               break;
           }

       case EAST: if (start.getX()<gameboard.width()-1){
               return Point(start.getX()+1,start.getY());
        } else {
            break;
        }

   }
       return start;
   }

bool Boggle::isMarked(Point point){

    int t=markedSquares[point.getX()][point.getY()];
    if (t==1) {return true;
    } else {
        return false;
    }
}
void Boggle::ClearBoard(Grid<int> &gboard){
    gboard.fill(0);
}
