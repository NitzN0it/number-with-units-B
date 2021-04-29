//
// Created by nitzan on 20/04/2021.
//

#include "NumberWithUnits.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
const double EPS = 0.0001;
using namespace ariel;
using namespace std;
map<string,map<string,double>> NumberWithUnits::units_map;
    NumberWithUnits::NumberWithUnits(double num, string unt)
    {
        if(units_map.find(unt) == units_map.end())
        {
            throw invalid_argument(unt + "Isn't in the units list");
        }
        number = num;
        unit = unt;
    }
     void NumberWithUnits::read_units(ifstream& fl)
    {
        if (!fl)//if the program fails to open the file, print error message
        {
            cout<<"error, fails to open the file"<<endl;
            exit(1);
        }
        char eq_sign;
        string unit1, unit2;
        int number1 = 0;
        double number2 = 0;
        while (fl >> number1 >> unit1 >> eq_sign >> number2 >> unit2) {
            units_map[unit1][unit2] = number2;
            units_map[unit2][unit1] = 1 / number2;
            update(unit1,unit2);
            update(unit2,unit1);
//            cout << unit1 << "->" << unit2 << " value: " << units_map[unit1][unit2] << endl;
//            cout << unit2 << "->" << unit1 << " value: " << units_map[unit2][unit1] << endl;
//            double tmp = 0;
//            for (auto &unt : units_map[unit1]) {
//                tmp = units_map[unit2][unit1] * unt.second;
//                units_map[unit2][unt.first] = tmp;
//                units_map[unt.first][unit2] = 1 / tmp;
//            }
//            for (auto &unt : units_map[unit2]) {
//                tmp = units_map[unit1][unit2] * unt.second;
//                units_map[unit1][unt.first] = tmp;
//                units_map[unt.first][unit2] = 1 / tmp;
//            }
            for (auto &pair : units_map[unit1])
            {
                cout << unit1 << "->" << unit2 << " value: " << units_map[unit1][unit2] << endl;
            }

            for (auto &pair : units_map[unit2])
            {
                cout << unit2 << "->" << unit1 << " value: " << units_map[unit2][unit1] << endl;
            }
        }
    }

void NumberWithUnits::update(string src, string dst)
{
    for (auto &conv : units_map[dst])
    {
        if (conv.first != src)
        {
            double num = units_map[src][dst] * conv.second;
            units_map[src][conv.first] = num;
            units_map[conv.first][src] = 1 / num;
        }
    }
}
    double NumberWithUnits::fix_units(const NumberWithUnits &num) const
    {
        if(num.unit == unit)
        {
            const double rst = num.number;
            return rst;
        }
        if (units_map[num.unit].contains(unit))
        {
            const double rst = num.number * units_map[num.unit][unit];
            return rst;
        }
        throw invalid_argument("Cannot convert from " + num.unit + " to " + unit);
    }
    int NumberWithUnits::cmp(const NumberWithUnits &num2) const
    {
        double tmp = number - fix_units(num2);
        if (fabs(tmp) < EPS)
        {
            return 0;
        }
        if (tmp > 0)
        {
            return 1;
        }
            return -1;
    }
    NumberWithUnits NumberWithUnits::operator + (const NumberWithUnits num2)
    {
        return NumberWithUnits(number + fix_units(num2), unit);
    }
    NumberWithUnits NumberWithUnits::operator + (const NumberWithUnits &num2) const
    {
        const NumberWithUnits tmp(number + fix_units(num2),unit);
        return tmp;
    }
    NumberWithUnits NumberWithUnits::operator + (const double num)
    {
        return NumberWithUnits(number+num,unit);
    }
    NumberWithUnits NumberWithUnits::operator + ()
    {
        return NumberWithUnits(+number,unit);
    }
    NumberWithUnits NumberWithUnits::operator - (NumberWithUnits num2)
    {
        return NumberWithUnits(number - fix_units(num2), unit);
    }
    NumberWithUnits NumberWithUnits::operator - ()
    {
        return NumberWithUnits(-number,unit);
    }
    NumberWithUnits &NumberWithUnits::operator += (const NumberWithUnits& num)
    {
        number += fix_units(num);
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator -= (const NumberWithUnits& num)
    {
        number -= fix_units(num);
        return *this;
    }
    const NumberWithUnits ariel::operator*(const NumberWithUnits num1, const double& num2)
    {
        return NumberWithUnits(num1.number * num2, num1.unit);
    }
    const NumberWithUnits ariel::operator*(const double& num1, const NumberWithUnits num2)
    {
        return NumberWithUnits(num2.number * num1, num2.unit);
    }
    bool NumberWithUnits::operator > (const NumberWithUnits& num2) const
    {
        return cmp(num2) > 0;
    }
    bool NumberWithUnits::operator >= (const NumberWithUnits& num2) const
    {
        return cmp(num2) >= 0;
    }
    bool NumberWithUnits::operator < (const NumberWithUnits& num2) const
    {
        return cmp(num2) < 0;
    }
    bool NumberWithUnits::operator <= (const NumberWithUnits& num2) const
    {
        return cmp(num2) <= 0;
    }
    bool NumberWithUnits::operator != (const NumberWithUnits& num2) const
    {
        const bool rst = number != fix_units(num2);
        return rst;
    }
    bool NumberWithUnits::operator == (const NumberWithUnits& num2) const
    {
        const bool rst = fabs(number - fix_units(num2)) <= EPS;
            return rst;
    }
    NumberWithUnits NumberWithUnits::operator ++(int d)
    {
        NumberWithUnits tmp(number,unit);
        number++;
        return tmp;
    }
    NumberWithUnits &NumberWithUnits::operator ++()
    {
        number++;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator --(int d)
    {
        NumberWithUnits tmp(number,unit);
        number--;
        return tmp;
    }
    NumberWithUnits &NumberWithUnits::operator --()
    {
        number--;
        return *this;
    }
    ostream& ariel::operator << (ostream& os, const NumberWithUnits num)
    {
        os << num.number << "[" << num.unit << ']';
        return os;
    }
static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
    char actualChar=0;
    input >> actualChar;
    if (!input) {return input;}
    if (actualChar!=expectedChar){
        input.setstate(ios::failbit);
    }
    return input;
}
istream& ariel::operator >> (istream& is, NumberWithUnits &num)
    {
        char eq_sign;
        string unit;
        double size = 0;
        is >> size >> eq_sign >> unit >> eq_sign;
        if (unit[unit.length() - 1] == ']')
        {
            unit.pop_back();
        }
        if (eq_sign == '-')
        {
            is.putback('-');
        }
        if (NumberWithUnits::units_map.find(unit) == NumberWithUnits::units_map.end())
        {
            throw invalid_argument(unit + " is not a valid unit!");
        }
        num.number = size;
        num.unit = unit;
        return is;
    }