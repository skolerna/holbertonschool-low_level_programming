Measurement Methodology 

In this project i had to make measurements of three C programs to check how code efficiency can affect performance. I compiled the program with GCC with the compilation flags. I used the clock () function from the <time.h> library to measure CPU time. The results were converted into seconds using CLOCKS_PER_SEC. For the two first exercises, I ran each program three times on the same machine to compare the execution times. 
In the third exercice, I added timing measurements with three functions : build_dataset(), process_dataset() and reduce_checksum(). And I measured the total execution time.
 

Observed Performance Differences

In the first exercise, the program gave me execution times of 0.060512, 0.061923, and 0.057052 seconds. The results were close but not exactly the same. 

In the second exercise, I compared two algorithms. The naive algorithm had an approximative execution time of 0.522655 seconds and the single-pass algorithm had an average of 0.000021 seconds. The naive algorithm was around 24,888 times slower. It uses nested loops and the single pass algorithm uses only one loop. 

In the third exercise, I measured three different phases. Building the dataset took 0.000110 seconds, processing took 0.000097 seconds and reducing took 0.000039 seconds. The total execution time was 0.000246 seconds. The build phase was the slowest in this run. 

Relation Between Runtime and Energy Consumption

Execution time can have an impact on energy consumption because the CPU needs energy to execute instructions. 
The single pass algorithm finished much faster than the naive algorithm which means that using a more efficient algorithm can help reduce CPU activity and energy consumption but in this experiment I didn't measure the electricity consumption. 

Limitations of the Experiment

We can observe that these experiments have some limitations. 
First, I measured CPU time using clock(), but as said earlier I didn’t measure actual energy.
The execution times can change depending on the system activity, CPU frequency or other processes running on the computer. 
The two first programs were executed three times, so it isn’t enough to get precise measurements of the average. 
The single pass algorithm makes the ratio less precise.

Practical Engineering Takeaway 

This project helped me to understand why measuring performance is important in software development. I learned that two different ways can have very different execution times and the algorithm can strongly affect performance. It makes me think that for further works i will try to measure my programs before making any changes because writing efficient code is important for performance. 