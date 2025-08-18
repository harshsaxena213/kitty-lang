#pragma once
#include <vector>
#include "./tokenization.hpp"
#include <string>
#include <iostream>
#include <variant>

struct NodeExpressionLit{
    Token int_lit;
};
struct NodeExpressionIdent{
    Token ident;
};
struct NodeExpression{
    std::variant<NodeExpressionIdent,NodeExpressionLit> var ; 
}; 

struct NodeStatementTail{
    NodeExpression expr;
};

struct NodeStatementGrab{
    Token ident;
    NodeExpression expr;
};
struct NodeStatement{
    std::variant<NodeStatementTail,NodeStatementGrab>stmt;
};

struct NodeProgram{
    std::vector<NodeStatement> stmt;
};


class Parser{
    public:
        inline Parser(std::vector<Token> tokens)
            :m_tokens(std::move(tokens))
        
        {

        }

        
        std::optional<NodeExpression> parse_expr(){
            if(look_ahead().has_value() && look_ahead().value().type==TokenType::int_lit){
                return NodeExpression{.var=NodeExpressionLit{.int_lit=take_it()}};
            }
            else if(look_ahead().has_value() && look_ahead().value().type==TokenType::ident){
                return NodeExpression{.var=NodeExpressionIdent{.ident=take_it()}};
            }
            else
            {
                std::cout<<"Invalid Expression From parse_expr";
                exit(EXIT_FAILURE);
            }
            
        }
        std::optional<NodeStatement> parse_statement(){
                if(look_ahead().has_value() && look_ahead().value().type==TokenType::tail && look_ahead(1).has_value() && look_ahead(1).value().type==TokenType::open_paranthesis){
                    take_it();
                    take_it();
                    NodeStatementTail tail_node;
                    if(auto node_expr=parse_expr()){
                        tail_node=NodeStatementTail{.expr=node_expr.value()};
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
                    return NodeStatement{.stmt=tail_node};
                }
                else if(look_ahead().has_value() && look_ahead().value().type==TokenType::grab && look_ahead(1).has_value() && look_ahead(1).value().type==TokenType::ident && look_ahead(2).has_value() && look_ahead(2).value().type==TokenType::eq){
                    take_it();
                    auto stmt_grab=NodeStatementGrab{.ident=take_it()};
                    take_it();
                    if(auto expr=parse_expr()){
                        stmt_grab.expr = expr.value();
                    }
                    else{
                        std::cout<<"Invalid Expression !";
                    }
                    if(look_ahead().has_value() && look_ahead().value().type==TokenType::attherate){
                        take_it();
                    }
                    else{
                        std::cout<<"Expected At The Rate";
                        exit(EXIT_FAILURE);
                    }
                    return NodeStatement{.stmt=stmt_grab};
                }
                else{
                    return {};
                }
        }

        std::optional<NodeProgram>parse_program(){
            NodeProgram pgram;
            if(auto stmt=parse_statement()){
                pgram.stmt.push_back(stmt.value());
            }else{
                        // std::cout<<"Expected At The Rate";
                        // exit(EXIT_FAILURE);
            }
            return pgram;
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