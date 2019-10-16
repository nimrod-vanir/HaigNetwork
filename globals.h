#ifndef GLOBALS_H
#define GLOBALS_H

class SecCookie
{
public:
    int id;
    void assign(int num) {
        id = num;
    }
};

extern SecCookie SecCookie_Instance;

class Globals
{
public:
    Globals();
    ~Globals();
};

#endif // GLOBALS_H
