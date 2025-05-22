import pickle

with open("npz-files/jets-WZ.npz", "rb") as f:
    while True:
        try:
            obj = pickle.load(f)
            print("Read object:", type(obj))
        except EOFError:
            break
        except Exception as e:
            print("Failed to load an object:", e)
            break