# to do
# def partialQuickSort(k, A, p, q):
# 	if p < q:
# 		p = a[q]
# 		p = partition(A, p, )
#
# 		
def quickSort(A, p, r):
	if p < r:
		q = partition(A, p, r)
		quickSort(a, p, q-1)
		quickSort(a, q+1, q)

def partition(A, p, r):
	#pivot
	x = a[r]
	i = p-1
	for j in range(p, r-1):
		if a[j] <= x: 
			i+=1
			a[i], a[j] = a[j], a[i]
	a[i+1], a[r] = a[r], a[i+1]
	return i+1

def merge(A, p, q, r):
	n1 = q - p +1
	n2 = r - q
	L = A[0:n1-1]
	R = A[q:r]

	i = 0
	j = 0
	k = 0
	while i <= q || j <= r
	if L[i] <= R[j]:
		A[k] = L[i]
		i+=1
	else:
		A[k] = R[j]
		j+=1

def mergeSort(A, p, r):
	if p < r:
		q = int((p + r)/2)
		mergeSort(A, p, q)
		mergeSort(A, q+1, r)
		merge(A, p, q, r)


b = [2,4,5,7,1,2,3,6]
mergeSort(b, 0,len(b))
print(b)
a = [7,5, 3, 2,1]

