# function_ploter
# it's sa simple gui program  built with c++ and Qt that calculate and plot any f(x) in a given ranges of x 
the program will handel the precedence and associativity of operation for example:
  1) (x+2)*2 => x+2 will be evaluated first then it will be multiplied by 2
  2) x-2* 4 => 2*4 will be evaluated first then x - 8
# snapshots of program 
![1](https://user-images.githubusercontent.com/40799479/147793503-2f4c5605-5f3b-48d6-84cc-6aa43427ec53.PNG)
![2](https://user-images.githubusercontent.com/40799479/147793507-cea4e3f6-57be-491d-a184-be935165b5a2.PNG)
![3](https://user-images.githubusercontent.com/40799479/147793510-5397299e-43b4-4041-8c70-1c7f7af11c8e.PNG)
# Error handelling 
the program will generate three diff error message depending on user input:
  1)if user inputs expression with unmatched parentheses
  ![4](https://user-images.githubusercontent.com/40799479/147793619-7c745c1d-5f33-4377-9962-93294a601c82.PNG)
  
  2)if user inputs expression with varibles other than x
  ![5](https://user-images.githubusercontent.com/40799479/147793626-3eb71dee-23f5-4d7d-b6f3-f377cadbdcbd.PNG)
  
  3)if user enter a invalid math expression as putting two operators ater each other 
  ![6](https://user-images.githubusercontent.com/40799479/147793659-1c3c0a8a-2303-403f-9683-ae812d28f7d1.PNG)
  
also program can have any white spaces in f(x) field and x1 and x2(x ranges) can be in any order
![7](https://user-images.githubusercontent.com/40799479/147793746-f2b6490d-143f-4fe6-baba-33cda0e32319.PNG)
