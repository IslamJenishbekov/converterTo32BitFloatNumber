#include <iostream>
#include <string>
using namespace std;

bool getMode(); //функция выбора режима  
string getNumberFromUser(string); //функция получения и проверки корректности числа для преобразования
string getSign10To2(string);// функция определения знака в преобразовании 10 -> 2
double power(double, int);// функция вычисления степени
string convertToBinary(int);// функция преобразования числа типа инт в двоичное число
string convertToBinary(double);//функция преобразования чила типа дабл в двоичное число
string getExponent10To2(string);//функция вычисления порядка числа в преобразовании 10 -> 2
string getFraction10to2(string);//функция вычисления мантиссы числа в преобразовании 10 -> 2
double convertToDecimal(string);//функция преобразования двоичного числа в десятичное число
bool getModeFor2To10();//функция выбора режима преобразования двоичного числа в десятиное число
string getSign2To10(string);//функция определения знака при преобразовании 32 битного двоичного числа в десятичное
double getNumber2To10(string);//функция определения числа при преобразовании 32 битного двоичного числа в десятичное
bool checkForPossible2To10(string);//функция проверки данного числа на возможность преобразования его с 32 битного представления в десятичное число
bool treatSpecialCases(string, string);//функция обработки частных случаев

int main() {
	setlocale(LC_ALL, "Russian");

	
	while (true) {
		string mode = (getMode()) ? "10->2" : "2->10";
		string numberFromUser = getNumberFromUser(mode);
		if (numberFromUser == "ex") continue;
		
		
		else if (mode == "10->2") {
			if (treatSpecialCases(numberFromUser, mode)) {
				cout << endl << "Сессия завершена успешно!" << endl << endl;
				continue; 
			}
			string sign = getSign10To2(numberFromUser);
			string exponent = getExponent10To2(numberFromUser);
			string fraction = getFraction10to2(numberFromUser);
			cout << sign << " " << exponent << " " << fraction;
		}
		else if (mode == "2->10") {
			bool mode2To10 = getModeFor2To10();
			if (mode2To10 == true && checkForPossible2To10(numberFromUser)) {
				if (treatSpecialCases(numberFromUser, mode)) {
				cout << endl << "Сессия завершена успешно!" << endl << endl;
				continue; 
				}
				string sign = getSign2To10(numberFromUser);
				double number = getNumber2To10(numberFromUser);
				cout << sign << number;
			}
			else if (mode2To10 == false) {
				cout << convertToDecimal(numberFromUser);
			}
		}
		cout << endl << "Сессия завершена успешно!" << endl << endl;
	}
	
	return 0;
}

bool getMode() {
	string mode;
	cout << "Выберите нужный режим:\n1 - из десятичной в 32 битное представление\n2 - из двоичного представления в десятичное представление\n";
	while (true) {
		cin >> mode;
		if (mode=="1") {
			return true;
		}
		else if (mode=="2") {
			return false;
		}
		else {
			cout << "Наберите режим правильно и введите его еще раз: ";
		}
	}
}

string getNumberFromUser(string mode) {
	string number;
	while (true) {
		cout << "Введите число без пробелов: (!если хотите поменять режим введите ex)\n";
		cin >> number;
		if (number == "ex") {
			return number;
		}
		
		else if (mode == "10->2") {
			int pointCounter=0;
			bool flagAlpha = true;
			for (int i=0; i<number.length(); i++) {
				if (i==0&&number[i] == '-') continue;
				else if (number[i] == '.') {pointCounter++; continue;}
				else if (isdigit(number[i])==false) {flagAlpha = false; break;}
			}
			
			if (pointCounter<=1 && flagAlpha==true) {
				string resultNumber="";
				for (int i=0; i<number.length(); i++) {
					if (number[i] != ' ') {
						string temp(1, number[i]);
						resultNumber+=temp;
					}
				}
				return resultNumber;
			}
		}
		
		else if (mode == "2->10") {
			int pointCounter = 0;
			bool flagAlpha = true;
			for (int i=0; i<number.length(); i++) {
				if (number[i] == '.') {pointCounter++; continue;}
				else if (number[i] != '1' && number[i] != '0') {flagAlpha = false; break;}
			}
			
			if (pointCounter<=1 && flagAlpha==true) {
				string resultNumber="";
				for (int i=0; i<number.length(); i++) {
					if (number[i] != ' ') {
						string temp(1, number[i]);
						resultNumber+=temp;
					}
				}
				return resultNumber;
			}
		}
		
		cout << "Вы ввели неправильное число!\nВведите снова и убедитесь, что выбрали нужный вам режим.\n";
		
	}
	
}

string getSign10To2(string numberFromUser) {
	for (int i=0; i<numberFromUser.length(); i++) {
		if (numberFromUser[i] == ' ') continue;
		else if (numberFromUser[i] == '-') return "1";
		else return "0";
	}
}

double power(double number, int numberPow) {
	if (numberPow==0) return 1;
	else if (numberPow<0) {
		return 1.0/power(number, -numberPow);
	}
	double result = 1;
	for (int i=0; i<numberPow; i++){
		result *= number;
	}
	return result;
}

string convertToBinary(int x) {
	if (x==0) return "0";
	string result = "";
	int tempValue;
	char zero = '0';
	char temp;
	while (x>0) {
		tempValue = x%2;
		temp = zero + tempValue;
		string subStr(1, temp);
		subStr+=result;
		result = subStr;
		x/=2;
	}
	return result;
}

string convertToBinary(double x) {
	string result = "";
	string wholePart = convertToBinary( (int)x );
	result += wholePart;
	x = x - int(x);
	result+=".";
	double xCompare = 0.0;
	double tempValue;
	for (int i=-1; i>-10; i--){
		tempValue = power(2, i);
		if (xCompare+tempValue==x) {
			string elem(1, '1');
			result += elem;
			break;
		}
		else if (xCompare+tempValue>x){
			string elem(1, '0');
			result += elem;	
		}
		else if (xCompare+tempValue<x) {
			string elem (1, '1');
			result += elem;
			xCompare+=tempValue;
		}
		tempValue=0;
		}
	return result;
}

string getExponent10To2(string numberFromUser) {
	
	for (int i=0; i<numberFromUser.length(); i++){
		if (numberFromUser[i] == ' ' || numberFromUser[i] == '-') {numberFromUser.erase(numberFromUser.begin()); continue;}
		else {break;}
    }
    
    bool doubleFlag=false;
    for (auto elem : numberFromUser) {
    	if (elem == '.') doubleFlag = true;
	}
	
	if (doubleFlag == false) {
		int expIn10 = stoi(numberFromUser);
		string expInBinary = convertToBinary(expIn10);
		expInBinary = convertToBinary((int)expInBinary.length()-1+127);
		if (expInBinary.length() == 7) expInBinary = "0" + expInBinary;
		return expInBinary;
	}
	
	else if (doubleFlag == true) {
		setlocale(LC_ALL, "English");
		double expIn10 = stod(numberFromUser);
		string expInBinary = convertToBinary(expIn10);
		int pointIndex;
		for (int i=0; i<expInBinary.length(); i++) {
			if (expInBinary[i] == '.') {
				pointIndex = i;
				break;
			}
		}
		
		if (pointIndex == 1 && expInBinary[0] == '0') {
			pointIndex = pointIndex - expInBinary.length() + 1;
			cout << "POINT INDEX; " << pointIndex << endl;
			cout << expInBinary << endl;
			expInBinary = convertToBinary(pointIndex+127);
			if (expInBinary.length() == 7) expInBinary = "0" + expInBinary;
			setlocale(LC_ALL, "Russian");
			return expInBinary;
		}
		
		expInBinary = convertToBinary(pointIndex-1+127);
		if (expInBinary.length() == 7) expInBinary = "0" + expInBinary;
		setlocale(LC_ALL, "Russian");
		return expInBinary;
		
	}	   
}

string getFraction10to2(string numberFromUser) {
	for (int i=0; i<numberFromUser.length(); i++){
		if (numberFromUser[i] == ' ' || numberFromUser[i] == '-') {numberFromUser.erase(numberFromUser.begin()); continue;}
		else {break;}
    }
    
    bool doubleFlag=false;
    for (auto elem : numberFromUser) {
    	if (elem == '.') doubleFlag = true;
	}
	
	string result="";
	if (doubleFlag == false) {
		int numberInt = stoi(numberFromUser);
		string numberBinary = convertToBinary(numberInt);
		for (int i=1; i<numberBinary.length(); i++) {
			string temp(1, numberBinary[i]);
			result += temp;
		}
	}
	else if (doubleFlag == true) {
		setlocale(LC_ALL, "English");
		double numberDouble = stod(numberFromUser);
		setlocale(LC_ALL, "Russian");
		string numberBinary = convertToBinary(numberDouble);
		for (int i=1; i<numberBinary.length(); i++) {
			if(numberBinary[0] == '0') {
				bool flagFirstOne = true;
				for(int j=2; j<numberBinary.length(); j++) {
					if (flagFirstOne == true && numberBinary[j] == '1') {
						flagFirstOne = false;
						continue;
					}
					else if (flagFirstOne == false && (numberBinary[i] == '0' || numberBinary[i] == '1')){
						string temp(1, numberBinary[i]);
						result += temp;
					}
				}
				break;	
			}
			else if (numberBinary[i] == '.') continue;
			string temp(1, numberBinary[i]);
			result += temp;
		}
	}
	
	while (result.length() < 23){
		result += "0";
	}
	
	return result;
}

double convertToDecimal(string strNumber) {
	double result = 0;
	int pointIndex = 0;
	for (int i=0; i<strNumber.length(); i++) {
		if (strNumber[i] == '.') {
			pointIndex = i;
			break;
		}
	}
		
	if (pointIndex == 0) {
		int zeroInd = '0';
		int powerCounter = 0;
		int temp;
		for (int i=strNumber.length()-1; i>=0; i--) {
			temp = strNumber[i] - zeroInd;
			result += temp * power(2, powerCounter++);
		}
		return result;
	}
	else if (pointIndex != 0) {
		int zeroInd = '0', temp;
		int powerCounter = pointIndex - strNumber.length() +1;
		for (int i=strNumber.length()-1; i>=0; i--) {
			if (strNumber[i] == '.') continue;
			temp = strNumber[i] - zeroInd;
			result += temp * power(2, powerCounter++);
		}
		return result;
	}
}

bool getModeFor2To10() {
	cout << "Это 32 битное число или обычное двоичное?\n1 - 32 битное \n2 - обычное двоичное число\n";
	string mode;
	while (true) {
		cin >> mode;
		if (mode == "1") {
			return true;
		}
		else if (mode == "2") {
			return false;
		}
		else {
			cout << "Введите 1 или 2!\n";
		}
	}
} 

string getSign2To10(string numberFromUser){
	if (numberFromUser[0] == '1') return "-";
	else if (numberFromUser[0] == '0') return "";
	else return "ERROR in getSign2To10!";
}

double getNumber2To10(string numberFromUser) {
	string expStr = "";
	string fraction = "1";
	string point = ".";
	for (int i=1; i<numberFromUser.length(); i++) {
		string temp(1, numberFromUser[i]);
		if (i<9) expStr += temp;
		else if (i>=9)  fraction += temp;
	}
	
	double exp = convertToDecimal(expStr) - 126;
	fraction.insert(exp, point);
	
	double result = convertToDecimal(fraction);
	return result;
}

bool checkForPossible2To10(string numberFromUser) {
	
	if (numberFromUser.length() < 10) {
		cout << endl << "Ошибка с размером введенного числа!";
		return false;
	}
	
	for (int i=0; i<numberFromUser.length(); i++) {
		if (numberFromUser[i] == '.') {
			cout << endl << "В 32 битном представлении не может быть символа точки!";
			return false;
		}
	}
	
	return true;
	
}

bool treatSpecialCases (string numberFromUser, string mode) {
	if (mode == "10->2" && numberFromUser == "0") {
		cout << "0 00000000 00000000000000000000000" << endl;
		return true;
	}
	
	else if (mode == "2->10") {
		int counterOneSymbol = 0;
		int counterOneSymbolInfinity = 0;
		for (int i=1; i<numberFromUser.length(); i++) {
			if (numberFromUser[i] == '1') {
				counterOneSymbol++;
			}
			if (i<9 && numberFromUser[i] == '1') {
				counterOneSymbolInfinity++;
			}
		}
		if (counterOneSymbol == 0) {
			if (numberFromUser[0] == '0') {
				cout << "0";
				return true;
			}
			else {
				cout << "-0";
				return true;
			}
		}
		
		else if (counterOneSymbolInfinity == 8 && counterOneSymbolInfinity == counterOneSymbol) {
			if (numberFromUser[0] == '0') {
				cout << "infinity";
				return true;
			}
			else {
				cout << "-infinity";
				return true;
			}
		}
		
		else if (counterOneSymbolInfinity == 8 && counterOneSymbolInfinity != counterOneSymbol) {
			cout << "NaN";
			return true;
		}
	}
	
	return false;
}
