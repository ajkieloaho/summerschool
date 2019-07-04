#!/bin/bash
#SBATCH -J my_job_name
#SBATCH -o %J.out
#SBATCH -e %J.err
#SBATCH -n 2
#SBATCH -p small
#SBATCH -t 5
#SBATCH --reservation=Summerschool

aprun -e OMP_NUM_THREADS=8 -e MPICH_MAX_THREAD_SAFETY=multiple -n 2 -d 8 ./heat_mpi
