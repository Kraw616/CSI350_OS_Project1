/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 3/25/22
   Description: 
*/
#include <deque>

using namespace std;

class Process
{
    public:
        int id;
        unsigned long long service_time;
        unsigned long long arrival_time;
        int memory_req;
        unsigned long long wait_time = 0;
        unsigned long long turnaround_time = 0;
        unsigned long long cycles_worked = 0;
};

class Processor
{
    public:
        int id;
        int speed;
        int memory_capability;
        int current_memory;
        deque<Process> current_processes;
};
