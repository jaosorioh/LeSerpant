#ifndef PUNTO_H
#define PUNTO_H

class Punto {

public:
    Punto(int, int, char*);
    //~Punto();

    void setC(char* c_);
    char* getC() const;
    void setXY(int, int);
    void setX(int);
    void setY(int);

    int getX() const;
    int getY() const;

private:
    int x;
    int y;
    char* c;
};

#endif
