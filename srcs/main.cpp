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

/*void  emulate(t_instruct instruct) {

   VmStack<IOperand*> vm;

   for(auto& ins : instruct)
   {
      if (ins.first == "push")
         vm.push_back();
   }
}*/

int   main(int ac, char **av) {

   if (ac < 2)
   {
      std::cout << "Usage : " << av[0] << " FILE.avm" << std::endl;
      return -1;
   }
   for (int i=1; i<ac; i++)
   {
      try {
         t_instruct instruct = Parse::getInstructions(std::string(av[i]));
         // emulate(instruct);
      } catch (std::runtime_error &e) {
         std::cout << av[i] << " : " << e.what() << std::endl;
      }
   }
   return 0;
}
