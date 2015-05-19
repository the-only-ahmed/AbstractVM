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
	std::string		_stringVal;

	TOperand &		operator=(TOperand const & src);
	TOperand(TOperand const & src);

public:
	TOperand(T value, eOperandType type) : _type(type), _value(value) {
		_stringVal = std::to_string(this->_value);
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
int TOperand<T>::getPrecision( void ) const {return static_cast<int>(this->_value);}

template<typename T>
eOperandType TOperand<T>::getType( void ) const {return this->_type;}

template<typename T>
IOperand const * TOperand<T>::operator+( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();
	double x = ::atof(this->_stringVal.c_str()) + ::atof(rhs.toString().c_str());
	std::string res = std::to_string(x);
	return Factory::createOperand(type, res);
}

template<typename T>
IOperand const * TOperand<T>::operator-( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();
	double x = ::atof(this->_stringVal.c_str()) - ::atof(rhs.toString().c_str());
	std::string res = std::to_string(x);
	return Factory::createOperand(type, res);
}

template<typename T>
IOperand const * TOperand<T>::operator*( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();
	double x = ::atof(this->_stringVal.c_str()) * ::atof(rhs.toString().c_str());
	std::string res = std::to_string(x);
	return Factory::createOperand(type, res);
}

template<typename T>
IOperand const * TOperand<T>::operator/( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();
	double b = ::atof(this->_stringVal.c_str());

	if (b == 0)
		throw std::runtime_error(("\033[31mCannot devide by 0\033[0m"));

	double x = ::atof(rhs.toString().c_str()) / b;
	std::string res = std::to_string(x);
	return Factory::createOperand(type, res);
}

template<typename T>
IOperand const * TOperand<T>::operator%( IOperand const & rhs ) const {

	eOperandType type = (this->_type >= rhs.getType())?this->_type : rhs.getType();

	if (type >= e_float)
		throw std::runtime_error(("\033[31mType Error ==> modulo operator cannot be used on float or double variables\033[0m"));

	int x = ::atoi(this->_stringVal.c_str()) % ::atoi(rhs.toString().c_str());
	std::string res = std::to_string(x);
	return Factory::createOperand(type, res);
}

template<typename T>
bool TOperand<T>::operator==( IOperand const & rhs ) const {

	if (this->_type != rhs.getType())
		return false;
	if (this->_stringVal != rhs.toString())
		return false;
	return true;
}

template<typename T>
std::string const & TOperand<T>::toString( void ) const {return _stringVal;}

#endif
