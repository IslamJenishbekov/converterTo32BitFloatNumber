#include <iostream>
#include <string>
using namespace std;

bool getMode(); //������� ������ ������  
string getNumberFromUser(string); //������� ��������� � �������� ������������ ����� ��� ��������������
string getSign10To2(string);// ������� ����������� ����� � �������������� 10 -> 2
double power(double, int);// ������� ���������� �������
string convertToBinary(int);// ������� �������������� ����� ���� ��� � �������� �����
string convertToBinary(double);//������� �������������� ���� ���� ���� � �������� �����
string getExponent10To2(string);//������� ���������� ������� ����� � �������������� 10 -> 2
string getFraction10to2(string);//������� ���������� �������� ����� � �������������� 10 -> 2
double convertToDecimal(string);//������� �������������� ��������� ����� � ���������� �����
bool getModeFor2To10();//������� ������ ������ �������������� ��������� ����� � ��������� �����
string getSign2To10(string);//������� ����������� ����� ��� �������������� 32 ������� ��������� ����� � ����������
double getNumber2To10(string);//������� ����������� ����� ��� �������������� 32 ������� ��������� ����� � ����������
bool checkForPossible2To10(string);//������� �������� ������� ����� �� ����������� �������������� ��� � 32 ������� ������������� � ���������� �����
bool treatSpecialCases(string, string);//������� ��������� ������� �������

int main() {
	setlocale(LC_ALL, "Russian");

	
	while (true) {
		string mode = (getMode()) ? "10->2" : "2->10";
		string numberFromUser = getNumberFromUser(mode);
		if (numberFromUser == "ex") continue;
		
		
		else if (mode == "10->2") {
			if (treatSpecialCases(numberFromUser, mode)) {
				cout << endl << "������ ��������� �������!" << endl << endl;
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
				cout << endl << "������ ��������� �������!" << endl << endl;
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
		cout << endl << "������ ��������� �������!" << endl << endl;
	}
	
	return 0;
}

bool getMode() {
	string mode;
	cout << "�������� ������ �����:\n1 - �� ���������� � 32 ������ �������������\n2 - �� ��������� ������������� � ���������� �������������\n";
	while (true) {
		cin >> mode;
		if (mode=="1") {
			return true;
		}
		else if (mode=="2") {
			return false;
		}
		else {
			cout << "�������� ����� ��������� � ������� ��� ��� ���: ";
		}
	}
}

string getNumberFromUser(string mode) {
	string number;
	while (true) {
		cout << "������� ����� ��� ��������: (!���� ������ �������� ����� ������� ex)\n";
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
		
		cout << "�� ����� ������������ �����!\n������� ����� � ���������, ��� ������� ������ ��� �����.\n";
		
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
	cout << "��� 32 ������ ����� ��� ������� ��������?\n1 - 32 ������ \n2 - ������� �������� �����\n";
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
			cout << "������� 1 ��� 2!\n";
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
		cout << endl << "������ � �������� ���������� �����!";
		return false;
	}
	
	for (int i=0; i<numberFromUser.length(); i++) {
		if (numberFromUser[i] == '.') {
			cout << endl << "� 32 ������ ������������� �� ����� ���� ������� �����!";
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
