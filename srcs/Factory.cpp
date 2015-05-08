/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 18:10:17 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/08 18:19:04 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
	if (type == e_int_8)
		return this->createInt8(value);
	if (type == e_int_16)
		return this->createInt16(value);
	if (type == e_int_32)
		return this->createInt32(value);
	if (type == e_float)
		return this->createFloat(value);
	if (type == e_double)
		return this->createDouble(value);
	return NULL;
}

IOperand const * Factory::createInt8( std::string const & value ) const {
	return new TOperand<int8_t>(static_cast<int8_t>(std::stoi(value)), e_int_8);
}

IOperand const * Factory::createInt16( std::string const & value ) const {
	return new TOperand<int16_t>(static_cast<int16_t>(std::stoi(value)), e_int_16);
}

IOperand const * Factory::createInt32( std::string const & value ) const {
	return new TOperand<int32_t>(static_cast<int32_t>(std::stoi(value)), e_int_32);
}

IOperand const * Factory::createFloat( std::string const & value ) const {
	return new TOperand<float>(static_cast<float>(::atof(value.c_str())), e_float);
}

IOperand const * Factory::createDouble( std::string const & value ) const {
	return new TOperand<double>(static_cast<double>(::atof(value.c_str())), e_double);
}
