import torch
import numpy as np

seed = 42

random_seed = False
if random_seed:
    seed = np.random.randint(1000)

def set_seed(seed):
    torch.manual_seed(seed)
    np.random.seed(seed)


load_preprocessed_training_data = True
input_path = "../match-and-clean/dataset-for-NN/"

## -------------------------------- ##
#When using plot2, need to have just gets, not boson included
boson = ""
## training dataset
train_type = "jets"
#train_type = "jets" + boson


## -------------------------------- ##

## test datasets
#unf_type = "jets" + boson
unf_type = "jets"


## -------------------------------- ##

# num of epochs
epochs = 1000
# batch size
batch_size = 2048
# how many jets to unfold
unfold_size = 5000000
# sample size during inference
sample_size = unfold_size//100


# compute validation loss, print loss, and save chekpoint every save_int epochs
save_int = 50
save_ckpts = True
state_name = train_type + '_b' + str(batch_size) + '_it' + str(epochs)


output_path = "./outputs/" + train_type + "/"
plots_path = "./plots/" + train_type + "/"
ckpt_path = 'model-state/' + train_type + '_b' + str(batch_size) + '_it5000' + "/" 


## Hyperparameter of diffusion model and perturbation process
lr = 3e-4
beta_1 = 1e-4 # 1e-4
beta_T = 0.02 # 0.02
T = 500 # 100

n_dims = 8
shape_in = ((n_dims)*2,)
shape_out = (n_dims,)
device = torch.device('cuda:0')


## ranges for normalization
eta_range = 4.7
phi_range = 3.5
pT_range = 1000
E_range = 5000
M_range = 110
norm_vec = np.array([pT_range, eta_range, phi_range, E_range, pT_range, pT_range, E_range, M_range])
