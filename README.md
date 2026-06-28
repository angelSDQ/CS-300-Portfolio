# CS-300 Portfolio

This repo has two pieces of work from my Data Structures and Algorithms course. Both are based on the ABCU advising program project, where the goal was to build a tool to help find the courses for the Computer Science program.

## Files
- **Project One** my pseudocode and runtime analysis comparing a vector, a hash table, and a binary search tree.
- **Project Two** my C++ program that loads the course data and prints all the courses in alphanumeric order.

## Reflection

**What was the problem you were solving in the projects for this course?**

The task asked for a program that could read in the course data, print all the courses in order, and look up a single course with its prerequisites. Project One was about figuring out which data structure to use, and Project Two was actually building it.

**How did you approach the problem? Consider why data structures are important to understand.**

I looked at what the program needed to do and then compared three structures for those jobs. A vector loads fast but you have to sort it every time you print. A hash table finds a course fast but doesn't stay in order. A binary search tree keeps everything sorted, so printing the list is easy and looking up a course is still quick. That comparison is why data structures matter. Picking the right one makes the program faster and cleaner. I went with the binary search tree because it handled both things the task was asking for, and that's what I built in Project Two.

**How did you overcome any roadblocks you encountered while going through the activities or project?**

The hardest part wasn't the algorithms, it was reading the file. Parsing each line and checking that every prerequisite was an actual course took some trial and error. I fixed the prerequisite check by reading the file in two passes, one to collect all the course numbers and one to check the prerequisites against them. When I got stuck I broke the code into smaller functions and tested them one at a time.

**How has your work on this project expanded your approach to designing software and developing programs?**

I learned to pick the data structure first instead of jumping straight into code. Writing the pseudocode before coding helped me catch problems early, and doing the runtime analysis got me thinking about how the program holds up as the data grows, not just whether it runs.

**How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?**

I broke the program into separate functions for loading, searching, and printing, so each part does one thing. I kept the menu separate from the data structure too, so the same menu works no matter what structure is behind it. Good names and comments made it easier to read and easier to come back to later.
