import numpy as np
#### Codigo para poner el mas grande al principio y el resto estan ordenados ascendentemente###################
# for pow in range (1,6): #[2,5)
#   for x in range(2,11): #[2,10)
#     n = x * (10**pow)
#     f = open("inputs/input_" + str(n), "w")
#     print("inputs/input_" + str(n)) ####debug####

    
#     f.write(str(np.random.randint(0,2*n)) + ' ' + str(2*n) + '\n')
#     anterior = 0

#     for num in range(n-1):
#         input2 = anterior + 2
#         input1 = np.random.randint(0,input2)  

#         anterior = input2
#         f.write(str(input1) + ' ' + str(input2) + '\n')
#     f.close()

#### Codigo para ordenados descendentemente###################
for pow in range (1,6): #[2,5)
  for x in range(2,11): #[2,10)
    n = x * (10**pow)
    f = open("inputs/input_" + str(n), "w")
    print("inputs/input_" + str(n)) ####debug####

    anterior = 2*n + 2

    for num in range(n):
        input2 = anterior - 2
        input1 = np.random.randint(0,input2)
        
        anterior = input2
        f.write(str(input1) + ' ' + str(input2) + '\n')
    f.close()

###############Codigo viejo####################################
# for power in range(16, 27):
#     n = 2 ** power
#     f = open("inputs/input_" + str(n), "w")
#     input = range(0, n-1)
#     f.write(str(n-1) + " ")
#     for num in input:
#         f.write(str(num) + " ")
#     f.close()

# for power in range(1,6):
#     n = 5 * (10**power) #n = cant actividades, 5 50 500 5000
#     f = open("inputs/input_" + str(n), "w")
    
#     anterior = 2*n + 2

#     for num in range(n):
#         input2 = anterior - 2
#         input1 = np.random.randint(0,input2-1)
        
#         anterior = input2
#         f.write(str(input1) + ' ' + str(input2) + '\n')
#     f.close()