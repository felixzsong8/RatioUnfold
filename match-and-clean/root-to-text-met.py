import numpy as np
import pandas
import uproot3 as u
import os
import subprocess


#boson = "W"
boson = "5Z"

dataset = []

# get the list of root files in the directory that have string boson (Z or W) in their name
for root, dirs, files in os.walk("./root-files/"):
    for file in files:
        if boson in file:
            dataset.append(file)


branches = ["eventNumber",
            "truthMET",
            "truthMET_phi",
            "recoMET",
            "recoMET_phi"]



print("Processing " + boson + " datasets (MET)")
out_filename = "./npz-files/met-" + boson + ".npz"

data_array = []
data_length = 0

for i in range(len(dataset)):

    in_file = "./root-files/" + dataset[i]
    
    if os.path.exists(in_file):
        print("Processing: " + dataset[i])
        
        # load root file
        data = u.open(in_file)['tree'].pandas.df(flatten=True, branches=branches).explode(branches)

        # append data to the array
        data_array.append(data)

        # check the length of the data
        data_length += len(data)
        print("number of events so far: " + str(data_length))

    else:
        print("File not found: " + in_file)
        continue

combined_data = pandas.concat(data_array, ignore_index=True)


event_num = combined_data['eventNumber']
gen_met = np.stack([combined_data[f'truthMET{x}'] for x in ['', '_phi']], axis=-1)
reco_met = np.stack([combined_data[f'recoMET{x}'] for x in ['', '_phi']], axis=-1)

# save gen_met and reco_met to .npz file
np.savez(out_filename, event_num=event_num, gen_met=gen_met, reco_met=reco_met)

# print # of entries in the .npz file
with np.load(out_filename, allow_pickle=True) as data:
    num_entries = len(data['gen_met'])
    print(f"{out_filename} has {num_entries} entries")