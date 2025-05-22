import os
import tqdm
import torch
import numpy as np
import torch.optim as optim
import matplotlib.pyplot as plt
from torch.optim.lr_scheduler import LinearLR
from model import Model
import configs

configs.set_seed(configs.seed)

if not os.path.exists(configs.plots_path):
   os.makedirs(configs.plots_path)
if not os.path.exists(configs.ckpt_path):
   os.makedirs(configs.ckpt_path)

print(configs.state_name)

# load training data
# x is truth, y is reco (detector)

# if loading a preprocessed dataset
if configs.load_preprocessed_training_data:
    x = np.load(configs.input_path + "train_truth_" + configs.train_type + ".npy", mmap_mode='r')
    y = np.load(configs.input_path + "train_reco_" + configs.train_type + ".npy", mmap_mode='r')


# use only 90% of data for training
x_train = x[:int(0.90*x.shape[0]),:]
y_train = y[:int(0.90*y.shape[0]),:]

# use other 10% of data for validation
x_val = x[int(0.90*x.shape[0]):,:]
y_val = y[int(0.90*y.shape[0]):,:]


# initiate model and optimizer
cDDPM = torch.compile(Model(configs.device, configs.beta_1, configs.beta_T, configs.T, configs.shape_in[0], configs.shape_out[0]))
optim = torch.optim.Adam(cDDPM.parameters(), lr = configs.lr)

# keep track of loss (for plotting)
train_loss_list = []
val_loss_list = []
epoch_list = []
step_list = []
# number of batches 
batch_size = configs.batch_size
batches = int(x_train.shape[0]/batch_size)
batches_val = int(x_val.shape[0]/batch_size)

scheduler = LinearLR(optim, 1, 1e-2, total_iters=configs.epochs*batches)


cum_train_loss = 0
cum_val_loss = 0
train_step = 0


# make a list of batches in device so we don't have to load each time

all_batches = []
for batch in range(batches):
    x_batch = torch.tensor(x_train[batch*batch_size:(batch+1)*batch_size], dtype=torch.float32, device=configs.device)
    y_batch = torch.tensor(y_train[batch*batch_size:(batch+1)*batch_size], dtype=torch.float32, device=configs.device)
    all_batches.append((x_batch, y_batch))

val_batches = []
for batch in range(batches_val):
    x_batch_val = torch.tensor(x_val[batch*batch_size:(batch+1)*batch_size], dtype=torch.float32, device=configs.device)
    y_batch_val = torch.tensor(y_val[batch*batch_size:(batch+1)*batch_size], dtype=torch.float32, device=configs.device)
    val_batches.append((x_batch_val, y_batch_val))


pbar = tqdm.tqdm(total=configs.epochs)

# start training loop
for iteration in range(1, configs.epochs+1):
    cum_train_loss = 0

    # define training batches
    for batch in range(batches):
        train_step += 1

        ## train the model
        x_batch, y_batch = all_batches[batch] 

        optim.zero_grad()
        loss = cDDPM.loss_fn(x_batch,y_batch)
        loss.backward()
        optim.step()
        scheduler.step()


        # add to cumulative loss
        cum_train_loss = cum_train_loss + loss.item()


    if iteration == 5 or iteration % configs.save_int == 0:
        # save model state checkpoint
        torch.save(cDDPM.state_dict(), configs.ckpt_path + 'gen_' + configs.train_type + '_b' + str(batch_size) + '_it' + str(iteration) + '.pth')

        cum_val_loss = 0
        cum_test_loss = 0
        for batch in range(batches_val):

            x_batch_val, y_batch_val = val_batches[batch]

            with torch.no_grad(): 
                loss_val = cDDPM.loss_fn(x_batch_val, y_batch_val)

            # add to cumulative loss
            cum_val_loss = cum_val_loss + loss_val.item()
            

    train_loss = cum_train_loss/batches
    val_loss = cum_val_loss/batches_val

    # save loss values and reset cumulative loss count every print_int iterations
    if iteration % configs.save_int == 0:
        epoch_list.append(iteration)
        step_list.append(train_step)
        train_loss_list.append((train_loss))
        val_loss_list.append((val_loss))

    pbar.update()
    pbar.set_description(f"train loss: {train_loss:.6f}, val loss: {val_loss:.6f}")

# plot loss
plt.clf()
plt.plot(epoch_list, train_loss_list)
plt.plot(epoch_list, val_loss_list)
plt.legend(["train loss", "validation loss"])
plt.xlabel(r'epoch')
plt.ylabel(r'loss')
plt.savefig(configs.plots_path + "loss_" + configs.train_type + "_it" +str(configs.epochs) + ".png")