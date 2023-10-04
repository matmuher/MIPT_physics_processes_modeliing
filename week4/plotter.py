import numpy as np
import matplotlib.pyplot as plt
import subprocess

def read_solver_data(file_name):

	xv_dtype = np.dtype([('x', np.float32), ('v', np.float32)])
	xv_data = np.fromfile(file_name, dtype = xv_dtype)

	return xv_data

def plot_solver_data(config_name):

	fig = plt.figure(figsize = (10, 10))
	ax = plt.gca()

	analytical_xv_data = read_solver_data('analytical_output.bin')
	euler_xv_data = read_solver_data('euler_output.bin')
	heun_xv_data = read_solver_data('heun_output.bin')

	t_sample_list = range(0, euler_xv_data.size)

	ax.plot(t_sample_list, analytical_xv_data['x'], label = 'analytical x') # wrap plotting rouitine
	ax.plot(t_sample_list, analytical_xv_data['v'], label = 'analytical v') # into function / class

	ax.plot(t_sample_list, euler_xv_data['x'], label = 'euler x')
	ax.plot(t_sample_list, euler_xv_data['v'], label = 'euler v')

	ax.plot(t_sample_list, heun_xv_data['x'], label = 'heun x')
	ax.plot(t_sample_list, heun_xv_data['v'], label = 'heun v')

	ax.set_title(config_name)
	ax.legend()

	fig.savefig(f'{config_name}.svg')	

if __name__ == '__main__':

	executable_name = './solver.exe'
	
	few_samples_config_path = 'few_samples_config.json'
	few_samples_config_name = 'few_samples'

	many_samples_config_path = 'many_samples_config.json'
	many_samples_config_name = 'many_samples'

	subprocess.run([executable_name, few_samples_config_path])
	plot_solver_data(few_samples_config_name)

	subprocess.run([executable_name, many_samples_config_path])
	plot_solver_data(many_samples_config_name)

	# it's better to open them not in sequential way
	# but in parallel, or plot them on the same figure
	subprocess.run(['eog', few_samples_config_name + '.svg'])
	subprocess.run(['eog', many_samples_config_name + '.svg'])

