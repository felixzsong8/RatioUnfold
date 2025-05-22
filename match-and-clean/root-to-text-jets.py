import numpy as np
import pandas
import uproot3 as u
import os
import subprocess


#boson = "W"
boson = "WZ"

dataset = []

# get the list of root files in the directory that have string boson (Z or W) in their name
for root, dirs, files in os.walk("./root-files/"):
    for file in files:
        if boson in file:
            dataset.append(file)


branches = ["eventNumber",
            "nTruthEle",
            "nTruthMuon",
            "truthMatchJet_pT",
            "truthMatchJet_eta",
            "truthMatchJet_phi",
            "truthMatchJet_E",
            "truthMatchJet_pX",
            "truthMatchJet_pY",
            "truthMatchJet_pZ",
            "truthMatchJet_M",
            "recoMatchJet_pT",
            "recoMatchJet_eta",
            "recoMatchJet_phi",
            "recoMatchJet_E",
            "recoMatchJet_pX",
            "recoMatchJet_pY",
            "recoMatchJet_pZ",
            "recoMatchJet_M"]



print("Processing " + boson + " datasets (Jets)")
out_filename = "./npz-files/jets-" + boson + ".npz"

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
        print("number of jets so far: " + str(data_length))

    else:
        print("File not found: " + in_file)
        continue

combined_data = pandas.concat(data_array, ignore_index=True)


event_num = combined_data['eventNumber']
lepton_count = combined_data['nTruthEle'] + combined_data['nTruthMuon']
gen_jets = np.stack([combined_data[f'truthMatchJet_{x}'] for x in ['pT', 'eta', 'phi', 'E', 'pX', 'pY', 'pZ', 'M']], axis=-1)
reco_jets = np.stack([combined_data[f'recoMatchJet_{x}'] for x in ['pT', 'eta', 'phi', 'E', 'pX', 'pY', 'pZ', 'M']], axis=-1)

# save gen_jets and reco_jets to .npz file
np.savez(out_filename, event_num=event_num, lepton_count=lepton_count, gen_jets=gen_jets, reco_jets=reco_jets)

# print # of entries in the .npz file
with np.load(out_filename, allow_pickle=True) as data:
    num_entries = len(data['gen_jets'])
    print(f"{out_filename} has {num_entries} entries")