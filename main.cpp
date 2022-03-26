/* Author: Jacob Krawitz (jkrawitz@muhlenberg.edu) 
   Date: 3/25/22
   Description: Main file for Project 1. Prompts user for the scenario and algorithm they would like to perform, then
   runs the appropriate combination and outputs the correct output. Assigns processes with randomly assigned service times and memory requirements
   to one of four processors. Simulates scheduling algorithms!
*/

// IMPORT LIBRARIES
#include <stdlib.h>
#include <iostream>
#include <random>
#include <queue>
#include <list>
#include <vector>

#include "processes.h"

using namespace std;

/*
Method: scenario_menu()
Prompts the user for their choice of scenario, and returns their choice. Performed in a loop until a valid answer is given.
@returns an integer of the user's choice of scenario
*/
int scenario_menu()
{
    int scenario;
    bool not_valid = true;

    while(not_valid)
    {
        cout << "What scenario would you like?: ";
        cin >> scenario;

        switch(scenario)
        {
            case 1:
                not_valid = false;
                return scenario;

            case 2:
                not_valid = false;
                return scenario;

            case 3:
                not_valid = false;
                return scenario;

            case 4:
                not_valid = false;
                return scenario;
            
            default:
                not_valid = true;   // If any other case happens, loop and ask again.
                //break;
        }
    }
}

/*
Method: algorithm_menu()
Prompts the user for their choice of algorithm (FIFO, SJR, RR, or ML), and returns their choice. Performed in a loop until a valid answer is given.
@returns an integer of the user's choice of algorithm, converted from their string answer
*/
int algorithm_menu()
{
    bool not_valid = true;
    string algorithm;
    int algorithm_choice;

    while(not_valid)
    {
        cout << "What scheduling algorithm would you like? (FIFO, SJF, RR, or ML): ";
        cin >> algorithm;

        if(algorithm == "FIFO")
        {
            algorithm_choice = 1;
            not_valid = false;
        }
        else if(algorithm == "SJF")
        {
            algorithm_choice = 2;
            not_valid = false;
        }
        else if(algorithm == "RR")
        {
            algorithm_choice = 3;
            not_valid = false;
        }
        else if(algorithm == "ML")
        {
            algorithm_choice = 4;
            not_valid = false;
        }
        else
        {
            not_valid = true;
        }

        return algorithm_choice;
    }
}

/*
Method: seed_and_create_processes()
Depending on the algorithm, creates processes and puts them into the proper data structure for the algorithm.
Also prompts the user for and seeds the random number generator, which uses a 64-bit Mersenne Twister generator along with a uniform integer distribution.
@params an integer that represents the algorithm of choice
@returns a queue (for now) containing all of the process objects of the class Process
*/
queue<Process> seed_and_create_processes(int algorithm)
{
    int seed_value;

    queue<Process> process_queue;

    cout << "Seed value?: ";
    cin >> seed_value;

    long long ten_to_sixth = 10000000;
    long long ten_to_twelth = 10000000000000;
    long long one = 1;
    long long ten_to_tenth = 100000000000;

    Process process;
    mt19937_64 gen64;

    gen64.seed(seed_value); // Seed generator

    if(algorithm == 1) // FIFO
    {
        uniform_int_distribution<> service_time(ten_to_sixth, ten_to_twelth); // 10x10^6 - 10x10^12
        uniform_int_distribution<> arrival_time(one, ten_to_tenth);   // 1 - 10x10^10
        uniform_int_distribution<> memory_requirement(1, 8);    // Initialize randomizers 


        for(int i=0; i<50; i++) // Create 50 processes with corresponding ID numbers, and random service times, arrival times,
        {                           // and memory requirements
            Process current_process;
            current_process.id = i+1;
            current_process.service_time = service_time(gen64);
            current_process.arrival_time = arrival_time(gen64);
            current_process.memory_req = memory_requirement(gen64);
            current_process.wait_time = 0;  // Wait time & turnaround time is calculated later, so is initially 0
            current_process.turnaround_time = 0;

            process_queue.push(current_process);    // Push process onto the queue
        }

    return process_queue;
    }

    else if(algorithm == 2) // SJR
    {
        cout << "Not implemented yet!" << endl;
    }

    else if(algorithm == 3) // RR
    {
        cout << "Not implemented yet!" << endl;
    }

    else if(algorithm == 4) // ML
    {
        cout << "Not implemented yet!" << endl;
    }
}

/*
Method: create_processors()
Depending on the scenario chosen, creates processors with corresponding memory capabilities and speeds. Creates 4 processes
and pushes them onto a processor list.
@params an integer representing the chosen scenario, which determines how the processes are intiialized
@returns a list of Processor objects containing the four processors in the simulation
*/
list<Processor> create_processors(int scenario)
{
    if(scenario == 1) // Scenario 1: All processors are identical (8 gb storage, 3GHz speed)
    {
        Processor P1;
        Processor P2;
        Processor P3;
        Processor P4;
        list<Processor> processor_list;

        P1.memory_capability = 8;
        P1.speed = 3; // GHz (3 billion clocks per second)
        P1.id = 1;

        P2.memory_capability = 8;
        P2.speed = 3; // GHz (3 billion clocks per second)
        P2.id = 2;


        P3.memory_capability = 8;
        P3.speed = 3; // GHz (3 billion clocks per second)
        P3.id = 3;

        P4.memory_capability = 8;
        P4.speed = 3; // GHz (3 billion clocks per second, 1,000,000,000)
        P4.id = 4;

        processor_list.push_front(P1);
        processor_list.push_front(P2);
        processor_list.push_front(P3);
        processor_list.push_front(P4);

        return processor_list;
    }

    else if(scenario == 2)  // SJR
    {
        cout << "Not implemented yet!" << endl;
    }

    else if(scenario == 3)  // RR
    {
        cout << "Not implemented yet!" << endl;
    }

    else if(scenario == 4)  // ML
    {
        cout << "Not implemented yet!" << endl;
    }
}


void print_process_array(Process process_array[])
{
    for(int i=0; i<50; i++)
    {
        cout << "ID: " << process_array[i].id << endl;
        cout << "Service time: " << process_array[i].service_time << endl;
        cout << "Wait time: " << process_array[i].wait_time << endl;
        cout << "Turnaround time: " << process_array[i].turnaround_time << endl;
        cout << "\n";
    }
}

/*
Method: fifo()
Simulates FIFO scheduling. First, puts the processes into an array to be indexed. Then, sets each process's wait time,
which is defined as the previous process's service time + wait time, or total time. 

**NOTE** I ran out of time and could not figure out how to choose random processes, so for now the processes are placed into
the queue 1-50 exactly (though a random one should be chosen each time), so the wait times are preprocessed**

Then, the turnaround times are calculated. Finally, each Processor is iterated through and if there is room a process is added.
Each of these processes is then allowed a certain amount of cycles to work on the processor, and if the cycles worked surpasses
their service time, they are put onto the finished queue and that space is cleared up.

Also keeps track of context switches, which is whenver a process is swapped onto a processor. Displays total turnaround time 
and average wait time.

@params a process_queue that contains 50 processes, and a list of processors from previous functions 
*/
void fifo(queue<Process> process_queue, list<Processor> processor_list)
{
    queue<Process> fifo_queue = process_queue;
    queue<Process> updated_queue;
    list<Process> finished_list;

    unsigned long long total_turnaround_time = 0;
    unsigned long long total_wait_time = 0;

    long long remainder;

    long long avg_turnaround_time = 0; 
    long long avg_wait_time = 0;

    long long context_switches = 0;

    Process process_array[50];
    Process current_process;

    for(int i=0; i<50; i++)
    {
        process_array[i] = fifo_queue.front();
        fifo_queue.pop();
    }

    process_array[0].wait_time = 0; // First process's wait time is 0

    // wait times
    for(int i=1; i<=50; i++)
    {
        process_array[i].wait_time = process_array[i-1].service_time + process_array[i-1].wait_time;
    }

    // turnaround time
    for(int i=0; i<50; i++)
    {
        process_array[i].turnaround_time = process_array[i].service_time + process_array[i].wait_time;
    }

    // put values into a queue
    for(int i=0; i<50; i++)
    {
        updated_queue.push(process_array[i]);
    }

    //print_process_array(process_array);
    /*for(int i=0; i<50; i++)
    {
        current_process = updated_queue.front();
        cout << current_process.turnaround_time << endl;
        updated_queue.pop();
    }*/

    while(updated_queue.empty() == false)   // While the process queue is not empty (still work to be done)
    {
        current_process = updated_queue.front();    // Current process is the first off the process queue

        for(Processor processor : processor_list)   // For each processor in the processor list...
        {
            if(processor.current_memory != processor.memory_capability && (processor.current_memory + current_process.memory_req <= processor.memory_capability))
            {   // If the processor has memory and would not go over memory if the process was added...
                context_switches += 1;  // Increment contest switches
                processor.current_processes.push_front(current_process);    // Push the process onto the processor's current processes

                current_process.cycles_worked += remainder; // Add any remainder that may be from recently finsihed processes
                remainder = 0;

                processor.current_memory += current_process.memory_req; // Add the process's memory requirement to the processor's current load
            }

            for(Process process : processor.current_processes)  // For each process "on" the processor...
             {
                process.cycles_worked += (processor.speed * 1000000000);    // Add to the process's cycles worked 3,000,000,000 cycles

                if(process.cycles_worked >= process.service_time)   // If cycles worked is more than or equal to the process's service time, it's done!
                {
                    remainder = process.cycles_worked - process.service_time;   // To not waste time, add any remaining cycles work to the next process
                    processor.current_processes.pop_front();    // Pop the process that is finished
                    finished_list.push_back(process);   // Add the process to the finished list

                    total_turnaround_time += process.turnaround_time;   // Add to total turnaround/wait time
                    total_wait_time += process.wait_time;

                    processor.current_memory -= process.memory_req; // Free space on the processor
                }
            }
        }
        updated_queue.pop();    // Continue through the process queue until it is empty
    }

    avg_turnaround_time = total_turnaround_time / 50;   // Calculate average turnaround and wait time
    avg_wait_time = total_wait_time / 50;

    if(finished_list.empty())
    {
        cout << "EMPTY" << endl;
    }
    else
    {
        for(Process process : finished_list)    // Print to user each process in order
        {
            cout << "ID: " << process.id << endl;
            cout << "Service time: " << process.service_time << endl;
            cout << "Arrival time(ignore): " << process.arrival_time << endl;
            cout << "Memory req: " << process.memory_req << endl;
            cout << "Wait time: " << process.wait_time << endl;
            cout << "Total time: " << process.turnaround_time << endl;
            cout << endl;
        }
    }
    cout << "Total turnaround time: " << total_turnaround_time << endl;
    cout << "Average wait time: " << avg_wait_time << endl;
    cout << "Context switches: " << context_switches << endl;

}

/*Method main()
Driver for the other functions.
*/
int main()
{
    int scenario_choice;
    int algorithm_choice;
    queue<Process> process_queue;
    list<Processor> processor_list;

    scenario_choice = scenario_menu();
    algorithm_choice = algorithm_menu();
    process_queue = seed_and_create_processes(algorithm_choice);
    processor_list = create_processors(scenario_choice);

    fifo(process_queue, processor_list);
}