#ifndef FILTER_H
#define FILTER_H

#include <iostream>

class Filter
{
public:
	Filter(){};
	virtual ~Filter(){
		std::cout << "Filter destractor" << std::endl;
	};
	/* @brief �t�B���^�K�p��̒l��Ԃ�
	@param measurement �ϑ��l
	@return �ϑ��l���t�B���^�ɒʂ�����̒l */
	virtual float update(const float measurement) = 0;
	virtual void clear() = 0;
};

#endif // FILTER_H