import numpy as np
import matplotlib.pyplot as plt
import subprocess


def read_solver_data(file_name):

	xv_dtype = np.dtype([('x', np.float32), ('v', np.float32)])
	xv_data = np.fromfile(file_name, dtype = xv_dtype)

	return xv_data

class MethodData:

	def __init__(self, method_name, binary_file, marker):

		self.binary_file = binary_file
		self.name = method_name
		self.marker = marker

		self.data = read_solver_data(binary_file);

	def plot_solution(self, ax):

		t_sample_list = range(0, self.data.size)
		ax.plot(t_sample_list, self.data['x'], label = self.name + ' x', marker = self.marker)
		ax.plot(t_sample_list, self.data['v'], label = self.name + ' v', marker = self.marker)

	def plot_energy(self, ax):

		t_sample_list = range(0, self.data.size)
		ax.plot(	t_sample_list,
					self.data['x'] * self.data['x'] + self.data['v'] * self.data['v'],
					label = self.name + ' x',
					marker = self.marker)

	def plot_error(self, ax, other):

		if self.data.size != other.data.size:

			raise Exception(f'Data not matches for {self.name} and {other.name}')

		t_sample_list = range(0, self.data.size)
		
		ax.plot(t_sample_list,
				np.abs(self.data['x'] - other.data['x']),
				label =  'x error: ' + self.name + ' and ' + other.name,
				marker = self.marker)
		
		ax.plot(t_sample_list,
				np.abs(self.data['v'] - other.data['v']),
				label = 'v error: ' + self.name + ' and ' + other.name,
				marker = self.marker)

	def plot_phase_diagram(self, ax):

		ax.plot(self.data['x'], self.data['v'], label = self.name + ' v', marker = self.marker)

def plot_solution(ax, methods):

	ax.set_title('Solutions comparison')
	ax.set_xlabel('time samples')
	ax.set_ylabel('x & v')	

	for method in methods:

		method.plot_solution(ax)

def plot_phase_diagram(ax, methods):

	ax.set_title('Phase diagrams comparison')
	ax.set_xlabel('x')
	ax.set_ylabel('v')

	for method in methods:

		method.plot_phase_diagram(ax)

def plot_energy(ax, methods):

	ax.set_title('System energy comparison')
	ax.set_xlabel('time samples')
	ax.set_ylabel('energy')	

	for method in methods:

		method.plot_energy(ax)

def plot_error(ax, methods):

	ax.set_title('Errors comparison')
	ax.set_xlabel('time samples')
	ax.set_ylabel('abs(error)')	

	analytic = methods[0]

	for i in range(1, len(methods)):

		methods[i].plot_error(ax, analytic);

class PlotFunction:

	def __init__(self, name, function):

		self.call = function
		self.name = name

def save_plot_to_picture(config_name, plot_function, methods):

	fig = plt.figure(figsize = (10, 10))
	ax = plt.gca()

	plot_function.call(ax, methods)

	ax.legend()
	fig.savefig(f'{config_name}_{plot_function.name}.svg');

def save_plots_to_pictures(config_name, plot_functions, methods):

	for plot_function in plot_functions:

		save_plot_to_picture(config_name, plot_function, methods)

def plot_solver_data(config_name):

	fig, axs = plt.subplots(1, 3, figsize = (30, 10))

	methods = 	[	
					MethodData('analytic', 'analytical_output.bin', '|'),
					MethodData('heun', 'heun_output.bin', 'o'),
					MethodData('euler', 'euler_output.bin', '^')
				]
	
	plot_functions = 	[
						PlotFunction('solution', plot_solution),
						PlotFunction('energy', plot_energy),
						PlotFunction('phase_diagram', plot_phase_diagram),
						PlotFunction('error', plot_error)
						]

	save_plots_to_pictures(config_name, plot_functions, methods) # TODO create tmp dir and save plot there

class ConfigInfo:

	def __init__(self, config_name, config_path):

		self.name = config_name
		self.path = config_path

if __name__ == '__main__':

	executable_name = './solver.exe'
	
	configs = 	[
				ConfigInfo('few_samples', 'configs/few_samples_config.json'),
				ConfigInfo('many_samples', 'configs/many_samples_config.json')
				]

	for config in configs:

		subprocess.run([executable_name, config.path])
		plot_solver_data(config.name)
