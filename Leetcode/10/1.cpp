#include <string>
#include <iostream>
#include <typeinfo>
#include <typeindex>
using namespace std;

// aa  a*
// aa  a.
// unspport 
class Match
{

public:
    Match(string &s) : _s(s) {}
    bool debug()
    {
        std::cout << std::type_index(typeid(this)).name() << std::endl;
        return this->match();
    }
    virtual bool match() = 0;
    void erase()
    {
        this->_s.erase(_s.begin(), _s.begin() + 1);
    }
    string &_s;
};
class CharterMatch : public Match
{
public:
    CharterMatch(string &s, char c) : Match(s), charter(c) {}

public:
    bool match()
    {
        if (this->_s.size() == 0)
        {
            return false;
        }
        if (this->_s.at(0) == charter)
        {
            this->erase();
            return true;
        }
        return false;
    }

private:
    char charter;
};

class AnyMatch : public Match
{

public:
    AnyMatch(string &s, Match *cm) : Match(s), _cm(cm) {}

public:
    bool match()
    {
        bool flag = false;
        while (this->_cm->match())
        {
            flag = true;
        }
        if (flag)
        {
            return true;
        }
        this->erase();
        return true;
    }

private:
    Match *_cm;
};

class AndMatch : public Match
{
public:
    AndMatch(string &s, Match *lcm, Match *rcm) : Match(s), _lcm(lcm), _rcm(rcm) {}
    bool match()
    {
        return _lcm->match() && _rcm->match();
    }

private:
    Match *_lcm;
    Match *_rcm;
};

class PointMatch : public Match
{
public:
    PointMatch(string &s) : Match(s) {}
    bool match()
    {
        this->erase();
        return true;
    }
};

class Regx
{

private:
    string _s;
    Match *_cm = nullptr;

public:
    Regx(string s, string &r) : _s(s)
    {
        for (auto c : _s)
        {
            switch (c)
            {
            case '*':
                _cm = new AnyMatch(r, _cm);
                break;
            case '.':
                if (_cm != nullptr)
                {
                    _cm = new AndMatch(r, _cm, new PointMatch(r));
                }
                else
                {
                    _cm = new PointMatch(r);
                }
                break;
            default:
                if (_cm != nullptr)
                {
                    _cm = new AndMatch(r, _cm, new CharterMatch(r, c));
                }
                else
                {
                    _cm = new CharterMatch(r, c);
                }
                break;
            }
        }
    }

    bool match()
    {
        return this->_cm->debug();
    }
};

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        Regx r(s, p);
        return r.match();
    }
};

int main()
{
    std::string s = "aa";
    std::string p = "a*";

    Solution soulution;
    std::cout << soulution.isMatch(s, p);
}