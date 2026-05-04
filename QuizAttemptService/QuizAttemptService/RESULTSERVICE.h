#pragma once
#ifndef RESULTSERVICE_H
#define RESULTSERVICE_H

#include "result.h"
#include <vector>

class ResultService
{
private:
    std::vector<Result> resultList; // lưu danh sách kết quả

public:
    // Constructor
    ResultService();

    // Lưu kết quả
    void saveResult(const Result& result);

    // Lấy kết quả theo attemptId
    Result getResultByAttemptId(int attemptId);
};

#endif
