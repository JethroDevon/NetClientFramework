#include "Substitution.h"

Substitution::Substitution(std::string _path){

    //gets the cipher from the file in args
    getCipherFromFile(_path);

    //initialised empty
	solvedString = "";

    //adds the symbols to a vector called symbols to store and perform operations on
    storeSymbols();

    //add frequency table to vector
    initialiseRFoL();

    //finds the relative frequency of each character in the whole string
    relativeFrequency();

    //initialise a list of combination of common combinations
    initialiseCombination(4);

     //shows frequency of characters appearance
    showFrequencyTable();

    std::cout<<"\n\n"<<solveFrequency();

}

//takes path to a .txt with the cipher text on and initialises the variable cipher on it
void Substitution::getCipherFromFile(std::string _path){

    
    //removes spaces
    cipher.erase(remove_if(cipher.begin(), cipher.end(), isspace),cipher.end());

    //transforms all text to lower case
	std::transform(cipher.begin(), cipher.end(), cipher.begin(), tolower);

    //removes a couple of awkward characters
    char chars[]= "/;!";
    for (unsigned int i = 0; i < 3; ++i){

            cipher.erase(std::remove(cipher.begin(),cipher.end(),chars[i]),cipher.end());
    }
}

void Substitution::showKeyMap(){

    for(auto k: keyMap){

        std::cout<< "\n" <<k.second << "-" <<k.first;
    }
}

void Substitution::storeSymbols(){

    //for each character or symbol in the cipher string
    for(char c: cipher){

        //default true flag is set to false when char is found before, else put on vector
        bool newSymbol = true;

        //check if the character or symbol has been encountered before
        for(auto  sym: symbols){

            if(sym == c){

                newSymbol = false;
            }
        }
        //pushes new symbol to vector list
        if(newSymbol){

            symbols.push_back(c);
        }
    }
}

//initialises the values that belong to RFoL, shows the frequency each character is used relative to the others
void Substitution::initialiseRFoL(){

	//initialising RFoL.push_back(std::pair<char,float>(s elements to be the character mapped to how often it occures relativley
	RFoL.push_back(std::pair<char,float>('a', 8.167));
	RFoL.push_back(std::pair<char,float>('b', 1.492));
	RFoL.push_back(std::pair<char,float>('c', 2.782));
	RFoL.push_back(std::pair<char,float>('d', 4.253));
	RFoL.push_back(std::pair<char,float>('e', 12.702));
	RFoL.push_back(std::pair<char,float>('f', 2.228));
	RFoL.push_back(std::pair<char,float>('g', 2.015));
	RFoL.push_back(std::pair<char,float>('h', 6.094));
	RFoL.push_back(std::pair<char,float>('i', 6.996));
	RFoL.push_back(std::pair<char,float>('j', 0.153));
	RFoL.push_back(std::pair<char,float>('k', 0.772));
	RFoL.push_back(std::pair<char,float>('l', 4.025));
	RFoL.push_back(std::pair<char,float>('m', 2.406));
	RFoL.push_back(std::pair<char,float>('n', 6.749));
	RFoL.push_back(std::pair<char,float>('o', 7.507));
	RFoL.push_back(std::pair<char,float>('p', 1.929));
	RFoL.push_back(std::pair<char,float>('q', 0.095));
	RFoL.push_back(std::pair<char,float>('r', 5.987));
	RFoL.push_back(std::pair<char,float>('s', 6.327));
	RFoL.push_back(std::pair<char,float>('t', 9.056));
	RFoL.push_back(std::pair<char,float>('u', 2.758));
	RFoL.push_back(std::pair<char,float>('v', 0.978));
	RFoL.push_back(std::pair<char,float>('w', 2.360));
	RFoL.push_back(std::pair<char,float>('x', 0.150));
	RFoL.push_back(std::pair<char,float>('y', 1.974));
	RFoL.push_back(std::pair<char,float>('z', 0.074));
}

//this function calculates the relative frequency of a character in cipher text
//and then loads it onto RFoSL map list as a key value pair, it also returns
//a percentage of just how similar the cipher was to the relative frequency of letters
//in plain text
void Substitution::relativeFrequency(){

    //loops for each character in the cipher
    for(char c: symbols){

        //stores the number of occurrences of the character
        float tempFirst = 0;

        //for each character in the cipher text store the  frequency of occurrence in RFoSL
        for(char s: cipher){

            if(c == s){

                tempFirst++;
            }
        }

        float temp = (tempFirst/cipher.size())*100;

        //add the character and frequency of its occurrence
        RFoSL.push_back(std::pair<char,float>( c, temp));
    }

    //organizes both vector of pairs RFoL and RFoSL in order of frequency
    sortVectors();
}

//shows frequency of each symbol in console
void Substitution::showFrequencyTable(){

    std::cout<< "FREQUENCY TABLE OF CHARACTERS \n\n"<<std::endl;

    float errorRatio;

    //loops for minimum size times of RFoL and RFoSL
    for(size_t K = 0; K < std::min(RFoL.size(), RFoSL.size()); ++K){

        //outputs order of occurrence of each string, shows which keys are likely to be substituted for which others
        std::cout<< RFoL[K].first<< " -  SUBSTITUTED FOR: "<< RFoSL[K].first <<std::endl;

        //subtracts the frequency of occurrence of the substituted letters from the frequency of letters used in
        //English plain text and later returns the absolute value so the user can see how close the cipher is, a
        //higher score should show that the cipher is not simple substitution
        errorRatio += abs(RFoSL[K].second - RFoL[K].second);
    }

    std::cout<< "\n\nError of cipher to frequency of English plain text is: " << errorRatio << ".\n Most common combinations of characters:\n" <<std::endl;

    //shows frequency of most common combinations
    for(auto a: commonCombinations){

        std::cout<< a <<std::endl;
    }

    std::cout<< "\n Most common pairs of characters:\n" <<std::endl;

    //shows frequency of most common combinations
    for(auto a: commonPairs){

        std::cout<< a <<std::endl;
    }
}

//this function sorts both vectors of pairs into descending order based on the second value of each pair
void Substitution::sortVectors(){

    //sorts the vector using lambdas and sort algorithm
    std::sort(RFoL.begin(), RFoL.end(), [](const std::pair<char,float> &left, const std::pair<char,float> &right) {

        return left.second > right.second;
    });
    std::sort(RFoSL.begin(), RFoSL.end(), [](const std::pair<char,float> &left, const std::pair<char,float> &right) {

        return left.second > right.second;
    });

    //loops for minimum size times of RFoL and RFoSL
    for(size_t K = 0; K < std::min(RFoL.size(), RFoSL.size()); ++K){

        //adds pair of characters left substituted right character with similar frequency
        keyMap.push_back(std::pair<char, char>( RFoL[K].first, RFoSL[K].first));
    }

}

//once the vectors are sorted the characters from one list
//are similarly
char Substitution::switchChar(char _substitute){

    //returns second value if first matches
    for(auto km: keyMap){

        if( km.first == _substitute){

            return km.second;
        }
    }

    //if nothing is found to perform switch return '!', most likley it can
    //point out there are symbols that should not be present
    return '!';
}

//finds the number of occurrences of the combination in args
int Substitution::addCombination(std::string _combination){

    int count = 0;
    size_t nPos = cipher.find(_combination, 0);
    while(nPos != std::string::npos){
        count++;
        nPos = cipher.find( _combination, nPos+1);
    }

    return count;
}

//this function returns the most common combination of characters that
//appear together in cipher that are not on the commonCombinations vector
std::string Substitution::maxNCombination(int _size){

    //empty temporary string for storing most common combination
    std::string mostCommon = "";

    //stores the highest yet number of occurrences
    int highestOccurrences = 0;

    //stores each combination of _size for the whole cipher
    std::vector<std::string> tempCombinations;

    //for each char in the cipher
    for(int c = 0; (c + _size) < cipher.size(); c++){

        tempCombinations.push_back(cipher.substr( c, _size));
    }

    /*the following logic uses two loops and flags to detect the most common occurrences of string combinations
     stored in tempCombinations, if they are not already on the list of common combinations already that is.*/

    //loops for each entry of tempCombinations
    for(auto &o: tempCombinations){

        //stores the number of occurrences
        int occurrences = 0;

        //loops for temp combinations again to find matches
        for(auto t: tempCombinations ){

            //if the strings are equal rack up occurrences
            if(o == t)
                occurrences++;
        }

        //if the occurrences are highest yet and the combination is not already known
        if((occurrences > highestOccurrences) && !findCombination(o)){

            highestOccurrences = occurrences;
            mostCommon = o;
        }else{

            o.erase();
        }
    }

    return mostCommon;
}

//this function initialises the string vector common combinations with the amount of combinations of up to
//five characters for the number of times passed in args
void Substitution::initialiseCombination(int _size){

    //searches for the 4 most common combinations for up to _size characters
    for(int a = 2; a <= _size; a++){
        for(int f = 0; f <= 6; f++){

            commonCombinations.push_back(maxNCombination(a));
        }
    }

        int highestPair = 0;

        for(auto k: keyMap){

            std::string temp = "";
            temp += k.first;
            temp += k.first;

            if((addCombination(temp) > highestPair) && !findPairs(temp)){

                highestPair = addCombination(temp);
                commonPairs.push_back(temp);
                std::cout<<temp<<" ";
            }
        }
}

//this function switches the places of two substituted characters mapped to pairs, that is the places
//of two second characters in keyMap, this is so changes can be made when solving
void Substitution::switchSubstitutes(char _swapA, char _swapB){

    //stores positions in vector
    size_t Apos, Bpos;

    //loops for keyMap
    for(size_t K = 0; K < keyMap.size(); ++K){

        if(keyMap[K].first == _swapA){

            Apos = K;
        }
        if(keyMap[K].first == _swapB){

            Bpos = K;
        }
    }

    keyMap[Apos].first = _swapB;
    keyMap[Bpos].first = _swapA;
}

//this function returns true or false if the string in args is actually on the vector container
bool Substitution::findCombination(std::string _find){

    for(auto o: commonCombinations){

        if(o == _find)
            return true;
    }

    return false;
}

//this function returns true or false if the string in args is actually on the vector container
bool Substitution::findPairs(std::string _find){

    for(auto o: commonPairs){

        if(o == _find)
            return true;
    }

    return false;
}

//this function checks the frequency of each chars frequency occurrence to others until
//the frequency that is most similar to the table is found, then
std::string Substitution::solveFrequency(){

    for(auto c: cipher){

        solvedString += switchChar(c);
    }

    return solvedString;
}
