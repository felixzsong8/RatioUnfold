
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import wasserstein_distance
from scipy.stats import energy_distance
from configs import *
import os
import configs


if not os.path.exists(plots_path):
   os.makedirs(plots_path)


dens = False
boson = ["W","Z"]


print("train data type: ", train_type + str(boson[0]))
print("test data type: ", unf_type + str(boson[0]))

## import data from output files
unfold = np.load("./outputs/jets" + boson[0] + "/unfold_" + unf_type + boson[0] + ".npy")[:,1:]
reco = np.load(input_path + "test_reco_" + unf_type + boson[0] + ".npy")[:,1:]
truth = np.load(input_path + "test_truth_" + unf_type + boson[0] + ".npy")[:,1:]

print("train data type: ", train_type + str(boson[1]))
print("test data type: ", unf_type + str(boson[1]))

unfoldZ = np.load("./outputs/jets" + boson[1] + "/unfold_" + unf_type + boson[1] + ".npy")[:,1:]
recoZ = np.load(input_path + "test_reco_" + unf_type + boson[1] + ".npy")[:,1:]
truthZ = np.load(input_path + "test_truth_" + unf_type + boson[1] + ".npy")[:,1:]

n_unf = unfold.shape[0]
print(n_unf)

n_unfZ = unfoldZ.shape[0]
print(n_unfZ)

# if not unfolding full data distribution
reco = reco[:n_unf,:]
truth = truth[:n_unf,:]

recoZ = recoZ[:n_unfZ,:]
truthZ = truthZ[:n_unfZ,:]


## undo normalization
reco = reco*norm_vec
truth = truth*norm_vec

recoZ = recoZ*norm_vec
truthZ = truthZ*norm_vec


x_text_1 = 0.15
x_text_2 = 0.45
y_text_1 = 0.90

def kl_divergence(p, q):
    return np.sum(p * np.log(p / q))


## make plots!!!

vec = ["pT", "eta", "phi", "E"]
axis_label = [r'$p_T$ [GeV]', r'$\eta$', r'$\phi$', r'$E$ [GeV]']
for i in range(4):
    if i == 0:
        bins = np.array([0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 225, 250, 275, 300, 350, 400, 450, 500, 600, 700, 800, 1000])
        # bins = np.linspace(plot_pT_min, plot_pT_max, n_bins)
    if i == 1:
        bins = np.linspace(-4.7, 4.7, 30)
    if i == 2:
        bins = np.linspace(-3.5, 3.5, 30)
    if i == 3:
        bins = np.array([0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1850, 2000, 2250, 2500, 3000, 4000])
        # bins = np.linspace(plot_E_min, plot_E_max, n_bins)

    bin_centers = 0.5*(bins[1:] + bins[:-1])

    #For W
    # calculate RMS between truth and unfolded
    rms_unfold = np.sqrt(np.mean((truth[:,i]-unfold[:,i])**2))
    # calculate the Wasserstein distance between truth and unfolded
    wass_unfold = wasserstein_distance(truth[:,i], unfold[:,i])
    # calculate the energy distance between truth and unfolded
    energy_unfold = energy_distance(truth[:,i], unfold[:,i])

    #For Z
    # calculate RMS between truth and unfolded
    rms_unfoldZ = np.sqrt(np.mean((truthZ[:,i]-unfoldZ[:,i])**2))
    # calculate the Wasserstein distance between truth and unfolded
    wass_unfoldZ = wasserstein_distance(truthZ[:,i], unfoldZ[:,i])
    # calculate the energy distance between truth and unfolded
    energy_unfoldZ = energy_distance(truthZ[:,i], unfoldZ[:,i])


    plt.clf()

    f, (a0, a1) = plt.subplots(2, 1, gridspec_kw={'height_ratios': [3, 1]})
    f1, (a2, a3) = plt.subplots(2, 1, gridspec_kw={'height_ratios': [3, 1]})

    
    # plot truth, reco, and unfold for W
    t = a0.hist(truth[:,i], bins=bins, density=dens, histtype='step', label='truth',linewidth=1.8, zorder=1)
    p = a0.hist(unfold[:,i], bins=bins, density=dens, histtype='step', label='unfold', linewidth=1.5, zorder=2)
    r = a0.hist(reco[:,i], bins=bins, density=dens, histtype='step', label='detector', linewidth=1.5, linestyle="dashed", zorder=3)

    # plot truth, reco, and unfold
    tZ = a2.hist(truthZ[:,i], bins=bins, density=dens, histtype='step', label='truth',linewidth=1.8, zorder=1)
    pZ = a2.hist(unfoldZ[:,i], bins=bins, density=dens, histtype='step', label='unfold', linewidth=1.5, zorder=2)
    rZ = a2.hist(recoZ[:,i], bins=bins, density=dens, histtype='step', label='detector', linewidth=1.5, linestyle="dashed", zorder=3)


    a0.legend(loc='upper right')
    a0.set_xticklabels([])
    a0.set_ylabel(r'events')
    a0.set_yscale('log')
    if i == 0:
        a0.set_xlim(0, pT_range)
    if i == 3:
        a0.set_xlim(0, E_range)
    if dens:
        a0.set_ylabel(r'$d\sigma/dx$')
        a0.set_ylim(1e-2, 9e-1)
        if i == 0 or i == 3:
            a0.set_ylim(1e-8, 5e-1)
    else:
        a0.set_ylim(0.5, 3e8)


    a2.legend(loc='upper right')
    a2.set_xticklabels([])
    a2.set_ylabel(r'events')
    a2.set_yscale('log')
    if i == 0:
        a2.set_xlim(0, pT_range)
    if i == 3:
        a2.set_xlim(0, E_range)
    if dens:
        a2.set_ylabel(r'$d\sigma/dx$')
        a2.set_ylim(1e-2, 9e-1)
        if i == 0 or i == 3:
            a2.set_ylim(1e-8, 5e-1)
    else:
        a2.set_ylim(0.5, 3e8)



    # take content of bins of hists t and p and divide them for W
    ratio_unfold = []
    for j in range(len(t[0])):
        if t[0][j] != 0:
            ratio_unfold.append(p[0][j]/t[0][j])
        else:
            ratio_unfold.append(0)
    ratio_reco = []
    for j in range(len(t[0])):
        if t[0][j] != 0:
            ratio_reco.append(r[0][j]/t[0][j])
        else:
            ratio_reco.append(0)

    # take content of bins of hists t and p and divide them for Z
    ratio_unfoldZ = []
    for j in range(len(tZ[0])):
        if tZ[0][j] != 0:
            ratio_unfoldZ.append(pZ[0][j]/tZ[0][j])
        else:
            ratio_unfoldZ.append(0)
    ratio_recoZ = []
    for j in range(len(tZ[0])):
        if tZ[0][j] != 0:
            ratio_recoZ.append(rZ[0][j]/tZ[0][j])
        else:
            ratio_recoZ.append(0)
    
    ## make array with middle value of each bin
    ones = []
    for j in range(len(bins)-1):
        ones.append((bins[j]+bins[j+1])/2)

    a1.hist(ones, bins=bins, weights=None, histtype="step", label='',linewidth=1.0, alpha=0.8)
    a1.hist(ones, bins=bins, weights=ratio_unfold, histtype="step", label='unfold/truth',linewidth=1.5)
    a1.hist(ones, bins=bins, weights=ratio_reco, histtype="step", label='detector/truth',linewidth=1.5, linestyle="dashed")

    # Major ticks every 20, minor ticks every 5
    major_ticks = np.arange(0.6, 1.45, 0.2)
    minor_ticks = np.arange(0.6,1.45, 0.1)

    a1.set_yticks(major_ticks)
    a1.set_yticks(minor_ticks, minor=True)

    # Or if you want different settings for the grids:
    a1.grid(which='minor', alpha=0.6)
    a1.grid(which='major', alpha=0.9)

    a1.legend(loc='upper right')
    a1.set_ylim(0.6, 1.45)
    a1.set_ylabel(r'ratios')
    a1.set_xlabel(axis_label[i])
    a1.grid(True)
    if i == 0:
        a1.set_xlim(0, pT_range)
    if i == 3:
        a1.set_xlim(0, E_range)

    f.tight_layout()
    f.subplots_adjust(wspace=0, hspace=0.05)
    f.savefig(plots_path + unf_type + boson[0] + "_" + vec[i] + ".png")
    # plt.show()

   ## plt.clf()
   # plt.close()



    ## make array with middle value of each bin for Z
    onesZ = []
    for j in range(len(bins)-1):
        onesZ.append((bins[j]+bins[j+1])/2)

    a3.hist(onesZ, bins=bins, weights=None, histtype="step", label='',linewidth=1.0, alpha=0.8)
    a3.hist(onesZ, bins=bins, weights=ratio_unfoldZ, histtype="step", label='unfold/truthZ',linewidth=1.5)
    a3.hist(onesZ, bins=bins, weights=ratio_recoZ, histtype="step", label='detector/truthZ',linewidth=1.5, linestyle="dashed")

    # Major ticks every 20, minor ticks every 5
    major_ticks = np.arange(0.6, 1.45, 0.2)
    minor_ticks = np.arange(0.6,1.45, 0.1)

    a3.set_yticks(major_ticks)
    a3.set_yticks(minor_ticks, minor=True)

    # Or if you want different settings for the grids:
    a3.grid(which='minor', alpha=0.6)
    a3.grid(which='major', alpha=0.9)

    a3.legend(loc='upper right')
    a3.set_ylim(0.6, 1.45)
    a3.set_ylabel(r'ratios')
    a3.set_xlabel(axis_label[i])
    a3.grid(True)
    if i == 0:
        a3.set_xlim(0, pT_range)
    if i == 3:
        a3.set_xlim(0, E_range)

    f1.tight_layout()
    f1.subplots_adjust(wspace=0, hspace=0.05)
    f1.savefig(plots_path + unf_type + boson[1] + "_" + vec[i] + ".png")
    # plt.show()

    plt.clf()
    plt.close()

     # ---- NEW PLOT FOR TRUTH W/Z AND UNFOLDED W/Z ----
     # ---- NEW PLOT FOR TRUTH W/Z AND UNFOLDED W/Z ----
    f2, (a4, a5) = plt.subplots(2, 1, gridspec_kw={'height_ratios': [3, 1]})

    # Plot truth W/Z and unfolded W/Z
    tW_all = a4.hist(truth[:,i], bins=bins, density=dens, histtype='step', label='Truth W', linewidth=1.8, color='blue', zorder=1)
    pW_all = a4.hist(unfold[:,i], bins=bins, density=dens, histtype='step', label='Unfolded W', linewidth=1.5, linestyle="dashed", color='blue', zorder=2)

    tZ_all = a4.hist(truthZ[:,i], bins=bins, density=dens, histtype='step', label='Truth Z', linewidth=1.8, color='red', zorder=1)
    pZ_all = a4.hist(unfoldZ[:,i], bins=bins, density=dens, histtype='step', label='Unfolded Z', linewidth=1.5, linestyle="dashed", color='red', zorder=2)

    ratio_unfold_all = [pW_all[0][j]/pZ_all[0][j] if pZ_all[0][j] != 0 else 0 for j in range(len(pZ_all[0]))]
    ratio_truth_all = [tW_all[0][j]/tZ_all[0][j] if tZ_all[0][j] != 0 else 0 for j in range(len(tZ_all[0]))]

    plt.clf()
    plt.close()
    f2, (a4, a5) = plt.subplots(2, 1, gridspec_kw={'height_ratios': [3, 1]})

    a4.hist(ones, bins=bins, weights=ratio_unfold_all, histtype="step", label='Unfolded W / Unfolded Z', linewidth=1.5, color='blue')
    a4.hist(onesZ, bins=bins, weights=ratio_truth_all, histtype="step", label='Truth W / Truth Z', linewidth=1.5, linestyle="dashed", color='red')

    # Formatting a4
    a4.legend(loc='upper right')
    a4.set_xticklabels([])
    a4.set_ylabel('Events')

    if dens:
        a4.set_ylabel(r'$d\sigma/dx$')
    else:
        a4.set_ylim(0, 3)

    # Plot the ratios
    ratio_division = [ratio_unfold_all[j] / ratio_truth_all[j] if ratio_truth_all[j] != 0 else 0 for j in range(len(ratio_truth_all))]
    a5.hist(ones, bins=bins, weights=ratio_division, histtype="step", label='Unfolded W / Unfolded Z', linewidth=1.5, color='blue')
    
    # Formatting a5
    a5.set_ylabel("Ratios")
    a5.set_xlabel(axis_label[i])
    a5.legend(loc='upper right')

    a5.set_ylim(0.6, 1.45)
    major_ticks = np.arange(0.6, 1.45, 0.2)
    minor_ticks = np.arange(0.6,1.45, 0.1)
    a5.set_yticks(major_ticks)
    a5.set_yticks(minor_ticks, minor=True)
    a5.grid(which='minor', alpha=0.6)
    a5.grid(which='major', alpha=0.9)

    # Save the new plot
    f2.tight_layout()
    f2.subplots_adjust(wspace=0, hspace=0.05)
    f2.savefig(plots_path + unf_type + "_truth_vs_unfolded_" + vec[i] + ".png")

    plt.close()
