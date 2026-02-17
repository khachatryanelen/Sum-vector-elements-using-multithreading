#include <iostream>
#include <random>
#include <vector>
#include <thread>
#include <future>
#include <chrono>


// commented way is using std::threads,uncommneted is with the help of std::async :)

constexpr size_t size=1000000000;

// void sumNumbers(std::vector<int>& vec,size_t a,size_t b,long long& s1){
//     for(size_t i=a;i<b;i++){
//         s1+=vec[i];
//     }
// }

void sumNumbers(std::vector<int>& vec,size_t begin,size_t end,long long& s1){
    s1=std::accumulate(vec.begin()+begin,vec.begin()+end,0LL);
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

    // std::thread t1;
    // std::thread t2;
    // std::thread t3;
    // std::thread t4;
    // std::thread t5;

    // t1 = std::thread(init, std::ref(vector), 0,part);
    // t2 = std::thread(init, std::ref(vector), part, 2*part);
    // t3 = std::thread(init, std::ref(vector), 2*part, 3*part);
    // t4 = std::thread(init, std::ref(vector), 3*part, 4*part);
    // t5 = std::thread(init, std::ref(vector), 4*part, vector.size());

    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();
    // t5.join();

    auto start = std::chrono::high_resolution_clock::now();

    auto g1 = std::async(std::launch::async, init, std::ref(vector), 0,part);
    auto g2 = std::async(std::launch::async, init, std::ref(vector), part, 2*part);
    auto g3 = std::async(std::launch::async, init, std::ref(vector), 2*part, 3*part);
    auto g4 = std::async(std::launch::async, init, std::ref(vector), 3*part, 4*part);
    auto g5 = std::async(std::launch::async, init, std::ref(vector), 4*part, vector.size());

    g1.get();
    g2.get();
    g3.get();
    g4.get();
    g5.get();

    // t1 = std::thread(sumNumbers, std::ref(vector), 0,part, std::ref(s1));
    // t2 = std::thread(sumNumbers, std::ref(vector), part, 2*part, std::ref(s2));
    // t3 = std::thread(sumNumbers, std::ref(vector), 2*part, 3*part, std::ref(s3));
    // t4 = std::thread(sumNumbers, std::ref(vector), 3*part, 4*part, std::ref(s4));
    // t5 = std::thread(sumNumbers, std::ref(vector), 4*part, vector.size(), std::ref(s5));

    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();
    // t5.join();

    auto afterInit = std::chrono::high_resolution_clock::now();

    auto f1 = std::async(std::launch::async, sumNumbers, std::ref(vector), 0,part, std::ref(s1));
    auto f2 = std::async(std::launch::async, sumNumbers, std::ref(vector), part, 2*part, std::ref(s2));
    auto f3 = std::async(std::launch::async, sumNumbers, std::ref(vector), 2*part, 3*part, std::ref(s3));
    auto f4 = std::async(std::launch::async, sumNumbers, std::ref(vector), 3*part, 4*part, std::ref(s4));
    auto f5 = std::async(std::launch::async, sumNumbers, std::ref(vector), 4*part, vector.size(), std::ref(s5));

    f1.get();
    f2.get();
    f3.get();
    f4.get();
    f5.get();

    auto end = std::chrono::high_resolution_clock::now();

    std::cout<<"Sum is: "<<s1+s2+s3+s4+s5<<std::endl;

    std::chrono::duration<double> duration1 = afterInit - start;
    std::cout << "Init time: " << duration1.count() << " seconds\n";

    std::chrono::duration<double> duration2 = end - start;
    std::cout << "Whole time: " << duration2.count() << " seconds\n";

    return 0;
}