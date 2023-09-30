#pragma once
#include "string"
#include "set"
#include "iostream"
#include "fstream"
#include "sstream"
#include "algorithm"
#include "unordered_map"
using std::string,
std::unordered_map,
std::cin,
std::cout,
std::endl,
std::set,
std::fstream, 
std::stringstream;

void Send_M(const string path, string sender, string sendername, string resiver, string resivername);
void Show_M(string resiver,string name);
void ChatWith(const string path, string sender, string sendername, string resiver, string resivername);