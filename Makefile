CC = gcc - lm -g
mpi_hello:
	mpicc  mpi_hello.c -o mpi_hello -lm
clean:
	rm -f mpi_hello hello 