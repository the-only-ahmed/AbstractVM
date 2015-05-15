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
#include "Factory.hpp"

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
	bool operator==( IOperand const & rhs ) const;
	std::string const & toString( void ) const;
};

/* ------------------------------------------------------------------------ */
template<typename T>
int TOperand<T>::getPrecision( void ) const {return 0;}

template<typename T>
eOperandType TOperand<T>::getType( void ) const {return this->_type;}

template<typename T>
IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();
	double x = ::atof(this->_ahmed.c_str()) + ::atof(rhs.toString().c_str());
	std::string res = std::to_string(x);
	return Factory().createOperand(type, res);
}

template<typename T>
IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();
	double x = ::atof(this->_ahmed.c_str()) - ::atof(rhs.toString().c_str());
	std::string res = std::to_string(x);
	return Factory().createOperand(type, res);
}

template<typename T>
IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();
	double x = ::atof(this->_ahmed.c_str()) * ::atof(rhs.toString().c_str());
	std::string res = std::to_string(x);
	return Factory().createOperand(type, res);
}

template<typename T>
IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();
	double x = ::atof(this->_ahmed.c_str()) / ::atof(rhs.toString().c_str());
	std::string res = std::to_string(x);
	return Factory().createOperand(type, res);
}

template<typename T>
IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();
	int x = ::atoi(this->_ahmed.c_str()) % ::atoi(rhs.toString().c_str());
	std::string res = std::to_string(x);
	return Factory().createOperand(type, res);
}

template<typename T>
bool TOperand<T>::operator==( IOperand const & rhs ) const {

	if (this->_type != rhs.getType())
	{
		std::cout << "AAA" << std::endl;
		return false;
	}
	if (this->_ahmed != rhs.toString())
	{
		std::cout << "BBB" << std::endl;
		return false;
	}
	return true;
}

template<typename T>
std::string const & TOperand<T>::toString( void ) const {return _ahmed;}

#endif
