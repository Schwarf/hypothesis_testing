import matplotlib.pyplot as plt
import numpy
import scipy.stats as stats

import constants


def compute_mean_and_std(data: numpy.array, axis: int, result_index: int) -> numpy.array:
    mean = numpy.mean(data, axis=axis)[result_index]
    standard_deviation = numpy.std(data, axis=axis, ddof=1)[result_index]
    standard_error = standard_deviation / numpy.sqrt(data.shape[axis])
    return numpy.array([mean, standard_deviation, standard_error])


def read_data() -> numpy.array:
    data = numpy.genfromtxt(constants.path_to_data, delimiter=',', skip_header=1)
    return data


def sampling_points_normal_distribution(mean: float, standard_deviation: float):
    x = numpy.linspace(260. - 4*31, 260 + 4*31, 1000)
    plt.plot(x, stats.t.pdf(x, 24, loc=260, scale=31/numpy.sqrt(24)))
    plt.show()
