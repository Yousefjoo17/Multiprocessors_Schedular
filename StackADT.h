#pragma once
template <class T>
class StackADT
{
    virtual void push(T& root)=0;

    virtual bool pop(T& root) = 0;
    virtual bool isEmpty() const = 0;

    virtual bool peek(T& root) const = 0;
    virtual ~StackADT() { };
};

