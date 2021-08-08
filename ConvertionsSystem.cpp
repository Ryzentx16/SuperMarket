//
// Created by user on 6/22/2021.
//
#include <iostream>
#include <math.h>
using namespace std;
#include "ConvertionsSystem.h"

string _trim(string str) {
  string chars = "\t\n\v\f\r0 ";
  str.erase(0, str.find_first_not_of(chars));
  str.erase(str.find_last_not_of(chars) + 1);
  return str;
}

int numLen(int n){
    int cnt=0;
    for(; n != 0; n /= 10){
        cnt++;
    }
    //cout << "numLen: " << max(1, cnt) << endl;
    return max(1, cnt);
}

int strToInt(string str){
    int i=0, sum=0;

    while(str[i] != '\0')                       //string not equals to null
    {
         sum = sum*10 + (str[i] - 48); //in ASCII 48 equal '0'
         i++;
    }

    return sum;
}

double strToDouble(string str){
    double result= 0.0f;
    int len = str.size();
    int dotpos = 0;
    for (int n = 0; n < len; n++) {
        if (str[n] == '.') {
            dotpos = len - n - 1; // to get any character's position use (len - n) - 1
        }
        else {
            result = result * 10 + (str[n]-'0');
        }
    }
    result /= pow(10,dotpos);
    return result;
}

string numToStr(double num){
    /*double numlen = numLen(num)+1;
    string result;
    for(int i = numlen-2 ; i >= 0; i--){
        result += num%10+'0';
        num /= 10;
    }
    for (int i = 0; i < result.size() / 2; i++)
        swap(result[i], result[result.size() - i - 1]);
*/
    return _trim(to_string(num));
}

string numToStr(int num){
    /*double numlen = numLen(num)+1;
    string result;
    for(int i = numlen-2 ; i >= 0; i--){
        result += num%10+'0';
        num /= 10;
    }
    for (int i = 0; i < result.size() / 2; i++)
        swap(result[i], result[result.size() - i - 1]);
*/
    return _trim(to_string(num));
}
