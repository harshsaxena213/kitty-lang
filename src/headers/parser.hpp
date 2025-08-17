#pragma once
#include <vector>
#include "./tokenization.hpp"
#include <string>
#include <iostream>
struct NodeExpression{
    Token int_lit;
};
struct NodeTail{
    NodeExpression expr;
};



class Parser{
    public:
        inline Parser(std::vector<Token> tokens)
            :m_tokens(std::move(tokens))
        
        {

        }

        std::optional<NodeExpression> parse_expr(){
            if(look_ahead().has_value() && look_ahead().value().type==TokenType::tail){
                return NodeExpression{.int_lit=take_it()};
            }
            if(look_ahead().has_value() && look_ahead().value().type==TokenType::int_lit){
                return NodeExpression{.int_lit=take_it()};
            }
            else
            {
                std::cout<<"Invalid Expression From parse_expr";
                exit(EXIT_FAILURE);
            }
            
        }
        std::optional<NodeTail> parse(){
            std::optional<NodeTail> tail_node;
            while (look_ahead().has_value())
            {
                if(look_ahead().value().type==TokenType::tail && look_ahead(1).has_value() && look_ahead(1).value().type==TokenType::open_paranthesis){
                    take_it();
                    take_it();
                    if(auto node_expr=parse_expr()){
                        tail_node=NodeTail{.expr=node_expr.value()};
                    }
                    else{
                        return {};
                    }
                    if(look_ahead().value().type==TokenType::close_paranthesis){
                        take_it();
                    }
                    else{
                        std::cerr<<"Expected A Open Paranthesis";
                        exit(EXIT_FAILURE); 
                    }
                    if(look_ahead().has_value() &&look_ahead().value().type==TokenType::attherate){
                        take_it();

                    }
                    else{
                        std::cout<<"No AtTheRate";
                        exit(EXIT_FAILURE);
                    }
                    
                }
            }
            m_index=0;
            return tail_node;
            
        }


    private:
        std::optional<Token> look_ahead(int ahead=0) const{
            if (temp_index+ahead>=m_tokens.size())
            {
                return {};
            }
            else{
                return m_tokens.at(temp_index+ahead);
            }
            }

        inline Token take_it(){                                 
            return m_tokens.at(temp_index++);
        }
        size_t temp_index=0;
        
    
        const std::vector<Token> m_tokens;
        size_t m_index=0;
};