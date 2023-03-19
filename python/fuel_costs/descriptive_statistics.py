import numpy
import constants



def compute_mean_and_std(data: numpy.array, axis: int, result_index: int) -> numpy.array:
    mean = numpy.mean(data, axis=axis)[result_index]
    standard_deviation = numpy.std(data, axis=axis, ddof=1)[result_index]
    return numpy.array([mean, standard_deviation])


def read_data() -> numpy.array:
    data = numpy.genfromtxt(constants.path_to_data, delimiter=',', skip_header=1)
    return data




