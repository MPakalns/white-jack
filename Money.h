#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <iomanip>

class Money {
    private:
        // Store the absolute value as an integer number of cents
        int totalCents;

    public:
        // Constructors to initialize from nothing OR dollars and cents OR an ammount of type double
        Money();
        Money(int _totalCents);
        Money(int dollars, int cents);
        Money(double ammount);

        // Functions to get absolute value's dollar part and cents part
        int getDollars() const;
        int getCents() const;
        int getTotalCents() const;

        // Overload basic arithmetic operators (+, -, *, /)
        Money operator+(const Money& otherValue) const;
        Money operator-(const Money& otherValue) const;
        Money operator*(double multiplierValue) const;
        Money operator/(double divisorValue) const;

        // Overload comparison (== and !=) operators
        bool operator==(const Money& otherValue) const;
        bool operator!=(const Money& otherValue) const;
        bool operator>(const Money& otherValue) const;
        bool operator<(const Money& otherValue) const;
        bool operator>=(const Money& otherValue) const;
        bool operator<=(const Money& otherValue) const;

        // Overload stream insertion operator for easy printing
        friend std::ostream& operator<<(std::ostream& os, const Money& money);
};

#endif // !MONEY_H

