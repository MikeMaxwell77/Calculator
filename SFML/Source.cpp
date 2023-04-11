#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
using namespace sf;
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
struct CalcNumbers {
    sf::Text MyText;
    string MyString="0";
    char operation=' ';
    int scientificDecimal=0;

    //functions
    string OperationString() {
        string temp = " ";
        temp.at(0) = operation;
        return temp;
    }
        void setFont(sf::Font font) {
        MyText.setFont(font);
    }
    void Clear() {//clear values
        MyString = "0";
        operation = ' ';
        MyText.setString("0");
    }
    //required by compiler
    void setString(string string) {
        MyText.setString(string);
    }
    void setCharacterSize(int CS) {
        MyText.setCharacterSize(CS);
    }
    void setFillColor(sf::Color Color) {
        MyText.setFillColor(Color);
    }
    void setPosition(float x,float y) {
        MyText.setPosition( x, y);
    }
    string CorrectFormat() {//formats
        string FormatedNumber = "00000000000000000";
        int i = GetScientificDecimal(MyString);
        cout << i << '\n';
        if (i > 100 || i < -100) {
            MyString = "0";
            return "Overload";
        }
        else if (i > 16) {
            i--;
            FormatedNumber.at(16) = i % 10 + 48;
            FormatedNumber.at(15) = i / 10 + 48;
            FormatedNumber.at(14) = 'e';
            for (i = 0; (i < MyString.size()) && i < 14; i++) {
                FormatedNumber.at(i) = MyString.at(i);
            }
            FormatedNumber.insert(FormatedNumber.begin() + 1 + (MyString.at(0) == '-'), '.');
        }
        else if (i < -15) {
            i = i * -1;
            FormatedNumber.at(16) = i % 10 + 48;
            FormatedNumber.at(15) = i / 10 + 48;
            FormatedNumber.at(14) = '-';
            FormatedNumber.at(13) = 'e';
            if (MyString.at(0) == '-') {
                FormatedNumber.at(0) = '-';
                i--;
            }
            i = i + 1 + (MyString.at(0) == '-');
            for (int j = (MyString.at(0) == '-'); (i + j < MyString.size()) && j < 13; j++) {
                FormatedNumber.at(j) = MyString.at(i + j);
            }
            FormatedNumber.insert(FormatedNumber.begin() + 1 + (MyString.at(0) == '-'), '.');
        }
        else {
            return MyString;
        }
        return FormatedNumber;
    }
};
char button(unsigned int x, unsigned int y,sf::Vector2u size) {
    unsigned int column = -1, row = -1;
    char lookup[20] = {'c','e','i','/','1','2','3','*','4','5','6','+','7','8','9','-','n','0','.','='};
    //adjust for window size
    x = x * 584 / size.x;
    y = y * 634 / size.y;
    //x coordinates
    if (x > 8 && x < 139) {
        column = 0;
}
    else if (x > 144 && x < 277) {
        column = 1;
    }
    else if (x > 280 && x < 412) {
        column = 2;
    }
    else if (x > 417 && x < 551) {
        column = 3;
    }
    //y coordinates
    if (y > 169 && y < 253) {
        row = 0;
    }
    else if (y > 257 && y < 342) {
        row = 1;
    }
    else if (y > 346 && y < 431) {
        row = 2;
    }
    else if (y > 436 && y < 521) {
        row = 3;
    }
    else if (y > 526 && y < 611) {
        row = 4;
    }

    if (row == -1 || column == -1) { return ' '; }
    row = row*4 + column;

    return lookup[row];
}
 /*void print(string a) {
    cout << '\n' << a << '\n';
    for (int i = 0; i < a.size(); i++) {
        cout << a.at(i) * 1 << " ";
    }
}*/
short Max(int a, int b) {
    if (a < b) { return b; }
    return a;
}
void clean(string& a) {//removes unnessesary characters from the string
    int i = 0;
    if (a.size() != (GetScientificDecimal(a) + (a.at(0) == '-'))) {
        //there are ending zeroes to clean up
        for (i = a.size() - 1; i > 0; i--) {
            if (a.at(i) > 57 || a.at(i) < 46 || a.at(i) == 48) {//not a number or a decimal
                a.pop_back();
            }
            else if (a.at(i) == '.' || (a.at(i) < 58 && a.at(i) > 47)) {
                break;
            }
        }
        if (a.back() == '.') {
            a.pop_back();
        }
    }
    //remove leading zeroes
    for (i = (a.at(0) == '-'); i < a.size(); i++) {
        if (a.at(i) == '.') {
            i--;
            break;
        }
        else if (a.at(i) < 58 && a.at(i) > 48) {
            break;
        }
    }
    a.erase(a.begin() + (a.at(0) == '-'), a.begin() + i);
}
string addition(string a, string b)
{
    // check for positive and negative
    int aRight, aLeft, bRight, bLeft, AnswerRight, AnswerLeft;
    aLeft = GetScientificDecimal(a);
    if (aLeft < 0) { aLeft = 1; }
    aLeft = aLeft + (a.at(0) == '-');
    aRight = a.size() - aLeft;
    bLeft = GetScientificDecimal(b);
    if (bLeft < 0) { bLeft = 1; }
    bLeft = bLeft + (b.at(0) == '-');
    bRight = b.size() - bLeft;
    string answer;
    AnswerLeft = max(aLeft, bLeft);
    AnswerRight = max(aRight, bRight); // minus one for the decimal
    answer.resize(AnswerLeft + AnswerRight + 1, '0');
    while (AnswerRight > 0) {
        if (AnswerRight <= aRight) {
            answer.at(AnswerLeft + AnswerRight) = answer.at(AnswerLeft + AnswerRight) + (a.at(0) != '-') * (a.at(aLeft + aRight - 1) - 48) - (a.at(0) == '-') * (a.at(aLeft + aRight - 1) - 48);
            aRight--;
        }
        if (AnswerRight <= bRight) {
            answer.at(AnswerLeft + AnswerRight) = answer.at(AnswerLeft + AnswerRight) + (b.at(0) != '-') * (b.at(bLeft + bRight - 1) - 48) - (b.at(0) == '-') * (b.at(bLeft + bRight - 1) - 48);
            bRight--;
        }
        AnswerRight--;
    }
    bRight = AnswerLeft; // record the position of the decimal
    while (AnswerLeft > 0)
    {
        if (aLeft > (a.at(0) == '-')) {
            answer.at(AnswerLeft) = answer.at(AnswerLeft) + (a.at(0) != '-') * (a.at(aLeft - 1) - 48) - (a.at(0) == '-') * (a.at(aLeft - 1) - 48);
            aLeft--;
        }
        if (bLeft > (b.at(0) == '-')) {
            answer.at(AnswerLeft) = answer.at(AnswerLeft) + (b.at(0) != '-') * (b.at(bLeft - 1) - 48) - (b.at(0) == '-') * (b.at(bLeft - 1) - 48);
            bLeft--;
        }
        AnswerLeft--;
    }
    // find out if they are positive or negative
    for (aRight = 0; aRight < answer.size(); aRight++){
        if (answer.at(aRight) != '0' && answer.at(aRight) != '.'){
            break;
        }
    }
    // if negative switch it on its head
    if (aRight == answer.size()){
        return "0";
    }
    else if (answer.at(aRight) < '0'){
        for (aRight = 0; aRight < answer.size(); aRight++){
            answer.at(aRight) = 96 - answer.at(aRight);
        }
        answer.insert(answer.begin(), '-');
        bRight++;//bRight holds the decimal position since we added negative symbol the decimal will be further right
    }
    // clean up and make it so all the characters are numbers, deciamal, or negative sign
    for (AnswerLeft = answer.size() - 1; AnswerLeft > (answer.at(0) == '-'); AnswerLeft--){
        if (AnswerLeft == (bRight + 2))
        { // decimal
            if (answer.at(AnswerLeft) > '9'){
                answer.at(AnswerLeft) = answer.at(AnswerLeft) - 10;
                answer.at(AnswerLeft - 1) = answer.at(AnswerLeft - 1) + 1;
            }
            else if (answer.at(AnswerLeft) < '0'){
                answer.at(AnswerLeft) = answer.at(AnswerLeft) + 10;
                answer.at(AnswerLeft - 2) = answer.at(AnswerLeft - 2) - 1;
            }
            answer.at(bRight + 1) = '.';
            AnswerLeft--;
        }
        else if (answer.at(AnswerLeft) > '9'){
            answer.at(AnswerLeft) = answer.at(AnswerLeft) - 10;
            answer.at(AnswerLeft - 1) = answer.at(AnswerLeft - 1) + 1;
        }
        else if (answer.at(AnswerLeft) < '0'){
            answer.at(AnswerLeft) = answer.at(AnswerLeft) + 10;
            answer.at(AnswerLeft - 1) = answer.at(AnswerLeft - 1) - 1;
        }
    }
    clean(answer);
    return answer;
}
string multiply(string a, string b) {
    //we have n! in the for loops.  Look for a better way to do that
    if ((a.size() == 1 && a.at(0) == '0') || (b.size() == 1 && b.at(0) == '0')) {
        return "0";
    }
    short int tempA = 0, tempB = 0;
    int i, j;
    int decimal = 0;
    bool positive;
    //find out if the operation is positive 
    if (a.at(0) == '-') {
        tempA++;
        a.erase(a.begin());
    }

    if (b.at(0) == '-') {
        tempA++;
        b.erase(b.begin());
    }

    if (tempA == 1) {
        positive = false;
    }
    else {
        positive = true;
    }
    tempA = 0;
    //finding decimals
    for (i = 0; i < a.size(); i++) {
        if (a.at(i) == '.') {
            decimal = a.size() - (i + 1);
            a.erase(a.begin() + i);
            break;
        }
    }
    for (i = 0; i < b.size(); i++) {
        if (b.at(i) == '.') {
            decimal = decimal + (b.size() - (i + 1));
            b.erase(b.begin() + i);
            break;
        }
    }
    vector<short int> c(a.size() + b.size());
    for (i = 0; i < a.size(); i++) {
        for (j = 0; j < b.size(); j++) {
            tempA = a.at(i) - '0';
            tempB = b.at(j) - '0';
            tempA = tempA * tempB;
            c.at(i + j) = c.at(i + j) + tempA / 10;
            c.at(i + j + 1) = c.at(i + j + 1) + tempA % 10;
        }
    }
    //some may be double digits
    for (i = c.size() - 1; i > 0; i--) {
        c.at(i - 1) = c.at(i - 1) + c.at(i) / 10;
        c.at(i) = c.at(i) % 10;
    }
    //to character
    a.clear();
    //change vector to char
    a.resize(c.size() + (decimal > 0));
    if (decimal > 0) {
        decimal = c.size() - decimal;
        for (i = 0; i < decimal; i++) {
            a.at(i) = c.at(i) + '0';
        }
        a.at(decimal) = '.';
        for (i = decimal + 1; i < c.size() + 1; i++) {
            a.at(i) = c.at(i - 1) + '0';
        }
    }
    else {
        for (i = decimal; i < c.size(); i++) {
            a.at(i) = c.at(i) + '0';
        }
    }
    //removing leading zeros and after the program since its called somewhere else
    clean(a);
    return a;
}
string division(string Dividend, string Divisor) {
    if (Divisor.size() == 1 && Divisor.at(0) == 48 || Dividend.size() == 1 && Dividend.at(0) == 48) { return "0"; }//technically its undefined but instead of creating a new edge case we are going to treat it as if it reset itself
    bool negative = 0;
    //find out if the answer is negative or positive
    if (Dividend.at(0) == '-') {
        Dividend.erase(Dividend.begin());
        negative = 1;
    }
    if (Divisor.at(0) == '-') {
        Divisor.erase(Divisor.begin());
        negative = !negative;
    }
    //find out decimal
    //decimal for the answer and several other uses
    int DividendDecimal = GetScientificDecimal(Dividend), DivisorDecimal = GetScientificDecimal(Divisor);
    //erase decimals
    if (DividendDecimal == Dividend.size()) {//do nothing no deciamal
    }
    else if (DividendDecimal >= 0) {//what if there is no decimal
        Dividend.erase(Dividend.begin() + DividendDecimal);
    }
    else {
        Dividend.erase(Dividend.begin() + 1);
    }
    clean(Dividend);

    //erase decimals
    if (DivisorDecimal == Divisor.size()) {//do nothing no deciamal
    }
    else if (DivisorDecimal >= 0) {//what if there is no decimal
        Divisor.erase(Divisor.begin() + DivisorDecimal);
    }
    else {
        Divisor.erase(Divisor.begin() + 1);
    }
    clean(Divisor);
    //Division
    string answer = "0";
    string multiplier = "0";
    answer.resize(Dividend.size() + Divisor.size() + 16, '0');
    Dividend.resize(answer.size(), '0');
    //do the first one
    int i = 0, j = 0;
    multiplier.at(0) = (Dividend.at(0) - 48) / (Divisor.at(0) - 48) + 48;
    answer.at(i) = multiplier.at(0);
    multiplier = multiply(multiplier, Divisor);
    //make sure we have a multiplier of the same size
    while (multiplier.size() > Divisor.size()) {
        for (j = multiplier.size() - 1; j > 0; j--) {
            multiplier.pop_back();
        }
        answer.at(0) = answer.at(0) - 1;
        multiplier.at(0) = answer.at(0);
        multiplier = multiply(multiplier, Divisor);
    }
    //subtract multiplier from Dividend
    //cout<<'\n'<<multiplier<<'\n';
    for (j = 0; j < multiplier.size(); j++) {
        Dividend.at(i + j) = Dividend.at(i + j) - multiplier.at(j) + 48;
    }
    //adjust dividend to be actual numbers and not negative
    for (j = 0; j < multiplier.size(); j++) {
        //cout<<"......................................................\n";
        //cout<<Dividend.at(i+j)*1<<" "<<Dividend.at(i+j);
        if (Dividend.at(i + j) != 48) {
            break;
        }
    }
    if (j != multiplier.size() && Dividend.at(i + j) < 48) {//we have a negative result and we need to add a divisor to adjust
        answer.at(0) = answer.at(0) - 1;
        for (j = 0; j < multiplier.size(); j++) {
            Dividend.at(i + j) = Dividend.at(i + j) + Divisor.at(j) - 48;//check we might be able to remove this
        }
    }
    //adjust to make the numbers one through nine
    //cout<<"\nadjusting Division to be in between 0 and 9 Dividend: "<<Dividend;
    for (j = multiplier.size() - 1; j > 0; j--) {
        //cout<<"Dividend at i+j: "<<Dividend.at(i+j)<<" and i+j "<<i+j<<'\n';
        if (Dividend.at(i + j) > 58) {
            Dividend.at(i + j) = Dividend.at(i + j) - 10;
            Dividend.at(i + j - 1) = Dividend.at(i + j - 1) + 1;
        }
        else if (Dividend.at(i + j) < 48) {
            Dividend.at(i + j) = Dividend.at(i + j) + 10;
            Dividend.at(i + j - 1) = Dividend.at(i + j - 1) - 1;
        }
        //cout<<"Dividend at i+j after the process: "<<Dividend.at(i+j)<<" and i+j "<<i+j<<" Dividind: "<<Dividend<<'\n';
    }
    i = 1; j = 0;
    while (i < Dividend.size()-Divisor.size()){
        //find out the maximim number of divisor which can be in here
        multiplier = "0";
        multiplier.at(0) = ((Dividend.at(i - 1) - 48) * 10 + (Dividend.at(i) - 48)) / (Divisor.at(0) - 48) + 48;
        answer.at(i) = multiplier.at(0);//assume we are correct
        if (multiplier.at(0) != 48) {
            multiplier = multiply(Divisor, multiplier);
            //assume we are correct
            //subtract multiplier from Dividend
            for (j = 0; j < multiplier.size(); j++) {
                Dividend.at(i + j - (multiplier.size() > Divisor.size())) = Dividend.at(i + j - (multiplier.size() > Divisor.size())) - multiplier.at(j) + 48;
            }
            //adjust dividend to be actual numbers and not negative
            for (j = 0; j < multiplier.size(); j++) {
                if (Dividend.at(i + j - (Divisor.size() < multiplier.size())) != 48) {
                    break;
                }
            }
            //we have a negative result and we need to add a divisor to adjust
            while (j != multiplier.size() && Dividend.at(i + j - (Divisor.size() < multiplier.size())) < 48 && answer.at(i) > 48) {
                answer.at(i) = answer.at(i) - 1;
                for (j = Divisor.size() - 1; j >= 0; j--) {
                    Dividend.at(i + j) = Dividend.at(i + j) + Divisor.at(j) - 48;
                    if (Dividend.at(i + j) > 57) {
                        Dividend.at(i + j) = Dividend.at(i + j) - 10;
                        Dividend.at(i + j - 1) = Dividend.at(i + j - 1) + 1;
                    }
                    else if (Dividend.at(i + j) < 48) {
                        Dividend.at(i + j) = Dividend.at(i + j) + 10;
                        Dividend.at(i + j - 1) = Dividend.at(i + j - 1) - 1;
                    }
                }
                //check again
                for (j = 0; j < multiplier.size(); j++) {
                    if (Dividend.at(i + j - (Divisor.size() < multiplier.size())) != 48) {
                        break;
                    }
                }
            }
            //adjust to make the numbers one through nine
            for (j = multiplier.size() - 1; j >= 0; j--) {
                if (Dividend.at(i + j) > 57) {
                    Dividend.at(i + j) = Dividend.at(i + j) - 10;
                    Dividend.at(i + j - 1) = Dividend.at(i + j - 1) + 1;
                }
                else if (Dividend.at(i + j) < 48) {
                    Dividend.at(i + j) = Dividend.at(i + j) + 10;
                    Dividend.at(i + j - 1) = Dividend.at(i + j - 1) - 1;
                }
            }
        }
        //next
        i++;
    }
    //answer should have the information we need
    //note:: popback size of divisor and remove the excess zeroes
    for (j = 0; j < Divisor.size(); j++) {
        answer.pop_back();
    }
    //now we add decimals as neccesary
    if (0 > (DividendDecimal - DivisorDecimal)) {
        //reverse and resize
        for (i = 0; i < answer.size() / 2; i++) {//using multiplier at zero so we don't need to declare new memory
            multiplier.at(0) = answer.at(i);
            answer.at(i) = answer.at(answer.size() - 1 - i);
            answer.at(answer.size() - 1 - i) = multiplier.at(0);
        }
        answer.resize(answer.size() - (DividendDecimal - DivisorDecimal) + 1, '0');
        answer.at(answer.size() - 2) = '.';
        //reverse again
        //reverse and resize
        for (i = 0; i < answer.size() / 2; i++) {//using multiplier at zero so we don't need to declare new memory
            multiplier.at(0) = answer.at(i);
            answer.at(i) = answer.at(answer.size() - 1 - i);
            answer.at(answer.size() - 1 - i) = multiplier.at(0);
        }
    }
    else if (DividendDecimal - DivisorDecimal + 1 > answer.size()) {//add zeros at the end
        if (DivisorDecimal < 0) {
            DivisorDecimal++;
        }
        answer.resize(DividendDecimal - DivisorDecimal, '0');
    }
    else {//we are have decimal somewhere in the middle
        answer.insert(answer.begin() + DividendDecimal - DivisorDecimal, '.');//(DividendDecimal-DivisorDecimal),'.');
    }
    if (negative) {
        answer.insert(answer.begin(), '-');
    }
    clean(answer);
    return answer;
}
int main(){

    sf::Event event;
    //setup font for the calculator
    sf::Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\Consola.ttf");
    //make window
    sf::RenderWindow window(sf::VideoMode(584, 634), "Calculator");
    sf::Vector2u size;//we need the size of the window for the button function
    window.setFramerateLimit(30);

    //calculator background
    Texture BackgroundImage;
    BackgroundImage.loadFromFile("C:\\Users\\Michael\\OneDrive\\Documents\\GitHub\\Calculator\\images\\Calculator Background.png");
    sf::Sprite Background(BackgroundImage);

    //set current
    CalcNumbers EntryText;
    EntryText.MyText.setFont(font);
    EntryText.setString("0");
    EntryText.MyText.setCharacterSize(49);
    EntryText.MyText.setFillColor(sf::Color::Black);
    EntryText.MyText.setPosition(17, 84);
    //set up history
    CalcNumbers History;
    sf::Color Grey{ 20,20,20 };
    History.MyString = "0";
    History.MyText.setFont(font);
    History.MyText.setString(History.MyString+History.OperationString());
    History.MyText.setCharacterSize(28);
    History.MyText.setFillColor(Grey);
    History.MyText.setPosition(27, 55);
    //start game
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { window.close(); }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    size = window.getSize();
                    EntryText.operation = button(event.mouseButton.x, event.mouseButton.y, size);
                    cout << EntryText.operation;

                }

                //react to button press
                
                switch (EntryText.operation)
                {
                case ' ':
                    //do nothing no button was pressed
                    break;
                case 'c'://clear both entries
                    History.Clear();
                    EntryText.Clear();
                    break;
                case 'e':
                    //clear current entry
                    EntryText.Clear();
                    break;
                case 'i':
                    //inverse
                    break;
                case 'n'://negative
                    if (EntryText.MyString.size() == 1 && EntryText.MyString.at(0) == '0') {
                        //do nothing
                    }
                    else if (EntryText.MyString.at(0) == '-') {
                        EntryText.MyString.erase(EntryText.MyString.begin());
                    }
                    else{
                        EntryText.MyString.insert(EntryText.MyString.begin(), '-');
                    }
                    EntryText.MyText.setString(EntryText.CorrectFormat());
                    break;
                case '=':
                    //based on history operation calculate new value
                    if (History.operation == ' ') {
                        History.MyString = EntryText.MyString;
                        EntryText.Clear();
                    }
                    else if (History.operation == '/') {
                        History.MyString = division(History.MyString, History.MyString);
                        EntryText.Clear();
                    }
                    else if (History.operation == '-') {
                        if (EntryText.MyString.at(0) == '-') {
                            EntryText.MyString.erase(EntryText.MyString.begin());
                        }
                        else {
                            EntryText.MyString.insert(EntryText.MyString.begin(), '-');
                        }
                        History.MyString = addition(History.MyString,EntryText.MyString);
                        EntryText.Clear();
                    }
                    else if (History.operation == '+') {
                        History.MyString = addition(EntryText.MyString, History.MyString);
                        EntryText.Clear();
                    }
                    else {
                        History.MyString = multiply(EntryText.MyString, History.MyString);
                        EntryText.Clear();
                    }
                    History.operation = ' ';
                    History.MyText.setString(History.CorrectFormat() + History.operation);
                    break;
                case '/'://division
                    if (History.operation == ' ' && (History.MyString.size() != 1 || History.MyString.at(0) != '0')) {
                        History.operation = '/';
                    }
                    else if (History.operation == ' ' || (History.MyString.size() == 1 && History.MyString.at(0) == '0')) {
                        History.MyString = EntryText.MyString;
                        History.operation = '/';
                        EntryText.Clear();
                    }
                    else {
                        //division
                        History.MyString = division(History.MyString, History.MyString);
                        History.operation = ' ';
                        EntryText.Clear();
                    }
                    History.MyText.setString(History.CorrectFormat() + History.operation);
                    break;
                case '-'://subtract
                    if (History.operation == ' ' && (History.MyString.size() != 1 || History.MyString.at(0) != '0')) {
                        History.operation = '-';
                    }
                    else if (History.operation == ' ' || (History.MyString.size() == 1 && History.MyString.at(0) == '0')) {
                        History.MyString = EntryText.MyString;
                        History.operation = '-';
                        EntryText.Clear();
                    }
                    else {
                        if (EntryText.MyString.at(0) == '-') {
                            EntryText.MyString.erase(EntryText.MyString.begin());
                        }
                        else {
                            EntryText.MyString.insert(EntryText.MyString.begin(), '-');
                        }
                        History.MyString = addition(History.MyString,EntryText.MyString);
                        History.operation = ' ';
                        EntryText.Clear();
                    }
                    History.MyText.setString(History.CorrectFormat() + History.operation);
                    break;
                case '+':
                    if (History.operation == ' ' && (History.MyString.size() != 1 || History.MyString.at(0) != '0')) {
                        History.operation = '+';
                    }
                    else if (History.operation == ' ' || (EntryText.MyString.size() == 1 && EntryText.MyString.at(0) == '0')) {
                        History.MyString = EntryText.MyString;
                        History.operation = '+';
                        EntryText.Clear();
                    }
                    else {
                        //addition
                        History.MyString = addition(EntryText.MyString, History.MyString);
                        History.operation = EntryText.operation;
                        EntryText.Clear();
                    }
                    History.MyText.setString(History.CorrectFormat() + History.operation);
                    break;
                case '*'://multiply
                    if (History.operation == ' ' && (History.MyString.size() != 1 || History.MyString.at(0) != '0')) {
                        History.operation = '*';

                    }
                    else if (History.operation == ' ' || (History.MyString.size() == 1 && History.MyString.at(0) == '0')) {
                        History.MyString = EntryText.MyString;
                        History.operation = '*';
                        EntryText.Clear();
                    }
                    else {
                        History.MyString=multiply(EntryText.MyString, History.MyString);
                        History.operation = EntryText.operation;
                        EntryText.Clear();
                    }
                    History.MyText.setString(History.CorrectFormat() + History.operation);
                    break;
                case '.':
                    if (GetScientificDecimal(EntryText.MyString) == EntryText.MyString.size()) {
                        EntryText.MyString.push_back('.');
                        EntryText.MyText.setString(EntryText.MyString);
                    }
                    break;
                case '0':
                    cout << "0\n";
                    if (EntryText.MyString.size() == 1 && EntryText.MyString.at(0) == '0') {
                        break;
                    }
                default:
                    cout << "default\n";
                    if (EntryText.MyString.size() < 17) {
                        if (EntryText.MyString.size() == 1 && EntryText.MyString.at(0) == '0') {
                            EntryText.MyString.at(0) = EntryText.operation;
                        }
                        else {
                            EntryText.MyString.push_back(EntryText.operation);
                        }
                        EntryText.MyText.setString(EntryText.MyString);
                    }
                    break;
                }
                //check for overload
                
            }
        }

        //render
        window.clear();
        window.draw(Background);
        window.draw(EntryText.MyText);
        window.draw(History.MyText);
        window.display();
    }

    return 0;
}
