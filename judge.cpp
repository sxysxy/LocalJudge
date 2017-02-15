#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
#define TMP_BUF_SIZE 512
struct{
  string source, input, output, answer, spj;
  string compiler;
  int time, points;
  double timerfrq;
}config;
void set_config(){
  ifstream cof("config.txt");
  if(!cof){
    cout << "Configuration not found, abort!";
    exit(0);
  }
  string s;
  string prefix(".\\test_data\\");
  while(getline(cof, s)){
    int p;
    if((p = s.find("source")) != string::npos){
      config.source = s.substr(p+7, s.length()-(p+6+2));
      cout << "Source File: " << config.source << endl;
    }else if((p = s.find("input")) != string::npos){
      config.input = s.substr(p+6, s.length()-(p+5+2));
      cout << "Input Filename: " << config.input << endl;
      config.input = prefix + config.input;
    }else if((p = s.find("output")) != string::npos){
      config.output = s.substr(p+7, s.length()-(p+6+2));
      cout << "Output Filename: " << config.output << endl;
      config.output = prefix + config.output;
    }else if((p = s.find("answer")) != string::npos){
      config.answer = s.substr(p+7, s.length()-(p+6+2));
      cout << "Answer Filename: " << config.answer << endl;
      config.answer = prefix + config.answer;
    }else if((p = s.find("time")) != string::npos){
      sscanf(s.substr(p+5, s.length()-(p+4+2)).c_str(), "%d", &config.time);
      cout << "Time Limit: " << config.time << " ms" << endl;
    }else if((p = s.find("spj")) != string::npos){
      config.spj = s.substr(p+4, s.length()-(p+3+2));
      cout << "Judge Command: " << config.spj << endl;
    }else if((p = s.find("compiler")) != string::npos){
      config.compiler = s.substr(p+9, s.length()-(p+9+2));
      cout << "Compile Command: " << config.compiler << endl;
    }else if((p = s.find("points")) != string::npos){
      sscanf(s.substr(p+6, s.length()-(p+5+2)).c_str(), "%d", &config.points);
      cout << "Test points: " << config.points << endl;
    }
  }
  cout << endl;
  cof.close();
}
void compile_source(){
  char buf[TMP_BUF_SIZE];
  cout << "Compiling...";
  sprintf(buf, config.compiler.c_str(), config.source.c_str());
  system(buf);
  ifstream tmp("test.exe");
  if(!tmp){
    cout << "Fail:temp.exe not exist! Abort" << endl;
    exit(0);
  }else{
    cout << "OK!" << endl;
    tmp.close();
  }
}
void init_timer(){
  long long t;
  QueryPerformanceFrequency((LARGE_INTEGER*)&t);
  config.timerfrq = t/1000.0;
}
void judge(){
  char buf[TMP_BUF_SIZE];
  init_timer();
  for(int i = 1; i <= config.points; i++){
    sprintf(buf, config.input.c_str(), i);
    string ifn(buf);
    sprintf(buf, config.output.c_str(), i);
    string ofn(buf);
    sprintf(buf, config.answer.c_str(), i);
    string afn(buf);
    
    sprintf(buf, "test.exe < %s > %s", ifn.c_str(), ofn.c_str());
    
    long long st; QueryPerformanceCounter((LARGE_INTEGER*)&st);
    int r = system(buf);
    long long ed; QueryPerformanceCounter((LARGE_INTEGER*)&ed);
    if(r)
      printf("Runtime Error on test %d\n", i);
    else{
      int usetime = (int)((ed-st)/config.timerfrq);
      if(usetime > config.time)
        printf("Time Limit Exceed on test %d", i);
      else{
        sprintf(buf, config.spj.c_str(), ofn.c_str(), afn.c_str());
        if(!system(buf))
          printf("Accept on test %d", i);
        else
          printf("Wrong Answer on test %d", i);
      }
      printf(" ... Time: %d ms\n", usetime);
    }
  }
}
int main(int argc, char *argv[]){
  set_config();
  if(argc > 1 && strcmp(argv[1], "--only-compare"))
    compile_source();
  else puts("Only Compare:");
  judge();
  return 0;
}
