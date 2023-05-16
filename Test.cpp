//#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
//using namespace sf;
using namespace std;

int GetScientificDecimal(string MyString) {
    int i = 0;
    if (MyString.at(i) == '-') { i++; }//negative
    if (MyString.at(i) == '0' && MyString.at(i + 1) == '.') {//negitive decimal and it must come in as 0.aaaaaa
        i = i + 2;
        while (MyString.at(i) == '0' && i < MyString.size()) {
            i++;
        }
        i++;
        return (i - (2 + (MyString.at(0) == '-'))) * -1;
    }
    //positive decimals
    while (i < MyString.size() && MyString.at(i) != '.') {
        i++;
    }
    return i - (MyString.at(0) == '-');
}
string CorrectFormat(string &MyString) {//formats
        string FormatedNumber = "00000000000000000";
        int i = GetScientificDecimal(MyString);
        cout<<i<<'\n';
        if(i>100||i<-99){
            return "Overload";
        }
        else if (i > 16) {
            i--;
            FormatedNumber.at(16) = i % 10 + 48;
            FormatedNumber.at(15) = i / 10 + 48;
            FormatedNumber.at(14)='e';
            for (i = 0; (i < MyString.size())&&i<14; i++) {
                FormatedNumber.at(i) = MyString.at(i);
            }
            FormatedNumber.insert(FormatedNumber.begin() + 1 + (MyString.at(0) == '-'), '.');
        }
        else if(i<-15){
            i=i*-1;
            FormatedNumber.at(16) = i % 10 + 48;
            FormatedNumber.at(15) = i / 10 + 48;
            FormatedNumber.at(14) = '-';
            FormatedNumber.at(13) = 'e';
            if(MyString.at(0)=='-'){
                FormatedNumber.at(0)='-';
                i--;
            }
            i=i+1+(MyString.at(0)=='-');
            for (int j =(MyString.at(0)=='-'); (i+j < MyString.size())&&j<13; j++) {
                FormatedNumber.at(j) = MyString.at(i+j);
            }
            FormatedNumber.insert(FormatedNumber.begin() + 1 + (MyString.at(0) == '-'), '.');
        }
        else {
            return MyString;
        }
        return FormatedNumber;
    }
    int main(){         //-123456789.123456789.123456789.123456789.
        string MyString = "-0.0000000000000000000000000000000000000000000000000000000001278910";
        string Format =CorrectFormat(MyString);
        cout<< Format;
        return 0;
    }