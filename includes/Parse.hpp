/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 16:18:51 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/07 18:11:05 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include "IOperand.hpp"

class Parse
{
private:
   static std::string    *_instructions;

   static bool           _check_instruction(std::string str);
   static std::string    *_setInstructions();
   static t_instruct     Parsing(std::istream &ifin, std::string &line);

   Parse & operator=(const Parse & rhs);
   Parse(const Parse & src);

public:
   Parse();
   ~Parse();

   static t_instruct getInstructions(std::string path);
   static t_instruct getInstructions();

   class ParseException : public std::runtime_error
   {
      public :
         ParseException(std::string error) throw();
         ~ParseException() throw();
         virtual const char* what() const throw();

      private :
         ParseException &		operator=(ParseException const & src);
         // ParseException(ParseException const & src) throw();
   };
};

#endif
