#pragma once

#include <vector>
#include <algorithm>

template <class T, int N>
class AvgFilter
{
private:
    T data [N];
    std::vector<T> medVec;
    int readIndex = 0;
    T total = 0;
public:
    AvgFilter();
    void addDatum(T reading);
    T getAvg();
    T getMedian();
    T getTotal();
};

template <class T, int N>
AvgFilter<T,N>::AvgFilter() {
    for (int i = 0; i < N; i++) {
        data[i] = 0;
    }
}

template <class T, int N>
void AvgFilter<T,N>::addDatum(T reading) {
    total -= data[readIndex];
    data[readIndex] = reading;
    total += data[readIndex];
    readIndex++;
    if (readIndex >= N) {
        readIndex = 0;
    }
}

template<class T, int N>
T AvgFilter<T,N>::getAvg() {
    return total/N;
}

template<class T, int N>
T AvgFilter<T,N>::getMedian() {
    medVec.assign(data, data + N);
    std::nth_element(medVec.begin(), medVec.begin() + medVec.size()/2, medVec.end());
    return medVec[medVec.size()/2];
}

template<class T, int N>
T AvgFilter<T, N>::getTotal() {
    return total;
}