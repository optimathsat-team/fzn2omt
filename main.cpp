#include<iostream>
#include "parser/flatzincparser.h"
#include "terms/termmanager.h"
#include "toplevel/cmdline.h"
#include "configuration.h"
#include "toplevel/flatzincinterface.h"
#include <fstream>
#include <unistd.h>


using namespace std;


int main(int argc, char* argv[]){
	int c;
  bool bv = false;
	std::ofstream output;
	std::ifstream input;
	while ((c = getopt (argc, argv, "hi:o:b")) != -1)
    switch (c)
      {
      case 'o':{
      	output.open(optarg);
        std::cout.rdbuf(output.rdbuf());
        break;
      }
      case 'i':{
      	input.open(optarg);
        std::cin.rdbuf(input.rdbuf());
        break;
      }
      case 'b':{
        bv = true;
        break;
      }
      case 'h':{
        std::cout<<"Usage: ./fzn2omt < INPUTFILE.fzn > OUTPUTFILE.smt2 [-b]"<<std::endl<<std::endl;
        std::cout<<"Alternatively you can pass files as command option arguments:"<<std::endl;
        std::cout<<"-i INPUTFILE.fzn"<<std::endl;
        std::cout<<"-o OUTPUTFILE.smt2"<<std::endl<<std::endl;
        std::cout<<"-b can be used to represent Integers using BitVectors.";
        return 1;
      }
      case '?':
        return 1;
      default:
        abort ();
      }
	msat::CmdLine cmd(bv);
	msat::Configuration conf(bv);
	msat::opt::FlatZincInterface *toplevel = new msat::opt::FlatZincInterface(&conf, &cmd, bv);
	toplevel->main_loop(std::cin);

	return 0;
}