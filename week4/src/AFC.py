import src.plotter
import numpy as np

def find_steady_state_amplitude(w0, damp_ratio, omega, dt, data, steady_time_multiplier):

	steady_state_time = get_decay_time(w0, damp_ratio)
	steady_state_index = steady_time_multiplier * int(steady_state_time / dt)

	force_period_time = (2 * np.pi / omega)
	force_period_index = int(force_period_time / dt) 
	
	# print(f'steady time: {steady_state_time}')
	# print(f'force period time: {force_period_time}')
	# print(f'dt: {dt}')

	amplitude = 0.
	for step in range(0, force_period_index):

		sample_index = steady_state_index + step 

		if sample_index >= len(data):

			raise Exception('Cant find amplitude as there are not enough samples')

		if abs(data['x'][steady_state_index + step]) > amplitude:

			amplitude = abs(data['x'][steady_state_index + step])

	return amplitude 

def get_decay_time(w0, damp_ratio):

	return 1 / (w0 * damp_ratio)

