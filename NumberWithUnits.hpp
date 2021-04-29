//
// Created by nitzan on 20/04/2021.
//

#ifndef NUMBER_WITH_UNITS_NUMBERWITHUNITS_H
#define NUMBER_WITH_UNITS_NUMBERWITHUNITS_H
#include <string>
#include <iostream>
#include <map>
using namespace std;
namespace ariel {
    class NumberWithUnits {
    private:
        string unit;
        double number;
        static map<string,map<string,double>> units_map;
        double fix_units(const NumberWithUnits &num) const;
        int cmp(const NumberWithUnits &num2) const;
        static void update(string src, string dest);
    public:
        NumberWithUnits(){}
        NumberWithUnits(double num, string unt);
        static void read_units(ifstream& fl);
        NumberWithUnits operator + (NumberWithUnits num2);
        NumberWithUnits operator + (const NumberWithUnits &num2) const;
        NumberWithUnits operator + (const double num);
        NumberWithUnits operator + ();
        NumberWithUnits operator - (NumberWithUnits num2);
        NumberWithUnits operator -();
        NumberWithUnits &operator += (const NumberWithUnits& num);
        NumberWithUnits &operator -= (const NumberWithUnits& num);
        friend const NumberWithUnits operator*(const NumberWithUnits num1, const double& num2);
        friend const NumberWithUnits operator*(const double& num1, const NumberWithUnits num2);
        bool operator > (const NumberWithUnits& num2) const;
        bool operator >= (const NumberWithUnits& num2) const;
        bool operator < (const NumberWithUnits& num2) const;
        bool operator <= (const NumberWithUnits& num2) const;
        bool operator != (const NumberWithUnits& num2) const;
        bool operator == (const NumberWithUnits& num2) const;
        NumberWithUnits operator ++(int d);
        NumberWithUnits &operator ++();
        NumberWithUnits operator --(int d);
        NumberWithUnits &operator --();
        friend ostream& operator << (ostream& os, const NumberWithUnits num);
        friend istream& operator >> (istream& is, NumberWithUnits &num);
    };

};
#endif //NUMBER_WITH_UNITS_NUMBERWITHUNITS_H
