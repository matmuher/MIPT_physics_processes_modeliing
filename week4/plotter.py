import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':

	fileNameEuler = 'euler.bin'
	fileNameAnalytical = 'analytical.bin'

	xv_dtype = np.dtype([('x', np.float32), ('v', np.float32)])
	
	analytical_xv_data = np.fromfile(fileNameAnalytical, dtype = xv_dtype);
	euler_xv_data = np.fromfile(fileNameEuler, dtype = xv_dtype);

	t_sample_list = range(0, euler_xv_data.size)

	plt.plot(t_sample_list, analytical_xv_data['x'], label = 'analytical x')
	plt.plot(t_sample_list, analytical_xv_data['v'], label = 'analytical v')

	plt.plot(t_sample_list, euler_xv_data['x'], label = 'euler x')
	plt.plot(t_sample_list, euler_xv_data['v'], label = 'euler v')

	plt.legend()

	plt.savefig('plot.svg')

	print('Hello world')
	print(analytical_xv_data)
	print(euler_xv_data)
