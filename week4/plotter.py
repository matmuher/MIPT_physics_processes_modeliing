import numpy as np
import matplotlib.pyplot as plt
import subprocess
import os
import glob
import json

import matplotlib.pyplot as plt
import numpy as np

from config_helper import *

# Move to Jupiter

	# Make a Session class that hold everything that is
	# connected with a single executable start

	# Plot data
	# Binary data

# Add deltaT as parameter
# Make report

class MethodData:

	def read_solver_data(file_name):

		xv_dtype = np.dtype([('x', np.float32), ('v', np.float32)])
		xv_data = np.fromfile(file_name, dtype = xv_dtype)

		return xv_data

	def __init__(self, method_name, binary_file, marker, w):

		self.binary_file = binary_file
		self.name = method_name
		self.marker = marker

		self.w = w
		self.data = MethodData.read_solver_data(binary_file);

	def plot_x(self, ax):

		t_sample_list = range(0, self.data.size)

		ax.plot(t_sample_list,
				self.data['x'],
				label = self.name + ' x',
				marker = self.marker)

	def plot_v(self, ax):

		t_sample_list = range(0, self.data.size)

		ax.plot(t_sample_list,
				self.data['v'],
				label = self.name + ' v',
				marker = self.marker)

	def plot_energy(self, ax):

		t_sample_list = range(0, self.data.size)

		ax.plot(	t_sample_list,

					self.w * self.w * self.data['x'] * self.data['x'] +
					self.data['v'] * self.data['v'],

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

		ax.plot(self.data['x'],

				self.data['v'],
			
				label = self.name + ' v',
				marker = self.marker)

def plot_x(ax, methods):

	ax.set_title('Coord comparison')
	ax.set_xlabel('time samples')
	ax.set_ylabel('x')	

	for method in methods:

		method.plot_x(ax)

def plot_v(ax, methods):

	ax.set_title('Velocity comparison')
	ax.set_xlabel('time samples')
	ax.set_ylabel('v')	

	for method in methods:

		method.plot_v(ax)

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

	analytic = methods[-1]

	for i in range(0, len(methods)-1):

		methods[i].plot_error(ax, analytic);

class PlotFunction:

	def __init__(self, name, function):

		self.call = function
		self.name = name

def create_empty_dir(dir_path):

	if not os.path.exists(dir_path):

		os.makedirs(dir_path)

def save_plot_to_picture(config_name, plot_function, methods):

	save_dir = os.path.join(".", "tmp")
	save_dir = os.path.join(save_dir, config_name)

	create_empty_dir(save_dir)

	fig = plt.figure(figsize = (10, 10))
	ax = plt.gca()

	plot_function.call(ax, methods)

	ax.legend()
	fig.savefig(os.path.join(save_dir, f'{config_name}_{plot_function.name}.svg'));

def save_plots_to_pictures(config_name, plot_functions, methods):

	for plot_function in plot_functions:

		save_plot_to_picture(config_name, plot_function, methods)

def plot_solver_data(config):

	fig, axs = plt.subplots(1, 3, figsize = (30, 10))

	with open(config.path) as file:

		config_dict = json.load(file)

		w = config_dict["w"]

	methods = 	[	
					MethodData('rk4', 'rk4_output.bin', 's', w),
					# MethodData('heun', 'heun_output.bin', 'o', w),
					# MethodData('euler', 'euler_output.bin', '^', w),
					# MethodData('analytic', 'analytical_output.bin', '|', w)
				]
	
	plot_functions = 	[
						PlotFunction('x', plot_x),
						PlotFunction('v', plot_v),
						PlotFunction('energy', plot_energy),
						PlotFunction('phase_diagram', plot_phase_diagram),
						# PlotFunction('error', plot_error)
						]

	save_plots_to_pictures(config.name, plot_functions, methods)

class ConfigInfo:

	def __init__(self, config_name, config_path):

		self.name = config_name
		self.path = config_path

def run_config(exec_name, config_name):

	print(get_config_path(config_name))

	subprocess.run([exec_name, get_config_path(config_name)]) # TODO: popen	

'''

Conig file -> various methods (make it configurable???):

	rk4
	
		x_plot
		energy_plot

	euler

		x_plot
		energy_plot

	heun

		x_plot
		energy_plot


MethodData is not good creation, as we can have several same methods
relate to different models

ModelData (Damped)
|
|----MethodData (rk4)
|----MethodData (Heun)


ModelData (Harmonic)
|
|----MethodData (rk4)
|----MethodData (Heun)

SessionData = Model + Method => .bin data

SessionPlotter:

	sessionPlotter = SessionPlotter(SessionData)

	sessionPlotter.plot_x(ax)
	sessionPlotter.plot_energt(ax)

'''

class SesInfo:

	def read_data(file_name):

		xv_dtype = np.dtype([('x', np.float32), ('v', np.float32)])
		xv_data = np.fromfile(file_name, dtype = xv_dtype)

		return xv_data

	def __init__(self, session_name, binary_file, w, marker = 's'):

		self.name = session_name

		self.binary_file = binary_file
		self.data = SesInfo.read_data(binary_file); 

		self.w = w

		self.t_sample_list = range(0, self.data.size)

		self.marker = marker

class SesPlotter:

	def plot_x(ses_info, ax):

		ax.plot(ses_info.t_sample_list,
				ses_info.data['x'],
				label = ses_info.name,
				marker = ses_info.marker)

	def plot_v(ses_info, ax):

		ax.plot(ses_info.t_sample_list,
				ses_info.data['v'],
				label = ses_info.name,
				marker = ses_info.marker)

	def plot_energy(ses_info, ax):

		ax.plot(	ses_info.t_sample_list,

					ses_info.w * ses_info.w *
					ses_info.data['x'] * ses_info.data['x'] +
					ses_info.data['v'] * ses_info.data['v'],

					label = ses_info.name,
					marker = ses_info.marker)

	def plot_error(ses_info, ses_info_other, ax):

		if ses_info.data.size != ses_info_other.data.size:

			raise Exception(f'Data not matches for {ses_info.name} and {ses_info_other.name}')

		ax.plot(ses_info.t_sample_list,

				np.abs(ses_info.data['x'] - ses_info_other.data['x']),
			
				label =  ses_info.name + ' vs ' + ses_info_other.name,
				marker = ses_info.marker)

	def plot_phase_diagram(ses_info, ax):

		ax.plot(ses_info.data['x'],

				ses_info.data['v'],
			
				label = ses_info.name,
				marker = ses_info.marker)