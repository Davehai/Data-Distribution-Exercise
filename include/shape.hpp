/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#ifndef SHAPE
#define SHAPE

#include <string>           //std::string

namespace ilrd
{

/*******************************************************************************
 * Shape
*******************************************************************************/
class Shape
{
public:
    //Shape() = default;
    virtual  ~Shape();
    virtual std::string GetType() const = 0;
    virtual std::string ToString() const = 0;
    virtual void Print() const = 0;
};

class Square: public Shape
{
public:
    Square(std::string color_, int size_, int alt_);
    Square(const Square &square_);
    ~Square();
    std::string GetType() const;
    std::string ToString() const;
    void Print() const;
    std::string GetColor() const;
    int GetSize() const;
    int GetAlt() const;
    void SetColor(std::string color_);
    void SetSize(int size_);
    void SetAlt(int alt_);
private:
    std::string m_color;
    int m_size;
    int m_alt;
};

class Circle: public Shape
{
public:
    Circle(std::string color_, int size_, int alt_);
    Circle(const Circle &circle_);
    ~Circle();
    std::string GetType() const;
    std::string ToString() const;
    void Print() const;
    std::string GetColor() const;
    int GetSize() const;
    int GetAlt() const;
    void SetColor(std::string color_);
    void SetSize(int size_);
    void SetAlt(int alt_);
private:
    std::string m_color;
    int m_size;
    int m_alt;
};

std::ostream& operator<<(std::ostream& os_, const Square& square_);
std::ostream& operator<<(std::ostream& os_, const Circle& circle_);

/*******************************************************************************
 * Shape to string
*******************************************************************************/
Shape* StringToShape(const std::string &shape_);

Square StringToSquare(const std::string &square_);

Circle StringToCircle(const std::string &circle_);

}

#endif      //SHAPE