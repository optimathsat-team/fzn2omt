#include<iostream>
#include "parser/flatzincparser.h"
#include "terms/termmanager.h"
#include "toplevel/cmdline.h"
#include "configuration.h"
#include "toplevel/flatzincinterface.h"
#include <fstream>
#include <unistd.h>


using namespace std;

enum omt_languages{
  OPTIMATHSAT = 0,
  Z3 = 1,
  CVC4 = 2,
  BCLT = 3
};

void incipit(int l, bool bv){
  // Setting background theory
  switch(l){
    case OPTIMATHSAT:
    break;
    
    case Z3:
      if(!bv)
        std::cout<<"(set-logic QF_NIRA)"<<std::endl;
      else
        std::cout<<"(set-logic ALL)"<<std::endl;
    break;
    case CVC4:
      std::cout<<"(set-logic ALL)"<<std::endl;
    break;
  }

  // Setting directives
  std::cout<<"(set-option :produce-models true)"<<std::endl;
  
}

int main(int argc, char* argv[]){
	int c;
  bool bv = false;
	std::ofstream output;
	std::ifstream input;
  int language = 0;
	while ((c = getopt (argc, argv, "ho:bl:")) != -1)
    switch (c)
      {
      case 'o':{
      	output.open(optarg);
        std::cout.rdbuf(output.rdbuf());
        break;
      }
      case 'b':{
        bv = true;
        break;
      }
      case 'h':{
        std::cout<<"Usage: ./fzn2omt < INPUTFILE.fzn > OUTPUTFILE.smt2 [-b] [-l LANGUAGE]"<<std::endl<<std::endl;
        std::cout<<"Alternatively you can pass files as command option arguments:"<<std::endl;
        std::cout<<"-o OUTPUTFILE.smt2"<<std::endl;
        std::cout<<"-b can be used to represent Integers using BitVectors."<<std::endl;
        std::cout<<"-l set the output language in [OptiMathSAT, Z3] (default OptiMathSAT)"<<std::endl;
        return 1;
      }
      case 'l':{
        if(strcmp(optarg,"Z3") == 0){
          language = Z3;
        }
        if(strcmp(optarg,"CVC4") == 0){
          language = CVC4;
        }
        if(strcmp(optarg,"BCLT") == 0){
          language = BCLT;
        }
        break;
      }
      case '?':
        return 1;
      default:
        abort ();
      }
  incipit(language, bv);
	msat::CmdLine cmd(bv);
	msat::Configuration conf(bv, language);
	msat::opt::FlatZincInterface *toplevel = new msat::opt::FlatZincInterface(&conf, &cmd, bv);
	toplevel->main_loop(std::cin);

	return 0;
}