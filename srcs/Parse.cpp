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
   return was.c_str();
}

/* ------------------------------ Parsing ------------------------------ */

Parse::~Parse() {}
Parse::Parse() {}

std::string* Parse::_instructions = Parse::_setInstructions();

t_instruct     Parse::getInstructions(std::string path) {

   t_instruct stack;

   std::ifstream ifin (path.c_str(), std::ifstream::in);
   if (!ifin.good())
   {
      ifin.close();
      throw ParseException("\033[31mYou dont Have rights to read from file " + path +" !! check rights\033[0m");
   }
   if (!ifin.is_open())
   {
      ifin.close();
      throw ParseException("\033[31mYou dont Have rights to read from file " + path +" !! check rights\033[0m");
   }
   std::string line;
   bool first_line = false;

   if (getline(ifin, line).fail())
   {
      ifin.close();
      throw ParseException("\033[31mCannot read from file " + path +" !! check the file\033[0m");
   }

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
         throw ParseException("\033[31mUndefined instruction : " + str[0] +" !!\033[0m");
      if (str[0] == "push" || str[0] == "assert")
      {
         if (str.size() != 2)
            throw ParseException("\033[31mFalse " + str[0] + " instruction usage : " + str[0] + " value \033[0m");

      }
      else
      {
         if (str.size() != 1)
            throw ParseException("\033[31mFalse instruction usage : " + str[0] + " doesn't have arguments !!\033[0m");
         str.push_back("empty");
      }

      stack.push_back(std::make_pair(str[0], str[1]));
   }
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
