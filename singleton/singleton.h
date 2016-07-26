#ifndef _SINGLETON_H__
#define _SINGLETON_H__

class Singleton {

public:
    static Singleton *getInstance(void);
    void doSomething();
    void destroy(); 
private:
    Singleton();
    ~Singleton();
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton *instance;
};

#endif
