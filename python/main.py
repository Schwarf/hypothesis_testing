import descriptive_statistics
import fuel_costs.descriptive_statistics




# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    data =descriptive_statistics.read_data()
    mean, standard_deviation, standard_error = descriptive_statistics.compute_mean_and_std(data, axis=0, result_index=1)
    print(mean, ", ",standard_deviation, ", ", standard_error)
    descriptive_statistics.sampling_points_normal_distribution(mean, standard_deviation)
# See PyCharm help at https://www.jetbrains.com/help/pycharm/
