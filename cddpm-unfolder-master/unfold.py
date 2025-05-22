import torch
import tqdm
import os
import numpy as np
from model import Model
from diffusion import DiffusionProcess
import configs


configs.set_seed(configs.seed)

if not os.path.exists(configs.output_path):
   os.makedirs(configs.output_path)

print("training data: ", configs.train_type)
print("test data: ", configs.unf_type)

print("loading data...")
if configs.load_preprocessed_training_data:
    reco = np.load(configs.input_path + "test_reco_" + configs.unf_type + "_part.npy", mmap_mode='r')[:,1:]
    event_number = np.load(configs.input_path + "test_reco_" + configs.unf_type + "_part.npy", mmap_mode='r')[:,0]

reco = torch.from_numpy(np.array(reco, copy=True)).float().to(configs.device)
event_number = np.array(event_number, copy=True)

# cleanup for loading saved state from compiled model
state_dict = torch.load(configs.ckpt_path + 'gen_' + configs.state_name + '.pth', weights_only=True)
unwanted_prefix = '_orig_mod.'
for k,v in list(state_dict.items()):
    if k.startswith(unwanted_prefix):
        state_dict[k[len(unwanted_prefix):]] = state_dict.pop(k)

# initiate models and load saved state
cDDPM = Model(configs.device, configs.beta_1, configs.beta_T, configs.T, configs.shape_in[0], configs.shape_out[0])
cDDPM.load_state_dict(state_dict)
process = DiffusionProcess(configs.beta_1, configs.beta_T, configs.T, cDDPM, configs.device, configs.shape_out,)

print("unfolding...")

unfolded = []
n = reco.shape[0]//configs.sample_size
pbar = tqdm.tqdm(total=n)

with torch.no_grad():
    for i in range(n):
        unfolded_part = process.sampling(configs.sample_size, reco[i*configs.sample_size:(i+1)*configs.sample_size])
        unfolded.append(unfolded_part)
        pbar.update()

unfolded = torch.cat(unfolded)
unfolded = unfolded.cpu().numpy()
unfolded = unfolded[:,:7]
pbar=0

## undo normalization
unfolded = unfolded*configs.norm_vec
## append event number
event_number = event_number[:unfolded.shape[0]]
unfolded = np.append(event_number[:,np.newaxis], unfolded, axis=1)
## save unfolded results
np.save(configs.output_path + "unfold_" + configs.unf_type + ".npy", unfolded)

print("done!")

