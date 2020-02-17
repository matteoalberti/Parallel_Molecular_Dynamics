import ctypes as ct

so_ljmd = "../lib/ljmd.so"
c_ljmd = ct.CDLL(so_ljmd)

c_ljmd.main()
