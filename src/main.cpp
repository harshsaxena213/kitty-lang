#include <iostream>
#include <fstream>
#include <sstream>
#include "./headers/tokenization.hpp"
#include "./headers/genration.hpp"


int main(int argc,char* argv[]){
	
	
	if(argc!=2){
	std::cout<<"Wrong Usage Please Use Like Given Below!!\n";
	std::cout<<"meow <filename>.kitty";
	}
	
	
	std::string content;
	{
		std::stringstream content_string;
		std::fstream input(argv[1],std::ios::in);
		content_string<<input.rdbuf();
		content=content_string.str();
	}

	Tokenizer Token_obj(std::move(content));
	std::vector<Token> tokenized_content=Token_obj.tokenze();
	Parser parser(std::move(tokenized_content));
	std::optional<NodeProgram> prog=parser.parse_program();

	if(!prog.has_value()){
		std::cerr<<"No Valid Program FOund";
		exit(EXIT_FAILURE);

	}
	Genrator genrator(prog.value());

	{
        std::fstream file("./asm/out.asm",std::ios::out);
        file<<genrator.gen_prgram();
    }
    system("nasm -felf64 ./asm/out.asm");
    system("ld -o ./asm/out ./asm/out.o");
	
	}
