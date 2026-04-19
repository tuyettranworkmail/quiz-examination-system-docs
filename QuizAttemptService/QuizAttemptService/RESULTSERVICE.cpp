#include "RESULTSERVICE.h"

// Constructor
ResultService::ResultService()
{
}

// Lưu kết quả
void ResultService::saveResult(const Result& result)
{
    resultList.push_back(result);
}

// Tìm kết quả theo attemptId
Result ResultService::getResultByAttemptId(int attemptId)
{
    for (int i = 0; i < resultList.size(); i++)
    {
        if (resultList[i].getAttemptId() == attemptId)
        {
            return resultList[i];
        }
    }

    // không tìm thấy → trả về object rỗng
    return Result();
}
