#include <iostream>
#include <fstream>
#include <regex>
#include <Stmt.h>
using namespace std;

int main(int argc, char **argv) {
    string fn = argv[1];

    fstream f;
    string line;
    f.open(fn);

    if(f.is_open()){
        while(getline(f, line)){
            cout << line << "\n";
            if(line.compare("start") != 0){
                cout << "String detected!" << std::endl;
                //insert into instruction buffer
            }

        }
        f.close();
    }
    else cout << "Error opening input file";
    return 0;
}
