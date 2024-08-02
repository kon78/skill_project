#pragma once
#include<iostream>
#include<memory>
#include<vector>
#include<exception>
#include<stdexcept>
#include<fstream>
#include<string>
#include<filesystem>

#define do_this 1
#define do_not 0
#define execute 1

using namespace std;
namespace fs = filesystem;

string ArgumSet(int argc, char *argv[]);
