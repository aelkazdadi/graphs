from sys import argv
import numpy as np
import matplotlib.pyplot as plt


degrees = np.loadtxt(argv[1], dtype=np.int32)
hist = np.histogram(degrees, bins=np.arange(np.max(degrees) + 2))
hist = np.array((hist[1][:-1], hist[0]), dtype=np.int64)

np.savetxt(argv[2], hist.T, fmt='%-1d')
plt.bar(hist[0], hist[1])
plt.tight_layout()
plt.savefig(argv[3])
