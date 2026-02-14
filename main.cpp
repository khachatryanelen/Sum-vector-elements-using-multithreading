#include <iostream>
#include <random>
#include <vector>
#include <thread>

constexpr size_t size=1000000000;

void sumNumbers(std::vector<int>& vec,size_t a,size_t b,long long& s1){
    for(size_t i=a;i<b;i++){
        s1+=vec[i];
    }

}

void init(std::vector<int>& vec,size_t a,size_t b){
    for(size_t i=a;i<b;i++){
        vec[i]=rand()%100;
    }

}

int main(int argc,const char* argv[]){
    srand(time(0));
    std::vector<int> vector(size);
    size_t part=vector.size()/5;

    long long s1=0;
    long long s2=0;
    long long s3=0;
    long long s4=0;
    long long s5=0;

    std::thread t1;
    std::thread t2;
    std::thread t3;
    std::thread t4;
    std::thread t5;



    t1 = std::thread(init, std::ref(vector), 0,part);
    t2 = std::thread(init, std::ref(vector), part, 2*part);
    t3 = std::thread(init, std::ref(vector), 2*part, 3*part);
    t4 = std::thread(init, std::ref(vector), 3*part, 4*part);
    t5 = std::thread(init, std::ref(vector), 4*part, vector.size());

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    t1 = std::thread(sumNumbers, std::ref(vector), 0,part, std::ref(s1));
    t2 = std::thread(sumNumbers, std::ref(vector), part, 2*part, std::ref(s2));
    t3 = std::thread(sumNumbers, std::ref(vector), 2*part, 3*part, std::ref(s3));
    t4 = std::thread(sumNumbers, std::ref(vector), 3*part, 4*part, std::ref(s4));
    t5 = std::thread(sumNumbers, std::ref(vector), 4*part, vector.size(), std::ref(s5));

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    std::cout<<"Sum is: "<<s1+s2+s3+s4+s5<<std::endl;


    return 0;
}