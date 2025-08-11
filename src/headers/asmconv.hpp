#include <fstream>
#include <vector>
#include "./tokenization.hpp"
#include <sstream>

std::string content_token_to_asm(const std::vector<Token>& token_vector){
    std::stringstream writter;
    writter<<"global _start\n_start:\n";
    for (int i = 0; i < token_vector.size(); i++)
    {
        const Token& token_part=token_vector.at(i);
        if(token_part.type==TokenType::tail){
            if(i+1<token_vector.size() && token_vector.at(i+1).type==TokenType::int_lit){
                if(i+2<token_vector.size() && token_vector.at(i+2).type==TokenType::attherate){
                    writter<<"    mov rax,60\n";
                    writter<<"    mov rdi,"<<token_vector.at(i+1).value.value()<<"\n";
                    writter<<"    syscall";
                }
            }
        }
    }
    return writter.str();
    
}