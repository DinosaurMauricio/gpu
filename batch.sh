#!/bin/bash
#SBATCH --partition=edu5
#SBATCH --nodes=1
#SBATCH --tasks=1
#SBATCH --gres=gpu:1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00
#SBATCH --job-name=test
#SBATCH --output=double-test-%j.out
#SBATCH --error=double-test-%j.err



if [[ "$4" == "--valgrind" ]]; then
    srun valgrind --tool=cachegrind ./bin/gpu_transpose "$1" "$2" "$3"
else
    srun ./bin/gpu_transpose "$1" "$2" "$3"
fi
