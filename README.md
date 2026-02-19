# CourseMarksData
Reads, analyses and outputs student mark data from a .dat file

### Statement on the use of AI
No generative AI was used in the writing of or debugging of this code, all code was written and debugged by me with the use of the internet.

### Description of devlopment timeline

Created a base program that reads a given .dat file and stores the data into 3 vectors (1 per column). Changed to using a struct which contained the three vectors to more compactly store the data and make it easier to create a separate function to read the file.

Impleneted std and stE calculations as separate functions for code cleanliness. Then filtered data for a specified year and printed out std and stE again for the new set. 

Initially I read each column as a n-dimensional vector - meaning 3 different vectors for the data set, but this was cumbersome and made sorting by name difficult. I therefore switched to using a struct for each course, with a name, id, and mark attribute. Therefore only one n-dimensional vector was required using this "Course" data type, each element representing one row of data (one course). This allowed for cleaner code and for significantly easier sorting of data.

I then added better data validation, as before it would just stop reading the file as soon as it encountered a row with wrong data types in. Now it simply skips those lines and warns the user which lines were unable to be read. Also made program terminate if file could not be opened at all. I decided to add sort by mark as an easy quick to implement feature as well.