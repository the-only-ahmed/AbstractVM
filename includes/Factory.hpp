/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 18:10:17 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/08 18:19:04 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_HPP
# define FACTORY_HPP

#include <stdexcept>
#include <climits>
#include <cfloat>
#include <cfenv>
#include <math.h>

class Factory
{
private:
	static IOperand const * createInt8( std::string const & value );
	static IOperand const * createInt16( std::string const & value );
	static IOperand const * createInt32( std::string const & value );
	static IOperand const * createFloat( std::string const & value );
	static IOperand const * createDouble( std::string const & value );

	Factory &		operator=(Factory const & src);
	Factory(Factory const & src);

public:
	Factory();
	~Factory();

	static IOperand const * createOperand( eOperandType type, std::string const & value );

	class OverflowError : public std::runtime_error
	{
		public :
			OverflowError(std::string error) throw();
			~OverflowError() throw();
			virtual const char* what() const throw();

		private :
			OverflowError &		operator=(OverflowError const & src);
			// OverflowError(OverflowError const & src) throw();
	};

	class UnderflowError : public std::runtime_error
	{
		public :
			UnderflowError(std::string error) throw();
			~UnderflowError() throw();
			virtual const char* what() const throw();

		private :
			UnderflowError &		operator=(UnderflowError const & src);
			// UnderflowError(UnderflowError const & src) throw();
	};
};

#endif
