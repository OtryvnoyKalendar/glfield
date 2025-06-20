#pragma once

template <typename T>
class EagerSingleton {
public:
    static T& GetInstance() {
        return instance;
    }
    T& operator()() {
        return instance;
    }
protected:
    EagerSingleton() = default;
    ~EagerSingleton() = default;
    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;
private:
    static T instance;
};

template <typename T>
T EagerSingleton<T>::instance;


template <typename T>
class LazySingleton {
public:
    static T& GetInstance() {
        static T instance;
        return instance;
    }
    T& operator()() {
        static T instance;
        return instance;
    }
protected:
    LazySingleton() = default;
    ~LazySingleton() = default;
    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;
};

