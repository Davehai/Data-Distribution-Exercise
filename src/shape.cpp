/****************************************
 * Author: David Hairapetian	        *
 * code review:                    		*
 * Date: 07/12/23        	            *
 * Version: 0.0                         *
 * Status:                              *
****************************************/
#include <sstream>      //std::stringstream
#include <iostream>     //std::cout

#include "shape.hpp"

namespace ilrd
{

/*******************************************************************************
 * Shape definition
*******************************************************************************/
Shape::~Shape()
{
    //empty
}

Square::Square(std::string color_, int size_, int alt_): m_color(color_), m_size(size_), m_alt(alt_)
{
    //empty
}

Square::Square(const Square &square_): m_color(square_.m_color), m_size(square_.m_size), m_alt(square_.m_alt)
{
    //Empty
}

Square::~Square()
{
    //empty
}

std::string Square::GetType() const
{
    return "square";
}

std::string Square::ToString() const
{
    std::string type = GetType();
    std::string color = GetColor();
    std::string size = std::to_string(GetSize());
    std::string alt = std::to_string(GetAlt());
    
    return "1=" + type + "/" + "2=" + color + "/" + "3=" + size + "/" + "4=" + alt;
}

void Square::Print() const
{
    std::cout << *this << std::endl;
}

std::string Square::GetColor() const
{
    return m_color;
}

int Square::GetSize() const
{
    return m_size;
}

int Square::GetAlt() const
{
    return m_alt;
}

void Square::SetColor(std::string color_)
{
    m_color = color_;
}

void Square::SetSize(int size_)
{
    m_size = size_;
}

void Square::SetAlt(int alt_)
{
    m_alt = alt_;
}

Circle::Circle(std::string color_, int size_, int alt_): m_color(color_), m_size(size_), m_alt(alt_)
{
    //empty
}

Circle::Circle(const Circle &circle_): m_color(circle_.m_color), m_size(circle_.m_size), m_alt(circle_.m_alt)
{
    //Empty
}

Circle:: ~Circle()
{
    //empty
}

std::string Circle::GetType() const
{
    return "circle";
}

std::string Circle::ToString() const
{
    std::string type = GetType();
    std::string color = GetColor();
    std::string size = std::to_string(GetSize());
    std::string alt = std::to_string(GetAlt());
    
    return "1=" + type + "/" + "2=" + color + "/" + "3=" + size + "/" + "4=" + alt;
}

void Circle::Print() const
{
    std::cout << *this << std::endl;
}

std::string Circle::GetColor() const
{
    return m_color;
}

int Circle::GetSize() const
{
    return m_size;
}

int Circle::GetAlt() const
{
    return m_alt;
}

void Circle::SetColor(std::string color_)
{
    m_color = color_;
}

void Circle::SetSize(int size_)
{
    m_size = size_;
}

void Circle::SetAlt(int alt_)
{
    m_alt = alt_;
}

std::ostream& operator<<(std::ostream& os_, const Square& square_)
{
    os_ << "Type =\t" << square_.GetType() << std::endl;
    os_ << "Color =\t" << square_.GetColor() << std::endl;
    os_ << "Size =\t" << square_.GetSize() << std::endl;
    os_ << "Alt =\t" << square_.GetAlt();

    return os_;
}

std::ostream& operator<<(std::ostream& os_, const Circle& circle_)
{
    os_ << "Type =\t" << circle_.GetType() << std::endl;
    os_ << "Color =\t" << circle_.GetColor() << std::endl;
    os_ << "Size =\t" << circle_.GetSize() << std::endl;
    os_ << "Alt =\t" << circle_.GetAlt();

    return os_;
}

/*******************************************************************************
 * Shape to string definition
*******************************************************************************/
Shape* StringToShape(const std::string &shape_)
{
    std::size_t index = shape_.find("square");
    if(std::string::npos != index)
    {
        Square tmp = StringToSquare(shape_);
        return new Square(tmp);
    }

    index = shape_.find("circle");
    if(std::string::npos != index)
    {
        Circle tmp = StringToCircle(shape_);
        return new Circle(tmp);
    }

    return nullptr;
}

Square StringToSquare(const std::string &square_)
{
    std::string type;
    std::string color;
    int size = 0;
    int alt = 0;
    std::stringstream inpute(square_);
    std::string segment;

    while(std::getline(inpute, segment, '/'))
    {
        switch (segment[0])
        {
        case '1':
            type = segment.substr(segment.find('='));
            break;
        case '2':
            color = segment.substr(segment.find('=') + 1);
            break;
        case '3':
            size = stoi(segment.substr(segment.find('=') + 1));
            break;
        case '4':
            alt = stoi(segment.substr(segment.find('=') + 1));
            break; 
        default:
            break;
        }
    }

    Square tmp(color, size, alt);

    return tmp;
}

Circle StringToCircle(const std::string &circle_)
{
    std::string type;
    std::string color;
    int size = 0;
    int alt = 0;
    std::stringstream inpute(circle_);
    std::string segment;

    while(std::getline(inpute, segment, '/'))
    {
        switch (segment[0])
        {
        case '1':
            type = segment.substr(segment.find('='));
            break;
        case '2':
            color = segment.substr(segment.find('=') + 1);
            break;
        case '3':
            size = stoi(segment.substr(segment.find('=') + 1));
            break;
        case '4':
            alt = stoi(segment.substr(segment.find('=') + 1));
            break; 
        default:
            break;
        }
    }

    Circle tmp(color, size, alt);

    return tmp;
}

}