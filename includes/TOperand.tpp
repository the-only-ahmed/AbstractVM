/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOperand.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 18:10:17 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/08 18:19:04 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPERAND_TPP
# define TOPERAND_TPP

#include "IOperand.hpp"

template<typename T>
class TOperand : public IOperand
{
private:
	eOperandType	_type;
	T					_value;
	std::string		_ahmed;

public:
	TOperand(T value, eOperandType type) : _type(type), _value(value) {
		_ahmed = std::to_string(this->_value);
	}

	~TOperand() {};

	int getPrecision( void ) const;
	eOperandType getType( void ) const;
	IOperand const * operator+( IOperand const & rhs ) const;
	IOperand const * operator-( IOperand const & rhs ) const;
	IOperand const * operator*( IOperand const & rhs ) const;
	IOperand const * operator/( IOperand const & rhs ) const;
	IOperand const * operator%( IOperand const & rhs ) const;
	std::string const & toString( void ) const;
};

/* ------------------------------------------------------------------------ */
template<typename T>
int TOperand<T>::getPrecision( void ) const {return 0;}

template<typename T>
eOperandType TOperand<T>::getType( void ) const {return e_typeNb;}

template<typename T>
IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const {(void)rhs; return this;}

template<typename T>
IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const {(void)rhs; return this;}

template<typename T>
IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const {(void)rhs; return this;}

template<typename T>
IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const {(void)rhs; return this;}

template<typename T>
IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const {(void)rhs; return this;}

template<typename T>
std::string const & TOperand<T>::toString( void ) const {return _ahmed;}

#endif
