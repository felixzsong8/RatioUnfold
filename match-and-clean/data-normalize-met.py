import numpy as np
from configs import *

#set_seed(seed)


distribution = ["train", "test"]

# test
boson = "Z"
type = ["met"]


# if making part or step dataset, define part_size
part_size = 500000


input_path = "npz-files/"
output_path = "datasets-for-NN/"
    
## ranges for normalization
E_range = 7 
M_range = 1000 #This was 100
norm_vec = np.array([M_range, E_range])


## load data distribution and make cuts!
#This is 1,000,000 events after cuts

for k in range(len(distribution)):

    for i in range(len(type)):    
        print("dataset:", type[i] + "-" + boson + "-" + distribution[k])


        # open pythia dataset
        data_full = np.load(input_path + type[i] + "-" + boson + ".npz")

        #jets are a 615006 * 8 array where 615006 is number of events and 8 is characteristics of each jet
        # get event number, truth, and reco
        event_num = data_full['event_num']
        truth = data_full['gen_met']
        reco = data_full['reco_met']

        data = np.append(truth, reco, axis=1)
        data = np.append(event_num[:,np.newaxis], data, axis=1)

        # get rid of events with reco mass > M_range and < M_min
        # data = data[data[:,16] < M_range]
        # data = data[data[:,16] > M_min]


        # take only part_size[i] events
        if distribution[k] == "train":
            data = data[:part_size,:]
        elif distribution[k] == "test" and data.shape[0] >= part_size*2:
            data = data[-part_size:,:]
        else:
            continue

        np.random.shuffle(data)
        # first column is event_num, next 8 columns are truth, last 8 are reco
        event_num = data[:,0]
        truth = data[:,1:3]
        reco = data[:,3:5]


        ## normalize data
        truth = truth/norm_vec
        reco = reco/norm_vec
        
        #Check that everything is normalized correctly
        high_t = [0] * truth.shape[1]
        for a in range(len(truth)):
            for b in range(len(truth[0])):
                if(truth[a][b] >= 1 or truth[a][b] <= -1):
                    print("Problem here: " + str(a) + " " + str(b) + ": with value: " + str(truth[a][b]))
                if(truth[a][b] >= high_t[b]):
                    high_t[b] = truth[a][b]
        print("The highest truth value [0]: " + str(high_t[0]))
        print("The highest truth value [1]: " + str(high_t[1]))
        high_r = [0] * reco.shape[1]
        for a in range(len(reco)):
            for b in range(len(reco[0])):
                if(reco[a][b] >= 1 or reco[a][b] <= -1):
                    print("Problem here: " + str(a) + " " + str(b) + ": with value: " + str(reco[a][b]))
                if(reco[a][b] >= high_r[b]):
                    high_r[b] = reco[a][b]
        print("The highest reco value [0]: " + str(high_r[0]))
        print("The highest reco value [1]: " + str(high_r[1]))
        

        truth = np.append(event_num[:,np.newaxis], truth, axis=1)
        reco = np.append(event_num[:,np.newaxis], reco, axis=1)


        np.save(output_path + distribution[k]+ "_truth_" + type[i] + boson +  ".npy", truth)
        np.save(output_path + distribution[k]+ "_reco_" + type[i] + boson + ".npy", reco)