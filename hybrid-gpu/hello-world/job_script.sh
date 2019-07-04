#!/bin/bash
#SBATCH -N 1
#SBATCH -n 1
#SBATCH -p gpu
#SBATCH -t 00:05:00
#SBATCH test-acc
#SBATCH --gres=gpu:k80:2
#SBATCH --reservation=Summerschool
module load pgi/19.1 openmpi/3.1.4 libpng/1.6
srun ./a.out

