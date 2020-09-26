

// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "Boggle.h"
#include "shuffle.h"
#include "error.h"
#include "point.h"
#include "grid.h"
#include "foreach.h"
#include "iostream"
#include "strlib.h"


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

    gameboard.resize(4,4);
        _dictionary=dictionary;
        _boardText=boardText;

        shuffle(CUBES,16);
        if (boardText.empty())
        {
            for (int i=0; i<gameboard.width();i++)
            {
                shuffle(CUBES[i]);
                for (int j=0; j<gameboard.height(); j++)
                {
                    gameboard[i][j]=CUBES[i][j];
                }
            }
        } else
        {
            toUpperCase(boardText);
            vector<std::string> vec;
            for (int i=1;i<16;i=i+4){
                vec.push_back(boardText.substr(i-1,4));
            }
            for (int i=0; i<vec.size();i++) {

                for (int j=0;j<vec[i].size();j++){

                gameboard[i][j]=vec[i][j];
                }
            }

        }
}

char Boggle::getLetter(int row, int col) {
    char letter;
    if (gameboard.inBounds(row,col))
        {
            letter=gameboard.get(row,col);
        } else
        {
            //cout << "Exception occured while trying to access" << row, col <<
            throw -1;
        }
    return letter;
}

bool Boggle::checkWord(string word) {
    Vector<string> wordsfound;
        if ((word.size()<4)||(!_dictionary.contains(word))||
                (wordsfound.contains(word))) {
            return false;} else {
            return true;}  // remove this
}

bool Boggle::humanWordSearch(string word) {
    word =toUpperCase(word);
    if (!wordExists(word)) return false;
        Point start=FindFirstLetter(word);
        string w=word.substr(0,1);
        MarkSquare(start);
            foreach(char t in word){
            for (int dir=NORTH; dir!=EASTEAST; dir++){
                bool check=FindWord(word,w,adjacentPoint(start,dir),t,dir);
                if (check){
            //        w.push_back(t);
                    //return true;
                }
            }
        }
           if (w==word) return true;
           else
        return false;   // remove this
}

int Boggle::getScoreHuman() {
    // TODO: implement
    return 0;   // remove this
}

Set<string> Boggle::computerWordSearch() {
    Set<string> _result;
    string word ="";
        for(int i=0; i<=gameboard.height(); i++){
            for (int j=0; j<=gameboard.width(); j++){
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

bool Boggle::wordExists(string word) {

    if (_dictionary.containsPrefix(word)) {
        return true;
    } else { return false; }
}
void Boggle::MarkSquare(Point point){
    char t=std::tolower(gameboard[point.getX()][point.getY()]);
    gameboard[point.getX()][point.getY()]=t;
    }
void Boggle::UnmarkSquare(Point point){
    char t=std::toupper(gameboard[point.getX()][point.getY()]);
    gameboard[point.getX()][point.getY()]=t;
    }

Point Boggle::FindFirstLetter(string word){
    for (int i=0;i<gameboard.height();i++){
        for (int j=0;j<gameboard.width();j++){
            if (gameboard[i][j]==word[0]){
               Point pt(i,j);
               return pt;}}
    }
    Point pt(10,10);
    return pt;


}
bool Boggle::FindWord(string word, string &shortword, Point start,
                      char ch){
    //if (!dictionary.containsPrefix(shortword)) return false;
    if (isMarked(gameboard,start)) return false;
    if (gameboard[start.getX()][start.getY()]!=ch){
       return false;
    }
    if (shortword==word) return true;
    foreach(char t in word){
    for (int dir=NORTH; dir!=EASTEAST; dir++){
    MarkSquare(start);
    if (FindWord(word, shortword, adjacentPoint(start,dir),
                 ch, dir)){
        return true;

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

Point Boggle::adjacentPoint(Point start, int direct){

    switch(direct){
    case NORTH:
        if (start.getX()>0) {
        return Point(start.getX()-1,start.getY());
        } else {
            break;
        }
    case SOUTHEAST:
        if ((start.getX()<gameboard.height()-1)&&(start.getY()<gameboard.width()-1)){
        return Point(start.getX()+1, start.getY()+1);
        } else {
            break;
        }
    case SOUTHWEST:
        if ((start.getX()<gameboard.height()-1)&&(start.getY()>0)){
        return Point(start.getX()+1, start.getY()-1);
        } else {
            break;
        }

    case NORTHEAST:
        if ((start.getX()>0)&&(start.getY()<gameboard.width())){
        return Point(start.getX()-1, start.getY()+1);
        } else {
            break;
        }


    case NORTHWEST: if ((start.getX()>0)&&(start.getY()>0)){
            return Point(start.getX()-1, start.getY()-1);
        } else {
            break;
        }

    case WEST: if (start.getY()>0){
            return Point(start.getX(),start.getY()-1);
        } else {
            break;
        }

    case EAST: if (start.getY()<gameboard.width()-1){
            return Point(start.getX(),start.getY()+1);}
        else {
            break;
        }
    case SOUTH: if (start.getX()<gameboard.height()-1){
                    return Point(start.getX()+1,start.getY());
        } else {
            break;
        }

}
return start;}

bool isMarked(Grid<char>& board,Point point){
    char ch=board[point.getX()][point.getY()];
    if (toupper((board[point.getX()][point.getY()]))!=ch) {
        return true;}else {
        return false;
    }
}
