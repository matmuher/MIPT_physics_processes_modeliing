import matplotlib.pyplot as plt

'''
[Usecase]:

	def prepare_x():

	    fig = plt.figure(figsize = (10, 10))
	    ax = plt.gca()

	    return fig, ax

	with PlotContextManager(prepare_x, "x_plot") as ax:

	    x = np.linspace(0, 100, 100)
	    y = x*x
	    ax.plot(x, y, label = 'y = x^2')

'''
class PlotContextManager:

    def __init__(self, prepare_plot, plot_name):

        self.plot_name = plot_name
        self.fig, self.ax = prepare_plot()        
    
    def __enter__(self):
        
        return self.ax
    
    def __exit__(self, exc_type, exc_value, exc_tb):

        self.fig.savefig(self.plot_name)
