#pragma once
#include <iostream>
#include <string>   
#include <sstream>   
#include "./parser.hpp"

class Genrator{
    public:
    inline Genrator(NodeTail root)
        :m_root(std::move(root))
    {
    }
    std::string genrate()const 
    {
    std::stringstream writter;
    writter<<"global _start\n_start:\n";
    writter<<"    mov rax,60\n";
    writter<<"    mov rdi,"<<m_root.expr.int_lit.value.value()<<"\n";
    writter<<"    syscall";
    return writter.str();
    }

    private:
    const NodeTail m_root;

};