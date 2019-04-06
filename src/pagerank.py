from sys import argv
import numpy as np
import matplotlib.pyplot as plt

plt.rc('text', usetex=True)
plt.rc('font', family='serif')

indegrees = np.loadtxt(argv[1]+"/indeg.dat", dtype=np.int32)
outdegrees = np.loadtxt(argv[1]+"/outdeg.dat", dtype=np.int32)

pagerank15 = np.loadtxt(argv[1]+"/15.dat")
print(".", end="", flush=True)
pagerank10 = np.loadtxt(argv[1]+"/10.dat")
print(".", end="", flush=True)
pagerank20 = np.loadtxt(argv[1]+"/20.dat")
print(".", end="", flush=True)
pagerank50 = np.loadtxt(argv[1]+"/50.dat")
print(".", end="", flush=True)
pagerank90 = np.loadtxt(argv[1]+"/90.dat")
print(".", flush=True)

order = np.argsort(pagerank15)
print("Top 5")
print(order[-5:][::-1])

print("Bottom 5")
index = order.size - order[pagerank15[order] > pagerank15[order[0]]].size
print(order[index:index+5], flush=True)

fig = plt.figure(figsize=(4.5, 4.5), dpi=200)
ax = plt.gca()

ax.scatter(pagerank15, indegrees, s=1)
ax.set_xscale("log")
ax.set_xlim(pagerank15.min(), pagerank15.max())
ax.set_ylim(indegrees.min(), indegrees.max())
fig.tight_layout()
fig.savefig(argv[1] + "/1.png")

plt.cla()
ax.set_xscale("log")
ax.scatter(pagerank15, outdegrees, s=1)
ax.set_xlim(pagerank15.min(), pagerank15.max())
ax.set_ylim(outdegrees.min(), outdegrees.max())
fig.tight_layout()
fig.savefig(argv[1] + "/2.png")

plt.cla()
ax.scatter(pagerank15, pagerank10, s=1)
ax.set_xscale("log")
ax.set_yscale("log")
ax.set_xlim(pagerank15.min(), pagerank15.max())
ax.set_ylim(pagerank10.min(), pagerank10.max())
fig.tight_layout()
fig.savefig(argv[1] + "/3.png")

plt.cla()
ax.scatter(pagerank15, pagerank20, s=1)
ax.set_xscale("log")
ax.set_yscale("log")
ax.set_xlim(pagerank15.min(), pagerank15.max())
ax.set_ylim(pagerank20.min(), pagerank20.max())
fig.tight_layout()
fig.savefig(argv[1] + "/4.png")

plt.cla()
ax.scatter(pagerank15, pagerank50, s=1)
ax.set_xscale("log")
ax.set_yscale("log")
ax.set_xlim(pagerank15.min(), pagerank15.max())
ax.set_ylim(pagerank50.min(), pagerank50.max())
fig.tight_layout()
fig.savefig(argv[1] + "/5.png")

plt.cla()
ax.scatter(pagerank15, pagerank90, s=1)
ax.set_xscale("log")
ax.set_yscale("log")
ax.set_xlim(pagerank15.min(), pagerank15.max())
ax.set_ylim(pagerank90.min(), pagerank90.max())
fig.tight_layout()
fig.savefig(argv[1] + "/6.png")
