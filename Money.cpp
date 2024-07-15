#include "Money.h"

Money::Money() : totalCents(0) {}
Money::Money(int _totalCents) : totalCents(_totalCents) {}
Money::Money(int dollars, int cents) : totalCents(dollars * 100 + cents) {}
Money::Money(double ammount)
{
    totalCents = static_cast<int>(std::round(ammount * 100));
}

int Money::getDollars() const { return totalCents / 100; }
int Money::getCents() const { return std::abs(totalCents % 100); }
int Money::getTotalCents() const { return totalCents; }

Money Money::operator+(const Money& otherValue) const 
{ 
    Money result(totalCents + otherValue.totalCents);
    return result;
}
Money Money::operator-(const Money& otherValue) const { return Money(totalCents - otherValue.totalCents); }

Money Money::operator*(double multiplierValue) const
{
    double result = static_cast<double>(totalCents) * multiplierValue / 100.0;
    return Money(result);
}

Money Money::operator/(double divisorValue) const
{
    if (divisorValue == 0.0) 
    {
        std::cerr << "ERROR: Division by zero!" << std::endl;
        return *this; // Return original object on division by zero
    }

    double result = static_cast<double>(totalCents) / (divisorValue * 100.0);
    return Money(result);
}

bool Money::operator==(const Money& otherValue) const { return totalCents == otherValue.totalCents; }
bool Money::operator!=(const Money& otherValue) const { return totalCents != otherValue.totalCents; }
bool Money::operator>(const Money& otherValue) const { return totalCents > otherValue.totalCents; }
bool Money::operator<(const Money& otherValue) const { return totalCents < otherValue.totalCents; }
bool Money::operator>=(const Money& otherValue) const { return totalCents >= otherValue.totalCents; }
bool Money::operator<=(const Money& otherValue) const { return totalCents <= otherValue.totalCents; }

std::ostream& operator<<(std::ostream& os, const Money& money) 
{
    int dollars = money.getDollars();
    int cents = money.getCents();
    os << "$" << dollars << "." << std::setw(2) << std::setfill('0') << cents;
    return os;
}
