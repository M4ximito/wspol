#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

int int_array[50];

bool is_new_data = false;

condition_variable if_new_data;
condition_variable if_readed_data;
mutex mutex_;

class Generator
{
private:
    int n;    
public:
    Generator(int _n) : n(_n) {
        
    }
    
    void operator()(){
        for (int i = 0; i < n; i++)
        {
            unique_lock<mutex> guard(mutex_);

            int_array[i] = '0' + i;
        
            is_new_data = true;
            
            if_new_data.notify_one();
            
            if (i < n-1)
                if_readed_data.wait(guard);
        }
    };
};

int main(int argc, char *argv[])
{
    Generator generator_(15);
    thread generator_thread(generator_);

    for (int i = 0; i < 15; i++)
    {
        unique_lock<mutex> guard(mutex_);

        if(!is_new_data)
            if_new_data.wait(guard);
        
        cout << int_array[i] << endl;

        is_new_data = false;

        if_readed_data.notify_one();
    }

    generator_thread.join();
}
