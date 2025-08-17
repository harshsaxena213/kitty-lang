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
	std::optional<NodeTail> tree=parser.parse();

	if(!tree.has_value()){
		std::cerr<<"No Exit Statemtn FOund";
		exit(EXIT_FAILURE);

	}
	Genrator genrator(tree.value());

	{
        std::fstream file("./asm/out.asm",std::ios::out);
        file<<genrator.genrate();
    }
    system("nasm -felf64 ./asm/out.asm");
    system("ld -o ./asm/out ./asm/out.o");
	
	}
