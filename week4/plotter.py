import numpy as np
import matplotlib.pyplot as plt

if __name__ == '__main__':

	fileName = 'output.bin'

	xv_dtype = np.dtype([('x', np.float32), ('v', np.float32)])

	xv_data = np.fromfile(fileName, dtype = xv_dtype);


	t_sample_list = range(0, xv_data.size)

	plt.plot(t_sample_list, xv_data['x'], label = 'x')
	plt.plot(t_sample_list, xv_data['v'], label = 'v')
	plt.legend()

	plt.savefig('plot.svg')

	print('Hello world')
	print(xv_data)