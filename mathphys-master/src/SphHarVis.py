import numpy as np
import matplotlib.pyplot as plt
from scipy import special
import mpl_toolkits.mplot3d.axes3d as axes3d

theta, phi = np.linspace(0, np.pi, 100), np.linspace(0, 2*np.pi, 100)
THETA, PHI = np.meshgrid(theta, phi)
#help(special.sph_harm)
R = (special.sph_harm(2,3,PHI,THETA).real)**2
X = R * np.sin(THETA) * np.cos(PHI)
Y = R * np.sin(THETA) * np.sin(PHI)
Z = R * np.cos(THETA)
fig = plt.figure()
ax = fig.add_subplot(1,1,1, projection='3d')
plot = ax.plot_surface(
    X, Y, Z, rstride=1, cstride=1, cmap=plt.get_cmap('jet'),
    linewidth=0, antialiased=False, alpha=0.5)

# below are codes copied from stackoverflow, to make the scaling correct
max_range = np.array([X.max()-X.min(), Y.max()-Y.min(), Z.max()-Z.min()]).max() / 2.0
mid_x = (X.max()+X.min()) * 0.5
mid_y = (Y.max()+Y.min()) * 0.5
mid_z = (Z.max()+Z.min()) * 0.5
ax.set_xlim(mid_x - max_range, mid_x + max_range)
ax.set_ylim(mid_y - max_range, mid_y + max_range)
ax.set_zlim(mid_z - max_range, mid_z + max_range)

#ax.view_init(elev=30,azim=0) #调节视角，elev指向上(z方向)旋转的角度，azim指xy平面内旋转的角度

plt.show()
