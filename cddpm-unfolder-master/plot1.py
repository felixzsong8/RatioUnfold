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
bosons = ["Z", "W"]  # We'll process both bosons

print("train data type: ", train_type)
print("test data type: ", unf_type)

# Initialize dictionaries to store data for both bosons
unfold_data = {}
reco_data = {}
truth_data = {}

for boson in bosons:
    # Load data for each boson
    unfold_data[boson] = np.load(f"./outputs/jets{boson}/unfold_{unf_type}{boson}.npy")[:,1:]
    reco_data[boson] = np.load(input_path + f"test_reco_{unf_type}{boson}.npy")[:,1:]
    truth_data[boson] = np.load(input_path + f"test_truth_{unf_type}{boson}.npy")[:,1:]
    
    # Match the number of events
    n_unf = unfold_data[boson].shape[0]
    reco_data[boson] = reco_data[boson][:n_unf,:]
    truth_data[boson] = truth_data[boson][:n_unf,:]
    
    # Undo normalization
    reco_data[boson] = reco_data[boson]*norm_vec
    truth_data[boson] = truth_data[boson]*norm_vec

vec = ["pT", "eta", "phi", "E"]
axis_label = [r'LeadJet $p_T$ [GeV]', r'$\eta$', r'$\phi$', r'$E$ [GeV]']

# First, create the same plots for W that exist for Z
for boson in bosons:
    for i in range(4):
        if i == 0:
            bins = np.array([20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 225, 250, 275, 300, 350, 400, 450, 500, 600, 700, 800, 1000])
        if i == 1:
            bins = np.linspace(-4.7, 4.7, 30)
        if i == 2:
            bins = np.linspace(-3.5, 3.5, 30)
        if i == 3:
            bins = np.array([0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1850, 2000, 2250, 2500, 3000, 4000])

        bin_centers = 0.5*(bins[1:] + bins[:-1])

        plt.clf()
        fig, a0 = plt.subplots()

        # plot truth, reco, and unfold
        a0.hist(truth_data[boson][:, i], bins=bins, density=dens, histtype='step', label='truth', linewidth=1.8, zorder=1)
        #a0.hist(reco_data[boson][:, i], bins=bins, density=dens, histtype='step', label='detector', linewidth=1.5, linestyle="dashed", zorder=3)

        a0.legend(loc='upper right')
        a0.set_ylabel('events')
        a0.set_yscale('log')
        a0.set_xlabel(axis_label[i])
        a0.set_title(f"{boson} + jets")
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

        fig.tight_layout()
        fig.savefig(plots_path + f"{boson}_{unf_type}_{vec[i]}.png")
        plt.clf()
        plt.close()

# Now create the ratio plots (W/Z) for both detector and truth levels
for i in range(4):
    if i == 0:
        bins = np.array([20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 225, 250, 275, 300, 350, 400, 450, 500, 600, 700, 800, 1000])
    if i == 1:
        bins = np.linspace(-4.7, 4.7, 30)
    if i == 2:
        bins = np.linspace(-3.5, 3.5, 30)
    if i == 3:
        bins = np.array([0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1850, 2000, 2250, 2500, 3000, 4000])

    # Calculate histograms for both bosons at detector and truth levels
    truth_W, _ = np.histogram(truth_data["W"][:, i], bins=bins)
    truth_Z, _ = np.histogram(truth_data["Z"][:, i], bins=bins)
    reco_W, _ = np.histogram(reco_data["W"][:, i], bins=bins)
    reco_Z, _ = np.histogram(reco_data["Z"][:, i], bins=bins)
    
    # Calculate ratios with protection against division by zero
    truth_ratio = np.divide(truth_W, truth_Z, out=np.zeros_like(truth_W, dtype=float), where=truth_Z!=0)
    reco_ratio = np.divide(reco_W, reco_Z, out=np.zeros_like(reco_W, dtype=float), where=reco_Z!=0)
    
    bin_centers = 0.5*(bins[1:] + bins[:-1])
    
    # Plot the ratio comparison
    plt.clf()
    fig, (a0, a1) = plt.subplots(2, 1, figsize=(8, 8), gridspec_kw={'height_ratios': [3, 1]})
    
    # Top plot: Detector and truth distributions
    a0.hist(bin_centers, bins=bins, weights=truth_W, density=dens, histtype='step', 
            label='W truth', linewidth=1.8, zorder=1)
    a0.hist(bin_centers, bins=bins, weights=truth_Z, density=dens, histtype='step', 
            label='Z truth', linewidth=1.8, zorder=2)
    a0.hist(bin_centers, bins=bins, weights=reco_W, density=dens, histtype='step', 
            label='W detector', linewidth=1.5, linestyle="dashed", zorder=3)
    a0.hist(bin_centers, bins=bins, weights=reco_Z, density=dens, histtype='step', 
            label='Z detector', linewidth=1.5, linestyle="dashed", zorder=4)
    
    a0.legend(loc='upper right')
    a0.set_ylabel('events')
    a0.set_yscale('log')
    a0.set_title(f'W/Z jets: {vec[i]} distribution and ratio')
    
    # Bottom plot: Ratios
    a1.plot(bin_centers, truth_ratio, 'o-', label='Truth W/Z', markersize=4)
    a1.plot(bin_centers, reco_ratio, 'o-', label='Detector W/Z', markersize=4)
    a1.axhline(1.0, color='gray', linestyle='--', alpha=0.5)
    a1.legend(loc='upper right')
    a1.set_ylabel('Ratio')
    a1.set_xlabel(axis_label[i])
    a1.set_ylim(0, 2)  # Adjust as needed
    
    if i == 0:
        a0.set_xlim(0, pT_range)
        a1.set_xlim(0, 600)
    if i == 3:
        a0.set_xlim(0, E_range)
        a1.set_xlim(0, E_range)
    
    if dens:
        a0.set_ylabel(r'$d\sigma/dx$')
        a0.set_ylim(1e-2, 9e-1)
        if i == 0 or i == 3:
            a0.set_ylim(1e-8, 5e-1)
    else:
        a0.set_ylim(0.5, 3e8)
    
    fig.tight_layout()
    fig.savefig(plots_path + f"WZ_ratio_{unf_type}_{vec[i]}.png")
    plt.clf()
    plt.close()