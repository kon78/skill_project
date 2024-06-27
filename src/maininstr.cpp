#include"header.h"

string ArgumSet(int argc, char *argv[]){
    string ret;
      for(int i = 0; i < argc; i++){
        ret += argv[i];
        if(i != (argc-1))
          ret += " ";
        }
    cout << "argumentv is " << ret << endl;
    return ret;
}