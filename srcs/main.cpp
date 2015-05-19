/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 16:18:51 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/08 19:55:35 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"
#include "IOperand.hpp"
#include "Factory.hpp"
#include "Emulator.hpp"

void  emulate(t_instruct instruct) {

   Emulator fac;
   for(auto& ins : instruct)
      fac.Execute(ins);
}

int   main(int ac, char **av) {

   if (ac < 2)
   {
      try {
         t_instruct instruct = Parse::getInstructions();
         std::cout << std::endl;
         emulate(instruct);
      } catch (std::runtime_error &e) {
         std::cout << e.what() << std::endl;
      }
   }
   for (int i=1; i<ac; i++)
   {
      try {
         t_instruct instruct = Parse::getInstructions(std::string(av[i]));
         emulate(instruct);
      } catch (std::runtime_error &e) {
         std::cout << av[i] << " : " << e.what() << std::endl;
      }
   }
   return 0;
}
