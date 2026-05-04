#pragma once
#ifndef IGRADINGSERVICE_H
#define IGRADINGSERVICE_H

#include "ATTEMPT.h"

class IGradingService
{
public:
    virtual ~IGradingService() {}

    // Hàm chấm điểm 
    virtual int gradeAttempt(const Attempt& attempt) = 0;
};

#endif
