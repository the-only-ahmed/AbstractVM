/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 16:18:51 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/04 16:26:24 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

int   main(int ac, char **av) {

   if (ac < 2)
   {
      std::cout << "Usage : " << av[0] << " FILE.avm" << std::endl;
      return -1;
   }
   for (int i=1; i<ac; i++)
   {
      try {
         t_stack stack = Parse::getStack(std::string(av[i]));
         std::cout << av[i] << " : OK" << std::endl;
      } catch (std::runtime_error &e) {
         std::cout << av[i] << " : " << e.what() << std::endl;
      }
   }
   return 0;
}
