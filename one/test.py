from numpy import sort, loadtxt

A, B = sort(loadtxt('input.txt', int).T)
print(sum(abs(A - B)),
      sum(a * sum(a==B) for a in A))

