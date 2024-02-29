# PS6: Kronos Time Clock

## What is this assignment:
In this assignment we analyzed a Kronos InTouch time clock log by using regular expressions to
parse the file. We also verified the device boot up timing. This assignment we scanned the
complete log file and created a text file report that chronologically describes each time the
Kronos InTouch device was restarted.

## What was accomplished:
What I accomplished in this assignment was I was able to get my program to scan and parse the
Kronos InTouch log file. I was successfully able to then create a file to write out each time the
device was booted that contained the specific line, date and time the boot was started. As well as
if the boot was ever completed or incomplete. If the boot was complete my program would then
calculate the milliseconds that it took from the boot start to the boot complete.

## Key algorithms:
The key algorithm used in this assignment was just having a while loop scanning each line of the
log file. The program will first take the users input argument and open the file. In my program it
used two different while loops. The first while loop scanned/ parsed the file to get the number of
lines. After this first loop I made my program create an output file containing this information. I
then started my second loop to parse each individual line for when boot started and when/ if the
boot was completed. Scan for these specific lines we were required to use regular expressions to
search for these boots.

## Data Structures:
In this assignment a queue data structure was similarly used. The program had two while loops
that read the file each time. The first while just counted for the number of lines and searched for
the number of boots and completed. It then closed the file, which immediately was then to open
again. This time it scanned/parsed each line like it was in a queue to search for the specific
regular expressions that were set.

![p61](https://github.com/JustinCheok/PS6-Kronos-Time-Clock/assets/80936005/b69c2cbf-3c6e-4efa-89a6-979a0775e45d)
![ps62](https://github.com/JustinCheok/PS6-Kronos-Time-Clock/assets/80936005/01cc88fe-c6fd-4643-8592-b89584a0adb4)

