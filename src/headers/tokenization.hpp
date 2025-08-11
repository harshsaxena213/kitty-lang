#pragma once
#include <vector>
#include <optional>

enum class TokenType{
    tail,  //end    
    attherate, //Marks The End Of A Statement Just Like ; in Cpp
    int_lit //Interger
};

struct Token{
    TokenType type;
    std::optional<std::string> value;
};

class Tokenizer{
    public:
        inline Tokenizer(std::string src)
            :m_src(std::move(src))
            {

            }
        
        inline std::vector<Token> tokenze()    
        {
            std::vector<Token> content_tokens;
            std::string temp_dumper;  //Temp Store Data From Conditions
            while (look_ahead().has_value())
            {
                if (std::isalpha(look_ahead().value()))  //Checking For Alpha Characters In Content
                {
                    temp_dumper.push_back(take_it());

                    while(look_ahead().has_value() && std::isalnum(look_ahead().value()))   //Check For AlphaNum
                    {
                        temp_dumper.push_back(take_it());
                    }
                    if (temp_dumper=="tail")
                    {
                        content_tokens.push_back({.type=TokenType::tail});        //Check For Tail 
                        temp_dumper.clear();
                        continue;
                    }else{
                        std::cout<<"Wrong Please Refer To Docs For Correct Usage";  
                        exit(EXIT_FAILURE);
                    } 
                }
                else if(std::isdigit(look_ahead().value())){  ///Check For DIgit
                    temp_dumper.push_back(take_it());
                    while (look_ahead().has_value() && std::isdigit(look_ahead().value()))
                    {
                        temp_dumper.push_back(take_it());
                    }
                      content_tokens.push_back({.type=TokenType::int_lit,.value=temp_dumper});
                      temp_dumper.clear();
                }
                else if(std::isspace(look_ahead().value())){                //Check For Space
                    take_it();
                    continue;
                }
                else if(look_ahead().value()=='@'){   
                    take_it();                                               //Check For attherate
                    content_tokens.push_back({.type=TokenType::attherate});
                    continue;
                }
                else{
                    std::cout<<"Error Please Refer To Docs";
                    exit(EXIT_FAILURE);
                }

            }
            
            temp_index=0;
            return content_tokens;
        }

    private:

        std::optional<char> look_ahead(int ahead=0) const{
            if (temp_index+ahead>=m_src.length())
            {
                return {};
            }
            else{
                return m_src.at(temp_index+ahead);
            }
            }

        char take_it(){                                 
            return m_src.at(temp_index++);
        }
            const std::string m_src;
            size_t temp_index=0;

        };
