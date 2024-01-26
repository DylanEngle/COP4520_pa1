# COP4520_pa1
Code for Programming Assignment 1 of class COP4520

Instructions for how to compile and run this code:
1. Open up powershell terminal
2. Next, to compile type: "g++ cop4520_pa1.cpp"
3. Now run the executable: "./a"
4. To see the solution, open up primes.txt

Summary of Approach: To count all the prime numbers to 10^8, we spawn 8 threads that will each handle a chunk of size 10^7. They all must be padded with a lockguard (mutex), using the principle of mutual exclusion to ensure memory is not being corrupted between each thread. After they finish, they join together and combine results.
Efficiency wise, the program finishes in about 6 seconds, which is an adequately fast program for going through such a large numbers and finding primes. The prime number function is also optimized to ensure the overall program doesn't slow. 

Reasoning: I would say that this design is a correct one because I tested my prime number function to ensure it works, and the final sum of the primes and total number matches the accurate number. Using parrallelism the threads ensured this program work faster than having one thread handle all this work.

Experimental Evaluation: At first, I was getting memory errors because I was not equipping my threads with a lock guard, so each thread would corrupt the other. After doing this, I fixed the problem. I also sped up my prime number function, since this function has to be run 10^8 times, so it needs to be fast. I made it faster to speed up the runtime, to get a final time of about 6 seconds.