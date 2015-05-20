/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 16:19:06 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/07 18:03:24 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

/* ------------------------------ Exception ------------------------------ */

Parse::ParseException::ParseException(std::string error) throw()
   : std::runtime_error(error) {}

Parse::ParseException::~ParseException() throw() {}

const char*		Parse::ParseException::what() const throw() {

   std::string was = "Parse Error : " + std::string(std::runtime_error::what());
   // std::cout << was.c_str() << std::endl;
   return was.c_str();
}

/* ------------------------------ Parsing ------------------------------ */

Parse::~Parse() {}
Parse::Parse() {}

bool                       Parse::_info = false;
int                        Parse::_count = 0;
std::vector<std::string>   Parse::_errors;
std::string*               Parse::_instructions = Parse::_setInstructions();

void           Parse::_PushMessage(std::string msg) {

   if (Parse::_count > 1)
      msg = "Parse Error : " + msg;
   Parse::_errors.push_back(msg);
}

t_instruct     Parse::getInstructions(std::string path, bool info) {

   Parse::_info = info;
   std::ifstream ifin (path.c_str(), std::ifstream::in);
   if (!ifin.good())
   {
      Parse::_count++;
      ifin.close();
      if (!Parse::_info)
         throw ParseException("\033[31mYou dont Have rights to read from file " + path +" !! check rights\033[0m");
      else
         Parse::_PushMessage("\033[31mYou dont Have rights to read from file " + path +" !! check rights\033[0m");
   }
   if (!ifin.is_open())
   {
      Parse::_count++;
      ifin.close();
      if (!Parse::_info)
         throw ParseException("\033[31mYou dont Have rights to read from file " + path +" !! check rights\033[0m");
      else
         Parse::_PushMessage("\033[31mYou dont Have rights to read from file " + path +" !! check rights\033[0m");
   }
   std::string line;
   if (getline(ifin, line).fail())
   {
      Parse::_count++;
      ifin.close();
      if (!Parse::_info)
         throw ParseException("\033[31mCannot read from file " + path +" !! check the file\033[0m");
      else
         Parse::_PushMessage("\033[31mCannot read from file " + path +" !! check the file\033[0m");
   }
   return Parse::Parsing(ifin, line);
}

t_instruct  Parse::Parsing(std::istream &ifin, std::string &line) {

   t_instruct stack;
   bool first_line = false;
   int ext = 0;
   while (true)
   {
      if (first_line)
      {
         if (!getline(ifin, line))
            break;
      }
      if (!first_line) first_line = true;
      std::replace(line.begin(), line.end(), '\t', ' ');
      if (line.find(";") == 0 || line.empty())
         continue;
      size_t pos = line.find(';');
      if (pos != std::string::npos)
         line = line.substr(0, pos);
      std::vector<std::string> str;
      std::string part;
      std::istringstream buf(line);
      while (std::getline(buf, part, ' '))
         str.push_back(part);
      std::vector<std::string>::iterator it = str.begin();
      while(it != str.end())
      {
         if(it->empty())
              it = str.erase(it);
         else
              ++it;
      }
      if (str.empty())
         continue;
      if (!Parse::_check_instruction(str[0]))
      {
         Parse::_count++;
         if (!Parse::_info)
            throw ParseException("\033[31mUndefined instruction : " + str[0] +" !!\033[0m");
         else
            Parse::_PushMessage("\033[31mUndefined instruction : " + str[0] +" !!\n\033[0m");
      }
      if (str[0] == "exit")
      {
         ext++;
         if (ext > 1)
         {
            Parse::_count++;
            if (!Parse::_info)
               throw ParseException("\033[31mCall of exit instruction more than once !\033[0m");
            else
               Parse::_PushMessage("\033[31mCall of exit instruction more than once !\n\033[0m");
         }
         str.push_back("empty");
      }
      else if (str[0] == "push" || str[0] == "assert")
      {
         if (str.size() != 2)
         {
            Parse::_count++;
            if (!Parse::_info)
               throw ParseException("\033[31mFalse " + str[0] + " instruction usage : " + str[0] + " value \033[0m");
            else
               Parse::_PushMessage("\033[31mFalse " + str[0] + " instruction usage : " + str[0] + " value \n\033[0m");
         }
      }
      else
      {
         if (str.size() != 1)
         {
            Parse::_count++;
            if (!Parse::_info)
               throw ParseException("\033[31mFalse instruction usage : " + str[0] + " doesn't have arguments !!\033[0m");
            else
               Parse::_PushMessage("\033[31mFalse instruction usage : " + str[0] + " doesn't have arguments !!\n\033[0m");
         }
         str.push_back("empty");
      }
      stack.push_back(std::make_pair(str[0], str[1]));
   }
   if (ext == 0)
   {
      Parse::_count++;
      if (!Parse::_info)
         throw ParseException("\033[31mMissing exit instruction !\033[0m");
      else
         Parse::_PushMessage("\033[31mMissing exit instruction !\033[0m");
   }
   if (Parse::_info && !Parse::_errors.empty())
      throw ParseException(Parse::_SetException());
   return stack;
}

std::string  *Parse::_setInstructions() {

   std::string *inst = new std::string[11];
   inst[0] = "push";
   inst[1] = "pop";
   inst[2] = "dump";
   inst[3] = "assert";
   inst[4] = "add";
   inst[5] = "sub";
   inst[6] = "mul";
   inst[7] = "div";
   inst[8] = "mod";
   inst[9] = "print";
   inst[10] = "exit";
   return inst;
}

bool  Parse::_check_instruction(std::string ins) {

   if (std::find(Parse::_instructions, Parse::_instructions+11, ins) != Parse::_instructions+11)
      return true;
   return false;
}

t_instruct     Parse::getInstructions(bool info) {

   Parse::_info = info;
   std::string line;
   std::cout << "\033[33mType control + D to end your file\033[0m" << std::endl;
   return Parse::Parsing(std::cin, line);
}

std::string    Parse::_SetException() {

   std::string exc;
   for (auto& str : Parse::_errors)
      exc += str;
   return exc;
}
