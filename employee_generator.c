#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_EMPLOYEES 10
// The number of employees to generate
enum Department { HR, Sales, Research, Software, Executive };
// Enumeration for departments
struct Employee {
    enum Department dept; 
    int salary;            
    unsigned ssn;          // Social Security Number
};
// Function to get the department name as a string
char* getDeptName(enum Department d) {
    switch(d) {
        case HR: return "HR";
        case Sales: return "Sales";
        case Research: return "Research";
        case Software: return "Software";
        case Executive: return "Executive";
        default: return "Enter a valid department";
    }
}
// Function to generate a random salary based on department
int generateSalary(enum Department d) {
    int base = 0;
    int offset = rand() % 10000; // Random offset for salary variation

    switch(d) {
        case HR:       base = 50000; break;
        case Sales:    base = 60000; break;
        case Research: base = 70000; break;
        case Software: base = 80000; break;
        case Executive:base = 110000; break;
    }
// Return the base salary plus a random offset
    return base + offset;
}

int main() 
{
    srand(time(NULL)); // Seed the random number generator
    struct Employee employees[NUM_EMPLOYEES];
 // Initialize the employees array
    for(int i = 0; i < NUM_EMPLOYEES; i++) 
    {
        employees[i].dept = rand() % 5;
        employees[i].salary = generateSalary(employees[i].dept);
        employees[i].ssn = 100000000 + i;
    }
// Print the employee details
    printf("Dept\tSalary\t\tSSN\n");
    printf("--------------------------------\n");
    for(int i = 0; i < NUM_EMPLOYEES; i++) 
    {
        printf("%-10s %-10d %u\n",
               getDeptName(employees[i].dept),
               employees[i].salary,
               employees[i].ssn);
    }

    return 0;
}
