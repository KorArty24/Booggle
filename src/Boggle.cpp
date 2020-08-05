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

enum directions {NORTH, SOUTH, SOUTHEAST, SOUTHWEST, WEST, EAST, NORTHEAST, NORTHWEST, EASTEAST};
Point adjacentPoint(Point start, int dir);
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
    gameboard.resize(4,4);
        this->dictionary=dictionary;
        this->_boardText=boardText;

        shuffle(CUBES,16);


        if (boardText.empty()) {
            for (int i=0; i<=gameboard.width();i++){
                shuffle(CUBES[i]);
                for (int j=0; j<=gameboard.height(); j++){
                    gameboard[i][j]=CUBES[i][j];
            }}} else {
                    toUpperCase(boardText);
                }

}

char Boggle::getLetter(int row, int col) {
    if (gameboard.inBounds(row,col))
        {
            char letter=gameboard.get(row,col);
        } else
        {
            //cout << "Exception occured while trying to access" << row, col <<
            throw -1;
        }
}

bool Boggle::checkWord(string word) {
    Vector<string> wordsfound;
        if ((word.size()<4)||(!dictionary.contains(word))||
                (wordsfound.contains(word))) {return false;}
         else
        {return true;}  // remove this
}

bool Boggle::humanWordSearch(string word) {
    if (!wordExists(word)) return false;
        Point start=FindFirstLetter(word);
        string w="";

            foreach(char t in word){
                MarkSquare(start);
            for (int dir=NORTH; dir!=EASTEAST; dir++){
                if (FindWord(word,w,adjacentPoint(start,dir),t,dir)){
                    w.push_back(t);
                    return true;
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

        for(int i=0; i<=gameboard.height(); i++){
            for (int j=0; j<=gameboard.width(); j++){
                for (int dir=NORTH; dir!=EASTEAST; dir++){
                Point start(i,j);
                MarkSquare(start);
                if (ComputerFindWord(start,dir,word))
                    result.add(word);
                word="";

            }}
        }



           // remove this
        return result;        // remove this
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

    if (dictionary.containsPrefix(word)) {
        return true;
    } else { return false; }
}
void Boggle::MarkSquare(Point point){
    char t=gameboard[point.getX()][point.getY()];
    if (gameboard[point.getX()][point.getY()]!='0') {
    gameboard[point.getX()][point.getY()]='0';} else {
    gameboard[point.getX()][point.getY()]=t;}
}


Point Boggle::FindFirstLetter(string word){
    for (int i=0;i<=gameboard.height();i++){
        for (int j=0;j<=gameboard.width();j++){
            if (gameboard[i][j]==word[0]){
               Point pt(i,j);
               return pt;}}
    }
    Point pt(10,10);
    return pt;


}
bool Boggle::FindWord(string word, string shortword, Point start,
                      char ch, int dir){
    //if (!dictionary.containsPrefix(shortword)) return false;
    if (isMarked(start.getX(),start.getY()))return false;
    if (gameboard[start.getX()][start.getY()]!=ch) return false;
    if (shortword==word) return true;
    if (FindWord(word, shortword, adjacentPoint(start,dir),
                 ch, dir)){
        return true;
    }
     MarkSquare(start);

     return false;
}

bool Boggle::ComputerFindWord(Point start, int dir, string &word){
    char ch=gameboard[start.getX()][start.getY()];
    word+=ch;
    if (!dictionary.containsPrefix(word)) return false;
    if (dictionary.containsPrefix(word)&&(word.length()>3)) return true;
    if (ComputerFindWord(adjacentPoint(start,dir),dir,word)) return true;
    MarkSquare(start);
    return false;
        }






Point adjacentPoint(Point start, int direct){

    switch(direct){
    case NORTH: return Point(start.getX()-1,start.getY());
    case SOUTHEAST: return Point(start.getX()+1, start.getY()+1);
    case SOUTHWEST: return Point(start.getX()+1, start.getY()-1);
    case NORTHEAST: return Point(start.getX()-1, start.getY()+1);
    case NORTHWEST: return Point(start.getX()-1, start.getY()-1);
    case WEST: return Point(start.getX(),start.getY()-1);
    case EAST: return Point(start.getX(),start.getY()+1);
    case SOUTH: return Point(start.getX()+1,start.getY());

}
return start;}
