#ifndef __lang_hpp__
#define __lang_hpp__

//c
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//c++
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//misc
#include "strconv.hpp"





class Item
{
    void Init();
public:
    typedef std::pair<std::string,std::string> DDDPair;

    Item();
    ~Item();
    Item(const Item& tc);
    Item& operator=(const Item& tc);

    const DDDPair& GetDDD() const;
    void SetDDD(const DDDPair& dddp);

    
private:
    DDDPair m_ddd;//der Vater : tata (der die das word)
};


class Content
{
public:    
    Content();
    void read(const std::string& file);
    void write(const std::string& file);
    void show_ddd(bool show_de) const;


    std::vector<Item> m_vec;

};



#endif//__lang_hpp__


