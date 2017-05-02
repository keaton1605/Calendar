
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include "DayOfWeek.h"

using namespace std;

void DayOfWeek::read(int month1, int day1, int year1)
{
    ifstream inf("DOW.dat", ios::binary);
    int totalBits = (year1 - 1990) * 372 + (month1 - 1) * 31 + day1 - 1;
    inf.seekg(totalBits * sizeof(DayOfWeek));
    inf.read((char*)this, sizeof(DayOfWeek));
    inf.close();
    
}//reads the .dat file

void DayOfWeek::print()
{
    char str[4], newStr[50], Str[4];
    int i = 0, j = day;
    
    strcpy(newStr, dayName);
    strcat(newStr, ", ");
    strcat(newStr, monthName);
    strcat(newStr, " ");    
    
    while(j > 0)
    {
        str[i] = '0' + j % 10;
        j = j / 10;
        ++i;
        
    }//converts int to string
    
    str[i] = '\0';
    
    if (str[1])
        Str[0] = str[1];
    
    if (str[0])
        Str[1] = str[0];
    
    if (strlen(str) == 1)
        strcpy(Str, str);
    
    Str[i] = '\0';
    
    strcat(newStr, Str);
    
    cout << setw(30) << left << newStr;
    
}//prints day of week