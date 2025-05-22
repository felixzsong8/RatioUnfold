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
            "truthMatchMuon_pT",
            "truthMatchMuon_eta",
            "truthMatchMuon_phi",
            "truthMatchMuon_E",
            "truthMatchMuon_pX",
            "truthMatchMuon_pY",
            "truthMatchMuon_pZ",
            "truthMatchMuon_M",
            "recoMatchMuon_pT",
            "recoMatchMuon_eta",
            "recoMatchMuon_phi",
            "recoMatchMuon_E",
            "recoMatchMuon_pX",
            "recoMatchMuon_pY",
            "recoMatchMuon_pZ",
            "recoMatchMuon_M"]



print("Processing " + boson + " datasets (Muons)")
out_filename = "./npz-files/muons-" + boson + ".npz"

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
        print("number of muons so far: " + str(data_length))

    else:
        print("File not found: " + in_file)
        continue

combined_data = pandas.concat(data_array, ignore_index=True)


event_num = combined_data['eventNumber']
gen_muons = np.stack([combined_data[f'truthMatchMuon_{x}'] for x in ['pT', 'eta', 'phi', 'E', 'pX', 'pY', 'pZ', 'M']], axis=-1)
reco_muons = np.stack([combined_data[f'recoMatchMuon_{x}'] for x in ['pT', 'eta', 'phi', 'E', 'pX', 'pY', 'pZ', 'M']], axis=-1)

# save gen_muons and reco_muons to .npz file
np.savez(out_filename, event_num=event_num, gen_muons=gen_muons, reco_muons=reco_muons)

# print # of entries in the .npz file
with np.load(out_filename, allow_pickle=True) as data:
    num_entries = len(data['gen_muons'])
    print(f"{out_filename} has {num_entries} entries")