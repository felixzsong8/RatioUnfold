import numpy as np
from configs import *

#set_seed(seed)


distribution = ["train", "test"]

# test
boson = "WZ"
type = ["jets"]


# if making part or step dataset, define part_size
part_size = 6000000


input_path = "npz-files/"
output_path = "dataset-for-NN/"
    
## ranges for normalization
eta_range = 4.7 #This was 4.4
phi_range = 3.5
pT_range = 1250
E_range = 5000 
M_range = 130 #This was 100
norm_vec = np.array([pT_range, eta_range, phi_range, E_range, pT_range, pT_range, E_range, M_range])

# cut on minimum jet mass
M_min = 2


## load data distribution and make cuts!

for k in range(len(distribution)):
    for i in range(len(type)):    
        print("dataset:", type[i] + "-" + boson + "-" + distribution[k])


        # open pythia dataset
        data_full = np.load(input_path + type[i] + "-" + boson + ".npz", allow_pickle=True)
        print(data_full.files)
        print(data_full["gen_jets"])
        #jets are a 615006 * 8 array where 615006 is number of events and 8 is characteristics of each jet
        # get event number, truth, and reco
        event_num = data_full['event_num']
        truth = data_full['gen_jets']
        reco = data_full['reco_jets']

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
        truth = data[:,1:9]
        reco = data[:,9:17]


        ## normalize data
        truth = truth/norm_vec
        reco = reco/norm_vec

        #Check that everything is normalized correctly

        high_t = [0] * truth.shape[1]
        for a in range(len(truth)):
            for b in range(len(truth[0])):
                #if(truth[a][b] >= 1 or truth[a][b] <= -1):
                    #print("Problem here: " + str(a) + " " + str(b) + ": with value: " + str(truth[a][b]))
                if(truth[a][b] >= high_t[b]):
                    high_t[b] = truth[a][b]
        for c in range(len(high_t)):
            print("The highest truth value [" + str(c) + "]:" + str(high_t[c]))
        high_r = [0] * reco.shape[1]
        for a in range(len(reco)):
            for b in range(len(reco[0])):
                #if(reco[a][b] >= 1 or reco[a][b] <= -1):
                    #print("Problem here: " + str(a) + " " + str(b) + ": with value: " + str(reco[a][b]))
                if(reco[a][b] >= high_r[b]):
                    high_r[b] = reco[a][b]
        for c in range(len(high_r)):
            print("The highest reco value [" + str(c) + "]:" + str(high_r[c]))


        truth = np.append(event_num[:,np.newaxis], truth, axis=1)
        reco = np.append(event_num[:,np.newaxis], reco, axis=1)


        np.save(output_path + distribution[k]+ "_truth_" + type[i] + boson +  ".npy", truth)
        np.save(output_path + distribution[k]+ "_reco_" + type[i] + boson + ".npy", reco)