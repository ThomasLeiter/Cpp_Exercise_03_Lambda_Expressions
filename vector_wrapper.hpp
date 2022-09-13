#ifndef VECTOR_WRAPPER_HPP
#define VECTOR_WRAPPER_HPP

#include <vector>
#include <functional>
#include <algorithm>

template <typename T>
class VectorWrapper
{
public:
    VectorWrapper(const std::vector<T> &);

    template <typename U>
    VectorWrapper<U> apply(const std::function<U(T)> &) const;

    VectorWrapper<T> filter(const std::function<bool(T)> &) const;

    VectorWrapper<T> &sort(const std::function<bool(T, T)> &);

    std::vector<T> collect() const;

protected:
    std::vector<T> data;
};

template <typename T>
VectorWrapper<T>::VectorWrapper(const std::vector<T> &vec) : data{vec} {}

template <typename T>
VectorWrapper<T> VectorWrapper<T>::filter(const std::function<bool(T)> &p) const
{
    std::vector<T> r;
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(r), p);
    return VectorWrapper<T>{r};
}

template <typename T>
VectorWrapper<T> &VectorWrapper<T>::sort(const std::function<bool(T, T)> &cmp)
{
    std::sort(data.begin(), data.end(), cmp);
    return *this;
}

template <typename T>
std::vector<T> VectorWrapper<T>::collect() const
{
    return data;
}

template <typename T>
template <typename U>
VectorWrapper<U> VectorWrapper<T>::apply(const std::function<U(T)> &f) const
{
    std::vector<U> r;
    std::transform(data.cbegin(), data.cend(), std::back_inserter(r), f);
    return VectorWrapper<U>{r};
}

#endif