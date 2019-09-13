#pragma once

class IError : public IAddRef
{
public:
    virtual const char *getErrorMessage() = 0;
};