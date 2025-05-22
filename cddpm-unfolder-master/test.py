import numpy as np
import pandas
import uproot3 as u
import os
import subprocess


# datasets for upload

# for Delphes

proc_name = "dataW"

# for ATLAS AnaFram
# type = "fromAnaFram/"
# proc = ["dijets_noBias", "dijets_noBias_NNPDF23lo0130", "graviton_noBias", "lepqua_noBias", "lepqua_noBias_NNPDF23lo0130", "lepqua_withBias", "ttbar_noBias", "ttbar_noBias_NNPDF23lo0130",  "ttbar_noBias_vincia", "ttbar_withBias", "wjets_noBias", "wjets_noBias_NNPDF23lo0130", "wjets_withBias", "wToJets_ISR_FSR", "wToJets_noBias", "wToJets_noBias_NNPDF23lo0130", "zjets_noBias", "zjets_noBias_NNPDF23lo0130", "zjets_withBias"] 
# proc_name = ["dijets_CT14lo", "dijets_NNPDF23lo0130", "graviton_CT14lo", "lepqua_CT14lo", "lepqua_NNPDF23lo0130", "lepqua_CT14lo_bias", "ttbar_CT14lo", "ttbar_NNPDF23lo0130", "ttbar_CT14lo_vincia", "ttbar_CT14lo_bias", "wjets_CT14lo", "wjets_NNPDF23lo0130", "wjets_CT14lo_bias", "wToJets_CT14lo_ISRFSR", "wToJets_CT14lo", "wToJets_NNPDF23lo0130", "zjets_CT14lo", "zjets_NNPDF23lo0130", "zjets_CT14lo_bias"]

n = 20 # max number of files

# data_dir = "../../atlas-datasets"
data_dir = "/Users/felixsong/Desktop/coding-tufts/SeniorThesis/pythia-outputs"


branches = ["eventNumber",
            "truMatchJet_pT_tree",
            "truMatchJet_eta_tree",
            "truMatchJet_phi_tree",
            "truMatchJet_E_tree",
            "truMatchJet_pX_tree",
            "truMatchJet_pY_tree",
            "truMatchJet_pZ_tree",
            "truMatchJet_M_tree",
            "recMatchJet_pT_tree",
            "recMatchJet_eta_tree",
            "recMatchJet_phi_tree",
            "recMatchJet_E_tree",
            "recMatchJet_pX_tree",
            "recMatchJet_pY_tree",
            "recMatchJet_pZ_tree",
            "recMatchJet_M_tree"]


for j in range(len(proc)):
    print(proc_name + " -> " + proc_name[j])
    out_filename = data_dir + proc_name + ".npz"

    data_array = []

    data_length = 0

    for i in range(1, n+1):
        
        name = proc_name + "-" + str(i)
        in_file = "./" + name + ".root"
        
        if os.path.exists(in_file):
            print("Processing: " + name)
            # load root file
            data = u.open(in_file)['ParticleTree'].pandas.df(flatten=True, branches=branches).explode(branches)

            # append data to the array
            data_array.append(data)

            # check the length of the data
            data_length += len(data)
            print("number of jets so far: " + str(data_length))

        else:
            continue

    combined_data = pandas.concat(data_array, ignore_index=True)


    event_num = combined_data['eventNumber']
    gen_jets = np.stack([combined_data[f'truMatchJet_{x}_tree'] for x in ['pT', 'eta', 'phi', 'E', 'pX', 'pY', 'pZ', 'M']], axis=-1)
    reco_jets = np.stack([combined_data[f'recMatchJet_{x}_tree'] for x in ['pT', 'eta', 'phi', 'E', 'pX', 'pY', 'pZ', 'M']], axis=-1)

    # save gen_jets and reco_jets to .npz file
    np.savez(out_filename, event_num=event_num, gen_jets=gen_jets, reco_jets=reco_jets)

    # print # of entries in the .npz file
    with np.load(out_filename, allow_pickle=True) as data:
        num_entries = len(data['gen_jets'])
        print(f"{out_filename} has {num_entries} entries")