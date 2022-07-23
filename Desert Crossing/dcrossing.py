import math

# 1 litre of fuel = 12 units of distance
# max 60 litre tank, four twenty litre cans
# distance to go is 2413 km / 12 = approx 201 units

# d(f) = farthest amount of distance the jeep can go on f amount of fuel
# theorum d(f) = 1 + 1/3 + 1/5 + ... + 1/2f-1
# x = point in the desert, x0 = d, 
# k = final distance, if x < xk, then n(x) >= 2k + 1
# since x is less than xk, the jeep must consumer more than k loads of fuel to the right of x.

# 1/4 of 140 litres
# Depot ---------------
