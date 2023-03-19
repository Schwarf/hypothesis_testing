import descriptive_statistics
import fuel_costs.descriptive_statistics




# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    data =descriptive_statistics.read_data()
    print(descriptive_statistics.compute_mean_and_std(data, axis=0, result_index=1))

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
