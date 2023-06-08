#!/bin/bash

# Ruta al ejecutable de C++
cpp_executable="/mnt/c/Users/lucas/Documents/Git/TDP/LAB2/parser"

# Ruta al ejecutable de Python
python_executable="/mnt/c/Users/lucas/Documents/Git/TDP/LAB2/asd.py"

# Número de iteraciones
num_iterations=5

# Contador
counter=0

while [ $counter -lt $num_iterations ]
do
    echo "Ejecutando el programa C++..."
    $cpp_executable
    
    echo "Ejecutando el programa de Python..."
    python3 $python_executable
    
    counter=$((counter+1))
done
