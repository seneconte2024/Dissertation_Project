# Dissertation_Project
This repository contains code, data, and documentation for my Master's dissertation: "Comparing Similarity Between Two Territory Partitions in Districting Problem Using Weighted Pair Counting Similarity Indices." Includes algorithms, datasets, and results for comparing territorial partitions in districting problems.

This project implements a framework for comparing territorial partitions using similarity indices such as:

* Rand Index (RI)
* Fowlkes-Mallows Index (FMI)
* Jaccard Index (JI)


# Project Structure
* root directory
    * project/: Contains all source code, headers, and build fiiles.
    * include/: Header files.
    * src/: Source files.
    * Makefile: Script for building the project.

# Compilation Instructions
To compile the project, follow these steps:

1. Navigate to the 'project/' directory:
   
   ![image](https://github.com/user-attachments/assets/af3a5898-9ab9-4cf5-b062-e17c6e69a557)
   
2. Execute the 'make' command to build the project:
   
   ![image](https://github.com/user-attachments/assets/4bd68b11-5b86-48bd-816c-32f5295c9dd1)
   
3. The compiled binary will be created as a file named 'Project' in the 'project/' directory.

# Running the Project

![image](https://github.com/user-attachments/assets/1359cf13-76a2-45c6-885e-e5d2bc5cc399)

To run the compiled project, execute the 'Project' binary from the 'project/' directory, passing the following arguments:

<number_of_iterations>: The number of perturbation iterations applied to the partition.
<number_of_samples>: The number of samples to be calculated to analyse min, average and maximum values.
<Index>: The similarity index to use. Options: RI, FMI, JI.

Example Execution:

![image](https://github.com/user-attachments/assets/7f42ab94-4d41-48d5-ab56-b7b27508dc52)

This will run the program with 1000 perturbation iterations, evaluating 500 samples, using the Rand Index (RI) as the similarity measure.

# Sample Output

The program outputs the minimum, average, and maximum similarity values for both traditional and weighted similarity indices.

Example output for Rand Index (RI):

![image](https://github.com/user-attachments/assets/5714bb5f-ade0-427e-b175-b93c88bed90f)

# Interpreting Results:
* Traditional Similarity Values: Provide a general comparison between partitions.
* Weighted Similarity Values: Offer a more sensitive evaluation by prioritizing high-impact zones in the partition.

# Future Improvements

* Add support for additional similarity indices.
* Optimize performance for large-scale partitions.
* Implement visualization tools to graphically compare partitions.


