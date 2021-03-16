// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include "lexicon.h"
#include "iostream"
#include <fstream>
#include <string>
#include <Boggle.h>
#include "simpio.h"
#include <bogglegui.h>
//using namespace std;
void playOneGame(Lexicon& dictionary) {
    // TODO: implement
    //dictionary.addWordsFromFile("dictionary.txt");
    std::string word;
    //string wd="FYCLIOMGORILHJHU";
    set<string> words;
    string boardtext=getLine ("Enter the board text");
    std::cout << boardtext <<endl;
    //std::cout << dictionary.size();
    Boggle bogl(dictionary,boardtext);
    if (!BoggleGUI::isInitialized()) {
        BoggleGUI::initialize(bogl.gameboard.height(),bogl.gameboard.width());
    }
    BoggleGUI::labelAllCubes(boardtext);
   // std::string gameboard_content=bogl.gameboard.toString2D();
   // std::cout << gameboard_content << endl;
    while (true) {
        std::cout << "Type a word (or Enter to stop):" <<endl;
        std::getline (std::cin,word);
        word=toUpperCase(word);
        if ((word!="")&&(bogl.humanWordSearch(word))) {
            std::cout << "The word exists!" <<endl;
            for (char c:word){

            }
        } else if (word.length()==0) {

        } else {
            cout << "This word doesn't exist";
        }
        cout<< "It's my turn!" <<endl;
        words=bogl.computerWordSearch();
        for (auto w : words){
            cout << w <<endl;
        }
    }
}
