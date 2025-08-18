#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "./parser.hpp"
#include <unordered_map>
class Genrator
{
public:
    inline Genrator(NodeProgram pgrm)
        : m_pgrm(std::move(pgrm))
    {
    }
    void gen_expr(const NodeExpression& expr)
    {
        struct ExprVisitor
        {
            Genrator* gen;
            void operator()(const NodeExpressionLit &expr_int_lit)
            {
                gen->m_writer << "    mov rax," << expr_int_lit.int_lit.value.value() << "\n";
                gen->push(" rax");
                // gen->m_writer <<"    push rax\n";
            }
            void operator()(const NodeExpressionIdent &expr_garb)
            {
                if(!gen->m_vars.contains(expr_garb.ident.value.value())){
                    std::cout<<"Undeclared Identifers";
                    exit(EXIT_FAILURE);
                }
                const auto& var=gen->m_vars.at(expr_garb.ident.value.value());
                std::stringstream offset;
                offset<<"QWORD [rsp +"<<(gen->m_stack_locater-var.stack_log-1)*8<<"]\n";
                gen->push(offset.str());
            }
        };
         ExprVisitor visitor{.gen=this};
         std::visit(visitor, expr.var);;
    }


    void gen_stmt(const NodeStatement& stmt)
    {
        struct StmtVisitor
        {   Genrator* gen;
            void operator()(const NodeStatementTail& stmt_tail)const
            {
                gen->gen_expr(stmt_tail.expr);
                gen->m_writer << "    mov rax,60\n";
                gen->pop(" rdi");
                gen->m_writer << "    syscall\n";
            }
            void operator()(const NodeStatementGrab &stmt_grab)
            {
                if(gen->m_vars.contains(stmt_grab.ident.value.value())){
                std::cout<<"Identifier"<<stmt_grab.ident.value.value()<<" Already Used ";
                exit(EXIT_FAILURE);
                }
                gen->gen_expr(stmt_grab.expr);
                gen->m_vars.insert({stmt_grab.ident.value.value(),Var{.stack_log=gen->m_stack_locater}});
                gen->gen_expr(stmt_grab.expr);
                gen->m_stack_locater++;
        }
        };
        StmtVisitor visitor{.gen=this};
        std::visit(visitor, stmt.stmt);
    }


    std::string gen_prgram()
    {
        m_writer << "global _start\n_start:\n";

        for (const NodeStatement& stmt : m_pgrm.stmt)
        {
            gen_stmt(stmt);
        }

        
        if (m_pgrm.stmt.empty()) {
        
        m_writer << "    mov rax,60\n";
        m_writer << "    xor rdi,rdi\n";  
        m_writer << "    syscall\n";
        return m_writer.str();
        
    }

        m_writer << "    mov rax,60\n";
        m_writer << "    pop rdi\n";
        m_writer << "    syscall\n";
        return m_writer.str();
    }

private:

    void push(const std::string& reg){
        m_writer<<"    push"<<reg<<"\n";
        m_stack_locater++;
    }

    void pop(const std::string& reg){
        m_writer<<"    pop"<<reg<<"\n";
        m_stack_locater--;
    }

    struct Var{
        size_t stack_log;
    };

    size_t m_stack_locater=0;
    NodeProgram m_pgrm;
    std::stringstream m_writer;
    std::unordered_map<std::string,Var>m_vars {};
};
