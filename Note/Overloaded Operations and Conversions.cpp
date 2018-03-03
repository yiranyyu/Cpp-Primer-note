namespace note{class OverloadedOperationsAndConversions{

// 1. 2. 3. have same call signature int(int, int), i.e. same function type.
// so we can easily use std::map<std::string, int(*)(int, int)> to organize them.
void f(){
    auto mod = [](int i, int j) { return i % j; };      // 1.
}
    int add(int i, int j) { return i + j; }             // 2.
    struct divide{                                      // 3. 
        int operator()(int denominator, int divisor){
            return denominator / divisor;
        }
    };
};
}