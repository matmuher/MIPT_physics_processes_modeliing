import numpy as np
import matplotlib.pyplot as plt

class Style:

	def __init__(self, marker):

		self.marker = marker

class SesInfo:

	def read_data(file_name):

		xv_dtype = np.dtype([('x', np.float32), ('v', np.float32)])
		xv_data = np.fromfile(file_name, dtype = xv_dtype)

		return xv_data

	def __init__(self, session_name, config, style):

		self.name = session_name

		self.data = SesInfo.read_data(config['output']); 

		self.t_sample_list = range(0, self.data.size)

		self.marker = style.marker

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